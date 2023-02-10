int TIP120pin = 7; //for this project, I pick Arduino's PMW pin 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TIP120pin, OUTPUT); // Set pin for output to control TIP120 Base pin
  analogWrite(TIP120pin, 0);
  Serial.println("hello");
  analogWrite(TIP120pin, 255); // By changing values from 0 to 255 you can control motor speed
}

void loop() {
  // put your main code here, to run repeatedly:

}
