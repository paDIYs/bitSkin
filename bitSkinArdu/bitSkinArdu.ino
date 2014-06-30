int encoderPin1 = 2;
int encoderPin2 = 3;

const int buttonPin = 7;
int lastVal = 0;
int Val = 0;
int mode = 0;


volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void setup() {
  Serial.begin (9600);
  
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

}

void loop(){ 
  
  Val = digitalRead(buttonPin);

  if (Val != lastVal) {
    if (Val == LOW) {
      mode++;
    }
  }
  lastVal = Val;

  switch (mode) {
    case 1:
      Serial.print("a,");
      Serial.println(encoderValue);
      break;
    case 2:
      Serial.print("b,");
      Serial.println(encoderValue);
      break;
    case 3:
      Serial.print("c,");
      Serial.println(encoderValue);
      break;
    case 4:
      mode = 0;
      break;
  }
  delay(100);
  //Do stuff here

  //Serial.println(encoderValue);
  //delay(200); //just here to slow down the output, and show it will work  even during a delay
}


void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

// here you can find more informations about work on rotary encoderhttp://bildr.org/2012/08/rotary-encoder-arduino/
// a great work wich is based the reading of the rotary in this work
