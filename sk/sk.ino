char data;


void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW); // Ensure buzzer is initially off
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    data = Serial.read();
    if (data == '1') {
      digitalWrite(8, HIGH); // Turn on the buzzer
    } else {
      digitalWrite(8, LOW); // Turn off the buzzer
    }
  }
}
