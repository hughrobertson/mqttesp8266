/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
 - publishes "hello world" to the topic "outTopic" every two seconds
 - subscribes to the topic "inTopic", printing out any messages
 it receives. NB - it assumes the received payloads are strings not binary
 - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
 else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
 - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
 http://arduino.esp8266.com/stable/package_esp8266com_index.json
 - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
 - Select your ESP8266 in "Tools -> Board"

 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "config.h"
#include "DHT.h"

byte CRC8(char *data, byte len);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
const char* ver = "relayDriver V1.03 2016/09/08  hr";
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int msgCount = 0;

DHT dht(DHTPIN, DHT22, 15);
float humidity = 0;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
int value = 0;

int hfanControl(float h);
/*  humidity fan Control
 * fan connected to gpio 12 on relay board
 *
 */

int hfanControl(float h) {
	int fanStatus = 0;
	const int uplimit = 250;
	static int humitityHigh = 0;

	if (h > humidityLimit) {
		humitityHigh++;
		//fanStatus = ON;
	} else {
		humitityHigh--;
		//fanStatus = OFF;
	}

	if (humitityHigh > uplimit) {
		fanStatus = ON;
		humitityHigh = uplimit;
		controlON(fanPin);
	} else if (humitityHigh < 0) {
		fanStatus = OFF;
		humitityHigh = 0;
		controlOFF(fanPin);
	}

	return fanStatus;
}

void setGPIO(int chan) {
	Serial.print(chan);
	Serial.print("  ");
	pinMode(chan, OUTPUT);
	digitalWrite(chan, 0);
}
void controlON(int chan) {
	digitalWrite(chan, GPIO_on);
}

void controlOFF(int chan) {
	digitalWrite(chan, GPIO_off);
}

void setup_wifi() {

	delay(10);
	// We start by connecting to a WiFi network
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	//Serial.print(F("Setting static ip to : "));
	//Serial.println(ip);

	//WiFi.config(ip, gateway, subnet);// needs???WiFiServer server(80);
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

void callback(char* topic, byte* payload, unsigned int length) {
	String incomming = "";
	byte crc =0;
	//Serial.print("payload:");
	//String ppp=payload;
	//Serial.println(ppp);

	crc = CRC8((char*)payload, (byte)length-1);

	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print(" crc:");
	Serial.print(crc);
	Serial.println("] ");
	Serial.println("rx crc: ");
	Serial.println(payload[length-1]);

	for (int i = 0; i < length-1; i++) {
		incomming += i;
		incomming += "[";
		incomming += (char) payload[i];
		incomming += "],";
		byte pl = payload[i];
		//Serial.println(pl);
		if (validGPIO[i] == 1) {
			if (pl == 48 + 1) {
				controlON(i);
				Serial.print(i);
				Serial.println(" on ");
			} else {
				controlOFF(i);
				Serial.print(i);
				Serial.println(" off ");
			}
		}
	}

	Serial.println(incomming);

}

void reconnect() {
// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect("ESP8266Client")) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			client.publish(outTopic, "reconnect");
			// ... and resubscribe
			client.subscribe(inTopic);
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void setup() {

	dht.begin();

//pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
	Serial.begin(115200);
	Serial.println(ver);
	Serial.println(ver_config);

// initialise selected gpio
	for (int i = 0; i < maxGPIO; i++) {
		if (validGPIO[i] == 1) {
			//setGPIO(i);
			pinMode(i, OUTPUT);
			digitalWrite(i, 0);  //initialise off
		}
	}
//boot mode
	digitalWrite(0, 1);
	digitalWrite(2, 1);
	digitalWrite(15, 0);
	//digitalWrite(16, 1);

	setup_wifi();
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);
}

void loop() {
	int bufferSize = 250;
	char charBuf[bufferSize];
	String mqttMessage = "";
	String DHTmessage = ", DHT:";
	float h = 0;
	float t = 0;
	String gpioStatus = "";
	String gpioEnabled = "";
	if (DHTfitted == YES) {
		h = dht.readHumidity();
		t = dht.readTemperature();
		if (isnan(h) || isnan(t)) {
			DHTmessage += "notFitted";
			DHTfitted = NO;
			//return;
		} else {
			DHTmessage += "Fitted";
			humidity = h;
			if (fanFitted == YES) {
				hfanControl(h);
			}
		}
	} else {
		DHTmessage += "notFitted";
	}

	if (!client.connected()) {
		reconnect();
	}
	client.loop();
	//controlOFF(0);
	long now = millis();
	if (now - lastMsg > 2000) {

		int pin = 0;

		//client.print("read:");
		for (int i = 0; i < maxGPIO; i++) {
			if (validGPIO[i] == 1) {
				gpioEnabled += "1";
			} else {
				gpioEnabled += "0";
			}
			pin = digitalRead(i);
			gpioStatus += pin;
		}
		//gpioEnabled+=" ";
		//gpioStatus+=" ";

		//Serial.println(gpioEnabled);
		//Serial.println(gpioStatus);

		lastMsg = now;
		mqttMessage = "hdr:";
		mqttMessage += headerID;
		mqttMessage += ", c:";
		mqttMessage += ++value;
		mqttMessage += ", ge:";
		mqttMessage += gpioEnabled;
		mqttMessage += ", gs:";
		mqttMessage += gpioStatus;
		mqttMessage += DHTmessage;
		mqttMessage += ", H:";
		mqttMessage += h;
		mqttMessage += ", T:";
		mqttMessage += t;

		byte sizzz = mqttMessage.length();
		//Serial.println(sizzz);

		mqttMessage += CRC8(charBuf, sizzz);

		mqttMessage.toCharArray(charBuf, sizzz);



		client.publish(outTopic, charBuf);
		//Serial.println(charBuf);
		//client.publish(outTopic, "x");
	}
}

//CRC-8 - based on the CRC8 formulas by Dallas/Maxim
//code released under the therms of the GNU GPL 3.0 license
byte CRC8(char *data, byte len) {
	byte crc = 0x00;
	while (len--) {
		byte extract = *data++;
		for (byte tempI = 8; tempI; tempI--) {
			byte sum = (crc ^ extract) & 0x01;
			crc >>= 1;
			if (sum) {
				crc ^= 0x8C;
			}
			extract >>= 1;
		}
	}
	return crc;
}
