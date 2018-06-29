long numberMillisOverflows = 0;

unsigned long toDay = 24;
unsigned long toHour = 60;
unsigned long toMinute = 60;
unsigned long toSecond = 1000;

unsigned long offsetHour = 20*toHour*toMinute*toSecond;
unsigned long offsetMinute = 22*toMinute*toSecond;
unsigned long offsetSecond = 45*toSecond;

int getHours(){
  unsigned long factor = toDay*toHour*toMinute*toSecond;
  unsigned long milliseconds = (millis())%factor;
  milliseconds = (milliseconds + offsetHour + offsetMinute + offsetSecond)%factor;
  return milliseconds/toHour/toMinute/toSecond;
}

int getMinutes(){
  unsigned long factor = toHour*toMinute*toSecond;
  unsigned long milliseconds = (millis())%factor;
  milliseconds = (milliseconds + offsetMinute + offsetSecond)%factor;
  return milliseconds/toMinute/toSecond;
}

int getSeconds(){
  unsigned long factor = toMinute*toSecond;
  unsigned long milliseconds = (millis())%factor; 
  milliseconds = (milliseconds + offsetSecond)%factor;
  return milliseconds/toSecond;
}

int getMilliseconds(){
  return millis()%toSecond;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(
  "Offset Hour: " + String(offsetHour) + 
  " Offset Minute " + String(offsetMinute)
  );
  Serial.println("begin");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Current time: " + String(getHours()) + ":" + String(getMinutes()) + ":" + String(getSeconds()) + ":" + String(getMilliseconds()) + "             millis: " + String(millis()));
  delay(200);
}
