
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 // Number of snowflakes in the animation example
#include <Bonezegei_HCSR04.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        D4 
#define NUMPIXELS 8
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
const int TRIGGER_PIN = D6;
const int ECHO_PIN = D7;

Bonezegei_HCSR04 ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(D3,OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  
 
}
void loop() {
    display.clearDisplay();

     int d=ultrasonic.getDistance();
     if(d>0) {
  Serial.print("Distance:");
  Serial.print(d);
  Serial.println(" cm");
  delay(100);

    // Big text
    display.setTextSize(2);  // Larger text
    display.setTextColor(SSD1306_WHITE);
    
    display.setCursor(0, 0);
    display.println("Distance:");

    
    display.setCursor(0, 20);
    display.print(d);
    display.print(" cm");

   if(d<60){
    
      digitalWrite(D3,HIGH);
      pixels.clear();
       pixels.setPixelColor(0, pixels.Color(0, 150, 0));
       pixels.setPixelColor(1, pixels.Color(0, 150, 0));
       pixels.setPixelColor(2, pixels.Color(0, 150, 0));
       pixels.setPixelColor(3, pixels.Color(0, 150, 0));
       pixels.setPixelColor(4, pixels.Color(0, 150, 0));
       pixels.show();
       
    
    }else{
      digitalWrite(D3,LOW);
      pixels.clear();
      pixels.clear();  // clear() จะล้างไฟทั้งหมด (ทำให้เป็นสีดำ)
      pixels.show();
      
      
      }

    display.display();  // Show the content on the display

    
   } 
}
