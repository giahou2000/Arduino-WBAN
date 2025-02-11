#define LED_pin A1
#define period 100

char* string = "This is a test transmission";
int string_length;

void setup() {
  // put your setup code here, to run once:

  pinMode(LED_pin, OUTPUT);
  string_length = strlen(string);

}

void loop() {
  // put your main code here, to run repeatedly:

  for(int j = 0 ; j < string_length ; j++){
    digitalWrite(LED_pin, LOW);
    delay(period);

    for(int i = 0 ; i < 8 ; i++){
      digitalWrite(LED_pin, string[j](0x01 << i)!=0);
      delay(period);
    }

    digitalWrite(LED_pin, HIGH);
    delay(period);
  }

  delay(1000);

}