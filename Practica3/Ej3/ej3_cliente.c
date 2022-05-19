/*
Cliente que envia por una cola abierta para escritura una cadena de caracteres
recogida por teclado, mientras que el valor de esa cadena sea distinto a la palabra exit
*/

#include "ej3_common.h"
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include <signal.h> //Para la parte de señales

// Prototipo de funcion
void funcionLog(char *);

// Para log
char log[MAX_SIZE];

// Buffer para intercambiar mensajes
char buffer[MAX_SIZE];

void senal(int signal);
// Apuntador al fichero de log. No se usa en este ejemplo, pero le servira en ejercicio resumen
FILE *fLog = NULL;

int main(int argc, char **argv) {
    // Cola del servidor
    mqd_t mq_server;


    // Cola del cliente
    mqd_t mq_client;

    // Nombre para la cola de servidor
    char serverQueue[100];

    // Nombre para la cola de cliente
    char clientQueue[100];

    // Tam para el tamaño del buffer
    char tam[MAX_SIZE];

    if (signal(SIGINT, senal) == SIG_ERR){
			printf("[Cliente]: Error al asignal la señal SIGINT\n");
			funcionLog("[Cliente]: Error al asignal la señal SIGINT\n");
	}
	if (signal(SIGTERM, senal == SIG_ERR)){
			printf("[Cliente]: Error al asignal la señal SIGTERM\n");
			funcionLog("[Cliente]: Error al asignal la señal SIGTERM\n");
	}


    // Abrir la cola del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen.
    // No es necesario crearla si se lanza primero el servidor, sino el programa no funciona.

    // Nombre para la cola. Al concatenar el login sera unica en un sistema compartido.
    sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    printf("[Cliente]: El nombre de la cola del servidor es: %s\n", serverQueue);
    sprintf(log, "[Cliente]: El nombre de la cola del servidor es: %s\n", serverQueue);
    funcionLog(log);

    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Cliente]: El nombre de la cola del cliente es: %s\n", clientQueue);
    sprintf(log, "[Cliente]: El nombre de la cola del cliente es: %s\n", clientQueue);
    funcionLog(log);


    mq_server = mq_open(serverQueue, O_WRONLY);
    mq_client = mq_open(clientQueue, O_RDONLY);


    // flag que indica cuando hay que parar. Se escribe palabra exit
    int must_stop = 0;



    // mq_server = mq_open(SERVER_QUEUE, O_WRONLY);
    if (mq_server == (mqd_t)-1) {
        perror("[Cliente]: Error al abrir la cola del servidor\n");
        funcionLog("[Cliente]: Error al abrir la cola del servidor\n");
        exit(-1);
    }

    if (mq_client == (mqd_t)-1) {
        perror("[Cliente]: Error al abrir la cola del cliente\n");
        funcionLog("[Cliente]: Error al abrir la cola del cliente\n");
        exit(-1);
    }
    printf("[Cliente]: El descriptor de la cola de servidor es: %d\n", (int)mq_server);
    sprintf(log, "[Cliente]: El descriptor de la cola de servidor es: %d\n", (int)mq_server);
    funcionLog(log);

    printf("[Cliente]: El descriptor de la cola de cliente es: %d\n", (int)mq_client);
    sprintf(log, "[Cliente]: El descriptor de la cola de cliente es: %d\n", (int)mq_client);
    funcionLog(log);

    printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);
    do {

        // Número de bytes leidos
        ssize_t bytes_read;

        printf("> ");

        /* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
        It stops when either (n-1) characters are read, the newline character is read,
        or the end-of-file is reached, whichever comes first.
        Automáticamente fgets inserta el fin de cadena '\0'
        */
        fgets(buffer, MAX_SIZE, stdin);

        // Enviar y comprobar si el mensaje se manda
        if (mq_send(mq_server, buffer, MAX_SIZE, 0) != 0) {
            perror("[Cliente]: Error al enviar el mensaje\n");
            funcionLog("[Cliente]: Error al enviar el mensaje\n");
            exit(-1);
        }

        if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP)) == 0){
            must_stop = 1;
        }

        else{
            // Recibir el mensaje
            bytes_read = mq_receive(mq_client, tam, MAX_SIZE, NULL);
            // Comprar que la recepción es correcta (bytes leidos no son negativos)
            if (bytes_read < 0) {
                perror("[Cliente]: Error al recibir el mensaje\n");
                funcionLog("[Cliente]: Error al recibir el mensaje\n");
                exit(-1);
            }

        printf("[Cliente]: Número de caracteres recibidos: %s", tam);
        sprintf(log, "[Cliente]: Número de caracteres recibidos: %s", tam);
        funcionLog(log);
        }


        // Iterar hasta escribir el código de salida
    } while (!must_stop); // Iterar hasta que llegue el código de salida, es decir, la palabra exit

    // Cerrar la cola del servidor
    if (mq_close(mq_server) == (mqd_t)-1) {
        perror("[Cliente]: Error al cerrar la cola del servidor\n");
        funcionLog("[Cliente]: Error al cerrar la cola del servidor\n");
        exit(-1);
    }

    if (mq_close(mq_client) == (mqd_t)-1) {
        perror("[Cliente]: Error al cerrar la cola del cliente\n");
        funcionLog("[Cliente]: Error al cerrar la cola del cliente\n");
        exit(-1);
    }
    return 0;
}

/* Función auxiliar, escritura de un log.
No se usa en este ejemplo, pero le puede servir para algun
ejercicio resumen */
void funcionLog(char *mensaje) {
    int resultado;
    char nombreFichero[100];
    char mensajeAEscribir[300];
    time_t t;

    // Abrir el fichero
    sprintf(nombreFichero, "log-cliente.txt");
    if (fLog == NULL) {
        fLog = fopen(nombreFichero, "at");
        if (fLog == NULL) {
            perror("Error abriendo el fichero de log");
            exit(1);
        }
    }

    // Obtener la hora actual
    t = time(NULL);
    struct tm *p = localtime(&t);
    strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

    // Vamos a incluir la hora y el mensaje que nos pasan
    sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);

    // Escribir finalmente en el fichero
    resultado = fputs(mensajeAEscribir, fLog);
    if (resultado < 0)
        perror("Error escribiendo en el fichero de log");

    fclose(fLog);
    fLog = NULL;
}

void senal(int signal){
    printf("[Cliente]: Señal capturada, id: %d\n", signal);
    sprintf(log, "[Cliente]: Señal capturada, id: %d\n", signal);
    funcionLog(log);
    sprintf(buffer, "exit");
}