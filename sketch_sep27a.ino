#include "DHT.h"

#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define OLED_RESET 4

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

int screenWidth = SCREEN_WIDTH;
int screenHeight = SCREEN_HEIGHT;

void setup() {
  {
    Wire.begin();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.begin(9600);
    dht.begin();

    pinMode(8, OUTPUT);
    digitalWrite(8, LOW);
    
    Serial.println("initialized");
  }

   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void loop() {
  delay(2000); // Pause for 2 seconds
  display.display();
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (h > 70) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  
  //Set the cursor coordinates
  display.setCursor(0,30); 
  display.print("Humidity:    "); 
  display.print(h);
  display.print(" %");
  
  display.setCursor(0,40);
  display.print("Temperature: "); 
  display.print(t);
  display.print(" C");
}
