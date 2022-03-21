// plotChartWebServer
// Import required libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
// Replace with your network credentials
const char* ssid = "";
const char* password = "";
// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.51.190/ddm4341ea/post-esp-data.php";
// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key
String apiKeyValue = "tPmAT5Ab3j7F9";
float nA = 0, nB = 0, nC = 0,
      mA = 0, mB = 0, mC = 0;
String readNoiseA() {
  if (isnan(nA)) {
    Serial.println("Failed to read from noise sensor!");
    return "";
  } else {
    Serial.println("readNoiseA: ");
    Serial.print("\t");
    Serial.print(nA);
    return String(nA);
  }
}
String readNoiseB() {
  if (isnan(nB)) {
    Serial.println("Failed to read from noise sensor!");
    return "";
  } else {
    Serial.println("readNoiseB: ");
    Serial.print("\t");
    Serial.print(nB);
    return String(nB);
  }
}
String readNoiseC() {
  if (isnan(nC)) {
    Serial.println("Failed to read from noise sensor!");
    return "";
  } else {
    Serial.println("readNoiseC: ");
    Serial.print("\t");
    Serial.print(nC);
    return String(nC);
  }
}
String readMotionA() {
  if (isnan(mA)) {
    Serial.println("Failed to read from motion sensor!");
    return "";
  } else {
    Serial.println("readMotionA: ");
    Serial.print("\t");
    Serial.print(mA);
    return String(mA);
  }
}
String readMotionB() {
  if (isnan(mB)) {
    Serial.println("Failed to read from motion sensor!");
    return "";
  } else {
    Serial.println("readMotionB: ");
    Serial.print("\t");
    Serial.print(mB);
    return String(mB);
  }
}
String readMotionC() {
  if (isnan(mC)) {
    Serial.println("Failed to read from motion sensor!");
    return "";
  } else {
    Serial.println("readMotionC: ");
    Serial.print("\t");
    Serial.print(mC);
    return String(mC);
  }
}
// plotChartWebServer end

unsigned long now = millis();

// timerForSending
#define timeSecondsSending 5
unsigned long lastTriggerSending;
void IRAM_ATTR Sending() {
  lastTriggerSending = millis();
}
// timerForSending end

// ifTriggered
#define timeSeconds 5
boolean triggered = false;
const int micPinFlatA = 13, micPinFlatB = 25, micPinFlatC = 26,
          motionPinFlatA = 27, motionPinFlatB = 14, motionPinFlatC = 12;
// Timer: Auxiliary variables
unsigned long lastTriggerMicPinFlatA = 0, lastTriggerMicPinFlatB = 0, lastTriggerMicPinFlatC = 0,
              lastTriggerMotionPinFlatA = 0, lastTriggerMotionPinFlatB = 0, lastTriggerMotionPinFlatC = 0;
boolean startTimerMicPinFlatA = false, startTimerMicPinFlatB = false, startTimerMicPinFlatC = false,
        startTimerMotionPinFlatA = false, startTimerMotionPinFlatB = false, startTimerMotionPinFlatC = false;
// Sets sth activate and starts a timer
void IRAM_ATTR detectsNoiseFlatA() {
  Serial.println("NOISE DETECTED!!! from FlatA");
  startTimerMicPinFlatA = true;
  lastTriggerMicPinFlatA = millis();
  nA = 1;
  triggered = true;
}
void IRAM_ATTR detectsNoiseFlatB() {
  Serial.println("NOISE DETECTED!!! from FlatB");
  startTimerMicPinFlatB = true;
  lastTriggerMicPinFlatB = millis();
  nB = 1;
  triggered = true;
}
void IRAM_ATTR detectsNoiseFlatC() {
  Serial.println("NOISE DETECTED!!! from FlatC");
  startTimerMicPinFlatC = true;
  lastTriggerMicPinFlatC = millis();
  nC = 1;
  triggered = true;
}
void IRAM_ATTR detectsMovementFlatA() {
  Serial.println("MOTION DETECTED!!! from FlatA");
  startTimerMotionPinFlatA = true;
  lastTriggerMotionPinFlatA = millis();
  mA = 1;
  triggered = true;
}
void IRAM_ATTR detectsMovementFlatB() {
  Serial.println("MOTION DETECTED!!! from FlatB");
  startTimerMotionPinFlatB = true;
  lastTriggerMotionPinFlatB = millis();
  mB = 1;
  triggered = true;
}
void IRAM_ATTR detectsMovementFlatC() {
  Serial.println("MOTION DETECTED!!! from FlatC");
  startTimerMotionPinFlatC = true;
  lastTriggerMotionPinFlatC = millis();
  mC = 1;
  triggered = true;
}
// ifTriggered end





