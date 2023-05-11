#include <AccelStepper.h>
#include <MultiStepper.h>

#include <HopeDuino_Buzz.h>
#include <HopeDuino_UART.h>

#define NOT_AN_INTERRUPT -1
#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

buzzClass Buzz;
uartClass uart;

const int moveSteps = 200;

const byte PIN_INTERRUPT = 2;
const byte PIN_STEP = 8;
const byte PIN_DIR = 9;
const byte PIN_ENABLE = 10;
const byte PIN_LED = 13;

volatile byte state = 0;

byte music[18] = {
  SM_1, SM_2, SH_3, SM_1,
  20,   20,   20,   20
};

char cstr[16];

AccelStepper stepper(AccelStepper::DRIVER, PIN_STEP, PIN_DIR);

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);

  stepper.setMaxSpeed(500.0);
  // stepper.setAcceleration(200.0);
  stepper.setSpeed(50.0);
  // stepper.moveTo(moveSteps);

  // pinMode(PIN_STEP, OUTPUT);
  // pinMode(PIN_DIR, OUTPUT);
  // pinMode(PIN_ENABLE, OUTPUT);
  // digitalWrite(PIN_ENABLE, LOW);
  stepper.setPinsInverted(false, false, true);
  stepper.setEnablePin(PIN_ENABLE);
  stepper.enableOutputs();

  pinMode(PIN_INTERRUPT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), interrupt_handler, FALLING);

  Buzz.vBuzzInit();
  Buzz.vBuzzPlay(music, 4);

  // uart.vUartInit(9600, _8N1);
  // uart.vUartPutString((char *)"Serial start\n");
}

void loop()
{
  // uart.vUartPutByte(digitalRead(PIN_INTERRUPT)+48);
  // uart.vUartNewLine();
  // if (!stepper.isRunning()) {
  //   digitalWrite(PIN_LED, !digitalRead(PIN_LED));;
  // }
  // uart.vUartPutByte(level + 48);
  // uart.vUartNewLine();

  // stepper.run();
  // itoa(stepper.currentPosition(), cstr, 10);
  // uart.vUartPutString(cstr);
  // uart.vUartNewLine();
  stepper.runSpeed();
}

void invert() {
  state = 1 + state % 2;
  switch (state) {
    case 1:
      stepper.disableOutputs();
      // digitalWrite(PIN_ENABLE, HIGH);
      break;
    case 2:
      stepper.setSpeed(-stepper.speed());
      digitalWrite(PIN_LED, !digitalRead(PIN_LED));
      stepper.enableOutputs();
      // digitalWrite(PIN_ENABLE, LOW);
      break;
    default:
      break;
  }
}

void interrupt_handler()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200)
  {
    invert();
  }
  last_interrupt_time = interrupt_time;
}
