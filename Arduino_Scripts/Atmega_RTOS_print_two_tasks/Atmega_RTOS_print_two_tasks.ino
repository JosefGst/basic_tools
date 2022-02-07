//**************************************************************************
// FreeRtos on Samd21
// By Scott Briscoe
//
// Project is a simple example of how to get FreeRtos running on a SamD21 processor
// Project can be used as a template to build your projects off of as well
//
//**************************************************************************

#include <Arduino_FreeRTOS.h>

//**************************************************************************
// Type Defines and Constants
//**************************************************************************


//**************************************************************************
// global variables
//**************************************************************************
TaskHandle_t Handle_aTask;
TaskHandle_t Handle_bTask;


void myDelayUs(int us)
{
  vTaskDelay( us / portTICK_PERIOD_MS );  
}

void myDelayMs(int ms)
{
  vTaskDelay( (ms * 1000) / portTICK_PERIOD_MS );  
}

void myDelayMsUntil(TickType_t *previousWakeTime, int ms)
{
  vTaskDelayUntil( previousWakeTime, (ms * 1000) / portTICK_PERIOD_MS );  
}

//*****************************************************************
// Create a thread that prints out A to the screen every two seconds
// this task will delete its self after printing out afew messages
//*****************************************************************
static void threadA( void *param ) 
{
  (void) param;
  Serial.println("Thread A: Started");

  while(1)
  {
    Serial.println("A");
    Serial.flush();
    myDelayMs(2000);
  }

}


//*****************************************************************
// Create a thread that prints out B to the screen every second
// this task will run forever
//*****************************************************************
static void threadB( void *param ) 
{
  (void) param;
  Serial.println("Thread B: Started");

  while(1)
  {
    Serial.println("B");
    Serial.flush();
    myDelayMs(2000);
  }

}


//*****************************************************************

void setup() 
{

  Serial.begin(115200);

  delay(1000); // prevents usb driver crash on startup, do not omit this
  while (!Serial) ;  // Wait for Serial terminal to open port before starting program

  Serial.println("");
  Serial.println("******************************");
  Serial.println("        Program start         ");
  Serial.println("******************************");
  Serial.flush();

  
  // Create the threads that will be managed by the rtos
  // Sets the stack size and priority of each task
  // Also initializes a handler pointer to each task, which are important to communicate with and retrieve info from tasks
  xTaskCreate(threadA,     "Task A",       256, NULL, tskIDLE_PRIORITY + 3, &Handle_aTask);
  xTaskCreate(threadB,     "Task B",       256, NULL, tskIDLE_PRIORITY + 2, &Handle_bTask);
 

}

//*****************************************************************
// This is now the rtos idle loop
// No rtos blocking functions allowed!
//*****************************************************************
void loop() 
{
    
}


//*****************************************************************
