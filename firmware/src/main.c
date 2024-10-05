#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB5  // Pin 13 corresponds to PB5 on the ATmega328P

int main(void)
{
    // Set PB5 (Pin 13) as output
    DDRB |= (1 << LED_PIN);

    while (1)
    {
        // Set PB5 high to turn on the LED
        PORTB |= (1 << LED_PIN);
        _delay_ms(1000.0);
        PORTB &= ~(1 << LED_PIN);
        _delay_ms(1000.0);
    }

    return 0;
}
