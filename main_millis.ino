#define LED PB4   // LED on Port B pin 4

unsigned long prev = 0;
int on = 5000;
int off = 3000;

void setup()
{
  DDRB |= (1 << LED);     // LED output
  PORTB &= ~(1 << LED);   // LED off
}

void loop()
{
  unsigned long current = millis();

  // LED OFF -> turn ON after "off" time
  if ((current - prev >= off) && !(PINB & (1 << LED)))
  {
    prev = current;
    PORTB ^= (1 << LED);   // Toggle ON
  }

  // LED ON -> turn OFF after "on" time
  if ((current - prev >= on) && (PINB & (1 << LED)))
  {
    prev = current;
    PORTB ^= (1 << LED);   // Toggle OFF
  }
}
