
#include <FastLED.h>

#define NUM_LEDS 1 
#define DATA_PIN 1 //pin number where led is connected

CRGB leds[NUM_LEDS];

CRGB zeroColor = 0xFF0000; // color when one
CRGB oneColor = 0x0000FF; // color when one
CRGB offColor = 0x000000; // color when off

// ascii code for all capital letters
bool ascii[26][8] = {
  {0,1,0,0,0,0,0,1},// A
  {0,1,0,0,0,0,1,0},// B
  {0,1,0,0,0,0,1,1},// C
  {0,1,0,0,0,1,0,0},// D
  {0,1,0,0,0,1,0,1},// E
  {0,1,0,0,0,1,1,0},// F
  {0,1,0,0,0,1,1,1},// G
  {0,1,0,0,1,0,0,0},// H
  {0,1,0,0,1,0,0,1},// I
  {0,1,0,0,1,0,1,0},// J
  {0,1,0,0,1,0,1,1},// K
  {0,1,0,0,1,1,0,0},// L
  {0,1,0,0,1,1,0,1},// M
  {0,1,0,0,1,1,1,0},// N
  {0,1,0,0,1,1,1,1},// O
  {0,1,0,1,0,0,0,0},// P
  {0,1,0,1,0,0,0,1},// Q
  {0,1,0,1,0,0,1,0},// R
  {0,1,0,1,0,0,1,1},// S
  {0,1,0,1,0,1,0,0},// T
  {0,1,0,1,0,1,0,1},// U
  {0,1,0,1,0,1,1,0},// V
  {0,1,0,1,0,1,1,1},// W
  {0,1,0,1,1,0,0,0},// X
  {0,1,0,1,1,0,0,1},// Y
  {0,1,0,1,1,0,1,0} // Z
};

// string to send length
int strLength = 25;

// must be capital or small letters. Numbers and punctuations not allowed
char *str = "NOT ANOTHER HELLO WORLD  ";

// send zero
void zero(){
  leds[0] = zeroColor;
  FastLED.show();
  delay(700);
  leds[0] = offColor;
  FastLED.show();
  delay(300);
}

// send one
void one(){
  leds[0] = oneColor;
  FastLED.show();
  delay(700);
  leds[0] = offColor;
  FastLED.show();
  delay(300);
}

// delay for letter end
void nextLetter(){
  leds[0] = offColor;
  FastLED.show();
  delay(1500);
}

// delay for space (will be called 8 times for each space hence small delay)
void space(){
  leds[0] = offColor;
  FastLED.show();
  delay(200);
}

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS); 
  leds[0] = offColor;
  FastLED.show();
  external_interrupt(); 
}

void loop() {

}

// loop through string and send each character
void sendMessage(){
  for(int i = 0; i < strLength; i++){
    char letter = str[i];
    
    for(int j = 0; j < 8; j++){
      if(letter >= 65 && letter <= 90){
        if(ascii[letter - 65][j]){
          one();
        }
        else{
          zero();
        }
      }
      else if(letter >= 97 && letter <= 122){
        if(ascii[letter - 97][j]){
          one();
        }
        else{
          zero();
        }
      }
      else {
        space();
      }
    }
    nextLetter();
  }
}

// external interrupt attached to switch
void external_interrupt()
{
  DDRB |= (1<<PB1)|(1<<PB0);     // set PB2 as output(LED)
  sei();     //enabling global interrupt
  GIMSK |= (1<<INT0);     // enabling the INT0 (external interrupt) 
  MCUCR |= (1<<ISC01);    // Configuring as falling edge 
}

// interrupt service routine for interrupt
ISR (INT0_vect)        // Interrupt service routine 
{
  sendMessage();
}
