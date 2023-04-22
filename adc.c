#include <mega32.h>
#include <stdlib.h>
#include <stdio.h>
#include <delay.h>

// Alphanumeric LCD functions
#include <alcd.h>

#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

void main(void)
{
// Declare your local variables here
char dataSuhu[20], nilai;

ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

lcd_init(16);
while (1)
      {
      // Place your code here 
      nilai = read_adc(0)/2.05;
    
      lcd_clear();
      sprintf(dataSuhu,"%d",nilai);
      lcd_gotoxy(0,0);
      lcd_puts("Suhu Anda :");   
      lcd_gotoxy(12,0);
      lcd_puts(dataSuhu); 
      if (nilai >= 38) {
         lcd_gotoxy(0,2);
         lcd_puts("Waspada Covid19");
      } else if (nilai >= 36)  {
         lcd_gotoxy(0,2);
         lcd_puts("Anda Sehat");
      }  else {
         lcd_gotoxy(0,2);
         lcd_puts("Sedang Sakit");
      } 
      
      delay_ms (100);
      }
}