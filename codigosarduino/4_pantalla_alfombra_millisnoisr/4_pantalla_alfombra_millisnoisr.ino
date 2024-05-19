//lo mismo que el archivo 4_pantalla_alfombra pero sin interrupciones y reemplazando delay por millis
#include <Adafruit_NeoPixel.h>
#define PIN 14  //pin de la Wemos esp32 para data
#define LEFT 16
#define UP 17
#define RIGHT 25
#define DOWN 26
#define NUMPIXELS 64

Adafruit_NeoPixel pantalla2(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//COLORES DE LAS FILAS DE LA pantalla2
uint32_t colorL=pantalla2.Color(255, 0, 0); //color rojo
uint32_t colorU=pantalla2.Color(255, 255, 0); //color amarillo
uint32_t colorR=pantalla2.Color(0, 255, 0); //color verde
uint32_t colorD=pantalla2.Color(0, 0, 255); //color azul

//VARIABLES Y BANDERAS
bool start=true;
char equipo[]="PIKORO";
volatile int puntos=0;
int tiempo=800;
unsigned long myTime=0;
//OJO EL TAMAÑO NO ES DINAMICO SINO QUE DEBE EDITARSE
// 16 en blanco antes y 16 despues mas los 15 pasos de la cancion
#define MAXCANCION 47
char cancion[]="LUDURDDLDULLRLD";  //15 pasos por turno
#define NUMPASOS 15
bool cancionBailada[MAXCANCION][4];
int contador=0;
bool left_old = false;

bool up_old = false;

bool right_old = false;

bool down_old = false;



void setup(){
  pinMode(LEFT,INPUT);
  pinMode(UP,INPUT);
  pinMode(RIGHT,INPUT);
  pinMode(DOWN,INPUT);
  Serial.begin(9600);
  pantalla2.begin(); //inicializamos
  pantalla2.show();  // Turn OFF all pixels ASAP
  pantalla2.setBrightness(20);// Set BRIGHTNESS to about 1/5 (max = 255)
  configurarMatriz();
}

void loop(){
    pantalla2.clear();
    pantalla2.show();
    if(start){
      for(int i=0; i<16; i++){
        for(int j=0; j<4; j++){
          if(cancionBailada[contador+i][j]){
            switch(j){
              case 0:
                pantalla2.setPixelColor(i,colorL);
                break;
              case 1:
                pantalla2.setPixelColor(i+16,colorU);
                break;
              case 2:
                pantalla2.setPixelColor(i+32,colorR);
                break;
              case 3:
                pantalla2.setPixelColor(i+48,colorD);
                break;
            }
          }
        }
      }
      pantalla2.show();
      if(myTime==0){
        myTime=millis();
      }
      if(millis()-myTime>tiempo){
        myTime=millis();
        contador++;
        if(contador>=MAXCANCION-16){
          terminarJuego();
        }
      }
    }

    if(start){

      //Si presionan el boton left y la fila es colorL
      if(digitalRead(LEFT)==HIGH){
        if(left_old==false){
          left_old=true;
          if(pantalla1.getPixelColor(0)==colorL)
            puntos++;
        }
      }else{
        left_old=false;
      }

      //Si presionan el boton up y la fila es colorU
      if(digitalRead(UP)==HIGH){
        if(up_old==false){
          up_old=true;
          if(pantalla1.getPixelColor(16)==colorU)
            puntos++;
        }
      }else{
        up_old=false;
      }

      //Si presionan el boton right y la fila es colorR
      if(digitalRead(RIGHT)==HIGH){
        if(right_old==false){
          right_old=true;
          if(pantalla1.getPixelColor(32)==colorR)
            puntos++;
        }
      }else{
        right_old=false;
      }

      //Si presionan el boton down y la fila es colorD
      if(digitalRead(DOWN)==HIGH){
        if(down_old==false){
          down_old=true;
          if(pantalla1.getPixelColor(48)==colorD)
            puntos++;
        }
      }else{ down_old=false; }






    }else{
      if(ditigalRead(LEFT)==HIGH || digitalRead(UP)==HIGH || digitalRead(RIGHT)==HIGH || digitalRead(DOWN)==HIGH){
        reportarseOnline();
    }//fin del el start

} //fin del loop


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


void reportarseOnline(){
  Serial.println(equipo);
}

void terminarJuego(){
  Serial.println("PUNTOS DEL EQUIPO");
  //imprimo la cadena de texto = equipo + ',' + puntos
  Serial.print(equipo);
  Serial.print(",");
  Serial.println(puntos);
  puntos=0;
  start=false;
}
