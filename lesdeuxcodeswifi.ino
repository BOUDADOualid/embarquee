#include<ESP8266WiFi.h> 

 #define pinA A0

// Wake from sleep, in seconds.
#define wakeuptime 30

const char* ssid = "Androiddu"; //Le nom de votre wifi
const char* password = "152015ch17123";  //le mot de passe de votre wifi
 int buzzer =15;
 const char* host = "192.168.43.185";
  const char* passcode = "test";
  float sensor_volt;
  float RS_gas;
  float ratio;
  int sensorValue;
  const float R0 = 0.57;
WiFiServer server(80);
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
  Serial.println("WiFi connecté"); 
  server.begin();
  Serial.println("Server démaré");
  Serial.print("utiliser ce URL pour connecter: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}
void loop() {



WiFiClient client = server.available();

  if (!client )
  {
const int httpPort = 80;
client.connect(host, httpPort); 
   
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
 
   return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  } 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush(); 



// Connect to host
  Serial.print("Connecting to ");
  Serial.println(host);

}

