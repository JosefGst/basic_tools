#include <Arduino.h>

#include <EEPROM.h>
 
int addr = 0;
 
void setup()
{
  EEPROM.begin(512);  //Initialize EEPROM
  Serial.begin(115200); 
  Serial.println("");
  Serial.print(char(EEPROM.read(addr)));
  addr++;                      //Increment address
  Serial.print(char(EEPROM.read(addr)));
  addr++;                      //Increment address
  Serial.println(char(EEPROM.read(addr)));
 
  //Read string from eeprom (testing eeprom)
  String strText;   
  for(int i=0;i<14;i++) 
  {
    strText = strText + char(EEPROM.read(0x0F+i)); //Read one by one with starting address of 0x0F    
  }  
 
  Serial.print(strText);  //Print the text
}
 
void loop()
{ 
}