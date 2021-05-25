// Copyright (c) 2021 SQ9MDD Rysiek Labus
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <EEPROM.h>
#include <LittleFS.h>
#include <taskWebServer.h>

const byte wind_sensor = D5;
const byte dire_sensor = A0;
volatile byte interruptCounter = 0;
float ms;
float ms_max;
int rpm = 0;
int rpm_max = 0;
int rpm_avg = 0;
int rpm_max_arr[30];
int rpm_max_pointer = 0;
float diameter_mm = 216;    // srednica anemometru w mm
float kalibracja = 2.9;     // kalibracja miernika 
int direction_raw = 0;
int direction = 0;
int dir_calibration = 0;

int domoti_IP_1 = 192;
int domoti_IP_2 = 168;
int domoti_IP_3 = 0;
int domoti_IP_4 = 1;
int domoti_PORT = 80;
int send_interval = 5;
boolean domoti_on = false;
int idx_temp_rh_baro_sensor = 1;
int idx_wind_sensor = 2;
unsigned long domoticz_interval = 0;
unsigned long last_data_send = 0;
unsigned long last_read = 0;
unsigned long last_rpm_read = 0;
String gardner_name = "SINUX WS.0.3";
String wifi_config_file = "/wifi_conf.txt";
String config_file = "/config.txt";
String domoti_config_file = "/domoti_conf.txt";
String wifi_ssid = "";
String wifi_pass = "";
String www_pass = "sinux2021";
boolean spiffsActive = false;
boolean sensor_ok = true;
float sensor_temperature = 0.0;
float sensor_humidity = 0.0;
float sensor_dewpoint = 0.0;
float sensor_windchill = 0.0;
float sensor_baro = 0.0;
int above_sea_lvl = 0;

Adafruit_BME280 bme;              // ESP8266 connect 

void read_global(){
  if (LittleFS.begin()){
      spiffsActive = true;
  } else {
      Serial.println("Unable to activate SPIFFS");
  }
  File file = LittleFS.open(config_file,"r");
  if(!file){
    Serial.println("error opening file");
  }else{
    String s;
    int line = 0;
    while (file.position()<file.size()){
      s = file.readStringUntil('\n');
      s.trim();
      if(line == 0){  // nazwa
        gardner_name = s.c_str();
      } 
      if(line == 1){  // wysokosc
        above_sea_lvl = s.toInt();
      }   
      if(line == 2){  // www password
        www_pass = s.c_str();
      }    
      if(line == 3){  // anemometr diameter
        diameter_mm = s.toInt();
      }  
      if(line == 4){  // anemometr calibration factor
        kalibracja = s.toFloat();
      }   
      if(line == 5){  // direction sensor
        dir_calibration = s.toInt();
      }                       
      line++;
    }
  file.close();    
  }
}

void read_wifi_spiffs(){
  if (LittleFS.begin()){
      spiffsActive = true;
  } else {
      Serial.println("Unable to activate SPIFFS");
  }
  File file = LittleFS.open(wifi_config_file,"r");
  if(!file){
    Serial.println("error opening file");
  }
    String s;
    int line = 0;
    while (file.position()<file.size()){
      s = file.readStringUntil('\n');
      s.trim();
      if(line == 0){  //bot api
        wifi_ssid = s.c_str();
      }
      if(line == 1){  //chat id
        wifi_pass = s.c_str();
      }    
      line++;
    }
  file.close();
}

void read_domoti(){
  if (LittleFS.begin()){
      spiffsActive = true;
  } else {
      Serial.println("Unable to activate SPIFFS");
  }
  File file = LittleFS.open(domoti_config_file,"r");
  if(!file){
    Serial.println("error opening file");
  }  
    String s;
    int line = 0;
    while (file.position()<file.size()){
      s = file.readStringUntil('\n');
      s.trim();
      if(line == 0){ domoti_IP_1 = s.toInt(); }
      if(line == 1){ domoti_IP_2 = s.toInt(); }    
      if(line == 2){ domoti_IP_3 = s.toInt(); } 
      if(line == 3){ domoti_IP_4 = s.toInt(); }
      if(line == 4){ domoti_PORT = s.toInt(); } 
      if(line == 5){ send_interval = s.toInt(); } 
      if(line == 6){ domoti_on = s.toInt(); } 
      if(line == 7){ idx_temp_rh_baro_sensor = s.toInt(); } 
      if(line == 8){ idx_wind_sensor = s.toInt(); } 
      line++;
    }
  file.close();  
}

