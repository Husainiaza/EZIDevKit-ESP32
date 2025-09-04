/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/
//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------
#include <WiFi.h>
#include <MQTT.h>
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
    Serial.print("sambungan ke MQTT broker...");
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
      Serial.println(payload);
      digitalWrite(buzzer,HIGH);
      Serial.println("Buzzer ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(buzzer,LOW);
        Serial.println("Buzzer OFF");
        
      }
  } 

  //==========================Relay Control ========================
   
 
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
  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);
  client.onMessage(messageReceived);
  connect();
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
  
  
 //------SENSOR 2-------------------------------------------------------------
   
 
 //-----------end ----------------------------h-----
  }
}

//##################  Seksyen 3 - TAMAT #############################
