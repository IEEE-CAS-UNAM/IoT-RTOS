#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

xSemaphoreHandle binSemaphore;

void produce(void *params) // Producer
{
  while (true)
  {
    printf("Add something to share resource\n");
    xSemaphoreGive(binSemaphore);    
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}

void consume(void *params)//consumer
{
  printf("*\n");//se bloque la tarea
  printf("*\n");
  while (true)
  {    
    xSemaphoreTake(binSemaphore, portMAX_DELAY);//bloque da manera indefinida la tarea
    printf("consume resource\n");
  }
}

void app_main(void)
{
  binSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(consume, "Consumidor", 2048, NULL, 1, NULL);
  xTaskCreate(produce, "Productor", 2048, NULL, 1, NULL);
  
}
//Para ver mas aplicaciones consultar
//https://www.freertos.org/a00113.html
  


