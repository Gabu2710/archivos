#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
    char clientes[5][2][40] = {{"Juan", "1789654123"},
                               {"", ""},
                               {"", ""},
                               {"", ""},
                               {"", ""}};

    char habitaciones[9][3][40] = {{"1", "simple", "Dan_Carlton"},
                                   {"2", "doble", "Dan_Carlton"},
                                   {"3", "triple", "Dan_Carlton"},
                                   {"4", "simple", "Swissotel"},
                                   {"5", "doble", "Swissotel"},
                                   {"6", "triple", "Swissotel"},
                                   {"7", "simple", "Sheraton"},
                                   {"8", "doble", "Sheraton"},
                                   {"9", "triple", "Sheraton"}};

    double precios[9] = {90, 120, 160, 65, 100, 140, 85, 110, 150};

    int reservas[10][5] = {{-1, -1, -1, 0, 0},
                           {-1, -1, -1, 0, 0},
                           {-1, -1, -1, 0, 0},
                           {-1, -1, -1, 0, 0},
                           {-1, -1, -1, 0, 0},
                           {-1, -1, -1, 0, 0},
                           {-1, -1, -1, 0, 0},
                           {-1, -1, -1, 0, 0},
                           {-1, -1, -1, 0, 0},
                           {-1, -1, -1, 0, 0}};

    cargarDatos(clientes, habitaciones, precios, reservas);

    int opcion, numHabitacion = -1, numReserva;
    char cedula[40];
    int habitacionSeleccionada = 0;

    do {
        printf("Escoja una opcion:\n1.Buscar Habitacion\n2.Realizar reserva\n3.Ver reservas\n4.Pagar Reserva\n5.Salir\n>> ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("1.Por tamano\n2.Por Hotel\n>> ");
                scanf("%d", &opcion);
                switch (opcion) {
                    case 1:
                        buscarPorTamano(&numHabitacion, habitaciones, precios);
                        habitacionSeleccionada = 1;
                        printf("Habitacion Guardada con exito,"); 
                        printf("Recuerde que si desea cambiar Habitacion, debe buscar Habitacion nuevamente, Gracias\n");
                        break;
                    case 2:
                        buscarHotel(&numHabitacion, habitaciones, precios);
                        habitacionSeleccionada = 1;
                        printf("Habitacion Guardada con exito,");
                        printf("Recuerde que si desea cambiar Habitacion, debe buscar Habitacion nuevamente, Gracias\n"); 
                        break;
                }
                break;
            case 2:
                if (habitacionSeleccionada) {
                    realizarReserva(numHabitacion, habitaciones, clientes, reservas);
                } else {
                    printf("Primero debe buscar y seleccionar una habitacion antes de realizar una reserva.\n");
                }
                break;
            case 3:
                printf("Ingrese la cedula del cliente: ");
                scanf("%s", cedula);
                buscarReservaPorCedula(&numReserva, clientes, reservas, cedula);
                imprimirReserva(numReserva, reservas, habitaciones, precios);
                break;
            case 4:
                printf("Ingrese la cedula del cliente: ");
                scanf("%s", cedula);
                buscarReservaPorCedula(&numReserva, clientes, reservas, cedula);
                if (numReserva != -1) {
                    pagarReserva(numReserva, reservas, habitaciones, precios);
                } else {
                    printf("No se encontro ninguna reserva para la cedula ingresada.\n");
                }
                break;
        }
    } while (opcion != 5);

    guardarDatos(clientes, habitaciones, precios, reservas);

    return 0;
}

