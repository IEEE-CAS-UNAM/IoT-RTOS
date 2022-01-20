#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

//Declaracion del identificador de la cola
xQueueHandle queue;

//Declaracion del tamano de la cola
static const uint8_t queue_len = 5;

//Funcion de la tarea Escritora
void Escribir(void *params)
{
  int mensaje = 0; //Declaracion del valor que se envia como mensaje hacia la cola
  while (true)
  {
    mensaje++; //incremento (modificacion del mensaje)
    printf("\n-----Sending  message------\n");
    
    //funcion que manda el mensaje (escribe) a la cola
    if(xQueueSend(queue, (void *)&mensaje, 10 / portTICK_PERIOD_MS)) 
    {//si la cola no se encuentra llena entonces retorna pdTrue por lo tanto se envio con exito
      printf("--> Send message to queue\n");      
    } 
    else 
    {//si la cola se encuentra llena entonces retorna pdFalse por lo tanto no se envio con exito   
      printf("****** Queue Full!!! ******\n");      
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS); //Lapso en el cual se bloque la tarea y por lo tanto
  }                                        //cada vez que termina se manda(escribe) un mensaje 
}                                          //a la cola


//Funcion de la tarea lectora
void Leer(void *params) 
{
  int mensajeRecibido;//Declaracion del espacio en memoria donde se almacena el valor recibido
  while (true)        //desde la cola 
  { 
    //funcion que manda el recibe (lee) de la cola
    if(xQueueReceive(queue, (void *)&mensajeRecibido , 0))
    {//si la cola no se encuentra vacia entonces retorna pdTrue por lo tanto se recibe con exito
      printf("--> Reading message %d\n", mensajeRecibido);
    }
    else
    {//si la cola se encuentra vacia entonces retorna pdFalse por lo tanto no se recibe con exito
      //printf("Queue empty\n");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);//Lapso en el cual se bloque la tarea y por lo tanto
  }                                       //cada vez que termina se recibe(lee) un mensaje 
}                                         //de la cola


void app_main(void)
{
  queue = xQueueCreate(queue_len, sizeof(int));
  xTaskCreate(Escribir, "Escritor", 2048, NULL, 1, NULL);
  xTaskCreate(Leer, "Lector", 2048, NULL,1 , NULL);
}
//Para ver mas aplicaciones consultar
//https://www.freertos.org/a00018.html