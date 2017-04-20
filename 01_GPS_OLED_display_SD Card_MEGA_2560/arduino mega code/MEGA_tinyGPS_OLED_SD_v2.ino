/*
  2017/04/13
  Stefan Paskalev
  
  Example of code combining GPS receiver, OLED display, SD card module and arduino MEGA 2560 microcontroller board.
  
  The GPS device gets the satelite data. The data is visualized by the OLED display and saved on SD card in csv file.
 
  
  REVISIONS:
  2017/04/17 
    ...
  
*/


#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

static const int RXPin = 19, TXPin = 18;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

HardwareSerial & ss = Serial1;


/* SD CARD */

//Name of the directory for storing the logger files
char loggerFilesDir[] = "logger/";

const int chipSelect = 53;

char logFileName[20];
char filePrefix[2];

File dataFile;

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Searching for GPS satellites");
  display.clearDisplay();
  smartdelay(1000);


/* SD CARD INITIALIZATION */
  
   Serial.print("Initializing SD card...");
  // default chip select pin is set to output
   pinMode(53, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  else
  {
    Serial.println("card initialized.");
    
    //create dir if not exists
    if (!SD.exists(loggerFilesDir))
    {
      if (!SD.mkdir(loggerFilesDir))
      {
        Serial.print("Cannot create dir - ");
        Serial.println(loggerFilesDir);
      }
    }
    
    dataFile = SD.open(loggerFilesDir);
    int number = findFilePrefix(dataFile);
    dataFile.close();
    
    
    if (number != -1) {
      //TO DO if number equal 99. Should be rewiten the first file (00)
      
      //creating the next prefix number
      number++;
      
      if (number < 10) {
        //concatenate dir and filename
        sprintf(logFileName, "%s0%d_loggr.csv",  loggerFilesDir, number);
      }
      else
      {
        sprintf(logFileName, "%s%d_loggr.csv", loggerFilesDir, number);
      }
    }
    else
    {
      //if there is no files with prefix number, the first created file will start with '00'
      sprintf(logFileName, "%s00_loggr.csv", loggerFilesDir);
    }
 }
}

void loop()
{
  if (gps.location.isValid())
  {
    //Start writing in the logger file
    dataFile = SD.open(logFileName, FILE_WRITE);
    if (dataFile) {
      dataFile.print(gps.satellites.value());
      dataFile.print(",");
      dataFile.print(gps.location.lat(), 6);
      dataFile.print(",");
      dataFile.print(gps.location.lng(), 6);
      dataFile.print(",");
      dataFile.print(gps.speed.kmph(), 6);
      dataFile.print(",");
      dataFile.print(gps.altitude.meters(), 6);
      dataFile.print(",");
      dataFile.print(gps.date.year());
      dataFile.print("/");
      dataFile.print(gps.date.month());
      dataFile.print("/");
      dataFile.print(gps.date.day());
      dataFile.print(",");
      //TO DO: correct the time zone
      dataFile.print(gps.time.hour()); 
      dataFile.print(":");
      dataFile.print(gps.time.minute()); 
      dataFile.print(":"); 
      dataFile.print(gps.time.second(), 6);
      dataFile.println();
      dataFile.close();
    }
    else
    {
      Serial.print("error opening... ");
    }
    
    //Below code will generate data on the OLED display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("Lat: ");
    display.println(gps.location.lat(), 6);
    display.print("Lng: ");
    display.println(gps.location.lng(), 6);
    display.print("Speed: ");
    display.println(gps.speed.kmph());
    display.print(gps.date.year()); display.print("/");  display.print(gps.date.month()); display.print("/"); display.print(gps.date.day()); display.print(" ");
    display.print((gps.time.hour()+FIX_GPS_HOUR)); display.print(":");  display.print(gps.time.minute()); display.print(":"); display.println(gps.time.second());
    display.display();
    display.clearDisplay();
  }
  else
  {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Searching for GPS satellites");
    display.display();
    display.clearDisplay();
  }
  
  smartdelay(1000);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

// find last prefix number of the dir, for example 11_
int findFilePrefix(File dir) {
  
  int nextFilePrefixNumber = -1;
  int tempNumber;
  int firstIterationInDir = 1;
  int fileDigits[2];

   Serial.println("Found files: ");
   while(true) {

     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     if (!entry.isDirectory() && isDigit(entry.name()[0])) {
       
       //getting first and second digit 
         fileDigits[0] = entry.name()[0] -'0';
         fileDigits[1] = entry.name()[1] -'0';
       
       if (firstIterationInDir++ == 1)
       {
         nextFilePrefixNumber = fileDigits[0] * 10 + fileDigits[1]; 
       }
       else
       {
         tempNumber = fileDigits[0] * 10 + fileDigits[1];
         if (nextFilePrefixNumber < tempNumber)
         {
           nextFilePrefixNumber = tempNumber;
         }
       }
     } 
     entry.close();
   }
   return nextFilePrefixNumber;
}
