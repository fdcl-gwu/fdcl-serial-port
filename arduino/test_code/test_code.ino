void setup() {
  Serial.begin(9600);
}

void loop() {
  char line[] = "123";
  Serial.println(line);
  delay(100);
}
