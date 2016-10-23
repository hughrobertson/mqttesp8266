// Update these with values suitable for your network.


#ifndef config
#define config 

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
const char* ver_config = "config 1";
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
const char* headerID = " Relay Control 1";
const char* ssid = "VM485936-2G";
const char* password = "1234567890";
const char* mqtt_server = "192.168.2.96";
const char* outTopic = "outTopic";
const char* inTopic = "inTopic";
const int YES = 1;
const int NO = 0;
const int ON = 1;
const int OFF = 0;

#define DHTPIN 14 // 2 // pin where the dht22 is connected
int GPIO_on =1; //active low =1 ie a 1 switches off  set to 0
int GPIO_off =0;
int DHTfitted  = YES;
//this array selects the enabled gpio
//just two relays used gpio12 and 13
int validGPIO[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1 };
//gpio 0 and 2 should be hi for boot gpio 15 low gpio 6-11 internal flash memory
//gpio 1 and 3 are serial 0 port
int maxGPIO = 17;

//IPAddress ip(192, 168, 2, 60); // is the desired IP Address
//IPAddress gateway(192, 168, 2, 1); // set gateway to match your network
//IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network


int humidityLimit = 60;
int fanFitted = NO;
int fanPin = 12;

#endif
