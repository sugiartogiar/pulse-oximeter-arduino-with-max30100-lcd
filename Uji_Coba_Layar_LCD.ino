#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Inisialisasi nomor pin LCD

LiquidCrystal_I2C lcd(0x3f, 16, 2); 
 
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
}

void loop() // running secara berulang
{
}
