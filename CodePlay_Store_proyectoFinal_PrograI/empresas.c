#include <stdio.h>
#include <stdlib.h>
#include "empresas.h"
#include <string.h>

void loginEmpresas ()
{
    stEmpresa empresa;

    printf("Bienvenido a CodePlay\n");

    printf("INICIAR SESION (I) - REGISTRAR EMPRESA (R)\n");
    scanf(" %c", &empresa.opcion);

    if (empresa.opcion=='i' || empresa.opcion=='I')
    {

    }else if (empresa.opcion=='r' || empresa.opcion=='R')
    {

    }
}
/*char nombre[50];            // Nombre de la empresa
    char email[50];             // Correo de contacto
    char contrasenia[20];       // Contraseña
    char pais[30];              // País de origen
    char descripcion[150];      // Descripción breve
    char fechaRegistro[15];     // Fecha de creación de la cuenta*/

void cargarUnaEmpresa (stEmpresa empresa)
{
    printf("Nombre de la empresa: ");
    scanf("%s", empresa.nombre);

    printf("Mail de contacto: ");
    scanf("%s", empresa.email);

    printf("Pais: ");
    scanf("%s", empresa.pais);

    printf("Contrasenia: ");
    scanf("%s", empresa.contrasenia);

    printf("Fecha de registro: ");
    scanf("%s", empresa.fechaRegistro);

    printf("Ingrese una breve descripcion del: ");
    scanf("%s", empresa.descripcion);
}
