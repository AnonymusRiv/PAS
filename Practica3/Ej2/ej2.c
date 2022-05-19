#include <errno.h> //Control de errores
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Para la funcion strerror(), que permite describir el valor de errno como cadena.
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

//proceso 1 genera dos numeros aleatorios flotantes y envia la suma al proceso 2

int main() {
    // Para realizar el fork
    pid_t rf;
    int flag, status;
    // Para controlar los valores devueltos por las funciones (control de errores)
    float resultado;
    // Lo que vamos a leer y escribir de la tubería
    float suma = 0;
    // Para crear los números aleatorios
    float numeroAleatorio;
    // Descriptores de los dos extremos de la tubería
    int fileDes[2];
    // Iterador
    int i = 0;

    // Creamos la tubería
    resultado = pipe(fileDes);
    if (resultado == -1) {
        printf("\nERROR al crear la tubería.\n");
        exit(1);
    }

    rf = fork();
    switch (rf) {
    case -1:
        printf("No se ha podido crear el proceso hijo...\n");
        exit(EXIT_FAILURE);
    case 0:
        printf("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());

        close(fileDes[1]);

        for (i = 0; i < 1; i++) {
            // Recibimos un mensaje a través de la cola
            resultado = read(fileDes[0], &suma, sizeof(float));

            if (resultado != sizeof(float)) {
                printf("\n[HIJO]: ERROR al leer de la tubería...\n");
                exit(EXIT_FAILURE);
            }
            // Imprimimos el campo que viene en la tubería
            printf("[HIJO]: Leo la suma de los números aleatorios de la tubería: %f\n", suma);
        }
        // Cerrar el extremo que he usado
        printf("[HIJO]: Tubería cerrada ...\n");
        close(fileDes[0]);
        break;

    default:
        printf("[PADRE]: Mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);

        close(fileDes[0]);

        srand(time(NULL)); // Semilla de los números aleatorios establecida a la hora actual

        for (i = 0; i < 2; i++) {
            // Rellenamos los campos del mensaje que vamos a enviar
            numeroAleatorio = rand() % 5000; // Número aleatorio entre 0 y 4999

            printf("[PADRE]: El %d valor aleatorio es: %f\n", i+1, numeroAleatorio);

            suma=suma + numeroAleatorio;

        }

        printf("[PADRE]: Escribo la suma de los números aleatorio en la tubería...: %f\n", suma);

            // Mandamos el mensaje
            resultado = write(fileDes[1], &suma, sizeof(float));

            if (resultado != sizeof(float)) {
                printf("\n[PADRE]: ERROR al escribir en la tubería...\n");
                exit(EXIT_FAILURE);
            }

        // Cerrar el extremo que he usado
        close(fileDes[1]);
        printf("[PADRE]: Tubería cerrada...\n");

        /*Espera del padre a los hijos*/
        while ((flag = wait(&status)) > 0) {
            if (WIFEXITED(status)) {
                printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) { // Para seniales como las de finalizar o matar
                printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
            }
        }
        if (flag == (pid_t)-1 && errno == ECHILD) {
            printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
        } else {
            printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}
