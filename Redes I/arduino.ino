#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

String lastText = "";

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    lcd.init();
    lcd.backlight();
}

void print_lcd(String text)
{
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(lastText);
    lcd.setCursor(0, 1);
    lcd.print(text);
}

void loop()
{
    if (Serial.available())
    {
        String text = Serial.ReadString();
        print_lcd(text);
    }

    if (mfrc522.PICC_IsNewCardPresent())
    {
        if (mfrc522.PICC_ReadCardSerial())
        {
            String text = "UID:";
            for (byte i = 0; i < mfrc522.uid.size; i++)
            {
                text += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
                text += mfrc522.uid.uidByte[i];
            }
            print_lcd(text);
            Serial.println(text);
            mfrc522.PICC_HaltA();
        }
    }
}