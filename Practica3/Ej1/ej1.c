#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

int main(int argc, char ** argv){

    int c;      //Variable donde guardamos las opciones que se hayan introducido
    opterr = 0; //Para evitar error en caso de que getopt no reconozca el caracter c

    // Declaracion de las estructuras que almacenarán la informarción de un usuario y de un grupo
    char *lgn;
    int uid;
    char *gname;
    int gid;
    char *name;
    struct passwd *pw;
    struct group *gr;

    static struct option long_options[] = {
        /* Opciones que no van a actuar sobre un flag */
        //  {<nombre largo>, <recibe/no recibe argumento>, NULL, <nombre corto>}
        {"usser", required_argument, NULL, 'u'},
        {"group", required_argument, NULL, 'g'},
        {"active", no_argument, NULL, 'a'},
        {"maingruop", no_argument, NULL, 'm'},
        {"allfroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        /* Necesario para indicar el final de las opciones */
        {0, 0, 0, 0}
    };

    /* Estas variables servirán para almacenar el resultado de procesar la línea
     * de comandos */
    bool aflag = false;
    bool mflag = false;
    bool sflag = false;
    bool hflag = false;
    char *uvalue = NULL;
    char *gvalue = NULL;

    while ((c = getopt_long(argc, argv, "u:g:amsh:", long_options, NULL)) != -1) {
        switch (c) {
        case 'u':
            // printf("Opción -u con valor '%s'\n", optarg");
            uvalue = optarg;
            break;

        case 'g':
            // printf("Opción -g con valor '%s'\n", optarg");
            gvalue = optarg;
            break;

        case 'a':
            // printf("Opción -a\n);
            aflag = true;
            break;

        case 'm':
            // printf("Opción -m\n);
            mflag = true;
            break;

        case 's':
            // printf("Opción -s\n);
            sflag = true;
            break;

        case 'h':
            // printf("Opción -h\n);
            hflag = true;
            break;

        }
    }

    if (argc == 1)
    {
        if ((lgn = getenv("USER")) == NULL || (pw = getpwnam(lgn)) == NULL){
            fprintf(stderr, "Error al obtener información de usuario.\n");
            exit(-1);
        }

        if ((gr = getgrgid(pw->pw_gid)) == NULL){
            fprintf(stderr, "Error al obtener información de grupo.\n");
            exit(-1);
        }

        usuario(pw);
        grupo(gr);
    }

    else
    {
        if (hflag) //Si hemos introducido el comando h
        {
            help();

            exit(0);
        }

        else if ((uvalue != NULL) && (gvalue == NULL) && (!aflag) && (!mflag) && (!sflag) && (!hflag)) //Opcion u
        {
            if (isdigit(*uvalue)) //Si se introduce el uid
            {
                uid = atoi(uvalue);

                if ((pw = getpwuid(uid)) == NULL) //devuelve la estructura
                {
                    fprintf(stderr, "Error al obtener información de usuario.\n");
                    exit(-1);
                }
            }

            else //Se introduce el nombre de login
            {
                lgn = uvalue;

                if ((pw = getpwnam(lgn)) == NULL) //devuelve la estructua
                {
                    fprintf(stderr, "Error al obtener información de usuario\n");
                    exit(-1);
                }
            }

            usuario(pw);

            exit(0);
        }

        else if ((uvalue != NULL) && (gvalue == NULL) && (!aflag) && (mflag) && (!sflag) && (!hflag)) //Opcion usuario + m
        {
            if (isdigit(*uvalue)) //Caso en el que el usuario introduce el uid
            {
                uid = atoi(uvalue);

                if ((pw = getpwuid(uid)) == NULL) //devuelve la estructura
                {
                    fprintf(stderr, "Error al obtener información de usuario\n");
                    exit(-1);
                }
            }

            else //Caso en el que el usuario introduce el nombre de login
            {
                lgn = uvalue;

                if ((pw = getpwnam(lgn)) == NULL) //devuelve la estructura
                {
                    fprintf(stderr, "Error al obtener información de usuario\n");
                    exit(-1);
                }
            }

            usuario(pw); //Imprimimos el usuario

            //imprimir el maingroup

            if ((gr = getgrgid(pw->pw_gid)) == NULL)
            {
                fprintf(stderr, "Error al obtener información de usuario\n");
                exit(-1);
            }

            grupo(gr); //Imprimimos la informacion de grupo

            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue == NULL) && (aflag) && (!mflag) && (!sflag) && (!hflag)) //Opcion a
        {
            if ((lgn = getenv("USER")) == NULL || (pw = getpwnam(lgn)) == NULL)
            {
                fprintf(stderr, "Error al obtener información de usuario.\n");
                exit(-1);
            }

            usuario(pw); //Imprimimos la informacion de usuario

            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue == NULL) && (aflag) && (mflag) && (!sflag) && (!hflag)) //Opcion m + a
        {
            if ((lgn = getenv("USER")) == NULL || (pw = getpwnam(lgn)) == NULL)
            {
                fprintf(stderr, "Error al obtener información de usuario.\n");
                exit(-1);
            }

            usuario(pw); //Imprimimos usuario

            if ((gr = getgrgid(pw->pw_gid)) == NULL)
            {
                fprintf(stderr, "Error al obtener información de grupo.\n");
                exit(-1);
            }

            grupo(gr); //Imprimimos grupo

            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue != NULL) && (!aflag) && (!mflag) && (!sflag) && (!hflag)) //Opcion g
        {
            if (isdigit(*gvalue)) //introduce el gid
            {
                gid = atoi(gvalue);

                if ((gr = getgrgid(gid)) == NULL) //devuelve la estructura
                {
                    fprintf(stderr, "Error al obtener información de usuario.\n");
                    exit(-1);
                }
            }

            else //introduce el nombre de grupo
            {
                gname = gvalue;

                if ((gr = getgrnam(gname)) == NULL) //devuelve la estructura
                {
                    fprintf(stderr, "Error al obtener información de usuario.\n");
                    exit(-1);
                }
            }

            grupo(gr);

            exit(0);
        }

        else if ((uvalue == NULL) && (gvalue == NULL) && (!aflag) && (!mflag) && (sflag) && (!hflag)) //Opcion s
        {
            int num;
            FILE *f;
            //Abriremos el fichero donde estan los grupos y lo leeremos
            f = fopen("/etc/group", "r");

            if (f == NULL)
            {
                printf("Error al abrir el fichero /etc/group");
                exit(-1);
            }

            char buffer[256];
            char *grupo;
            char *psw;
            char *idgrupo;
            char *miembrogrupo;
            printf("Grupo:\n");

            while (fgets(buffer, 256, f) != NULL) //Leemos el fichero
            {
                grupo = strtok(buffer, ":");
                psw = strtok(NULL, ":");
                idgrupo = strtok(NULL, ":");
                strtok(NULL, ":");
                miembrogrupo = strtok(NULL, ":");
                //Se imprime el campo de la estructura que nos interesa
                printf("Nombre del grupo principal: %s\n", grupo);
                printf("Contraseña: %s\n", psw);
                printf("GID: %s\n", idgrupo);
                printf("Miembros secundarios: %s\n", miembrogrupo);
                printf("-----------------------------------------\n");
            }
            exit(0);
        }

        else //Caso en el que llamemos mal al programa
        {
            printf("Correcto llamamiento al programa: ./ej1 <opciones>\n");
            printf("\nCuyas opciones del programa son:\n");
            printf("-h, --help -> Mostrará la información del correcto uso del programa.\n");
            printf("-u, --user <nombre> o <uid> -> Mostrará la información del usuario por pantalla. \n");
            printf("-a, --active -> Mostrará información del usuario actual por pantalla.\n");
            printf("-m, --maingroup -> Mostrará información del usuario, además de la información de su grupo principal.\n");
            printf("-g, --group <nombre> o <gid> -> Mostrará la información del grupo por pantalla.\n");
            printf("-s, --allgroups -> Mostrará información de todos los grupos del sistema por pantalla.\n");
            exit(-1);
        }
    }
    exit(0);
}

