long numberMillisOverflows = 0;

#define _debug 0

#define outPin 9
bool start = false;
int intensity = 0;

#if _debug 
  #define dprintf(string) Serial.println(string)
  #define dprint(string) Serial.print(string)
#else
  #define dprintf(string)
  #define dprint(string)
#endif


unsigned long toDay = 24;
unsigned long toHour = 60;
unsigned long toMinute = 60;
unsigned long toSecond = 1000;

///////////////////////////////////////////////////////////////////
// Time conversion

unsigned long hourToMs(int hour){
  return hour*toHour*toMinute*toSecond;
}

unsigned long minToMs(int minute){
  return minute*toMinute*toSecond;
}

unsigned long secToMs(int sec){
  return sec*toSecond;
}

///////////////////////////////////////////////////////////////////
// Clock

unsigned long offsetHour = hourToMs(20);
unsigned long offsetMinute = minToMs(17);
unsigned long offsetSecond = secToMs(45);

 
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


///////////////////////////////////////////////////////////////////
// Tasks

struct taskDefinition{
  long lastUpdate = 0;
  long period = 0;
};

enum taskID{
  startIncreaseLight,
  increaseIntensity
};

taskDefinition task[2];

void setLastUpdate(int id){
  task[id].lastUpdate = millis();
}

bool isCalled(int id){
  if(millis()>(task[id].lastUpdate + task[id].period)){
      setLastUpdate(id);
      return true;
  } else {
    return false;
  }
}



void setup() {
  // put your setup code here, to run once:
  #if _debug
    Serial.begin(9600);
  #endif

  pinMode(outPin, OUTPUT);
  task[startIncreaseLight].period = minToMs(5);
  task[increaseIntensity].period = 2353;//7058; //equals 30 min from 0 to 255
  dprintf(
    "Offset Hour: " + String(offsetHour) + 
    " Offset Minute " + String(offsetMinute)
    );
  dprintf("begin");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(isCalled(startIncreaseLight)){
    start = true;
    dprintf("enabled start");
  }
  
  if(isCalled(increaseIntensity) && start && intensity < 256){
    intensity = intensity +1;
    dprintf("increase intensity");
  }
  
  analogWrite(intensity, outPin);
  dprint("intensity: ");dprintf(intensity);
  //dprintf("Current time: " + String(getHours()) + ":" + String(getMinutes()) + ":" + String(getSeconds()) + ":" + String(getMilliseconds()) + "             millis: " + String(millis()));
  delay(200);
}
