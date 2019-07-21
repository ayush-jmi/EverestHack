#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "Shanu";
const char *password = "20167635";
const char *host = "api.thingspeak.com";
String apiKey = "XB7NAHQUZTG7QKS3";

float calibrationFactor = 4.5;
volatile byte pulseCount;
int i;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;

void update(int n)
{
  WiFiClient client;          
  const int httpPort = 80; //Port 80 is commonly used for www
  //Connect to host, host(web site) is define at top 
  if(!client.connect(host, httpPort))
  {
    Serial.println("Connection Failed");
    delay(300);
    return; //Keep retrying until we get connected                                                                                   // File Handling
  }
  else                                                                                                                               // If wifi is connected
  {
    //Make GET request as pet HTTP GET Protocol format
    String ADCData;
    ADCData = String(n);   //String to interger conversion 
    Serial.println(ADCData);
    String Link="GET /update?api_key="+apiKey+"&field1=";  //Requeste webpage  
    Link = Link + ADCData;
    Link = Link + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";                
    client.print(Link);
    delay(100);
    //Wait for server to respond with timeout of 5 Seconds
    int timeout=0;
    while((!client.available()) && (timeout < 1000))     //Wait 5 seconds for data
    {
      delay(10);  //Use this with time out
      timeout++;
    }
    //If data is available before time out read it.
    if(timeout < 500)
    {
       while(client.available())
       {
          Serial.println(client.readString()); //Response from ThingSpeak       
       }
    }
    else
    {
       Serial.println("Request timeout..");
    }
  } 
}


void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}

void setup()
{
  Serial.begin(115200);
  pinMode(D2, 0);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  digitalWrite(D2, 1);
  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
  i                 = 0;
  attachInterrupt(D2, pulseCounter, FALLING); // Configured to trigger on a FALLING state change (transition from HIGH state to LOW state)
}

void loop()
{
  digitalWrite(D4,0);
  if ((millis() - oldTime) > 1000)   // Only process counters once per second
  {
    detachInterrupt(D2);
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
    Serial.print(totalMilliLitres/2);
    if(totalMilliLitres!=0)
    {
      if(digitalRead(D7)==0)
      {
        i++;
      }
      if(i>10)
      {
        Serial.print("  Output Liquid Quantity: ");             // Output separator
        Serial.print(totalMilliLitres/2);
        Serial.println("mL");
        update(totalMilliLitres/2);
        i=0;
        totalMilliLitres = 0;
      }
    }
    pulseCount = 0;
    attachInterrupt(D2, pulseCounter, FALLING);
  }
}

