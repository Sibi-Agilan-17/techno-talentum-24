#include <VirtualWire.h>
#include <ServoTimer2.h>

/* 
NOTE TO FUTURE SELF:
Using VirtualWire.h along with Servo.h creates a multiple definition conflict since both of 
them use the same timer (multiple references of __vector_11 found). This is solved by using 
ServoTimer2.h which is basically the same except the Servos are defined using the format

ServoTimer2 myServo; instead of 
Servo myServo;

Also dont use VirtualWire use RadioHead instead.
*/

#define Deg 5 // number of degrees to move the servo each time the command is received 

#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6

char command;

ServoTimer2 shoulderServo;
ServoTimer2 elbowServo;
ServoTimer2 wristServo;
ServoTimer2 clawServo;

int shoulderPos = 90;
int elbowPos = 90;
int wristPos = 90;
int clawPos = 90;

const int shoulderPin = 9;
const int elbowPin = 10;
const int wristPin = 11;
const int clawPin = 12;

void setup() {
  Serial.begin(19200);
  pinMode(OUTPUT, IN1);
  pinMode(OUTPUT, IN2);
  pinMode(OUTPUT, IN3);
  pinMode(OUTPUT, IN4);

  shoulderServo.attach(shoulderPin);
  elbowServo.attach(elbowPin);
  wristServo.attach(wristPin);
  clawServo.attach(clawPin);

  shoulderServo.write(shoulderPos);
  elbowServo.write(elbowPos);
  wristServo.write(wristPos);
  clawServo.write(clawPos);

  vw_setup(2000);  // Set the data rate in bits per second (baud rate)
  vw_set_rx_pin(2); // Set the digital pin for receiving data
  vw_rx_start();  // Start the receiver

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    if (buflen == sizeof(command)) {
      command = *(char *)buf;

      // Process the received command as needed
      switch (command) {
        case 'F':
          forward();
          break;
        case 'B':
          back();
          break;
        case 'L':
          left();
          break;
        case 'R':
          right();
          break;
        case 'S':
          Stop();
          break;
        
        case  'A':
          wristPos = constrain(wristPos + Deg, 0, 180);
          wristServo.write(wristPos);
          break;
        case 'Y':
          wristPos = constrain(wristPos - Deg, 0, 180);
          wristServo.write(wristPos);
          break;
        case 'D':
          shoulderPos = constrain(shoulderPos + Deg, 0, 180);
          shoulderServo.write(shoulderPos);
          //Serial.println(shoulderPos);
          break;
        case 'U':
          shoulderPos = constrain(shoulderPos - Deg, 0, 180);
          shoulderServo.write(shoulderPos);
          break;
        case 'C':
          clawPos = constrain(clawPos + Deg, 0, 180);
          clawServo.write(clawPos);
          break;
        case 'O':
          clawPos = constrain(clawPos - Deg, 0, 180);
          clawServo.write(clawPos);
          break;
        case 'V':
          elbowPos = constrain(elbowPos + Deg, 0, 180);
          elbowServo.write(elbowPos);
          break;
        case 'J':
          elbowPos = constrain(elbowPos - Deg, 0, 180);
          elbowServo.write(elbowPos);
          break;
      }
      delay(50);
      Serial.println("Received command: " + String(command));
    }
  }
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void back() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
