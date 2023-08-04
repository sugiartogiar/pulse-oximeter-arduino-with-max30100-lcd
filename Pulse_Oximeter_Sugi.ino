#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000

// Inisialisasi nomor pin LCD

LiquidCrystal_I2C lcd(0x3f, 16, 2); 
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup() // running sekali pada saat pertama
{
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");

    // Inisialisasi LCD

    lcd.init();

    // Print text ke LCD

    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Pulse");
    lcd.setCursor(0,1);
    lcd.print("Oximeter");
    lcd.print(" by Sugi");

    // untuk memberi jarak sebelum pindah ke baris kode selanjutnya
    
    delay(3000); 
 
    // Inisialisasi Pulse Oximeter
    // Jika terdapat kegagalan umumnya karena kabel I2C yang kurang tepat, tidak ada daya, atau target chip salah
    
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Callback untuk deteksi heart rate
    
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop() // running secara berulang
{
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

    // Menampilkan data Pulse Oximeter ke LCD 
    
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BPM : ");
        lcd.print(pox.getHeartRate());
        lcd.setCursor(0,1);
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");
 
        tsLastReport = millis();
    }
}
