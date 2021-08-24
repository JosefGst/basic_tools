#include <Arduino.h>

#include <EEPROM.h>
 
int addr = 0;
 
void setup()
{
  EEPROM.begin(512);  //Initialize EEPROM
 
  // write to EEPROM.
  EEPROM.write(addr, 'a');    
  addr++;                      //Increment address
  EEPROM.write(addr, 'b');   
  addr++;                      //Increment address
  EEPROM.write(addr, 'C');    
 
  //Write string to eeprom
  String sample = "testing eeprom";
  for(int i=0;i<sample.length();i++)
  {
    EEPROM.write(0x0F+i, sample[i]); //Write one by one with starting address of 0x0F
  }
  EEPROM.commit();    //Store data to EEPROM
}
 
void loop()
{   
}