// type_sensor enum: 1-temperature humidity baro, 2- wind
void send_domoticz(int type_sensor, int idx){
  String url = "http://" + String(domoti_IP_1) + "." + String(domoti_IP_2) + "." + String(domoti_IP_3) + "." + String(domoti_IP_4) + ":" +String(domoti_PORT) + "/json.htm";
  int hum_stat = 0;
  int baro_stat = 0;
  if(type_sensor == 1){
    if(sensor_humidity < 35.0) hum_stat = 2; 
    if(sensor_humidity >= 35.0 && sensor_humidity < 65.0) hum_stat = 1;
    if(sensor_humidity >= 65.0) hum_stat = 3;
    if(sensor_baro < 1000) baro_stat  = 4;
    if(sensor_baro >= 1000 && sensor_baro <1010) baro_stat  = 3;
    if(sensor_baro >= 1010 && sensor_baro <1020) baro_stat  = 2;
    if(sensor_baro >= 1020) baro_stat  = 1;
    url +=  "?type=command&param=udevice&idx=" + String(idx) + "&nvalue=0&svalue=" + String(sensor_temperature,1) + ";" + String(sensor_humidity) + ";" + String(hum_stat) + ";" + String(sensor_baro) + ";" + String(baro_stat);
  }
  if(type_sensor == 2){
    String direction_stat = "N";
    if(direction < 45 || direction > 315) direction_stat = "N";
    if(direction >= 45 && direction < 135) direction_stat = "E";
    if(direction >= 135 && direction < 225) direction_stat = "S";
    if(direction >= 225 && direction < 315) direction_stat = "W";
    url += "?type=command&param=udevice&idx=" + String(idx) + "&nvalue=0&svalue=" + String(direction) + ";" + direction_stat + ";" + String(ms*10) + ";" + String(ms_max*10) + ";" + String(sensor_temperature,1) + ";" + String(sensor_windchill) + ";" ;
  } 

  WiFiClient client;
  HTTPClient http;
  http.begin(client,url);
  http.GET();
  // dopisac obslugę błędów
  http.end();
  Serial.println(url);
}

double dewPointFast(double celsius, double humidity){
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}

void read_bme(){
  float hPa_offset = float(above_sea_lvl) * 0.10933;
  sensor_temperature = ((sensor_temperature * 9 ) + bme.readTemperature()) / 10;
  sensor_humidity = ((sensor_humidity * 9) + bme.readHumidity()) / 10;
  sensor_dewpoint = dewPointFast(sensor_temperature,sensor_humidity);
  sensor_baro = bme.readPressure() / 100.0F + hPa_offset;
}

void IRAM_ATTR wind_tick(){
  interruptCounter++;
}

int calculate_abs_degree(int mesure, int min_sensor, int max_sensor, int rev_sensor){
  int direction_abs = 0;
  if(mesure <= min_sensor){
    return(0);
  }
  if(rev_sensor == 1){
    direction_abs = map(mesure,min_sensor,max_sensor,315,0);
  }else{
    direction_abs = map(mesure,min_sensor,max_sensor,0,315);
  }
  return(direction_abs);
}

int calculate_rel_degree(int direction_abs, int calibration_offset){
  int direction_rel = 0;
  direction_rel = direction_abs + calibration_offset;
  if(direction_rel > 360){
    direction_rel = direction_rel - 360;
  }
  return(direction_rel);  
}

