#define LED_pin A1

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED_pin, HIGH);
  delay(1000);
  digitalWrite(LED_pin, LOW);
  delay(1000);

}
