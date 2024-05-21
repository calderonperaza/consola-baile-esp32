//este es un ejemplo de una conexion a un servidor mqtt
//utilizaremos la libreria mqtt de Joel Gaehwiler
//https://github.com/256dpi/arduino-mqtt

#include <WiFi.h>
#include <MQTT.h>
#define LEFT 16
char equipo[]="PIKORO";

const char ssid[] = "MICROPROGRAMACION";
const char pass[] = "12345678";

WiFiClient net;
MQTTClient client;


void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting a mqtt...");
  while (!client.connect(equipo, "", "")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\n MQTT connected!");

  client.subscribe("BAILE/BAILE");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  pinMode(LEFT,INPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, pass);


  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  //aqui ponemos la IP del servidor mqtt
  client.begin("192.168.1.2", net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  //publicaremos un mensaje cuando se presione el boton izquierdo
  if(digitalRead(LEFT)==HIGH){
    //client.publish("BAILE/EQUIPOS", "LEFT");
    //publicamos el nombre del equipo
    client.publish("BAILE/EQUIPOS", equipo);
    delay(1000);
  }

}