void setup() {
  pinMode(wind_sensor,INPUT_PULLUP);
  pinMode(dire_sensor,INPUT);
  attachInterrupt(digitalPinToInterrupt(wind_sensor), wind_tick, FALLING);
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\n");
  Serial.println("read config...");   
  read_wifi_spiffs();
  read_global();
  read_domoti();
  delay(2000);
  Serial.println("booting...");
  connect_to_wifi();
  restServerRouting();
  server.onNotFound(handleNotFound);
  server.begin();
  ArduinoOTA.setPassword(INI_UPLOAD_PASS);
  ArduinoOTA.onStart([](){
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH){
      type = "sketch";
    }else{
      type = "filesystem";
    }
	});
  ArduinoOTA.begin();
  // test for BME280 sensor
  if (!bme.begin(0x76)){
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    sensor_ok = false;
  } 
  Serial.println("booting done, enjoy\n"); 
  float hPa_offset = float(above_sea_lvl) * 0.10933;
  sensor_temperature = bme.readTemperature();
  sensor_humidity = bme.readHumidity();
  sensor_dewpoint = dewPointFast(sensor_temperature,sensor_humidity);
  sensor_baro = bme.readPressure() / 100.0F + hPa_offset;  
  Serial.println("www username is: root");
  Serial.println("www password is: " + String(www_pass));
  Serial.println("system name: " + String(gardner_name));
  Serial.println("baro montage lvl: " + String(above_sea_lvl));
  Serial.println("anemometer diameter: " + String(diameter_mm));
  Serial.println("anemometer calibration: " + String(kalibracja) + "\n");
  Serial.println("millis;temp;humidity;dewpoint;barometer;wind;gust");
}

void loop(){
  ArduinoOTA.handle();
  server.handleClient();
  // compute wind speed, gust and wind chill
  if(millis() - last_rpm_read > 10000){
    last_rpm_read = millis();
    rpm = (interruptCounter * 6) / 4;
    interruptCounter = 0;
    // obliczenie sredniej predkosci wiatru uśrednianie ostatnich 6-ciu pomiarów = średnia z minuty
    rpm_avg = (rpm_avg * 5 + rpm) / 6;
    ms = (diameter_mm * 3.14 * rpm_avg) / 1000 / 60;
    ms = ms * kalibracja; 
    // obliczenie predkosci max
    // dodaj kazdy pomiar do tablicy odczytaj z tablicy wartość max, 30el w tablicy co 10sec = 5min
    rpm_max_arr[rpm_max_pointer] = rpm;
    rpm_max_pointer++;
    if(rpm_max_pointer == 30){
      rpm_max_pointer = 0;
    }
    rpm_max = 0;
    for(int i = 0; i < 30; i++){
      if(rpm_max < rpm_max_arr[i]){
        rpm_max = rpm_max_arr[i];
      }
    }
    ms_max = (diameter_mm * 3.14 * rpm_max) / 1000 / 60;
    ms_max = ms_max * kalibracja;
    // Wyliczenie temp odczuwalnej
    if(sensor_temperature < 15.0 && ms > 1.34){
      float MPH = ms * 2.23693629;
      float TempF = (sensor_temperature * 9) / 5 + 32;
      float windchillF = 35.74 + 0.6215 * TempF - 35.75 * pow(MPH, 0.16) + 0.4275 * TempF * pow(MPH, 0.16);
      sensor_windchill = (windchillF - 32) * 5 / 9;      
    }else{
      sensor_windchill = sensor_temperature;
    }
    // odczytanie kierunku raw z przetwornika
    direction_raw = (direction_raw * 5 + analogRead(dire_sensor)) / 6;
    int direction_abs = calculate_abs_degree(direction_raw, 334, 921, 0);
    direction = calculate_rel_degree(direction_abs, dir_calibration);
  }

  // domoticz integration
  domoticz_interval = u_long(send_interval * 60 * 1000);
  if((millis() - last_data_send > domoticz_interval) && domoti_on){
    send_domoticz(1, idx_temp_rh_baro_sensor);
    send_domoticz(2, idx_wind_sensor);
    last_data_send = millis();
  }

  if(millis() - last_read > 5000){
    read_bme();
    last_read = millis();
    Serial.println(String(millis()) + ";" + String(sensor_temperature,1) + ";" + String(sensor_humidity,0) + ";" + String(sensor_dewpoint,1) + ";" + String(sensor_baro,1) + ";" + String(ms) + ";" + String(ms_max));
  }
}