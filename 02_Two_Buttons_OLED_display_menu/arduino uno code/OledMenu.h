#ifndef OLEDMENU_h
#define OLEDMENU_h

#include "Arduino.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1

Adafruit_SSD1306 display(OLED_RESET);

static const uint32_t GPSBaud = 9600;

#define MENU_ITEMS 3

const char * menuItems[] = {"Start", "Stop", "Back"};

class OledMenu {
  
public:

  inline void writeAText(char *initText, int delaySec, int sizeText) {
    display.setTextSize(sizeText);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.clearDisplay();
    display.println(initText);
    display.display();
    delay(delaySec);
  }
  
  inline void menuScreen(int counterMenuItem = 0) {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.clearDisplay();
    display.println("Menu");
    display.setTextSize(1);

    for (int i =0; i < MENU_ITEMS; ++i)
    {
      if (counterMenuItem == i)
      {
        display.setTextColor(BLACK, WHITE);
      }
      else
      {
        display.setTextColor(WHITE);
      }
      
      display.print(menuItems[i]);
      if(i < MENU_ITEMS -1)
      {
        display.setTextColor(WHITE);
        display.print(" | ");
      }
    }
    
    display.display();
    delay(1);
  }
};

#endif 
