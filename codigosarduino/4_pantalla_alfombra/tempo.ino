#include <Adafruit_NeoPixel.h>
#define PIN 14  //pin de la Wemos esp32 para data
#define LEFT 16
#define UP 17
#define RIGHT 25
#define DOWN 26
#define NUMPIXELS 64

Adafruit_NeoPixel pantalla(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t colorL=pantalla.Color(255, 0, 0); //color rojo
uint32_t colorU=pantalla.Color(255, 255, 0); //color amarillo
uint32_t colorR=pantalla.Color(0, 255, 0); //color verde
uint32_t colorD=pantalla.Color(0, 0, 255); //color azul


void setup(){
  Serial.begin(9600);
  Serial.println(colorL);
  Serial.println(colorU);
  Serial.println(colorR);
  Serial.println(colorD);
  pantalla.begin(); //inicializamos
  pantalla.clear();
  pantalla.show();  // Turn OFF all pixels ASAP
  pantalla.setBrightness(20);// Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.println("Valor de la pantalla oscura")

}


void loop(){

}
