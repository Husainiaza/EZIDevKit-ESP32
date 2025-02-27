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
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

//---Actuator and Relay  pin connection---
#define relay01     27 
#define relay02     26
#define buzzer      2
#define SensorSuhu  15 // pin sambungan ke DS18B20 (ONEWIRE)
#define sensorSoil   34


//---Penentuan nama Pembolehubah nama yg diumpukkan kepada satu nilai awal yg ditetapkan --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// ~~~~~~~~~~~~~~~~~~~~ PENTING ~~~~~~~~~~~~~~~~~~~~~~~~
// ------ Sila edit nama atau ID ikut keperluan --------
#define Client_Id   "andy64758765756474756688"
#define NamaBroker  "broker.hivemq.com"
#define namaSSID    "WIFIDELIMA";
#define SSIDpwd     "0987654321";
//#define namaSSID    "HaMa iPhone 13";
//#define SSIDpwd     "1234556790";
//#define namaSSID    "IoT";
//#define SSIDpwd     "iot@kksj2023";
// ~~~~~~~~~~~~~~~~~~~  TAMMAT   ~~~~~~~~~~~~~~~~~~~~~~~

//-----c.  - ISTIHAR  constant dan pembolehubah------------------------------
//---Penetapan nama Pembolehubah yg diumpukkan kepada satu nilai awal  --
const char ssid[] = namaSSID;
const char pass[] = SSIDpwd;

//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
unsigned long lastMillis = 0;
float dataSuhuC; // suhu dalam Celsius


//-----d. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

WiFiClient net;
MQTTClient client;

// Istihar objek bagi Module OLED Display - SSD1306 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Istihar objek bagi Module Sersor Suhu Dallas 18B20
OneWire oneWire(SensorSuhu);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


//##################  Seksyen 1 - TAMAT #############################

//==================  Seksyen 2 - Fungsi Setup ======================
//-------------------------------------------------------------------

void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT);

  Serial.begin(115200); // initialize serial

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);
  client.onMessage(messageReceived);


  sensors.begin();    // initialize the DS18B20 sensor

  connect();

/*
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
  delay(5000); */

  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" Irrigation  Systen ");
  lcd.setCursor(0,1);
  lcd.print("Andy UiTM P. Pinang ");
  
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
    sensors.requestTemperatures(); 
    dataSuhuC = sensors.getTempCByIndex(0);
    Serial.print(dataSuhuC);
    Serial.println(" ºC");
    client.publish("andy/suhu", String(dataSuhuC));

    lcd.setCursor(0,2);
    lcd.print("Bacaan Suhu :");
    lcd.setCursor(14,2);
    lcd.print(dataSuhuC);
    //----------------------------------------------------------------------------
  
    //------SENSOR seterusnya-------------------------------------------------------------
    int soilData = analogRead(sensorSoil);
    Serial.print(soilData);
    client.publish("andy/soil", String(soilData));

    lcd.setCursor(0,3);
    lcd.print("Bacaan Soil :");
    lcd.setCursor(14,3);
    lcd.print(soilData);

    if(soilData > 1000) {
      Serial.print(" Tanah Lembab ");
      digitalWrite(relay01,LOW);
      client.publish("andy/suhu/status", String("Tanah Lembab"));
       }
    
    else if(soilData <3000) {
      Serial.print(" Tanah Lembab ");
      digitalWrite(relay01,HIGH); }

    else{
       digitalWrite(relay01,LOW); 
       digitalWrite(buzzer,LOW);
       }

    }
     

    //----------------------------------------------------------------------------
  
  
}

//##################  Seksyen 3 - TAMAT #############################
