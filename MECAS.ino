 

// Define pins for the ultrasonic sensor
const int trigPin1 = 5;
const int echoPin1 = 4;
const int trigPin2 = 13;
const int echoPin2 = 15;
const int buzPin=12;
float current_time=0;
float prev_time=0,time_elapsed;
float current_dist1=0;
float prev_dist1=0,distance_elapsed1;
float current_dist2=0;
float prev_dist2=0,distance_elapsed2;
float v1,d1,t1;
float v2,d2,t2;
int i=0;

 

void setup() {
  // Set up the serial port for debugging output
  Serial.begin(9600);


 
  // Configure the ultrasonic sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
  pinMode(buzPin,OUTPUT);

   
  
}

void loop() {
      
      prev_time=current_time;
      current_time=millis()/1000.0;
      time_elapsed=current_time-prev_time;
      
      prev_dist1=current_dist1;
      prev_dist2=current_dist2;
        
      current_dist1 = distance(trigPin1,echoPin1);
      current_dist2=distance(trigPin2,echoPin2);
      
      distance_elapsed1=prev_dist1-current_dist1;
      distance_elapsed2=prev_dist2-current_dist2;
      
      if (distance_elapsed1==0)
          distance_elapsed1=0.1;
      if (distance_elapsed2==0)
          distance_elapsed2=0.1;
          
      v1=(distance_elapsed1/time_elapsed);
      v2=(distance_elapsed2/time_elapsed);
      
      d1=current_dist1;
      d2=current_dist2;
      
      
      t1=d1/v1;
      t2=d2/v2;


  
      /*Serial.print("distance1:");
      Serial.println(d1);
      Serial.print("distance2:");
      Serial.print(d2);
      Serial.println(" s");*/
     // Serial.println(time_elapsed);
      
      if ((t1>0 && t1<1)||(t2>0 && t2<1)){
          i=i+1;
          //Serial.println(i);
          if (i>1){
              digitalWrite(buzPin,19); 
              Serial.print(LOW);//Communicate with the ECU to stop the vehicle  
           
          }
      }
      else{
          i=0;
          digitalWrite(buzPin,0);
      }
      
      // Wait for a short time before taking the next measurement
      delay(100);
}
float distance(int trigPin,int echoPin){
 // Send a pulse to the ultrasonic sensor to trigger a measurement
    float distance;
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    // Read the duration of the echo pulse from the ultrasonic sensor
    long duration = pulseIn(echoPin, HIGH);
  
    // Convert the duration to distance in centimeters
     distance = duration / 58.0;
     if (distance > 15)
        distance = 15;
    //delay(100);
     return distance;
}
 

/*
float velocity(){
  float current_time=millis()/1000.0;
  float prev_time=0,t;
  float current_dist=distance();
  float prev_dist=0,d;
  float v=0;
  int c=0;
  
    
      
  
  return v;
}*/