void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  // insertIntoMySQL
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Sending();
  // insertIntoMySQL end

  // KY-038
  pinMode(micPinFlatA, INPUT);
  pinMode(micPinFlatB, INPUT);
  pinMode(micPinFlatC, INPUT);
  // KY-038 end

  // PIRMotionSensor
  pinMode(motionPinFlatA, INPUT);
  pinMode(motionPinFlatB, INPUT);
  pinMode(motionPinFlatC, INPUT);
  // PIRMotionSensor end

}





void loop() {
  // Current time
  now = millis();

  // afterEvent
  // Turn off sth after the number of seconds defined in the timeSeconds variable
  if (startTimerMicPinFlatA && (now - lastTriggerMicPinFlatA > (timeSeconds * 1000))) {
    Serial.println("Noise sensor from FlatA auto reset...");
    startTimerMicPinFlatA = false;
    nA = 0;
  }
  if (startTimerMicPinFlatB && (now - lastTriggerMicPinFlatB > (timeSeconds * 1000))) {
    Serial.println("Noise sensor from FlatB auto reset...");
    startTimerMicPinFlatB = false;
    nB = 0;
  }
  if (startTimerMicPinFlatC && (now - lastTriggerMicPinFlatC > (timeSeconds * 1000))) {
    Serial.println("Noise sensor from FlatC auto reset...");
    startTimerMicPinFlatC = false;
    nC = 0;
  }
  if (startTimerMotionPinFlatA && (now - lastTriggerMotionPinFlatA > (timeSeconds * 1000))) {
    Serial.println("Motion sensor from FlatA auto reset...");
    startTimerMotionPinFlatA = false;
    mA = 0;
  }
  if (startTimerMotionPinFlatB && (now - lastTriggerMotionPinFlatB > (timeSeconds * 1000))) {
    Serial.println("Motion sensor from FlatB auto reset...");
    startTimerMotionPinFlatB = false;
    mB = 0;
  }
  if (startTimerMotionPinFlatC && (now - lastTriggerMotionPinFlatC > (timeSeconds * 1000))) {
    Serial.println("Motion sensor from FlatC auto reset...");
    startTimerMotionPinFlatC = false;
    mC = 0;
  }
  if (triggered && (now - lastTriggerSending > (timeSecondsSending * 1000))) {
    insertIntoMySQL();
    triggered = false;
    Sending();
  }
  // afterEvent end

  int val_digital = digitalRead(micPinFlatA);
  if (val_digital == HIGH) {
    detectsNoiseFlatA();
  }
  int val_digital2 = digitalRead(micPinFlatB);
  if (val_digital2 == HIGH) {
    detectsNoiseFlatB();
  }
  int val_digital3 = digitalRead(micPinFlatC);
  if (val_digital3 == HIGH) {
    detectsNoiseFlatC();
  }
  int val_digital4 = digitalRead(motionPinFlatA);
  if (val_digital4 == HIGH) {
    detectsMovementFlatA();
  }
  int val_digital5 = digitalRead(motionPinFlatB);
  if (val_digital5 == HIGH) {
    detectsMovementFlatB();
  }
  int val_digital6 = digitalRead(motionPinFlatC);
  if (val_digital6 == HIGH) {
    detectsMovementFlatC();
  }

}




//insertIntoMySQL
void insertIntoMySQL() {
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + nA + 
                              "&value2=" + nB + "&value3=" + nC + 
                             "&value4=" + mA + "&value5=" + mB + "&value6=" + mC;
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}
//insertIntoMySQL end
