
const int flamePin = 11;
int flame = HIGH;
unsigned long time;

void setup() {
  // put your setup code here, to run once:
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  flame = digitalRead(flamePin);
  if (flame== LOW){
 
    Serial.println("Safe");
    delay(100);
  }
  else {
Serial.println("Fire");
 delay(100);
  }
}
