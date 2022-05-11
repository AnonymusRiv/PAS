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

    int c;

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

    if (argc == 1){

    }

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