#include <MIDI.h>

const int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int potentiometerPins[] = {A0, A1};
const int numButtons = 12;
const int numPotentiometers = 2;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  // Check button states
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      sendNoteOn(i + 1, 127); // Note numbers start from 1
      delay(100); // Adjust this delay according to your needs
      sendNoteOff(i + 1, 0);
    }
  }

  // Read potentiometer values and send control change messages
  for (int i = 0; i < numPotentiometers; i++) {
    int potValue = analogRead(potentiometerPins[i]);
    int mappedValue = map(potValue, 0, 1023, 0, 127);
    sendControlChange(i + 1, mappedValue); // Control numbers start from 1
    delay(10); // Adjust this delay according to your needs
  }
}

void sendNoteOn(int note, int velocity) {
  MIDI.sendNoteOn(note, velocity, 1); // 1 is the MIDI channel
}

void sendNoteOff(int note, int velocity) {
  MIDI.sendNoteOff(note, velocity, 1); // 1 is the MIDI channel
}

void sendControlChange(int control, int value) {
  MIDI.sendControlChange(control, value, 1); // 1 is the MIDI channel
}
