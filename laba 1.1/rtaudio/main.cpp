#include <iostream>
#include <cstring>
#include <cstdio>
#include <sndfile.hh>
#include "RtAudio.h"

SndfileHandle sndFile;
typedef signed short RTAUDIO_TYPE;

float gain = 1;
float step = 0.1;

void create_file(const char *fname, const int format, const int channels, const int srate)
{
  SndfileHandle file;
  printf("Creating file named '%s'\n", fname);
  sndFile = SndfileHandle(fname, SFM_WRITE, format, channels, srate);
}

RTAUDIO_TYPE *amplifierSond(int nBufferFrames, RTAUDIO_TYPE *bufferBytes)
{
  RTAUDIO_TYPE *buffer = bufferBytes;

  for (int i = 0; i <= nBufferFrames * sndFile.channels(); i++)
  {
    buffer[i] *= gain;
  }

  return buffer;
}

int inout(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *data)
{
  RTAUDIO_TYPE *inBuffer = (RTAUDIO_TYPE *)inputBuffer;
  unsigned int *bytes = (unsigned int *)data;
  memcpy(outputBuffer, amplifierSond((int)nBufferFrames, inBuffer), *bytes);
  memset(inputBuffer, 0, sizeof(inBuffer));

  sndFile.write(amplifierSond((int)nBufferFrames, inBuffer), nBufferFrames * sndFile.channels());
  return 0;
}

int main(int argc, char *argv[])
{
  int channels = 2, srate = 48000, iOffset = 0, oOffset = 0;

  RtAudio dac;
  if (dac.getDeviceCount() < 1)
  {
    std::cout << "No audio devices found!" << std::endl;
    exit(1);
  }
  if (argc > 1)
    channels = (int)atoi(argv[1]);

  const char *fname = "input.wav";

  create_file(fname, SF_FORMAT_WAV | SF_FORMAT_PCM_16, channels, srate);

  std::cout << "File format: " << sndFile.format() << std::endl;
  std::cout << "Channels: " << sndFile.channels() << std::endl;
  std::cout << "Samplerate " << sndFile.samplerate() << std::endl;

  if (dac.getDeviceCount() < 1)
  {
    std::cout << "\nNo audio devices found!\n";
    return 0;
  }

  RtAudio::StreamParameters inParam, outParam;
  inParam.deviceId = dac.getDefaultInputDevice();
  outParam.deviceId = dac.getDefaultOutputDevice();
  inParam.nChannels = outParam.nChannels = channels;
  inParam.firstChannel = iOffset;
  outParam.firstChannel = oOffset;
  unsigned int sampleRate = srate;
  unsigned int bufferFrames = 1024;

  unsigned int bufferBytes = bufferFrames * channels * sizeof(RTAUDIO_TYPE);

  try
  {
    dac.openStream(&outParam, &inParam, RTAUDIO_SINT16, sampleRate, &bufferFrames, &inout, (void *)&bufferBytes);
    dac.startStream();
  }
  catch (RtAudioError &e)
  {
    e.printMessage();
    return 0;
  }

  int number = 0;
  do
  {
    if (number == 0)
    {
      std::cout << "0. Show menu:" << std::endl;
      std::cout << "1. Increase gain;" << std::endl;
      std::cout << "2. Reduce gain;" << std::endl;
      std::cout << "3. Change gain step:" << std::endl;
      std::cout << "4. Stop and save;" << std::endl;
    }
    std::cin >> number;
    if (number == 1)
    {
      gain += step;

      if (gain > 1)
      {
        gain = 1;
        std::cout << "Warning!. Maximum gain is 1" << std::endl;
      }

      std::cout << "Current gain: " << gain << std::endl;
    }
    else if (number == 2)
    {
      gain -= step;

      if (gain < 0)
      {
        gain = 0;
        std::cout << "Warning!. Minimum gain is 0" << std::endl;
      }

      std::cout << "Current gain: " << gain << std::endl;
    }
    else if (number == 3)
    {
      float newStep;
      std::cout << "Enter new step: ";
      std::cin >> newStep;

      if (newStep > 1)
      {
        newStep = 1;
        std::cout << "Warning!. Maximum step is 1" << std::endl;
      }

      step = newStep;
      std::cout << "Current step: " << step << std::endl;
    }

  } while (number != 4);

  try
  {
    dac.stopStream();
  }
  catch (RtAudioError &e)
  {
    e.printMessage();
  }
  if (dac.isStreamOpen())
    dac.closeStream();

  return 0;
}