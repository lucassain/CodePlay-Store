#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

#define DIMENSION_LOGIN 30
#define ARCHIVOS_USUARIOS "usuarios.dat"

typedef struct
{
    char usuario[DIMENSION_LOGIN];
    char email[DIMENSION_LOGIN];
    char contrasenia[DIMENSION_LOGIN];
    char DNI[DIMENSION_LOGIN];
} stLogin;

// Prototipado
int loginUsuarios(stLogin *usuarioActual);
void registrarUnUsuario (stLogin* usuario);
int registrarseUsuario (stLogin* usuario);
int existeUsuario (char archivo[], stLogin nuevoUsuario);
int validarEmail (char email[]);
int validarUsuario (char nombreDeUsuario[]);
int validarContrasenia (char contrasenia[]);
int validarDni (char DNI[]);
void guardarUsuarios (char archivo[], stLogin usuarios);
int iniciarSesion(char archivo[], stLogin *usuarioActual);
void configuracion(stLogin* usuarioActual);
void editarDatosPerfil(stLogin* usuarioActual);
void modificarPerfil (char DniABuscar[], stLogin usuarioModificado);
void menuUsuario(stLogin* usuarioActual);
void inicializarArchivoUsuarios();
void crearArchivoDeUnUsuario(stLogin usuario);
void mostrarAyuda();
void mostrarUnUsuario (stLogin user);
void mostrarUsuarios (char archivo[]);

#endif
