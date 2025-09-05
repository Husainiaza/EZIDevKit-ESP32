/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/
//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DallasTemperature.h>
#include <OneWire.h>

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

//---Penentuan Saiz Skrin OLED --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Istihar objek bagi Module OLED Display - SSD1306 
Adafruit_SSD1306 paparOled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Istihar objek bagi Module Sersor Suhu Dallas 18B20
OneWire oneWire(SensorDS18);
DallasTemperature sensors(&oneWire);

//###################################################################
//==================  Seksyen 2 - Fungsi Setup ======================
//-------------------------------------------------------------------

void setup() {

  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT); 
  pinMode(sensorTilt, INPUT);
 
  Serial.begin(115200); // initialize serial
  sensors.begin();    // initialize the DS18B20 sensor

   if(!paparOled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
 
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

 //--- sensor TilT
  int dataTilt = digitalRead(sensorTilt);
  Serial.print(" Bacaan sensor TILT   :");
  Serial.println(dataTilt);

 //--- sensor LDR
  int dataCahaya = analogRead(sensorLDR);
  Serial.print(" Bacaan sensor Cahaya :");
  Serial.println(dataCahaya);

 //--- sensor SUHU (DS18B20)
  sensors.requestTemperatures(); 
  float dataSuhuC = sensors.getTempCByIndex(0);
  Serial.print(dataSuhuC);
  Serial.println(" ºC");

  paparOled.setTextColor(WHITE,BLACK);
  paparOled.setCursor(0,30);
  paparOled.print("LDR  :");
  paparOled.print(dataCahaya,1);
  paparOled.setCursor(0,40);
  paparOled.print("TILT :");
  paparOled.print(dataTilt);
  paparOled.setCursor(0,50);
  paparOled.print("SUHU :");
  paparOled.print(dataSuhuC);
  paparOled.display();
}

//##################  Seksyen 3 - TAMAT #############################
