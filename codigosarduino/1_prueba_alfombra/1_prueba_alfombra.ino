#define LEFT 16
#define UP 17
#define RIGHT 25
#define DOWN 26

//Debes colocar una resistencia de 10k
//El voltaje + es de 3.3V

volatile bool left = false;
volatile bool up = false;
volatile bool right = false;
volatile bool down = false;

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
  if(left){
    Serial.println("LEFT");
    left = false;
  }
  if(up){
    Serial.println("UP");
    up = false;
  }
  if(right){
    Serial.println("RIGHT");
    right = false;
  }
  if(down){
    Serial.println("DOWN");
    down = false;
  }

}

void isrleft(){
  left = true;
}

void isrup(){
  up = true;
}

void isrright(){
  right = true;
}

void isrdown(){
  down = true;
}


