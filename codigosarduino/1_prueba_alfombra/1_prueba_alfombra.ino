#define LEFT 16
#define UP 17
#define RIGHT 25
#define DOWN 26

//Debes colocar una resistencia de 10k
//El voltaje + es de 3.3V

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
}

void loop(){

}

void isrleft(){
  Serial.println("LEFT");
}

void isrup(){
  Serial.println("UP");
}

void isrright(){
  Serial.println("RIGHT");
}

void isrdown(){
  Serial.println("DOWN");
}


