
#include <Servo.h>
#include "FindNoLight.h"

Servo myServo;
const int sensorLed1 = A0;
const int sensorLed2 = A1;
const int sensorLed3 = A2;

int sensorValue[3];

Neural_Network *Network = new Neural_Network();

void setup() {
  randomSeed(analogRead(3));
  myServo.attach(3);
  Serial.begin(9600);

  int leds3[3] = {1000, 1000, 50};
  int leds2[3] = {1000, 50, 1000};
  int leds1[3] = {50, 1000, 1000};
  
    
  double cost_output; 
  
  for(int i = 0; i < 17000; i++){
    int random_point = random(0, 3);
    switch(random_point){
        case 0:
            cost_output = Network->back_propagation(leds1, 115);
            break;
        case 1:
            cost_output = Network->back_propagation(leds2, 90);
            break;
        case 2: 
            cost_output = Network->back_propagation(leds3, 65);
            break;
      }
      Serial.println(cost_output);
    }
}

void loop() {
  sensorValue[0] = analogRead(sensorLed1);
  delay(5);
  sensorValue[1] = analogRead(sensorLed2);
  delay(5);
  sensorValue[2] = analogRead(sensorLed3);
  delay(5);

  float output = Network->feed_forward(sensorValue);

  Serial.print("Sensor values: \t sensor1: ");
  Serial.print(sensorValue[0]);
  Serial.print("\t sensor2: ");
  Serial.print(sensorValue[1]);
  Serial.print("\t sensor3: ");
  Serial.println(sensorValue[2]);
  
  Serial.print("Neural Network angle output: \t");
  Serial.println(output);

  myServo.write((int)output);
  delay(20);
}
