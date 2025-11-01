#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "admin.h"
#include "empresas.h"

int main()
{
    int opcion = 0;

    do
    {
        printf("Bienvenido a CodePlay!\n");
        printf("USUARIO (1)\n");
        printf("ADMIN   (2)\n");
        printf("EMPRESA (3)\n");
        printf("Como desea ingresar? (Ingrese una opcion): ");
        scanf("%i", &opcion);

        if(opcion < 1 || opcion > 3)
        {

            printf("Opcion invalida. Intente de nuevo.\n\n");
        }

    } while(opcion < 1 || opcion > 3);

    switch (opcion)
    {
        case 1:
            loginUsuarios();
            break;

        case 2:
            loginAdmin();
            break;

        case 3:
            loginEmpresas();
            break;
    }

    return 0;
}
