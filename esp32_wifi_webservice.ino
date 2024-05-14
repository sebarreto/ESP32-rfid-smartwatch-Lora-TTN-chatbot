#include <WiFi.h> 
#include <HTTPClient.h> 
#include <SPI.h> 
#include <MFRC522.h> 

// name WiFi.
static const char *SSID = "XXXXXXXXXXXXXXX"; 
// Password WiFI. 
static const char *PASSWORD = "YYYYYYYYYYYYYYYYYYYYYYYYYYYY"; 

//IO pins
#define SS_PIN 5
#define RST_PIN 0
//Creción del objeto de tipo MFRC522.
MFRC522 mfrc522(SS_PIN, RST_PIN);

//URL API to consume
String serverName = "https://arioms.alwaysdata.net/XXXXXXXXXXXXXXXXXXXX/"; 
//To control execution.
unsigned long lastTime = 0; 
//Delay variable
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(9600); 
  //For WiFi
  WiFi.begin(SSID, PASSWORD);
  Serial.println("connecting...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected. IP: ");
  Serial.println(WiFi.localIP());
  //For RFID
  // initialize SPI bus
  SPI.begin();      
  // inicializar MFRC522
  mfrc522.PCD_Init();  
  Serial.println("Bring the card closer to the reader...");
  Serial.println();
}

void loop() {
  // New cards?
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Is there any card selected?
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on monitor screen
  Serial.print("Card, UID tag:");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "XX XX XX XX") //Use your own UID data.
  {
    Serial.println("Authorized access");
    Serial.println();
    consumo();
    delay(3000);
  }
 
 else   {
    Serial.println("Access denied");
    delay(3000);
  }
} 

void consumo() {
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + "XX XX XX XX" + "/1/" + "qjiXyaYa8A";

      String cleanedString = "";
      for (int i = 0; i < serverPath.length(); i++) {
        char c = serverPath.charAt(i);
        if (c != ' ') {
        cleanedString += c;
        }
      }
      
      // Initialize string for connection
      http.begin(cleanedString.c_str());
      
      // To authentication connections
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Enviamos HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Realease resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
  }
}