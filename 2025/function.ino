void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(Client_Id)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe("esidevkit/buzzer");
  client.subscribe("esidevkit/relay1");
  client.subscribe("esidevkit/relay2");
  // -- tambah subcribe disini ---
 
}

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);
   Serial.println(payload);
  
  
   //==========================Buzzer Control ==========
  if(String(topic) == "esidevkit/buzzer") 
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
 //-------------------------- END --------------------

 //========================== Relay Control ==========
 //---- Relay 01 -----
  if(String(topic) == "esidevkit/relay1") 
  {
      if(payload =="on")
      {
        Serial.println(payload);
        digitalWrite(relay01,HIGH);
        Serial.println("relay01 ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay01,LOW);
        Serial.println("relay01 OFF");
      }
  }

  //---- Relay 02 -----
  if(String(topic) == "esidevkit/relay2") 
  {
      if(payload =="on")
      {
        Serial.println(payload);
        digitalWrite(relay02,HIGH);
        Serial.println("relay02 ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay02,LOW);
        Serial.println("relay02 OFF");
      }
  }
 //-------------------------- END --------------------
//==========================Device Control ===========
  
//   ----Tulis Kod Kawalan ( subsribe here ) -------

//--------------------------- END --------------------

}
