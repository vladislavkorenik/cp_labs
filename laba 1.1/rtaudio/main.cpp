#include <iostream>
#include <cstring>
#include <cstdio>
#include <sndfile.hh>
#include "RtAudio.h"

SndfileHandle sndFile;
typedef signed short RTAUDIO_TYPE;

void create_file(const char *fname, const int format, const int channels, const int srate)
{
  SndfileHandle file;
  printf("Creating file named '%s'\n", fname);
  sndFile = SndfileHandle(fname, SFM_WRITE, format, channels, srate);
}

int fplay(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *data)
{
  RTAUDIO_TYPE *buffer = (RTAUDIO_TYPE *)outputBuffer;

  if (status)
  {
    std::cout << "Stream underflow detected!" << std::endl;
  }

  sndFile.read(buffer, nBufferFrames * sndFile.channels());

  return 0;
}

int inout(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *data)
{
  RTAUDIO_TYPE *inBuffer = (RTAUDIO_TYPE *)inputBuffer;

  unsigned int *bytes = (unsigned int *)data;
  memcpy(outputBuffer, inputBuffer, *bytes);
  memset(inputBuffer, 0, sizeof(inBuffer));

  sndFile.write(inBuffer, nBufferFrames * sndFile.channels());
  return 0;
}

int main()
{
  const char *fname = "av.wav";
  const int channels = 5;
  const int srate = 48000;

  create_file(fname, SF_FORMAT_WAV | SF_FORMAT_PCM_16, channels, srate);

  std::cout << "File format: " << sndFile.format() << std::endl;
  std::cout << "Channels: " << sndFile.channels() << std::endl;
  std::cout << "Samplerate " << sndFile.samplerate() << std::endl;

  RtAudio dac;
  if (dac.getDeviceCount() < 1)
  {
    std::cout << "\nNo audio devices found!\n";
    return 0;
  }

  RtAudio::StreamParameters inParam, outParam;
  inParam.deviceId = dac.getDefaultInputDevice();
  outParam.deviceId = dac.getDefaultOutputDevice();
  inParam.nChannels = outParam.nChannels = channels;
  inParam.firstChannel = 0;
  outParam.firstChannel = 0;
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

  char symbol;
  std::cout << "\nRecording ... press <enter> to quit.\n";
  std::cin.get(symbol);
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