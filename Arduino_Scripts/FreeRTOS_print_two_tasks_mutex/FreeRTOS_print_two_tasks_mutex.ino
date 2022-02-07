#include <FreeRTOS_SAMD21.h>

#define SERIAL          SerialUSB //Sparkfun Samd21 Boards


int a = 0;

SemaphoreHandle_t myMutex;
//volatile boolean myMutex = false;

//**************************************************************************
// global variables
//**************************************************************************
TaskHandle_t Handle_aTask;
TaskHandle_t Handle_bTask;
TaskHandle_t Handle_monitorTask;

void myDelayUs(int us)
{
  vTaskDelay( us / portTICK_PERIOD_US );  
}

void myDelayMs(int ms)
{
  vTaskDelay( (ms * 1000) / portTICK_PERIOD_US );  
}

void myDelayMsUntil(TickType_t *previousWakeTime, int ms)
{
  vTaskDelayUntil( previousWakeTime, (ms * 1000) / portTICK_PERIOD_US );  
}

static void threadA( void *pvParameters ) 
{ 
  while(1)
  {
  xSemaphoreTake(myMutex, portMAX_DELAY);
    
    for(int i = 0; i < 5; i++){
    SERIAL.println(i);
    myDelayMs(50);
    }  
  xSemaphoreGive(myMutex);
  }
}

static void threadB( void *pvParameters ) 
{
  while(1)
  {
  //xSemaphoreTake(myMutex, portMAX_DELAY);
    
  for(int i = 0; i < 5; i++){
  SERIAL.println(i);
  myDelayMs(50);
  }
  //xSemaphoreGive(myMutex);
  }
}

//*****************************************************************

void setup() 
{

  SERIAL.begin(115200);

  delay(1000); // prevents usb driver crash on startup, do not omit this
  while (!SERIAL) ;  // Wait for serial terminal to open port before starting program

  SERIAL.println("");
  SERIAL.println("******************************");
  SERIAL.println("        Program start         ");
  SERIAL.println("******************************");
  SERIAL.flush();
  
  myMutex = xSemaphoreCreateMutex();
  if(myMutex == NULL){
    SERIAL.println("Mutex ca nnot be created");
  }
  xTaskCreate(threadA,     "Task A",       256, NULL, tskIDLE_PRIORITY + 3, &Handle_aTask);
  xTaskCreate(threadB,     "Task B",       256, NULL, tskIDLE_PRIORITY + 2, &Handle_bTask);

  // Start the RTOS, this function will never return and will schedule the tasks.
  vTaskStartScheduler();

  // error scheduler failed to start
  // should never get here
  while(1)
  {
    SERIAL.println("Scheduler Failed! \n");
    SERIAL.flush();
    delay(1000);
  }

}


void loop() 
{

}
