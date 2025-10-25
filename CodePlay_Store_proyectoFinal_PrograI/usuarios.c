#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include <string.h>

void loginUsuarios (char archivos[])
{
    FILE* buffer=fopen(archivos, "ab");

    stLogin usuario;

    if(buffer!=NULL)
    {

        printf("Bienvenido a CodePlay\n");

        do
        {
        printf("INICIAR SESION(I)-REGISTRAR(R)\n");
        scanf(" %c", &usuario.opcion);

        if( usuario.opcion=='i' || usuario.opcion=='I')
        {


        }
        else if(usuario.opcion == 'r' || usuario.opcion=='R')
        {


        } else
        {
          printf("Opcion invalida. Elija otra opcion\n");
        }
        }while (usuario.opcion!='i' && usuario.opcion!='I' && usuario.opcion!='r' && usuario.opcion!='R');

        fclose(buffer);
    }
}
