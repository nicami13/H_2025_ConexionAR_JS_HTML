
int LDR= 33;
int VALOR;

void setup() {
  
  pinMode(LDR, INPUT);
  Serial.begin(115200);

}

void loop() {
  
  VALOR = analogRead(LDR);
  Serial.print("el val es: ");
  Serial.println(VALOR);
  delay(1000);

}
