#include <VirtualWire.h>

int carjoyX;
int carjoyY;


int cranejoyX1;
int cranejoyY1;

int cranejoyX2;
int cranejoyY2;


char command;

void setup() {
  Serial.begin(115200);
  vw_setup(2000);  // Set the data rate in bits per second (baud rate)
  vw_set_tx_pin(12);
   // Set the digital pin for transmitting data
}

void loop() {
    carjoyX = analogRead(A0);
  carjoyY = analogRead(A3);
  
  cranejoyX1 = analogRead(A1);
  cranejoyY1 = analogRead(A4);
  
  cranejoyX2 = analogRead(A2);
  cranejoyY2 = analogRead(A5);
  
  // backward forward left right
  
  if (carjoyX < 300) {
    command = 'B'; 
  } else if (carjoyX > 700) {
    command = 'F'; 
  } else if (carjoyY < 300) {
    command = 'L'; 
  } else if (carjoyY > 700) {
    command = 'R'; 
  } 
  
  
  else if (cranejoyX1 < 300) {
    command = 'A'; // wrist left
  } else if (cranejoyX1 > 700) {
    command = 'Y'; // wrist right
  } else if (cranejoyY1 < 300) {
    command = 'D'; // shoulder down
  } else if (cranejoyY1 > 700) {
    command = 'U'; // shoulder up
  }


  else if (cranejoyY2 < 300) {
    command = 'C'; // claw close
  } else if (cranejoyY2 > 700) {
    command = 'O'; // claw open
  } else if (cranejoyX2 < 300) {
    command = 'V'; // elbow down
  } else if (cranejoyX2 > 700) {
    command = 'J'; // elbow up
  }
  
  else {
    command = 'S'; // 'S' for stop (centered joystick)
  }
  
  
  
  Serial.println(command);
  vw_send((uint8_t *)&command, sizeof(command));
  vw_wait_tx();  // Wait for the transmission to complete
  
  delay(100); // Adjust the delay as needed
}
