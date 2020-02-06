int ledPin1 = 6;
int ledPin2 = 9;
int ledPin3 = 11;
String input;


void setup() {
  Serial.begin(9600);
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
}

void loop() {
  while (Serial.available()>0){
  delay(10);
    input = Serial.readString();
    Serial.println(input);
    }
  if( input == "p1"){  
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 17) {
    analogWrite(ledPin1, fadeValue);
    delay(30);
  }
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 17) {
    analogWrite(ledPin2, fadeValue);
    delay(10);
  }
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 17) {
    analogWrite(ledPin3, fadeValue);
    delay(30);
  }
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 17) {
    analogWrite(ledPin3, fadeValue);
    delay(30);
  }
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 17) {
    analogWrite(ledPin2, fadeValue);
    delay(30);
  }
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 17) {
    analogWrite(ledPin1, fadeValue);
    delay(30);
  }
  }
  else if(input == "l1"){
    digitalWrite(ledPin1 , HIGH);
    
  }
  else if(input == "l2"){
    digitalWrite(ledPin2 , HIGH);
    
  }
  else if(input == "l3"){
    digitalWrite(ledPin3 , HIGH);
  }
  else if(input == "l3_off"){
    digitalWrite(ledPin3 , LOW);
  }
  else if(input == "l2_off"){
    digitalWrite(ledPin2 , LOW);
  }
  else if(input == "l1_off"){
    digitalWrite(ledPin1 , LOW);
  }
  else if(input == "p1_off"){
    digitalWrite(ledPin3 , LOW);
    digitalWrite(ledPin2 , LOW);
    digitalWrite(ledPin1 , LOW);
  }
}
