long numberMillisOverflows = 0;

#define _debug 1

#define outPin 9

#if _debug 
  #define dprintf(string) Serial.println(string);
#else
  #define dprintf(string)
#endif

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
  #if _debug
    Serial.begin(9600);
  #endif

  pinMode(outPin, OUTPUT);
  
  dprintf(
    "Offset Hour: " + String(offsetHour) + 
    " Offset Minute " + String(offsetMinute)
    );
  dprintf("begin");
}

void loop() {
  // put your main code here, to run repeatedly:
  dprintf("Current time: " + String(getHours()) + ":" + String(getMinutes()) + ":" + String(getSeconds()) + ":" + String(getMilliseconds()) + "             millis: " + String(millis()));
  delay(200);
}
