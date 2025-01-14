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
#include <Adafruit_SSD1306.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Adafruit_GFX.h>

//--------------------------------------------------------------------
//=  B. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------

//---Actuator and Relay  pin connection---
#define relay01     27 
#define relay02     26
#define buzzer      25
#define SensorSuhu  15 // pin sambungan ke DS18B20 (ONEWIRE)
#define sensorLDR   34

//---Penentuan nama Pembolehubah nama yg diumpukkan kepada satu nilai awal yg ditetapkan --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// ~~~~~~~~~~~~~~~~~~~~ PENTING ~~~~~~~~~~~~~~~~~~~~~~~~
// ------ Sila edit nama atau ID ikut keperluan --------
#define Client_Id   "nama_id_yang_dberi_mestilah_unik"
#define NamaBroker  "broker.hivemq.com"
#define namaSSID    "IoT";
#define SSIDpwd     "iot@kksj2023";
// ~~~~~~~~~~~~~~~~~~~  TAMMAT   ~~~~~~~~~~~~~~~~~~~~~~~

//=   C.  - ISTIHAR  constant dan pembolehubah------------------------------
//---Penetapan nama Pembolehubah yg diumpukkan kepada satu nilai awal  --
const char ssid[] = namaSSID;
const char pass[] = SSIDpwd;

//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
unsigned long lastMillis = 0;
float dataSuhuC; // suhu dalam Celsius


//-=   D. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

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
    sensors.requestTemperatures(); 
    dataSuhuC = sensors.getTempCByIndex(0);
    Serial.print(dataSuhuC);
    Serial.println(" ºC");
    client.publish("esidevkit/suhu", String(dataSuhuC));
    //----------------------------------------------------------------------------
  
    //------SENSOR seterusnya-------------------------------------------------------------
    
          // ---masuk kod sensor seterusnya -----

    //----------------------------------------------------------------------------
  
  }
}
//##################  Seksyen 3 - TAMAT #############################
