#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "WArg-ssvAMLsTIsFXVLnASDhFRQliHop"; // Your Blynk auth token
char ssid[] = "sanjaykumar"; // Your WiFi network name
char pass[] = "23456789"; // Your WiFi network password

// Motor A connections
int IN1 = 13;
int IN2 = 12;
int EN1=26;

// Motor B  connections
int IN3 = 14;
int IN4 = 27;
int EN2=33;

//speed
int speed=190;
int engine_state=1;
int ENGINE_ON=4;

int in1,in2,in3,in4;

int x = 50;
int y = 50;


BlynkTimer timer;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1,OUTPUT);
  pinMode(EN2,OUTPUT);

  pinMode(ENGINE_ON,INPUT);
  //Inital condition
  in1=in2=in3=in4=1;
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);  


 
 //pwm config ~ 20k frequency
    ledcSetup(0,20000,8);//Motor A
    ledcSetup(1,20000,8);//Motor B
    ledcAttachPin(EN1,0);
    ledcAttachPin(EN2,1);
 
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  if(Blynk.connected())
    Serial.println("Successfully connected to Blynk"); 
  timer.setInterval(1000L, checkConnection); // Check connection every 1 second
}

void loop() {
   
  Blynk.run();
  timer.run();
  
  if( Serial.available()){ 
    char state=Serial.read();
    Serial.println(state);
  
    if(state=='0'){
      engine_state=0;
      ledcWrite(0,speed); 
      ledcWrite(1,speed);

      digitalWrite(IN1, 1-in1);
      digitalWrite(IN2, 1-in2);
      digitalWrite(IN3, 1-in3);
      digitalWrite(IN4, 1-in4);

      delay(120);
      in1=in2=in3=in4=0;
      digitalWrite(IN1,in1);
      digitalWrite(IN2,in2);
      digitalWrite(IN3,in3);
      digitalWrite(IN4,in4);  

    }
  }

  
  if(digitalRead(ENGINE_ON)==1){
    Serial.println("high");
    engine_state=1;
  }
  
 smartcar();
  
}

void checkConnection() {
  if (!Blynk.connected()) {
    Serial.println("Lost connection...");
    WiFi.disconnect();
    delay(1000);
    WiFi.begin(ssid, pass);
    Blynk.begin(auth, ssid, pass);
  }
  
}

 

 

void smartcar() {
  if (y > 80 && engine_state==1) {//forward
    
    in1=HIGH;
    in2=LOW;
    in3=HIGH;
    in4=LOW; 
    ledcWrite(0,speed);//Due to indifference in voltage
    ledcWrite(1,speed);
    digitalWrite(IN1, in1);
    digitalWrite(IN2, in2);
    digitalWrite(IN3, in3);
    digitalWrite(IN4, in4);
    
  } 
  else if (y < 20 && engine_state==1) {//backward
    in1=LOW;
    in2=HIGH;
    in3=LOW;
    in4=HIGH;
    ledcWrite(0,speed);
    ledcWrite(1,speed);
    digitalWrite(IN1, in1);
    digitalWrite(IN2, in2);
    digitalWrite(IN3, in3);
    digitalWrite(IN4, in4);
  } 
  else if (x < 30 && engine_state==1) {//left turn
    in1=LOW;
    in2=HIGH;
    in3=HIGH;
    in4=LOW;
    ledcWrite(0,175);
    ledcWrite(1,185);
    digitalWrite(IN1, in1);
    digitalWrite(IN2, in2);
    digitalWrite(IN3, in3);
    digitalWrite(IN4, in4);
  }
  else if (x > 70 && engine_state==1) {//Right Turn
    in1=HIGH;
    in2=LOW;
    in3=LOW;
    in4=HIGH;
    ledcWrite(0,175);
    ledcWrite(1,185);
    digitalWrite(IN1, in1);
    digitalWrite(IN2, in2);
    digitalWrite(IN3, in3);
    digitalWrite(IN4, in4);
  }
 
  else if (x < 70 && x > 30 && y < 70 && y > 30) {//Stop the vehicle
    in1=LOW;
    in2=LOW;
    in3=LOW;
    in4=LOW;
   
    
    digitalWrite(IN1, in1);
    digitalWrite(IN2, in2);
    digitalWrite(IN3, in3);
    digitalWrite(IN4, in4);
  }
}
BLYNK_WRITE(V0) { // Control speed of both motor
  speed = param.asInt();
 

  }

BLYNK_WRITE(V1)
{
    x = param.asInt();
  Serial.print("x: ");
  Serial.println(x);
 
}
BLYNK_WRITE(V2){
  y=param.asInt();
  Serial.print("y: ");
  Serial.println(y);
 
}
BLYNK_WRITE(V3) { // Control engine state
  engine_state = param.asInt();
 
 }

  
