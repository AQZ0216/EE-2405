#include "mbed.h"
#include <cmath>
#include "DA7212.h"

#define bufferLength (32)
#define signalLength (1024)

DA7212 audio;
Serial pc(USBTX, USBRX);

InterruptIn button(SW2);
InterruptIn keyboard0(SW3);

EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;
int idC = 0;

int16_t signal[signalLength];
int16_t waveform[kAudioTxBufferSize];
char serialInBuffer[bufferLength];
int serialCount = 0;

DigitalOut green_led(LED2);

void loadSignal(void)
{
  green_led = 0;
  int i = 0;
  serialCount = 0;
  audio.spk.pause();
  while(i < signalLength)
  {
    if(pc.readable())
    {
      serialInBuffer[serialCount] = pc.getc();
      serialCount++;
      if(serialCount == 5)
      {
        serialInBuffer[serialCount] = '\0';
        signal[i] = (float) atof(serialInBuffer);
        serialCount = 0;
        i++;
      }
    }
  }
  green_led = 1;
}

void playNote(int freq)
{
  for (int i = 0; i < kAudioTxBufferSize; i++)
  {
    waveform[i] = (int16_t) (signal[(uint16_t) (i * freq * signalLength * 1. / kAudioSampleFrequency) % signalLength]);
  }
  // the loop below will play the note for the duration of 1s
  for(int j = 0; j < kAudioSampleFrequency / kAudioTxBufferSize; ++j)
  {
    audio.spk.play(waveform, kAudioTxBufferSize);
  }
}

void loadSignalHandler(void) {queue.call(loadSignal);}

void playNoteC(void) {idC = queue.call_every(1, playNote, 261);}

void stopPlayNoteC(void) {queue.cancel(idC);}

int main(void)
{
  green_led = 1;
  t.start(callback(&queue, &EventQueue::dispatch_forever));
  button.rise(queue.event(loadSignalHandler));
  keyboard0.rise(queue.event(playNoteC));
  keyboard0.fall(queue.event(stopPlayNoteC));
}