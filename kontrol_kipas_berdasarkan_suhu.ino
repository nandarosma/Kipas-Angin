#include <Wire.h>
#include <LiquidCrystal_I2C.h> // library for LCD
#include <DHT.h>  // library for DHT11 sensor

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display
DHT dht(2, DHT11); // Pin 2, Type DHT11

const int kipas = 3; // Pin for the fan

void setup() {
  Serial.begin(9600);       // Start serial communication at 9600 baud rate
  dht.begin();              // Initialize DHT sensor
  lcd.begin(16, 2);         // Initialize LCD with 16 columns and 2 rows
  pinMode(kipas, OUTPUT);   // Set the fan pin as output
}

void loop() {
  float kelembaban = dht.readHumidity();     // Read humidity
  float suhu = dht.readTemperature();        // Read temperature in Celsius

  // Check if any reads failed and exit early (to try again).
  if (isnan(kelembaban) || isnan(suhu)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(0, 0);      // Set cursor to first row, first column
  lcd.print("Temperatur:"); // Print "Temperatur:" label
  lcd.setCursor(12, 0);     // Set cursor to first row, 13th column
  lcd.print(suhu);          // Print temperature value
  lcd.setCursor(14, 0);     // Set cursor to first row, 15th column
  lcd.print("C");           // Print "C" for Celsius

  lcd.setCursor(0, 1);      // Set cursor to second row, first column
  lcd.print("Kipas: ");     // Print "Kipas:" label

  lcd.setCursor(8, 1);      // Set cursor to second row, 9th column
  if (suhu > 27) {
    digitalWrite(kipas, HIGH);  // Turn the fan on
    lcd.print("ON ");           // Print "ON" on the LCD
  } else {
    digitalWrite(kipas, LOW);   // Turn the fan off
    lcd.print("OFF");           // Print "OFF" on the LCD
  }

  delay(2000);  // Wait for 2 seconds before next read
}
