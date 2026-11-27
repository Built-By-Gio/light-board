// World Saving LEDs — Simon Says on the Light Board.
// Pins match the silkscreen. Buttons pull to GND, LEDs are pin -> LED -> 470 -> GND.

const byte LEDS[7] = {9, 8, 7, 6, 5, 4, 3};
const byte BUTTONS[7] = {12, 11, 10, A3, A2, A1, A0};
const int TONES[7] = {262, 294, 330, 349, 392, 440, 494};
const byte BUZZER = 2;
const byte POWER = A4;

const int MAX_ROUNDS = 50;
byte seq[MAX_ROUNDS];
int rounds = 0;

void setup() {
  for (byte i = 0; i < 7; i++) {
    pinMode(LEDS[i], OUTPUT);
    pinMode(BUTTONS[i], INPUT_PULLUP);
  }
  pinMode(BUZZER, OUTPUT);
  pinMode(POWER, INPUT_PULLUP);
  randomSeed(analogRead(A6));
}

// Switch closed to GND = on. If yours reads backwards, flip this.
bool on() {
  return digitalRead(POWER) == LOW;
}

void flash(byte i, int ms) {
  digitalWrite(LEDS[i], HIGH);
  tone(BUZZER, TONES[i], ms);
  delay(ms);
  digitalWrite(LEDS[i], LOW);
  noTone(BUZZER);
}

void allLeds(bool state) {
  for (byte i = 0; i < 7; i++) digitalWrite(LEDS[i], state);
}

void startup() {
  for (byte i = 0; i < 7; i++) flash(i, 60);
  for (int i = 6; i >= 0; i--) flash(i, 60);
  delay(400);
}

void lose() {
  allLeds(HIGH);
  tone(BUZZER, 110, 700);
  delay(800);
  allLeds(LOW);
  for (int i = 0; i < rounds - 1; i++) {
    digitalWrite(LEDS[i % 7], HIGH);
    delay(150);
    digitalWrite(LEDS[i % 7], LOW);
    delay(100);
  }
  delay(800);
  rounds = 0;
}

void win() {
  for (byte k = 0; k < 3; k++) {
    allLeds(HIGH);
    tone(BUZZER, 880, 120);
    delay(150);
    allLeds(LOW);
    delay(100);
  }
  rounds = 0;
}

// Returns the button index, or -1 on timeout or power-off.
int waitForPress(unsigned long timeoutMs) {
  unsigned long start = millis();
  while (millis() - start < timeoutMs) {
    if (!on()) return -1;
    for (byte i = 0; i < 7; i++) {
      if (digitalRead(BUTTONS[i]) == LOW) {
        delay(20);
        if (digitalRead(BUTTONS[i]) != LOW) continue;
        digitalWrite(LEDS[i], HIGH);
        tone(BUZZER, TONES[i]);
        while (digitalRead(BUTTONS[i]) == LOW) {}
        digitalWrite(LEDS[i], LOW);
        noTone(BUZZER);
        delay(20);
        return i;
      }
    }
  }
  return -1;
}

void loop() {
  if (!on()) {
    allLeds(LOW);
    noTone(BUZZER);
    rounds = 0;
    delay(50);
    return;
  }

  if (rounds == 0) startup();

  seq[rounds++] = random(7);

  // Shows get faster as the sequence grows, down to 150 ms per step.
  int step = max(150, 450 - rounds * 15);
  for (int i = 0; i < rounds; i++) {
    flash(seq[i], step);
    delay(step / 2);
  }

  for (int i = 0; i < rounds; i++) {
    int pressed = waitForPress(3000);
    if (pressed != seq[i]) {
      if (on()) lose();
      return;
    }
  }

  if (rounds == MAX_ROUNDS) {
    win();
    return;
  }
  delay(600);
}
