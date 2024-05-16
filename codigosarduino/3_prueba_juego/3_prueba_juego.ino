//VAMOS A PROBAR LA PANTALLA Y LA ALFOMBRA DEL JUEGO
//TENDREMOS UNA CANCION DE BAILE DEFINIDA DE FORMA FIJA
#include <Adafruit_NeoPixel.h>
#define PIN 14  //pin de la Wemos esp32 para data
#define NUMPIXELS 64
Adafruit_NeoPixel pantalla(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//COLORES DE LAS FILAS DE LA PANTALLA
uint32_t colorL=pantalla.Color(255, 0, 0); //color rojo
uint32_t colorU=pantalla.Color(255, 255, 0); //color amarillo
uint32_t colorR=pantalla.Color(0, 255, 0); //color verde
uint32_t colorD=pantalla.Color(0, 0, 255); //color azul

//VARIABLES Y BANDERAS
bool start=true;

int tiempo=800;
//OJO EL TAMAÑO NO ES DINAMICO SINO QUE DEBE EDITARSE 16 en blanco mas los 10 de la cancion +1 en blanco
#define MAXCANCION 27
char cancion[]="LUDURDDLDU";  //10 pasos
bool cancionBailada[MAXCANCION][4];
int contador=0;

void setup(){
  pantalla.begin(); //inicializamos
  pantalla.show();  // Turn OFF all pixels ASAP
  pantalla.setBrightness(20);// Set BRIGHTNESS to about 1/5 (max = 255)
  configurarMatriz();
}

void loop(){
    pantalla.clear();
    pantalla.show();
    if(start){
      for(int i=0; i<16; i++){
        for(int j=0; j<4; j++){
          if(cancionBailada[contador+i][j]){
            switch(j){
              case 0:
                pantalla.setPixelColor(i,colorL);
                break;
              case 1:
                pantalla.setPixelColor(i+16,colorU);
                break;
              case 2:
                pantalla.setPixelColor(i+32,colorR);
                break;
              case 3:
                pantalla.setPixelColor(i+48,colorD);
                break;
            }
          }
        }
      }
      pantalla.show();
      delay(tiempo);
      contador++;
      //LA CANCION SOLO TIENE 10 MOVIMIENTOS
      if(contador==10){
        start=false;
      }
    }// fin de start == true

}


//metodo que toma la cancion y llena la matriz de baile
void configurarMatriz(){
  //primero ponemos todo a false
  for(int i=0; i<MAXCANCION; i++){
    for(int j=0; j<4; j++){
      cancionBailada[i][j]=false;
    }
  }
  //ahora llenamos la matriz
  for(int i=0; i<10; i++){
    switch(cancion[i]){
      case 'L':
        cancionBailada[15+i][0]=true;
        break;
      case 'U':
        cancionBailada[15+i][1]=true;
        break;
      case 'R':
        cancionBailada[15+i][2]=true;
        break;
      case 'D':
        cancionBailada[15+i][3]=true;
        break;
    }
  }
}

