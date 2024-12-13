/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/

//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------

#include <WiFi.h>
#include <MQTT.h>
#include <Wire.h>
#include <SPI.h>
#include <OneWire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

//---Actuator and Relay  pin connection---
#define relay01     27 
#define relay02     26
#define buzzer      25
#define SensorSuhu  15 // pin sambungan ke DS18B20 (ONEWIRE)
#define MQ135 35
#define MQ09 34
#define DHTPIN 27          
#define DHTTYPE DHT11   

//---Penentuan nama Pembolehubah nama yg diumpukkan kepada satu nilai awal yg ditetapkan --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

int ledR = 5;
int ledB = 18;
int ledG = 19;


// ~~~~~~~~~~~~~~~~~~~~ PENTING ~~~~~~~~~~~~~~~~~~~~~~~~
// ------ Sila edit nama atau ID ikut keperluan --------
#define Client_Id   "nama_id_yang_dberi_mestilah_unik"
#define NamaBroker  "broker.hivemq.com"
#define namaSSID    "IoT";
#define SSIDpwd     "iot@kksj2023";
// ~~~~~~~~~~~~~~~~~~~  TAMMAT   ~~~~~~~~~~~~~~~~~~~~~~~

//-----c.  - ISTIHAR  constant dan pembolehubah------------------------------
//---Penetapan nama Pembolehubah yg diumpukkan kepada satu nilai awal  --
const char ssid[] = namaSSID;
const char pass[] = SSIDpwd;

//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
unsigned long lastMillis = 0;
float dataSuhuC; // suhu dalam Celsius

float h ;
float t ;
int valMq09;
int valMq135;  

//-----d. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------
LiquidCrystal_I2C lcd(0x27,20,4);
DHT dht(DHTPIN, DHTTYPE);

WiFiClient net;
MQTTClient client;

// Istihar objek bagi Module OLED Display - SSD1306 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Istihar objek bagi Module Sersor Suhu Dallas 18B20
OneWire oneWire(SensorSuhu);
DallasTemperature sensors(&oneWire);

//##################  Seksyen 1 - TAMAT #############################

//==================  Seksyen 2 - Fungsi Setup ======================
//-------------------------------------------------------------------

void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(ledR,OUTPUT);
  pinMode(ledB,OUTPUT);
  pinMode(ledG,OUTPUT);

  Serial.begin(115200); // initialize serial

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);  client.onMessage(messageReceived);


  sensors.begin();    // initialize the DS18B20 sensor
dht.begin();


  connect();
   
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  namakan projek anda  ");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("---  ESI-DEVKIT  ---");
  display.setCursor(0,10);
  display.println("K. Komuniti Sbg Jaya");
  display.setCursor(10,20);
  display.println("--------------------");
  display.display();
  delay(5000);
}
//##################  Seksyen 2 - TAMAT #############################


//==============  Seksyen 3 - Fungsi Utama (LOOP) ===================
//-------------------------------------------------------------------
void loop() {

 client.loop();
 delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

// publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
  lastMillis = millis();

    //------SENSOR 1-------------------------------------------------------------
    float t = dht.readTemperature(); 
    float h = dht.readHumidity();
    client.publish("aref/suhu", String(t));
    client.publish("aref/humid", String(h));
    //----------------------------------------------------------------------------
    valMq135 = analogRead(MQ135);
    Serial.print ("raw MQ135= ");
    Serial.println (valMq135);
    client.publish("aref/mq135", String(valMq135));
    //----------------------------------------------------------------------------
    
    for(int x = 0 ; x < 100 ; x++) 
    { 
      valMq09 = analogRead(MQ09);  } 
    
    valMq09 = (valMq09-50)/35;   
    Serial.print ("raw MQ9= ");
    Serial.println (valMq09); 
    client.publish("aref/mq09", String(valMq09));
 
    //------SENSOR seterusnya-------------------------------------------------------------
    
    if( valMq135 >= 2001 || valMq09 >= 60){
      digitalWrite(ledR,HIGH);
      digitalWrite(ledB,LOW);
      digitalWrite(ledG,LOW);
      digitalWrite(buzzer,HIGH);
      delay(1000);
      digitalWrite(ledR,LOW);
      digitalWrite(ledB,LOW);
      digitalWrite(ledG,LOW);
      digitalWrite(buzzer,LOW); }

    else if( valMq135 >= 1000 && valMq135 <= 2000 || valMq09 >= 41 && valMq09 <= 59){
      digitalWrite(ledR,LOW);
      digitalWrite(ledB,HIGH);
      digitalWrite(ledG,LOW);
      Serial.print ("test biru ");}

    else if( valMq135 < 1000 || valMq09 < 40 ){
      digitalWrite(ledR,LOW);
      digitalWrite(ledB,LOW);
      digitalWrite(ledG,HIGH);
      Serial.print ("test hijau "); }
   
  
    //----------------------------------------------------------------------------
  
  }
}

//##################  Seksyen 3 - TAMAT #############################


void paparanLCD() {
  
  lcd.setCursor(0,2);
  lcd.print("Co2 : ");
  lcd.setCursor(6,2);
  lcd.print(valMq135);
  lcd.setCursor(0,3);
  lcd.print("LPG : ");
  lcd.setCursor(6,3);
  lcd.print(valMq09);
}