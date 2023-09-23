
#include <ArduinoWebsockets.h>
#include <WiFi.h>

#include <DIYables_IRcontroller.h>  

DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200);  // debounce time is 200ms


const char* ssid = "elixxrades";                      //Enter SSID
const char* password = "44466666";                    //Enter Password
const char* websockets_server_host = "192.168.1.11";  //Enter server adress
const uint16_t websockets_server_port = 8080;         // Enter server port

using namespace websockets;

WebsocketsClient wsclient;
void setup() {
  Serial.begin(115200);
  // Connect to wifi
  WiFi.begin(ssid, password);
  irController.begin();

  // Wait some time to connect to wifi
  for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
    Serial.print(".");
    delay(1000);
  }

  // Check if connected to wifi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("No Wifi!");
    return;
  }

  Serial.println("Connected to Wifi, Connecting to server.");
  // try to connect to Websockets server
  bool connected = wsclient.connect(websockets_server_host, websockets_server_port, "/");
  if (connected) {
    Serial.println("Connected!");
    wsclient.send("Hello Server");
  } else {
    Serial.println("Not Connected!");
  }

  // run callback when messages are received
  wsclient.onMessage([&](WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());
  });
}

void loop() {
  // let the websockets wswsclient check for incoming messages
  if (wsclient.available()) {
    wsclient.poll();
  }
  Key21 command = irController.getKey();
  if (command != Key21::NONE) {
    switch (command) {
      case Key21::KEY_CH_MINUS:
        wsclient.send("/CH-");

        break;

      case Key21::KEY_CH:
        wsclient.send("/CH");

        break;

      case Key21::KEY_CH_PLUS:
        wsclient.send("/CH+");

        break;

      case Key21::KEY_PREV:
        wsclient.send("/<<");

        break;

      case Key21::KEY_NEXT:
        wsclient.send("/>>");

        break;

      case Key21::KEY_PLAY_PAUSE:
        wsclient.send("/>||");

        break;

      case Key21::KEY_VOL_MINUS:
        wsclient.send("/-");

        break;

      case Key21::KEY_VOL_PLUS:
        wsclient.send("/+");

        break;

      case Key21::KEY_EQ:
        wsclient.send("/EQ");

        break;

      case Key21::KEY_100_PLUS:
        wsclient.send("/100+");

        break;

      case Key21::KEY_200_PLUS:
        wsclient.send("/200+");

        break;

      case Key21::KEY_0:
        wsclient.send("/0");

        break;

      case Key21::KEY_1:
        wsclient.send("/1");

        break;

      case Key21::KEY_2:
        wsclient.send("/2");

        break;

      case Key21::KEY_3:
        wsclient.send("/3");

        break;

      case Key21::KEY_4:
        wsclient.send("/4");

        break;

      case Key21::KEY_5:
        wsclient.send("/5");

        break;

      case Key21::KEY_6:
        wsclient.send("/6");

        break;

      case Key21::KEY_7:
        wsclient.send("/7");

        break;

      case Key21::KEY_8:
        wsclient.send("/8");

        break;

      case Key21::KEY_9:
        wsclient.send("/9");

        break;

      default:
        Serial.println("WARNING: undefined command:");
        break;
    }
  }
  delay(2);
}
