#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo1;  // Servo on pin 3
Servo servo2;  // Servo on pin 5
Servo servo3;  // Servo on pin 6
Servo servo4;  // Servo on pin 9
Servo servo5;  // Servo on pin 10
Servo servo6;  // Servo on pin 11

SoftwareSerial btSerial(2, 4);  // RX on pin 2, TX on pin 4

// To store the six servo values
int servoValues[6];  
int positionDelay = 1000;  // Seventh value: Delay between positions (default 1000 ms)
int loopDelay = 5;       // Eighth value: Delay for loop in servo speeds (default 5 ms)

// Define maximum number of positions to save
const int MAX_POSITIONS = 100;  // You can increase this based on memory availability
int savedPositions[MAX_POSITIONS][6];  // 2D array to store positions
int savedCount = 0;  // Track how many positions have been saved

bool stopMovement = false;  // Flag to stop playback

void setup() {
  Serial.begin(9600);  // Initialize Serial for debugging
  btSerial.begin(9600);  // Initialize Bluetooth communication
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(13, OUTPUT);
  // Attach servos to pins
  servo1.attach(11);
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(3);
  servo5.attach(6);
  servo6.attach(5);

  Serial.println("Setup complete. Waiting for Bluetooth data...");
}

void loop() {
  // Check if Bluetooth data is available to update servo positions
  if (btSerial.available() > 0) {
    String receivedData = btSerial.readStringUntil('\n');  // Read data until newline
    char command = receivedData.charAt(0);  // Get the first character as the command

    switch (command) {
      case 's':  // 's' for move servos
        processInput(receivedData.substring(1));  // Process the data after 's' to move servos
        break;
      case 'q':  // 'q' for saving current positions
        saveServoPositions();  // Save the current servo positions
        break;
      case 'r':  // 'r' for replaying saved positions
        playServoMovements();  // Play back saved servo positions
        break;
      default:
        Serial.println("Invalid command received.");
        break;
    }
  }
}

// Function to process the Bluetooth input and move servos
void processInput(String input) {
  int index = 0;
  int startIndex = 0;
  String temp;
  
  // Parse the six servo values
  for (int i = 0; i < 6; i++) {
    index = input.indexOf(',', startIndex);
    if (index != -1) {
      temp = input.substring(startIndex, index);
      servoValues[i] = temp.toInt();
      startIndex = index + 1;
    }
  }

  // Parse the seventh value: Delay between positions
  index = input.indexOf(',', startIndex);
  if (index != -1) {
    temp = input.substring(startIndex, index);
    positionDelay = temp.toInt();  // Store the delay between positions
    startIndex = index + 1;
  }

  // Parse the eighth value: Delay for loop controlling servo speeds
  temp = input.substring(startIndex);
  loopDelay = temp.toInt();  // Store the delay for the loop controlling servo speed

  // Debugging output
  Serial.print("Moving Servos to: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(servoValues[i]);
    Serial.print(" ");
  }
  Serial.print(" | Position Delay: ");
  Serial.print(positionDelay);
  Serial.print(" ms | Loop Delay: ");
  Serial.print(loopDelay);
  Serial.println(" ms");

  // Move servos to the new positions
  moveServosSmoothly();
}

// Function to move the servos smoothly with the loop delay
void moveServosSmoothly() {
  if (((servoValues[0] >= 0) && (servoValues[0] <= 180)) && ((servoValues[1] >= 0) && (servoValues[1] <= 180)) && ((servoValues[2] >= 0) && (servoValues[2] <= 180)) && ((servoValues[3] >= 0) && (servoValues[3] <= 180)) && ((servoValues[4] >= 0) && (servoValues[4] <= 180)) && ((servoValues[5] >= 0) && (servoValues[5] <= 180))) {
    for (int i = 0; i <= 100; i += 10) {  // Modify the increment for smoother speed control
      servo1.write(map(i, 0, 100, servo1.read(), servoValues[0]));
      servo2.write(map(i, 0, 100, servo2.read(), servoValues[1]));
      servo3.write(map(i, 0, 100, servo3.read(), servoValues[2]));
      servo4.write(map(i, 0, 100, servo4.read(), servoValues[3]));
      servo5.write(map(i, 0, 100, servo5.read(), servoValues[4]));
      servo6.write(map(i, 0, 100, servo6.read(), servoValues[5]));
      delay(loopDelay);  // Use the loop delay to control the speed
    }
  } else {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
  }
}

// Function to save the current servo positions
void saveServoPositions() {
  if (savedCount < MAX_POSITIONS) {
    digitalWrite(A0, HIGH);
    for (int i = 0; i < 6; i++) {
      savedPositions[savedCount][i] = servoValues[i];  // Store current servo positions
    }
    savedCount++;
    Serial.print("Position saved. Total saved: ");
    Serial.println(savedCount);
    digitalWrite(A0, LOW);
  } else {
    Serial.println("Memory full! Can't save more positions.");
  }
}

// Function to play the saved servo positions
void playServoMovements() {
  digitalWrite(A1, HIGH);
  Serial.println("Playing saved movements...");
  stopMovement = false;  // Reset stop flag

  for (int i = 0; i < savedCount && !stopMovement; i++) {
    // Move servos to the saved positions
    servo1.write(savedPositions[i][0]);
    servo2.write(savedPositions[i][1]);
    servo3.write(savedPositions[i][2]);
    servo4.write(savedPositions[i][3]);
    servo5.write(savedPositions[i][4]);
    servo6.write(savedPositions[i][5]);

    Serial.print("Moving to saved position: ");
    Serial.println(i + 1);

    delay(positionDelay);  // Add delay between each movement
  }

  digitalWrite(A1, LOW);
}