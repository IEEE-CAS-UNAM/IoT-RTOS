#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//parametros

int capacity = 3;

// identificadores de tareas (task handles)
static TaskHandle_t task1 = NULL; //filling
static TaskHandle_t task2 = NULL; //emptying

//funcion que realiza la tarea 1 (tarea de llenado)
void fill(void * params)
{
  while(1)
  {
    printf("\n -----Filling------\n"); //muestra en el monitor que se esta llenando el contenedor
    for (int i = 0; i < capacity; ++i)
    {
      printf("*\n");// se llena el contenedor
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      if(i == capacity - 1){
        printf("Full"); //si el iterador supera el valor de la capacidad
      }                 // se muestra en el mensaje en el monitor de lleno
    }
    printf("\n");
    
    vTaskDelay(2000 / portTICK_PERIOD_MS); //se manda al sub-estado de bloqueo por 2000 ticks
  }
  
}

//funcion que realiza la tarea 2 (tarea de vaciado)
void empty(void * params)
{
  while(1)
  {
    printf("\n -----Empyting-----\n");
    for (int i = capacity; i > 0 ; --i)
    {
      printf("O\n"); //se vacia el contenedor
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      if(i == 1){
        printf("  Empty\n");//si el iterador disminuye antes de llegar al cero
      }                     // se muestra en el mensaje en el monitor de vacio
    }
    printf("\n");
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);//se manda al sub-estado de bloqueo por 2000 ticks
  }
  
}




void app_main(void)
{
  printf("Status\n");
  xTaskCreate(fill,"Filling",2048,NULL,1,
   &task1);
    
  xTaskCreate(empty,"Emptying",2048,NULL,1,
   &task2);

    //Parte que demuestra como suspender y eliminar tareas
    
    /*
    while(1){
      for (int i = 0; i < 3; i++){
        vTaskSuspend(task1); // manda a la tarea al sub-estado suspedido
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        vTaskResume(task1); // saca a la tarea del sub-estado suspedido
        vTaskDelay(2000 / portTICK_PERIOD_MS);
      }
      if (task2 != NULL){
        vTaskDelete(task2);  //elimina la tarea 2 (vaciado)     
        task2 = NULL; // IMPORTANTE ELIMINAR EL IDENTIFICADOR TAMBIEN!!!
      }
    }
  */
    //Para ver mas aplicaciones consultar
    //https://www.freertos.org/a00112.html

}
