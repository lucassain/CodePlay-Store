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
int loginAdmin ();
void creacionAdmin ();
int iniciarSesionAdmin (char archivo[]);
int validarInicioSesionAdmin(char archivo[], stAdmin recibido);
void mostrarUsuariosRec(FILE *buffer);
void mostrarUsuariosAdmin();
int buscarUsuarioPorDni(char dniBuscado[]);
void verUsuarioPorDni();

#endif // ADMIN_H_INCLUDED
