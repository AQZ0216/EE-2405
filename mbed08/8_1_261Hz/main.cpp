#include "mbed.h"
#include <cmath>
#include "DA7212.h"

int idC, i;
Thread t;
DA7212 audio;
InterruptIn button(SW2);
int16_t waveform[kAudioTxBufferSize];
EventQueue queue(32 * EVENTS_EVENT_SIZE);

void playNote(int freq)
{
  for (i = 0; i < kAudioTxBufferSize; i++)
  {
    waveform[i] = (int16_t) (sin((double)i * 2. * M_PI / (double) (kAudioSampleFrequency / freq)) * ((1<<16) - 1));
  }
  // the loop below will play the note for the duration of 1s
  for(int j = 0; j < kAudioSampleFrequency / kAudioTxBufferSize; ++j)
  {
    audio.spk.play(waveform, kAudioTxBufferSize);
  }
}
void playNoteC(void) {idC = queue.call_every(1, playNote, 261);}
void stopPlayNoteC(void) {queue.cancel(idC);}

int main(void)
{
  t.start(callback(&queue, &EventQueue::dispatch_forever));
  button.fall(queue.event(playNoteC));
  button.rise(queue.event(stopPlayNoteC));
}