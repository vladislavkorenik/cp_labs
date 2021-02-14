#include <iostream>
#include <sndfile.hh>
#include "RtAudio.h"

SndfileHandle sndFile;

int fplay(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *userData)
{
  int16_t *buffer = (int16_t *)outputBuffer;

  if (status)
  {
    std::cout << "Stream underflow detected!" << std::endl;
  }

  sndFile.read(buffer, nBufferFrames * sndFile.channels());

  return 0;
}

int main()
{
  const char *fname = "test.wav";

  sndFile = SndfileHandle(fname);

  std::cout << "Reading file: " << fname << std::endl;
  std::cout << "File format: " << sndFile.format() << std::endl;
  std::cout << "Channels: " << sndFile.channels() << std::endl;
  std::cout << "Samplerate " << sndFile.samplerate() << std::endl;
  std::cout << "Samples in file: " << sndFile.frames() << std::endl;

  RtAudio dac;
  if (dac.getDeviceCount() < 1)
  {
    std::cout << "\nNo audio devices found!\n";
    return 0;
  }

  // Output params
  RtAudio::StreamParameters parameters;
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = sndFile.channels();
  parameters.firstChannel = 0;
  unsigned int sampleRate = sndFile.samplerate();
  unsigned int bufferFrames = sndFile.frames();

  try
  {
    dac.openStream(&parameters, NULL, RTAUDIO_SINT16,
                   sampleRate, &bufferFrames, &fplay, (void *)&sndFile);
    dac.startStream();
  }
  catch (RtAudioError &e)
  {
    e.printMessage();
    return 0;
  }

  char input;
  std::cout << "\nPlaying ... press <enter> to quit.\n";
  std::cin.get(input);
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