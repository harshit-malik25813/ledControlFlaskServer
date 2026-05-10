const int ledPin = 5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    String msg = Serial.readString();
    if(msg == "ON")
    {
      digitalWrite(ledPin, HIGH);

    }
    else if(msg == "OFF")
    {
      digitalWrite(ledPin, LOW);
    }
    else if(msg == "BLINK")
    {
      for(int i = 0; i < 5; i++)
      {
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
      }
    }
    
  }
}
