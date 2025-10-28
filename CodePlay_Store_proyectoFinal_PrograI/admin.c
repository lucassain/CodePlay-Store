#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include <string.h>

int main()
{
    loginAdmin ();
    return 0;
}
void loginAdmin ()
{
    int registro=0;


    printf("Bienvenido a CodePlay\n");
    printf("Ingrese con su cuenta de admin:\n");

    creacionAdmin ()
    iniciarSesionAdmin (ARCHIVOS_ADMINS);


}
void creacionAdmin ()
{
    FILE* buffer=fopen(ARCHIVO_ADMINS, "rb");

    if(buffer==NULL){
    buffer = fopen(ARCHIVO_ADMINS, "wb");


    stAdmin admins[]= {
    {"Lucas","lucasSain@gmail.com","lucaspro"},
    {"Franco","francobidegain@gmail.com","bidepro"},
    {"Santi", "santiolea@gmail.com","santipro"}
    };

  fwrite(admins, sizeof(stAdmin),3,buffer);
  fclose(buffer);



}

}

void iniciarSesionAdmin (char archivo[])
{
    stAdmin ingreso;

        printf("INICIAR SESION\n");
        printf("Ingrese su direccion de correo electronico: ");
        scanf("%s", ingreso.email);
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", ingreso.usuario);
        printf("Ingrese su contrasenia: ");
        scanf("%s", ingreso.contrasenia);

    validarInicioSesionAdmin(archivo, ingreso);



}
 int validarInicioSesionAdmin(char archivo[], stAdmin recibido)
 {

 FILE* buffer=fopen(archivo, "rb");
 stAdmin aux;


 while (fread(&aux, sizeof(stAdmin), 1, buffer)==1)
        {
            if (strcmp(aux.usuario, recibido.usuario)==0 && strcmp(aux.email, recibido.email)==0 && strcmp(aux.contrasenia, recibido.contrasenia)==0)
            {
                printf("Inicio de sesion exitoso. Bienvenido admin %s!\n", ingreso.usuario);
                registroExitoso=1;
                break;
            }

        }
        if(registroExitoso==0)
        {
            printf("Correo,usuario o contrasenia incorrectas\n");
        }

        fclose(buffer);
 }
