String receivedMessage;

void setup() {
  Serial.begin(9600);    // Initialize the Serial monitor for debugging
  Serial1.begin(9600);   // Initialize Serial1 for sending data
}

void loop() {
  while (Serial1.available() > 0) {
    char receivedChar = Serial1.read();
    if (receivedChar == '\n') {
      Serial.println(receivedMessage);  // Print the received message in the Serial monitor
      receivedMessage = "";  // Reset the received message
    } else {
      receivedMessage += receivedChar;  // Append characters to the received message
    }
  }
}