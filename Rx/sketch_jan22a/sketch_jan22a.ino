int lightintensity; 
void setup() {    
  pinMode(A0, INPUT);    
  Serial.begin(9600); 
} 
 
void loop() {    
  lightintensity = analogRead(A0);    
  Serial.println(lightintensity);    
  delay(100); 
}