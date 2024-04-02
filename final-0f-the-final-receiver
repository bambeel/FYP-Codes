#include <ESP8266WebServer.h>
#include <LoRa.h>
#include <SPI.h>

// SSID & Password
const char* ssid = "nabil";
const char* password = "hehehehe";

String instring = "";

// variable assign
String lux = "";
String irradiance = "";
String volt = "";
String current = "";
String power = "";
String temperature = "";
String pressure = "";
String status = "";

// identification assign
String masternode = "";
String slavenode = "";
String master = "master";
String slave = "node1";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(100);

  //LoRa Initialization
  LoRa.setPins(15, 16, 2);  //NSS, RST, DIO0
  while (!Serial)
    ;
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa Failed");
    while (1)
      ;
  } else {
    Serial.println("LoRa Initialization Successful");
  }

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  delay(100);
  server.handleClient();
  int packetsize = LoRa.parsePacket();
  if (packetsize) {
    while (LoRa.available()) {
      int inchar = LoRa.read();
      instring += (char)inchar;
    }
    // packet identification
    masternode = getvalue(instring, ',', 0);
    slavenode = getvalue(instring, ',', 1);
    if ((masternode != master) && (slavenode != slave)) {
      Serial.println("Not Mine");
      status = "Unintended Packet";
    } else {
      status = "Packet Received"; 
      lux = getvalue(instring, ',', 2);
      irradiance = getvalue(instring, ',', 3);
      volt = getvalue(instring, ',', 4);
      current = getvalue(instring, ',', 5);
      power = getvalue(instring, ',', 6);
      temperature = getvalue(instring, ',', 7);
      pressure = getvalue(instring, ',', 8);
      instring = "";

      // data print to serial print
      Serial.print("Signal Origin: ");
      Serial.println(slavenode);
      Serial.print("Lux: ");
      Serial.println(lux);
      Serial.print("Irradiance: ");
      Serial.println(irradiance);
      Serial.print("Volt: ");
      Serial.println(volt);
      Serial.print("Current: ");
      Serial.println(current);
      Serial.print("Power: ");
      Serial.println(power);
      Serial.print("Temperature: ");
      Serial.println(temperature);
      Serial.print("Pressure: ");
      Serial.println(pressure);
      Serial.print("RSSI: ");
      Serial.println(LoRa.packetRssi());
      Serial.print("SNR: ");
      Serial.println(String(LoRa.packetSnr()));
      Serial.println("");
    }
  } else{
    status = "Packet Unavailable";
  }
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(slavenode, lux, irradiance, volt, current, power, temperature, pressure, status));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(String var0, String var1, String var2, String var3, String var4, String var5, String var6, String var7, String var8) {
  String ptr = "<!DOCTYPE html><html>\n";
  ptr += "<head> <title>UN-VEIL</title> <meta name=\"viewport\" content=\"width = device - width, initial - scale = 1\">\n";
  ptr += "<style>\n";
  ptr += "html { font-family: Barlow, Barlow, Barlow; display: inline-block; text-align: center; background-color: #242424;}\n";
  ptr += "h1 {font-size: 1.8rem; color: white;}\n";
  ptr += ".topnav {overflow: hidden; background-color: #085189;}\n";
  ptr += "body {margin: 0;}\n";
  ptr += ".content {padding: 50px;}\n";
  ptr += ".card-grid {align-items: center; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));}\n";
  ptr += ".card {background-color: #085189; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); border-radius: 10px; }\n";
  ptr += ".card-title {font-size: 1.2rem; font-weight: bold; color: #ffffff;}\n";
  ptr += ".reading {font-weight: 500; font-size: 1.2rem; color: #ffffff;}\n";
  ptr += "</style>\n";
  ptr += "<script>\n";
  ptr += "setInterval(loadDoc, 100);\n";  // set refresh time
  ptr += "function loadDoc() {\n";
  ptr += "var xhttp = new XMLHttpRequest();\n";
  ptr += "xhttp.onreadystatechange = function() {\n";
  ptr += "if (this.readyState == 4 && this.status == 200) {\n";
  ptr += "document.body.innerHTML =this.responseText}\n";
  ptr += "};\n";
  ptr += "xhttp.open(\"GET\", \"/\", true);\n";
  ptr += "xhttp.send();\n";
  ptr += "}\n";
  ptr += "</script>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div class=\"topnav\">\n";
  ptr += "<h1>UN-VEIL: SOLAR MONITORING SYSTEM</h1>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"content\">\n";
  ptr += "<div class=\"card-grid\">\n";
  ptr += "<div class=\"card\">\n";
  ptr += "<p class=\"card-title\">Signal Origin</p>\n";
  ptr += "<p class=\"reading\"><span id=\"lux\"></span>";
  ptr += var0;
  ptr += "</p>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"card\">\n";
  ptr += "<p class=\"card-title\">Lux</p>\n";
  ptr += "<p class=\"reading\"><span id=\"lux\"></span>";
  ptr += var1;
  ptr += " Lux</p>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"card\">\n";
  ptr += "<p class=\"card-title\">Irradiance</p>\n";
  ptr += "<p class=\"reading\"><span id=\"irradiance\"></span>";
  ptr += var2;
  ptr += " W/M²</p>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"card\">\n";
  ptr += "<p class=\"card-title\">Volt</p>\n";
  ptr += "<p class=\"reading\"><span id=\"volt\"></span>";
  ptr += var3;
  ptr += " Volts</p>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"card\">\n";
  ptr += "<p class=\"card-title\">Current</p>\n";
  ptr += "<p class=\"reading\"><span id=\"current\"></span>";
  ptr += var4;
  ptr += " Amps</p>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"card\">\n";
  ptr += "<p class=\"card-title\">Power</p>\n";
  ptr += "<p class=\"reading\"><span id=\"power\"></span>";
  ptr += var5;
  ptr += " Watts</p>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"card\">\n";
  ptr += "<p class=\"card-title\">Temperature</p>\n";
  ptr += "<p class=\"reading\"><span id=\"temperature\"></span>";
  ptr += var6;
  ptr += " °C</p>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"card\">\n";
  ptr += "<p class=\"card-title\">Pressure</p>\n";
  ptr += "<p class=\"reading\"><span id=\"pressure\"></span>";
  ptr += var7;
  ptr += " hpa</p>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"card\">\n";
  ptr += "<p class=\"card-title\">Signal Status</p>\n";
  ptr += "<p class=\"reading\"><span id=\"lux\"></span>";
  ptr += var8;
  ptr += "</p>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

String getvalue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
