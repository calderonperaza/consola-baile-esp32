//Ejemplo de prueba para la pantalla led
// la pantalla utiliza tira led WS2812B de 5 voltios
//la pantalla se hace con 4 tiras tal como se muestra en la figura

#include <Adafruit_NeoPixel.h>
#define PIN 14  //pin de la Wemos esp32 para data
#define NUMPIXELS 64
Adafruit_NeoPixel pantalla(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

uint32_t colorL=pantalla.Color(255, 0, 0); //color rojo
uint32_t colorU=pantalla.Color(255, 255, 0); //color amarillo
uint32_t colorR=pantalla.Color(0, 255, 0); //color verde
uint32_t colorD=pantalla.Color(0, 0, 255); //color azul


void setup(){
  pantalla.begin(); //inicializamos
  pantalla.show();  // Turn OFF all pixels ASAP 
  pantalla.setBrightness(50);// Set BRIGHTNESS to about 1/5 (max = 255)

}

void loop(){
  pantalla.clear(); 
  for(byte x=0; x<16; x++){
    pantalla.setPixelColor(x,colorL);
    pantalla.setPixelColor(x+16,colorU);
    pantalla.setPixelColor(x+32,colorR);
    pantalla.setPixelColor(x+48,colorD);
  }
  pantalla.show();
  delay(500);
}

