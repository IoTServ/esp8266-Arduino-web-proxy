#include <ESP8266WiFi.h>
const char* id     = "id";  //http://www.mcunode.com/proxy/id/LED  if id==4567  then url:http://www.mcunode.com/proxy/4567/LED
const char* ssid     = "ssid";
const char* password = "password";
int ledPin = 13;
const char* host = "www.mcunode.com";

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Please open http://www.mcunode.com/proxy/");
  Serial.print(id);
  Serial.println("/LED");
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  WiFiClient client;
  const int httpPort = 8001;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


 if (client.connected())
{
  client.write(id);
  delay(1000);
  while (1)
  {

  String request = client.readStringUntil('\r');
  Serial.print(request);
  client.flush();
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 //Serial.println(value);


  if(value == HIGH) {
    client.print("<h1> ESP8266 Arduino Web Server</h1>Led pin is now:on <br><br><a href=\"LED=ON\"\"><button>Turn On </button></a><a href=\"LED=OFF\"\"><button>Turn Off </button></a><br />");
  } else {
    client.print("<h1> ESP8266 Arduino Web Server</h1>Led pin is now:off  <br><br><a href=\"LED=ON\"\"><button>Turn On </button></a><a href=\"LED=OFF\"\"><button>Turn Off </button></a><br />");
  }
  
  }
}
}
