#include "scheduler.h"
#include "Arduino_FreeRTOS.h"
#include "task.h"


TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
TaskHandle_t xHandle3 = NULL;
TaskHandle_t xHandle4 = NULL;
TaskHandle_t current_task = NULL;

void loop() {}



static void testFunc1( void *pvParameters )
{
	(void) pvParameters;
  unsigned long Task1_start = xTaskGetTickCount() *15 ;
  Serial.print("Task 1 starts at: ");
  Serial.println(Task1_start); 
  for(int i=0; i<6; i++){
    Serial.println("Task 1 is running  ");
	  vTaskDelay(1);
  }
	
  unsigned long Task1_end = xTaskGetTickCount() *15 ;

  Serial.print("Task 1 ends at: ");
  Serial.println(Task1_end); 

}


static void testFunc2( void *pvParameters )
{ 
  (void) pvParameters;
  unsigned long Task2_start = xTaskGetTickCount() *15 ;
  Serial.print("Task 2 starts at: ");
  Serial.println(Task2_start);

  for(int i=0; i<12; i++){
    Serial.println("Task 2 is running  ");
	  vTaskDelay(1);
  }
	
  unsigned long Task2_end = xTaskGetTickCount() *15 ;

  Serial.print("Task 2 ends at: ");
  Serial.println(Task2_end);
 
}
 static void testFunc3( void *pvParameters )
 { 
   (void) pvParameters;
   TickType_t Task3_start = xTaskGetTickCount() *15 ;
   Serial.print("Task 3 starts at: ");
   Serial.println(Task3_start);

   for(int i=0; i<4; i++){
       Serial.println("Task 3 is running ");
       vTaskDelay(1);
   }

 
   TickType_t Task3_end = xTaskGetTickCount() *15 ;

   Serial.print("Task 3 ends at: ");
   Serial.println(Task3_end);
 }
 static void testFunc4( void *pvParameters )
 { 
   (void) pvParameters;
   TickType_t Task4_start = xTaskGetTickCount() *15 ;
   Serial.print("Task 4 starts at: ");
   Serial.println(Task4_start);

   for(int i=0; i<8; i++){
       Serial.println("Task 4 is running  ");
       vTaskDelay(1);
   }

 	
   TickType_t Task4_end = xTaskGetTickCount() *15 ;

   Serial.print("Task 4 ends at: ");
   Serial.println(Task4_end);

 }
int main( void )
{
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
	char c1 = 'A';
	char c2 = 'B';
  char c3 = 'C';
  char c4 = 'D';			
	vSchedulerInit();
  vSchedulerPeriodicTaskCreate(testFunc1, "t1", configMINIMAL_STACK_SIZE, &c1, 4, &xHandle1, pdMS_TO_TICKS(0), pdMS_TO_TICKS(400), pdMS_TO_TICKS(100), pdMS_TO_TICKS(400));
  vSchedulerPeriodicTaskCreate(testFunc2, "t2", configMINIMAL_STACK_SIZE, &c2, 3, &xHandle2, pdMS_TO_TICKS(0), pdMS_TO_TICKS(800), pdMS_TO_TICKS(200), pdMS_TO_TICKS(700));
  vSchedulerPeriodicTaskCreate(testFunc3, "t3", configMINIMAL_STACK_SIZE, &c3, 2, &xHandle3, pdMS_TO_TICKS(0), pdMS_TO_TICKS(600), pdMS_TO_TICKS(150), pdMS_TO_TICKS(600));
  vSchedulerPeriodicTaskCreate(testFunc4, "t4", configMINIMAL_STACK_SIZE, &c4, 1, &xHandle4, pdMS_TO_TICKS(0), pdMS_TO_TICKS(5000), pdMS_TO_TICKS(300), pdMS_TO_TICKS(5000));
   TickType_t StartTime = xTaskGetTickCount();
  vSchedulerStart();
  TickType_t EndTime = xTaskGetTickCount();
  int overhead = (EndTime - StartTime)*15 ;
 vApplicationTickHook();
  current_task = xTaskGetCurrentTaskHandle();
  char current_taskname = pcTaskGetName(current_task);
  Serial.println(current_taskname);
	
	for( ;; );
}