void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

uint32_t water = 1023 - analogRead(A0);

  // print it
  Serial.print(F("The water level is: "));
  Serial.println(water);

  // wait a second
  delay(1000);


}
