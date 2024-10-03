#include <wiringPi.h>
const int i, leds[2] = {17, 23};
void blink(const int led)
{
    digitalWrite(led, HIGH);
    delay(30);
    digitalWrite(led, LOW);
    delay(30);
}
int main(void)
{
    wiringPiSetupGpio();
    for (int i; i < sizeof(leds); i++)
    {
        pinMode(leds[i], OUTPUT);
        delay(5);
    }
    while (1)
    {
        for (int j = 0; j < 2; j++)
        {
            blink(leds[j]);
        }
    }
    return 0;
}