const int buttonPin[] = {3,4,5,6};
int buttonValue[] = {1,1,1,1};

void setup() {
  for(int i = 0; i < (sizeof(buttonPin) / sizeof(buttonPin[0])); i++){
    pinMode(buttonPin[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < (sizeof(buttonPin) / sizeof(buttonPin[0])); i++){
    buttonValue[i] = digitalRead(buttonPin[i]);
  }

  Serial.print("$ButtonBox:");
  for(int i = 0; i < (sizeof(buttonPin) / sizeof(buttonPin[0])); i++){
    if(i != 0){
      Serial.print(",");
    }
    Serial.print(buttonValue[i]);
  }
  Serial.println("");

  delay(10);
}
