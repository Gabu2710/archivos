#include <stdio.h>
#include <string.h>
#include "funciones.h"

void buscarPorTamano(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char tamano[20];
    int opcionValida = 0;
    int selec = 0;

    while (!opcionValida) {
        printf("Ingrese el tamano de la habitacion (simple, doble, triple): ");
        scanf("%s", tamano);
        for (int i = 0; i < 9; i++) {
            if (strcmp(habitaciones[i][1], tamano) == 0) {
                printf("Habitacion %s, Hotel %s, Precio %.2f\n", habitaciones[i][0], habitaciones[i][2], precios[i]);
                opcionValida = 1;
            }
        }
        if (!opcionValida) {
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
    do {
        printf("Ingrese el numero de la habitacion que desea: ");
        scanf("%d", numHabitacion);
        *numHabitacion -= 1;
        printf("Desea guardar la habitacion? (1=Si, 2=No): ");
        scanf("%d", &selec);
    } while (selec != 1);
}

void buscarHotel(int *numHabitacion, char habitaciones[][3][40], double precios[]) {
    char hotel[40];
    int opcionValida = 0;
    int selec = 0;

    while (!opcionValida) {
        printf("Ingrese el nombre del hotel (Dan_Carlton, Swissotel, Sheraton): ");
        scanf("%s", hotel);
        for (int i = 0; i < 9; i++) {
            if (strcmp(habitaciones[i][2], hotel) == 0) {
                printf("Habitacion %s, Tipo %s, Precio %.2f\n", habitaciones[i][0], habitaciones[i][1], precios[i]);
                opcionValida = 1;
            }
        }
        if (!opcionValida) {
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
    do {
        printf("Ingrese el numero de la habitacion que desea: ");
        scanf("%d", numHabitacion);
        *numHabitacion -= 1;
        printf("Desea guardar la habitacion? (1=Si, 2=No): ");
        scanf("%d", &selec);
    } while (selec != 1);
}

void realizarReserva(int numHabitacion, char habitaciones[][3][40], char clientes[][2][40], int reservas[][5]) {
    char nombre[40], cedula[40];
    int diasEstancia;

    printf("Ingrese el nombre del cliente: ");
    scanf("%s", nombre);
    printf("Ingrese la cedula del cliente: ");
    scanf("%s", cedula);
    printf("Ingrese la cantidad de dias de estancia: ");
    scanf("%d", &diasEstancia);

    int clienteIndex = -1;
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][0], "") == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("No hay espacio para nuevos clientes.\n");
        return;
    }

    strcpy(clientes[clienteIndex][0], nombre);
    strcpy(clientes[clienteIndex][1], cedula);

    int reservaIndex = -1;
    for (int i = 0; i < 10; i++) {
        if (reservas[i][0] == -1) {
            reservaIndex = i;
            break;
        }
    }

    if (reservaIndex == -1) {
        printf("No hay espacio para nuevas reservas.\n");
        return;
    }

    reservas[reservaIndex][0] = numHabitacion;
    reservas[reservaIndex][1] = clienteIndex;
    reservas[reservaIndex][2] = 0; 
    reservas[reservaIndex][3] = 1; 
    reservas[reservaIndex][4] = diasEstancia;

    printf("Reserva realizada con exito.\n");
}

void buscarReservaPorCedula(int *numReserva, char clientes[][2][40], int reservas[][5], char cedula[]) {
    for (int i = 0; i < 10; i++) {
        if (reservas[i][1] != -1 && strcmp(clientes[reservas[i][1]][1], cedula) == 0) {
            *numReserva = i;
            return;
        }
    }

    *numReserva = -1;
}

void imprimirReserva(int numReserva, int reservas[][5], char habitaciones[][3][40], double precios[]) {
    if (numReserva == -1) {
        printf("No hay reserva para mostrar.\n");
        return;
    }

    int numHabitacion = reservas[numReserva][0];
    printf("Reserva #%d:\n", numReserva + 1);
    printf("Habitacion: %s\n", habitaciones[numHabitacion][0]);
    printf("Tipo: %s\n", habitaciones[numHabitacion][1]);
    printf("Hotel: %s\n", habitaciones[numHabitacion][2]);
    printf("Precio: %.2f\n", precios[numHabitacion]);
    printf("Dias de estancia: %d\n", reservas[numReserva][4]);
    printf("Estado de pago: %s\n", reservas[numReserva][2] ? "Pagada" : "No pagada");
}

void pagarReserva(int numReserva, int reservas[][5], char habitaciones[][3][40], double precios[]) {
    if (numReserva == -1) {
        printf("No hay reserva para pagar.\n");
        return;
    }

    reservas[numReserva][2] = 1; 
    printf("Reserva pagada con exito.\n");
}

void guardarDatos(char clientes[][2][40], char habitaciones[][3][40], double precios[], int reservas[][5]) {
    FILE *fclientes = fopen("D:\\Documentos\\UDLA\\PROGRAMACION\\archivos\\fclientes", "wb");
    FILE *fhabitaciones = fopen("D:\\Documentos\\UDLA\\PROGRAMACION\\archivos\\fhabitaciones", "wb");
    FILE *fprecios = fopen("D:\\Documentos\\UDLA\\PROGRAMACION\\archivos\\fprecios", "wb");
    FILE *freservas = fopen("D:\\Documentos\\UDLA\\PROGRAMACION\\archivos\\freservas", "wb");

    if (fclientes && fhabitaciones && fprecios && freservas) {
        fwrite(clientes, sizeof(clientes[0]), 5, fclientes);
        fwrite(habitaciones, sizeof(habitaciones[0]), 9, fhabitaciones);
        fwrite(precios, sizeof(double), 9, fprecios);
        fwrite(reservas, sizeof(reservas[0]), 10, freservas);

        fclose(fclientes);
        fclose(fhabitaciones);
        fclose(fprecios);
        fclose(freservas);
    } else {
        printf("Error al abrir los archivos para guardar los datos.\n");
    }
}

void cargarDatos(char clientes[][2][40], char habitaciones[][3][40], double precios[], int reservas[][5]) {
    FILE *fclientes = fopen("D:\\Documentos\\UDLA\\PROGRAMACION\\archivos\\fclientes", "rb");
    FILE *fhabitaciones = fopen("D:\\Documentos\\UDLA\\PROGRAMACION\\archivos\\fhabitaciones", "rb");
    FILE *fprecios = fopen("D:\\Documentos\\UDLA\\PROGRAMACION\\archivos\\fprecios", "rb");
    FILE *freservas = fopen("D:\\Documentos\\UDLA\\PROGRAMACION\\archivos\\freservas", "rb");

    if (fclientes && fhabitaciones && fprecios && freservas) {
        fread(clientes, sizeof(clientes[0]), 5, fclientes);
        fread(habitaciones, sizeof(habitaciones[0]), 9, fhabitaciones);
        fread(precios, sizeof(double), 9, fprecios);
        fread(reservas, sizeof(reservas[0]), 10, freservas);

        fclose(fclientes);
        fclose(fhabitaciones);
        fclose(fprecios);
        fclose(freservas);
    } else {
        printf("Error al abrir los archivos para cargar los datos.\n");
    }
}