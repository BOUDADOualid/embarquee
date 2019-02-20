/*
 * Description: Sends sensor value to MySQL database (by inserting values into a URL for PHP to GET) then goes into deep sleep for a minute.
 * Author: Matthew W. - www.mwhprojects.com - www.github.com/mwhprojects/NodeMCU-MySQL
 */
// Sensor pin number

 #define pinA A0

// Wake from sleep, in seconds.
#define wakeuptime 30

 
#include <ESP8266WiFi.h>
const char* ssid  = "BDIO";
const char* password = "ARDWINO300";
  const char* host = "192.168.1.111";
  const char* passcode = "test";
  float sensor_volt;
  float RS_gas;
  float ratio;
  int sensorValue;
  const float R0 = 0.57;



void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}
void loop() {
  
  // Connect to host
  Serial.print("Connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 8181;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed!");
    return;
  }

  // Read switch values
  
  sensorValue = analogRead(pinA);
  sensor_volt = (float)sensorValue / 1024 * 5.0;
  RS_gas = (5.0 - sensor_volt) / sensor_volt;
  ratio = RS_gas / R0 ;
  ratio = ratio/2.84;
  // Create a URL for the request. Modify YOUR_HOST_DIRECTORY so that you're pointing to the PHP file.
  String url = "/gas/index.php?value=";
  url += ratio;
  url += "&pass=";
  url += passcode;

  // This will send the request to the server
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
 
/*
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  */

  Serial.println();
  Serial.println("Closing connection");
  
  // Sleep
  Serial.println("Going to sleep");
  delay(5000);
//  ESP.deepSleep(wakeuptime * 1000, WAKE_RF_DEFAULT);
  delay(5000);
}



