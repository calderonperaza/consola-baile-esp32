//VAMOS A PROBAR LA pantalla1 Y LA ALFOMBRA DEL JUEGO
//TENDREMOS UNA CANCION DE BAILE DEFINIDA DE FORMA FIJA
#include <Adafruit_NeoPixel.h>
#define PIN 14  //pin de la Wemos esp32 para data
#define LEFT 16
#define UP 17
#define RIGHT 25
#define DOWN 26
#define NUMPIXELS 64

Adafruit_NeoPixel pantalla1(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//COLORES DE LAS FILAS DE LA pantalla1
uint32_t colorL=pantalla1.Color(255, 0, 0); //color rojo
uint32_t colorU=pantalla1.Color(255, 255, 0); //color amarillo
uint32_t colorR=pantalla1.Color(0, 255, 0); //color verde
uint32_t colorD=pantalla1.Color(0, 0, 255); //color azul

//VARIABLES Y BANDERAS
bool start=true;
char equipo[]="PIKORO";
volatile int puntos=0;
int tiempo=800;
//OJO EL TAMAÑO NO ES DINAMICO SINO QUE DEBE EDITARSE
// 16 en blanco antes y 16 despues mas los 15 pasos de la cancion
#define MAXCANCION 47
char cancion[]="LUDURDDLDULLRLD";  //15 pasos por turno
#define NUMPASOS 15
bool cancionBailada[MAXCANCION][4];
int contador=0;

void setup(){
  pinMode(LEFT,INPUT);
  pinMode(UP,INPUT);
  pinMode(RIGHT,INPUT);
  pinMode(DOWN,INPUT);
  Serial.begin(9600);
  attachInterrupt(LEFT,isrleft,RISING);
  attachInterrupt(UP,isrup,RISING);
  attachInterrupt(RIGHT,isrright,RISING);
  attachInterrupt(DOWN,isrdown,RISING);
  pantalla1.begin(); //inicializamos
  pantalla1.show();  // Turn OFF all pixels ASAP
  pantalla1.setBrightness(20);// Set BRIGHTNESS to about 1/5 (max = 255)
  configurarMatriz();
}

void loop(){
    pantalla1.clear();
    pantalla1.show();
    if(start){
      for(int i=0; i<16; i++){
        for(int j=0; j<4; j++){
          if(cancionBailada[contador+i][j]){
            switch(j){
              case 0:
                pantalla1.setPixelColor(i,colorL);
                break;
              case 1:
                pantalla1.setPixelColor(i+16,colorU);
                break;
              case 2:
                pantalla1.setPixelColor(i+32,colorR);
                break;
              case 3:
                pantalla1.setPixelColor(i+48,colorD);
                break;
            }
          }
        }
      }
      pantalla1.show();
      delay(tiempo);
      contador++;
      //nos salimos cuando hemos recorrido las filas de la cancion +16
      if(contador==(NUMPASOS+16)){
        terminarJuego();
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

void isrleft(){
  //Serial.println("LEFT");
  if(start){
    if(pantalla1.getPixelColor(0)==colorL){
      puntos++;
    }
  }else{
    reportarseOnline();
  }
}


void isrup(){
  //Serial.println("UP");
  if(start){
    if(pantalla1.getPixelColor(16)==colorU){
      puntos++;
    }
  }else{
    reportarseOnline();
  }
}

void isrright(){
  //Serial.println("RIGHT");
  if(start){
    if(pantalla1.getPixelColor(32)==colorR){
      puntos++;
    }
  }else{
    reportarseOnline();
  }
}

void isrdown(){
  Serial.println("DOWN");
  if(start){
    if(pantalla1.getPixelColor(48)==colorD){
      puntos++;
    }
  }else{
    reportarseOnline();
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
