/*
  Rui Santos
  Complete project details at our blog.
    - ESP32: https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
    - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-firebase-realtime-database/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/

#include <ESP8266WiFi.h>
// esp8266 헤더
#include <SoftwareSerial.h>
// 통신 헤더
#include <Firebase_ESP_Client.h>
// 파이어베이스 esp 연결 헤더
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "ESPERS" // wifi 이름
#define WIFI_PASSWORD "espers02399" // wifi 비밀번호

// Insert Firebase project API Key
#define API_KEY "AIzaSyBPQS1JFK4JRpGMy7T59-ZU68yIQXNwfxg"
// 파이어 베이스 API 키
// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://closet-seoul-default-rtdb.firebaseio.com/" 
// 파이어 베이스 URL 주소
//Define Firebase Data object
FirebaseData fbdo; // 파이어베이스 데이터 객체 생성
FirebaseAuth auth; // 접근 권한, 접근 제어(명령) 객체 생성
FirebaseConfig config; //??
FirebaseJson json;

SoftwareSerial serial_uno_mode(D6,D5); // RX, TX

 int c_mode=0;
int c_temp=0;
int c_humi=0;
bool signupOK = false;


void setup() {
serial_uno_mode.begin(115200);
  Serial.begin(115200); // 아두이노 통신 속도 115200
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // wifi 연결
  Serial.print("Connecting to Wi-Fi"); // 연결 확인문
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print(".");
   // serial_uno.print(".");
    delay(300);
  } // 연결 될 때 까지 기다리기
  Serial.println();
  //serial_uno.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP()); // wifi IP 출력
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY; // API 키 등록

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL; // url 연결

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    //serial_uno.println("ok");
    signupOK = true;
  } // 연결 확인
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  } 

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
    if (Firebase.ready() && signupOK ) {
    //명령
    if (Firebase.RTDB.getInt(&fbdo, "/mode")) {
        c_mode=fbdo.intData();
       Serial.print("  mode : "); Serial.println(c_mode);
        if(c_mode!=0)
        {
            serial_uno_mode.write(c_mode);
            json.set("/mode",0);
            Firebase.RTDB.setJSON(&fbdo,"/",&json);
        }
    }
    else {
        
      Serial.println(fbdo.errorReason());
    }


  
    
    delay(100);
}
}
