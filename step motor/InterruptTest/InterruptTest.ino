#define NOT_AN_INTERRUPT -1
#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

const byte PIN_INTERRUPT = 2;

volatile bool state = false;

void setup()
{
  pinMode(PIN_INTERRUPT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), invert, CHANGE);

  Serial.begin(9600);
  Serial.println("Serial start");
}

void loop()
{
  if (state) {
    // noInterrupts();
    Serial.println(millis());
    state = false;
    // interrupts();
  }
}

void invert() {
  state = true;
}
