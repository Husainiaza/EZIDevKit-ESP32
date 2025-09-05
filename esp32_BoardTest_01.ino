/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/
//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------

//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

#define relay01     26  // digital OUTPUT - RELAY 1
#define relay02     27  // digital OUTPUT - RELAY 2
#define buzzer      25  // digital OUTPUT - BUZZER
#define SensorDS18  15  // pin ke DS18B20 (ONEWIRE) sensor Suhu
#define sensorLDR   36  // analog INPUT   - Sensor Cahaya
#define sensorTilt  4   // digital Input  - Sensor Tilt
#define SensorVolt  35  // analog INPUT   - Sensor Voltan

//###################################################################
//==================  Seksyen 2 - Fungsi Setup ======================
//-------------------------------------------------------------------

void setup() {

  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT); 
  pinMode(sensorTilt, INPUT);
 
  Serial.begin(115200); // initialize serial
}

//##################  Seksyen 2 - TAMAT #############################
//==============  Seksyen 3 - Fungsi Utama (LOOP) ===================
//-------------------------------------------------------------------

void loop() {

  digitalWrite(relay01,HIGH);
  delay (500);
  digitalWrite(relay02,HIGH);
  delay (500);
  digitalWrite(relay01,LOW);
  digitalWrite(relay02,LOW);
  delay (500);
  digitalWrite(relay01,HIGH);
  digitalWrite(relay02,LOW);
  delay (500);
  digitalWrite(relay01,LOW);
  digitalWrite(relay02,HIGH);
  delay (500);
  digitalWrite(relay01,LOW);
  digitalWrite(relay02,LOW);
  digitalWrite(buzzer,HIGH);
  delay (1000);
  digitalWrite(buzzer,LOW);
  delay (500);

  int dataTilt = digitalRead(sensorTilt);
  Serial.print(" Bacaan sensor TILT   :");
  Serial.println(dataTilt);

  int dataCahaya = analogRead(sensorLDR);
  Serial.print(" Bacaan sensor Cahaya :");
  Serial.println(dataCahaya);

}

//##################  Seksyen 3 - TAMAT #############################
