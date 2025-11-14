#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#define DIMENSION_LOGIN 30
#define ARCHIVOS_ADMINS "admins.dat"


typedef struct
{
    char usuario[DIMENSION_LOGIN];
    char email[DIMENSION_LOGIN];
    char contrasenia[DIMENSION_LOGIN];

} stAdmin;



// Prototipo
int loginAdmin(stAdmin *adminActual);
void creacionAdmin ();
int iniciarSesionAdmin(char archivo[], stAdmin *adminActual);
int validarInicioSesionAdmin(char archivo[], stAdmin recibido);
void mostrarUsuariosRec(FILE *buffer);
void mostrarUsuariosAdmin();
int buscarUsuarioPorDni(char dniBuscado[]);
void verUsuarioPorDni();
void menuAdmin(stAdmin* adminActual);

#endif // ADMIN_H_INCLUDED
