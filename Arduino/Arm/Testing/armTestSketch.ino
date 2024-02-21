#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Maximum number of characters in an incoming serial command
const byte maxCommandLength = 32;
char serialCommand[maxCommandLength];
byte commandLength = 0;

void setup() {
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  servo4.attach(12);
  Serial.begin(9600);
  // Send a start-up message
  Serial.println("Servo Controller Initialized");
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\n') {
      processCommand(serialCommand, commandLength);
      commandLength = 0;
    } else if (commandLength < maxCommandLength - 1) {
      serialCommand[commandLength++] = ch;
      serialCommand[commandLength] = '\0'; // Null-terminate the string
    }
  }
}

void processCommand(char* command, byte length) {
  int servoID, position;
  if (sscanf(command, "%d,%d", &servoID, &position) == 2) {
    position = constrain(position, 0, 270); // Ensure position is within a safe range
    switch (servoID) {
      case 1:
        servo1.write(position);
        Serial.print("Servo 1 set to ");
        break;
      case 2:
        servo2.write(position);
        Serial.print("Servo 2 set to ");
        break;
      case 3:
        servo3.write(position);
        Serial.print("Servo 3 set to ");
        break;
      case 4:
        servo4.write(position);
        Serial.print("Servo 4 set to ");
        break;
    }
    Serial.println(position); // Send the set position back over Serial
  } else {
    Serial.println("Invalid command"); // Provide feedback on invalid input
  }
}
