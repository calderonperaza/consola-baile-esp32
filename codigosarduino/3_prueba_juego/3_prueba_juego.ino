//VAMOS A PROBAR LA PANTALLA
//TENDREMOS UNA CANCION DE BAILE DEFINIDA DE FORMA FIJA CON 15 PASOS
//ESOS PASOS SE DEBEN VISUALIZAR EN LA PANTALLA DE ARRIBA HACIA ABAJO
//ESTA PRUEBA ES SOLO PARA LA PANTALLA, AUN NO ACCIONA LA ALFOMBRA
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
unsigned long myTime=0;

//OJO EL TAMAÑO NO ES DINAMICO SINO QUE DEBE EDITARSE
// 16 en blanco antes y 16 despues mas los 15 pasos de la cancion
#define MAXCANCION 47
char cancion[]="LUDURDDLDULLRLD";  //15 pasos por turno
#define NUMPASOS 15
bool cancionBailada[MAXCANCION][4];
int contador=0;

void setup(){
  Serial.begin(9600);
  pantalla.begin(); //inicializamos
  pantalla.show();  // Turn OFF all pixels ASAP
  pantalla.setBrightness(20);// Set BRIGHTNESS to about 1/5 (max = 255)
  configurarMatriz();
}

//loop empleando delay
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
      //nos salimos cuando hemos recorrido las filas de la cancion +1
      if(contador==(NUMPASOS+16)){
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
  //Serial.println(sizeof(cancion)-1);
  for(int i=0; i<NUMPASOS; i++){
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


//loop empleando millis en lugar del delay
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
      if(myTime==0){
        myTime=millis();
      }

      if(millis()-myTime>tiempo){
        contador++;
        myTime=millis();
      }
      //nos salimos cuando hemos recorrido las filas de la cancion +1
      if(contador==(NUMPASOS+16)){
        start=false;
      }
    }// fin de start == true
}
