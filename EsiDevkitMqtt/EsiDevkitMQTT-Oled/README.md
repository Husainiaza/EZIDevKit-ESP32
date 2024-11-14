# **IoT MQTT**

## install MQTT Library
MQTT by Joel Gaehwiler

# SENSOR DS18B20 - Baca suhu

## Section 3 : void loop dengan if condition
```

DS18B20.requestTemperatures();       // arahan baca suhu
dataSuhuC = DS18B20.getTempCByIndex(0);  // nilai suhu disimpan dalam pembolehubah tempC
 
Serial.print("Temperature: ");
Serial.print(dataSuhuC);    
Serial.println("°C");
client.publish("topicAnda/suhu", String(dataSuhuC));

if (dataSuhuC < 25) {
    Serial.println(" suhu paras sejuk ");    
  }
  else if (dataSuhuC > 25 && dataSuhuC < 33 ) {
    Serial.println(" suhu paras normal ");  
    strcpy(statusSuhu, "suhu paras normal");
   // display.display();
  }

  else if (dataSuhuC > 33 && dataSuhuC < 41 ) {
    Serial.println("suhu paras panas ");   
    strcpy(statusSuhu, "suhu paras panas ");
    digitalWrite(buzzer,HIGH);
    delay(10);
    digitalWrite(buzzer,LOW);
    delay(100);
   
  }

  else if (dataSuhuC > 40 ) {
  Serial.println("suhu paras bahaya ");    
  strcpy(statusSuhu, "suhu paras bahaya");
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
 
  }

  else {
    Serial.print(" bacaan suhu tidak normal ");  
    digitalWrite(buzzer,LOW);
    digitalWrite(buzzer,LOW);
  }
```


# SENSOR DHT22 (AM2301) - baca suhu dan humiditi
## Section 1: Header
```
#include "DHT.h"
```

```
#define DHTPIN 4     
#define DHTTYPE DHT21

DHT dht(DHTPIN, DHTTYPE);
```
## Section 2 : void setup
```
dht.begin();
```
## Section 3 : void loop
```
float humid = dht.readHumidity();
float temp = dht.readTemperature();

Serial.print("Humidity: ");
Serial.println(humid);
Serial.print("Temperature: ");
Serial.print(temp);
Serial.println("°C ");

client.publish("topicAnda/temp", String(temp));  
client.publish("topicAnda/humid", String(humid));  

```

# ANALOG SENSOR INPUT

## Section 3 : void loop - baca semua jenis analog sensor
### Contoh analog sensor LDR
```
dataAnalog = analogRead(sensorLDR);
Serial.print("Cahaya: ");
Serial.println(dataAnalog);  

client.publish("topicAnda/ldr", String(dataLDR));  
```
# Kawalan MQTT (subscribe)
## Letak kod ini dalam fungsi - void messageReceived()
## Kawalan Buzzer ( Subscribe )
```
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
```
## Kawalan Relay  ( Subscribe )
```

  if(String(topic) == "topicAnda/socket1") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay01,HIGH);
      Serial.println("socket1 ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay01,LOW);
        Serial.println("socket1 OFF");
      }
  }

   if(String(topic) == "topicAnda/socket2") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay02,HIGH);
      Serial.println("socket2 ON");
  
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay02,LOW);
        Serial.println("Buzzer OFF");
     
      }
  }
```

