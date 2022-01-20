#include <stdio.h>
#include "freertos/FreeRTOS.h"//biblioteca con las configutaciones de FreeRTOS
#include "freertos/task.h" //biblioteca para poder crear tareas

//funcion que realiza la tarea
void Tarea1(){
  while(true){
    printf("Tarea1\n");
    vTaskDelay(1000/portTICK_PERIOD_MS); 
  }
  
}


void app_main(void)
{
  //Creacion de la tarea, al momento de crearse se ejecuta
  xTaskCreate(Tarea1, //Funcion a realizar  
     "MiPrimerTarea", //Nombre de la tarea
                2048, //Tamano de la pila en bytes
                NULL, //Parametros que requiere la funcion de la tarea
                   1, //Prioridad de la tarea
               NULL); //Identificador de la tarea
      
}
