#define PD A0
#define THRESHOLD 170
#define period 100

bool previous_state;
bool current_state;
char ret = 0;
int voltage = 0;
int volt = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  voltage = analogRead(PD);
  current_state = (voltage > THRESHOLD ? true : false);

  if(!current_state && previous_state){
    ret = 0;
    delay(period*1.5);
    for(int i ; i < 8 ; i++){
      volt = analogRead(PD);
      bool temp = (volt > THRESHOLD ? true : false);
      ret = ret | temp << i;
    }
    char buff[2];
    aprintf(buff, "%c", ret);
    Serial.print(buff);
  }

  previous_state = current_state;
}


  int voltage = analogRead(PD);
  // bool bit = (voltage > THRESHOLD ? true : false);
  Serial.println(voltage);    
  delay(100); 