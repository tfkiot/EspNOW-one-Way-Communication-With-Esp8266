#include <ESP8266WiFi.h>
#include <espnow.h>

#define led1 D1
#define led2 D4

// Structure to declare variable
typedef struct myStruct {
    bool a;
    bool b;
} myStruct;

// Create a myStruct called structObj
myStruct structObj;

// Callback function 
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&structObj, incomingData, sizeof(structObj));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("D1 button state: ");
  Serial.println(structObj.a);
  Serial.print("D3 button state: ");
  Serial.println(structObj.b);
  Serial.println();

 structObj.a ? digitalWrite(led1, HIGH) : digitalWrite(led1, LOW);
 structObj.b ? digitalWrite(led2, HIGH) : digitalWrite(led2, LOW);
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE); //set role
  esp_now_register_recv_cb(OnDataRecv); // set callback
}

void loop() {
  
}
