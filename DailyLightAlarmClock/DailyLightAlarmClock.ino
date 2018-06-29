int outPin = 9;
int intensity = 0;
unsigned long lastupdateTime = 0;
unsigned long period = 7100;
unsigned long startTime = 27900000; //7,5h
void setup() {
  pinMode(outPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() > startTime && millis()>(lastupdateTime+period) && intensity < 255){
      intensity++;
      analogWrite(outPin, intensity);
      lastupdateTime = millis();
  }
  delay(100);
}
