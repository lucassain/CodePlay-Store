#ifndef TRANSACCIONES_H_INCLUDED
#define TRANSACCIONES_H_INCLUDED

#include "juegos.h"
#include "usuarios.h"
#include "empresas.h"
#define ARCHIVO_TRANSACCIONES "transacciones.dat"


typedef struct {
    int idTransaccion;
    Fecha fecha;
    int idJuegoVendido;
    int cantidadVendida;
    float precioUnitarioVenta;
    float gananciaTotal;
    char dniCliente[15];
} Transaccion;

//Prototipado

int generarIdTransaccion();
Fecha cargarFechaManual();
void registrarTransaccion(const Transaccion *t);
void procesarCompra(stLogin usuario);
void verTransaccionesResumen();
void verTransaccionDetalle(int idBuscado);
void reporteRecaudacionMensual(int mes, int anio);
void reporteMayorGanancia();
void buscarYMostrarTransaccion();
void mostrarTransaccionPorId(int id);

#endif // TRANSACCIONES_H_INCLUDED

