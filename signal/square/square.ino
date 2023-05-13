// #include <HopeDuino_Buzz.h>

// buzzClass Buzz;

const byte PIN_LED = 13;

// byte music[18] = {
//     SM_1, SM_2, SH_3, SM_1,
//     20, 20, 20, 20};

void setup()
{
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);

    // Buzz.vBuzzInit();
    // Buzz.vBuzzPlay(music, 4);
}

void loop()
{
    digitalWrite(PIN_LED, LOW);
    delay(1000 * 2);
    digitalWrite(PIN_LED, HIGH);
    delay(1000 * 2);
}
