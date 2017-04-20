/*
  2017/04/13
  Stefan Paskalev
  
  This example implements 2-buttons menu with OLED display.
  
  REVISIONS:
  2017/04/17 
    ...
  
*/

#include "Arduino.h"
#include "OledMenu.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define btn1 6
#define btn2 7

int stateButton1 = 0;
int stateButton2 = 0;

int menuScreen = 0;
int counterMenuItem = -1;

OledMenu odm;

void setup()
{
 Serial.begin(9600);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 OledMenu init;
 
 pinMode(btn1, INPUT);
 pinMode(btn2, INPUT);
  
 init.writeAText("Loading main screen...", 500, 2); 
 display.clearDisplay();//OledMenu od2;
}

void loop()
{
  stateButton1 = digitalRead(btn1);
  stateButton2 = digitalRead(btn2);
  
  OledMenu odm;
  
  //In this state, with btn1, the selection 
  if (menuScreen) {
    display.clearDisplay();
    odm.menuScreen(counterMenuItem);
  }
  
  //Loads main screen
  if (stateButton1 == LOW && stateButton2 == LOW && menuScreen == 0)
  {
    display.clearDisplay();
    odm.writeAText("Main screen loaded", 1, 2);
  }
  
  //Eneters the menu
  if(stateButton1 == HIGH && menuScreen == 0)
  {
    menuScreen = 1;
    display.clearDisplay();
    delay(200);
  }
  
  //Going through the menu items
  if(stateButton1 == HIGH && menuScreen == 1)
  {
    if (counterMenuItem < 2)
    {
      counterMenuItem++;
    }
    else
    {
      counterMenuItem = 0;
    }
    display.clearDisplay();
    delay(200);
  }
  
  //Pressing btn2 selects menu item
  if(stateButton2 == HIGH)
  {
    display.clearDisplay();
//    
    if (counterMenuItem == 0) {
      odm.writeAText("Start doing something...", 1000, 1);
    }
    else if (counterMenuItem == 1) {
      odm.writeAText("Stop doing something...", 1000, 1);
    }
    else {
      odm.writeAText("Back to main screen...", 1000, 1);
    }
//    
    counterMenuItem = -1;
    menuScreen = 0;
  }
}
