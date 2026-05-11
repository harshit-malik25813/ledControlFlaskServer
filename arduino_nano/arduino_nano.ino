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
    String msg = Serial.readStringUntil("\n"); // To prevent it from resetting
    msg.trim(); // Meant to remove any whitespace
    
    // If user asks to turn on the light
    if(msg == "ON")
    {
      digitalWrite(ledPin, HIGH);

    }
    // If user asks to turn off the light
    else if(msg == "OFF")
    {
      digitalWrite(ledPin, LOW);
    }
    // If user asks to blink the light
    else if(msg == "BLINK")
    {
      for(int i = 0; i < 5; i++)
      {
        digitalWrite(ledPin, LOW);
        delay(500);
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
      }
    }
    
  }
}
