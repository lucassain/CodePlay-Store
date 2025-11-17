#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transacciones.h"
#include "juegos.h"
#include "usuarios.h"

int generarIdTransaccion()
{
    FILE* buffer = fopen(ARCHIVO_TRANSACCIONES, "rb");
    int idMax = 0;

    if (buffer != NULL)
    {
        Transaccion aux;
        while (fread(&aux, sizeof(Transaccion), 1, buffer) == 1)
        {
            if (aux.idTransaccion > idMax)
                idMax = aux.idTransaccion;
        }
        fclose(buffer);
    }
    else
    {

        return 1;
    }

    return idMax + 1;
}

Fecha cargarFechaManual()
{
    Fecha f;
    do {
        printf("Ingrese dia (1-31): ");
        scanf("%d", &f.dia);
    } while (f.dia < 1 || f.dia > 31);

    do {
        printf("Ingrese mes (1-12): ");
        scanf("%d", &f.mes);
    } while (f.mes < 1 || f.mes > 12);

    do {
        printf("Ingrese anio (ej. 2025): ");
        scanf("%d", &f.anio);
    } while (f.anio < 2000);

    return f;
}



void registrarTransaccion(const Transaccion *t)
{
    if (!t) return;
    FILE *f = fopen(ARCHIVO_TRANSACCIONES, "ab");
    if (!f)
    {
        printf("Error: no se pudo abrir %s para escribir.\n", ARCHIVO_TRANSACCIONES);
        return;
    }
    fwrite(t, sizeof(Transaccion), 1, f);
    fclose(f);
}


void procesarCompra(stLogin usuario)
{
    int idBuscado;
    printf("Ingrese el ID del juego a comprar: ");
    scanf("%d", &idBuscado);

    stJuego juego;
    if (!buscarJuegoEnArchivoPorId(idBuscado, &juego))
    {
        printf(" No existe un juego con ID %d.\n", idBuscado);
        return;
    }

    printf("\n¿Confirmar compra de '%s' por $%.2f? (s/n): ",
           juego.nombre, juego.precio);

    char opcion;
    fflush(stdin);
    scanf(" %c", &opcion);

    if (opcion != 's' && opcion != 'S')
    {
        printf("Compra cancelada.\n");
        return;
    }

    Transaccion t;
    t.idTransaccion = generarIdTransaccion();
    t.idJuegoVendido = juego.id;
    t.cantidadVendida = 1;
    t.precioUnitarioVenta = juego.precio;
    t.gananciaTotal = juego.precio;

    strncpy(t.dniCliente, usuario.DNI, sizeof(t.dniCliente)-1);
    t.dniCliente[sizeof(t.dniCliente)-1] = '\0';

    printf("Ingrese la fecha de la compra:\n");
    t.fecha = cargarFechaManual();

    registrarTransaccion(&t);

    printf("\n Compra registrada. ID Transaccion: %d\n", t.idTransaccion);
}


void verTransaccionesResumen()
{
    FILE *f = fopen(ARCHIVO_TRANSACCIONES, "rb");
    if (!f)
    {
        printf("No hay transacciones registradas.\n");
        return;
    }

    Transaccion t;
    printf("\n=== RESUMEN DE TRANSACCIONES ===\n");
    while (fread(&t, sizeof(Transaccion), 1, f) == 1)
    {
        printf("ID %d | Fecha %02d/%02d/%04d | Juego ID %d | Cant %d | Ganancia $%.2f\n",
               t.idTransaccion, t.fecha.dia, t.fecha.mes, t.fecha.anio,
               t.idJuegoVendido, t.cantidadVendida, t.gananciaTotal);
    }
    fclose(f);
}

void verTransaccionDetalle(int idBuscado)
{
    FILE *f = fopen(ARCHIVO_TRANSACCIONES, "rb");
    if (!f)
    {
        printf("No existen transacciones.\n");
        return;
    }

    Transaccion t;
    int encontrado = 0;
    while (fread(&t, sizeof(Transaccion), 1, f) == 1)
    {
        if (t.idTransaccion == idBuscado)
        {
            encontrado = 1;
            printf("\n=== DETALLE TRANSACCION ID %d ===\n", idBuscado);
            printf("Fecha: %02d/%02d/%04d\n", t.fecha.dia, t.fecha.mes, t.fecha.anio);
            printf("Juego ID: %d\n", t.idJuegoVendido);
            printf("Cantidad: %d\n", t.cantidadVendida);
            printf("Precio unitario: $%.2f\n", t.precioUnitarioVenta);
            printf("Ganancia total: $%.2f\n", t.gananciaTotal);
            printf("DNI cliente: %s\n", t.dniCliente);
            break;
        }
    }
    fclose(f);
    if (!encontrado)
        printf(" No existe una transacción con ID %d.\n", idBuscado);
}

void reporteRecaudacionMensual(int mes, int anio)
{
    FILE *f = fopen(ARCHIVO_TRANSACCIONES, "rb");
    if (!f)
    {
        printf("No hay transacciones.\n");
        return;
    }

    Transaccion t;
    float total = 0.0f;
    while (fread(&t, sizeof(Transaccion), 1, f) == 1)
    {
        if (t.fecha.mes == mes && t.fecha.anio == anio)
            total += t.gananciaTotal;
    }
    fclose(f);

    printf("\n Recaudación de %02d/%04d: $%.2f\n", mes, anio, total);
}

void reporteMayorGanancia()
{
    FILE *f = fopen(ARCHIVO_TRANSACCIONES, "rb");
    if (!f)
    {
        printf("No hay transacciones.\n");
        return;
    }

    Transaccion t;
    int found = 0;
    Transaccion best;
    while (fread(&t, sizeof(Transaccion), 1, f) == 1)
    {
        if (!found || t.gananciaTotal > best.gananciaTotal)
        {
            best = t;
            found = 1;
        }
    }
    fclose(f);

    if (!found)
    {
        printf("No se encontraron transacciones.\n");
        return;
    }

    printf("\n Transaccion con mayor ganancia:\n");
    printf("ID: %d | Ganancia: $%.2f | Juego ID: %d | Fecha: %02d/%02d/%04d\n",
           best.idTransaccion, best.gananciaTotal, best.idJuegoVendido,
           best.fecha.dia, best.fecha.mes, best.fecha.anio);
}

void buscarYMostrarTransaccion()
{
    int id;

    printf("Ingrese ID de la transacción a buscar: ");
    scanf("%d", &id);

    mostrarTransaccionPorId(id);
}
void mostrarTransaccionPorId(int id)
{
    FILE *f = fopen(ARCHIVO_TRANSACCIONES, "rb");
    if (!f) {
        printf("No hay transacciones.\n");
        return;
    }

    Transaccion t;
    int encontrado = 0;

    while (fread(&t, sizeof(Transaccion), 1, f) == 1)
    {
        if (t.idTransaccion == id)
        {
            encontrado = 1;

            printf("\n=== DETALLE DE TRANSACCIÓN ===\n");
            printf("ID: %d\n", t.idTransaccion);
            printf("Fecha: %02d/%02d/%d\n",
                   t.fecha.dia, t.fecha.mes, t.fecha.anio);
            printf("Juego ID: %d\n", t.idJuegoVendido);
            printf("Precio Venta: %.2f\n", t.precioUnitarioVenta);
            printf("Ganancia: %.2f\n", t.gananciaTotal);
            printf("DNI cliente: %s\n", t.dniCliente);

            break;
        }
    }

    fclose(f);

    if (!encontrado)
        printf(" Transacción no encontrada.\n");
}
