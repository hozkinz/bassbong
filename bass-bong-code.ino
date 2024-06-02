#include "MIDIUSB.h"


void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = { 0x08, 0x80 | channel, pitch, velocity };
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop() {

  // Check button states
  int button1State = digitalRead(2);
  int button2State = digitalRead(3);
  int button3State = digitalRead(4);

  // Read potentiometer value (0-1023)
  int potValue = analogRead(A0);
  int pitch = map(potValue, 0, 1023, 0, 127);

  // Send MIDI Note On messages on button press
  if (button1State == HIGH) {
    pitch = 0;
    { noteOff(0, pitch, 64); }
  }

  else if (button1State == LOW) {
    Serial.println("Sending note on");

    pitch = map(potValue, 0, 1023, 0, 127);
    noteOn(0, pitch, 64);  // Channel 0, potentiometer pitch, normal velocity
  }

  if (button2State == HIGH) {
    pitch = 0;
    { noteOff(1, pitch, 64); }
  }

  else if (button2State == LOW) {
    Serial.println("Sending note on");

    pitch = map(potValue, 0, 1023, 0, 127);
    noteOn(1, pitch, 64);  // Channel 1, potentiometer pitch, normal velocity
  }

  if (button3State == HIGH) {
    pitch = 0;
    { noteOff(2, pitch, 64); }
  }

  else if (button3State == LOW) {
    Serial.println("Sending note on");

    pitch = map(potValue, 0, 1023, 0, 127);
    noteOn(2, pitch, 64);  // Channel 2, potentiometer pitch, normal velocity
  }
}