void usuario(struct passwd *pw){
    printf("\n");
    printf("Nombre: %s\n", pw->pw_gecos);
    printf("Login: %s\n", pw->pw_name);
    printf("Password: %s\n", pw->pw_passwd);
    printf("UID: %d\n", pw->pw_uid);
    printf("Home: %s\n", pw->pw_dir);
    printf("Shell: %s\n", pw->pw_shell);
    printf("Número de grupo principal: %d\n", pw->pw_gid);
}

void grupo(struct group *gr){
    printf("\n");
    printf("Nombre del grupo: %s\n", gr->gr_name);
    printf("GID: %d\n", gr->gr_gid);
    printf("Miembros: %s\n", *gr->gr_mem);
}

void help(){
    printf("Correcto llamamiento al programa: ./ej1 <opciones>\n");
    printf("\nCuyas opciones del programa son:\n");
    printf("-h, --help -> Mostrará la información del correcto uso del programa.\n");
    printf("-u, --user <nombre> o <uid> -> Mostrará la información del usuario por pantalla. \n");
    printf("-a, --active -> Mostrará información del usuario actual por pantalla.\n");
    printf("-m, --maingroup -> Mostrará información del usuario, además de la información de su grupo principal.\n");
    printf("-g, --group <nombre> o <gid> -> Mostrará la información del grupo por pantalla.\n");
    printf("-s, --allgroups -> Mostrará información de todos los grupos del sistema por pantalla.\n");
}