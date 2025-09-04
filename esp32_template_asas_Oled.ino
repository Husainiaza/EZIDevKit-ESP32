/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/
//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------
#include <WiFi.h>
#include <MQTT.h>
#include <Adafruit_SSD1306.h>
//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

#define relay01     26 
#define relay02     27
#define buzzer      25
#define SensorDS18  15 // pin sambungan ke DS18B20 (ONEWIRE)
#define sensorLDR   36
#define sensorTilt  4
#define SensorVolt  35

//---Penentuan Saiz Skrin OLED --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// ~~~~~~~~~~~~~~~~~~~~ PENTING ~~~~~~~~~~~~~~~~~~~~~~~~
// ------ Sila edit nama atau ID ikut keperluan --------
#define Client_Id   "id_anda___"      // masukan nama ID dan mestilah unik
#define NamaBroker  "broker.emqx.io"
#define namaSSID    "IoT"
#define SSIDpwd     "iot@kksj2023"

// ~~~~~~~~~~~~~~~~~~~  TAMMAT   ~~~~~~~~~~~~~~~~~~~~~~~


//-----c.  - ISTIHAR  constant dan pembolehubah------------------------------
//---Penetapan nama Pembolehubah yg diumpukkan kepada satu nilai awal  --
const char ssid[] = namaSSID;
const char pass[] = SSIDpwd;

//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
unsigned long lastMillis = 0;

//-----d. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

WiFiClient net;
MQTTClient client;

// Istihar objek bagi Module OLED Display - SSD1306 
Adafruit_SSD1306 paparOled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//##################  Seksyen 1 - TAMAT #############################
//--------------FUNCTION----------------------------

void connect() {

  int mqtt_attempts = 0;

  Serial.println("penyambungan ke WIFI... ");
  Serial.print("SSID: ");
  Serial.println(namaSSID);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("sambungan ke WiFi berjaya!...");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  
  } else {
    Serial.println();
    Serial.println(" sambungan ke WiFi GAGAL!");
    Serial.println("Semak credentials dan cuba sekali lagi.");
    while(1) {
      delay(1000); // Stop execution if WiFi fails
    }
  }

  // Initialize MQTT client
  Serial.print("Penyambungan ke broker MQTT : ");
  Serial.println(NamaBroker);
  //Serial.print("\nconnecting...");
  while (!client.connect(Client_Id)) {
    Serial.print(".");
    delay(1000);
  }

   if (client.connect(Client_Id)) 
    {
      Serial.println("penyambungan ke MQTT broker BERJAYA!");
      Serial.print("Client ID: ");
      Serial.println(Client_Id);
      
    } 
    else {
      Serial.print(" FAILED! Error: ");
      Serial.println(client.lastError());
      delay(2000);
      mqtt_attempts++;
    }

  //Serial.println("\nconnected!");

  // -- sila tambah kawalan topic yg perlu subcribe disini ---
  client.subscribe("topicAnda/buzzer");
  client.subscribe("topicAnda/relay1");
  client.subscribe("topicAnda/relay2");
  // -- tambah subcribe disini ---
}


void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);
  
   Serial.print(String(topic));
   Serial.print(" : ");
   Serial.println(payload);
 
  //==============================================================
    if(String(topic) == "topicAnda/buzzer") 
    {
      if(payload =="on")
      {
      digitalWrite(buzzer,HIGH);
      Serial.println("Buzzer ON");
      }
      
      else if(payload =="off")
      {
        digitalWrite(buzzer,LOW);
        Serial.println("Buzzer OFF");
      }
  } 
  //==========================Relay 1 Control ========================
   if(String(topic) == "topicAnda/relay1") 
    {
      if(payload =="on")
      {
      digitalWrite(relay01,HIGH);
      Serial.println("RELAY 1 ON");
      }
      
      else if(payload =="off")
      {
        digitalWrite(relay01,LOW);
        Serial.println("RELAY 1 OFF");
      }
  } 
 
  //   ----Tulis Kod Kawalan ( subsribe here ) -------


  //--------------------------- Relay Control --------------------
}


//###################################################
//==================  Seksyen 2 - Fungsi Setup ======================
//-------------------------------------------------------------------


void setup() {

  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT); 
 
  Serial.begin(115200); // initialize serial
 
  if(!paparOled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
 
 
  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);
  client.onMessage(messageReceived);
  connect();

  paparOled.clearDisplay();
  paparOled.setTextSize(1);
  paparOled.setTextColor(WHITE);
  paparOled.setCursor(0,0);
  paparOled.println("---  ESI-DEVKIT  ---");
  paparOled.setCursor(0,10);
  paparOled.println("K. Komuniti Sbg Jaya");
  paparOled.setCursor(0,20);
  paparOled.println("--------------------");
  paparOled.display();
  delay(3000);
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


  //------SENSOR 1------------------------------------------------
  
  //=========================== end sensor 1 =====================
 
 //------SENSOR 2-------------------------------------------------------------
   
 //=========================== end sensor 2 =====================

  }

}

//##################  Seksyen 3 - TAMAT #############################
