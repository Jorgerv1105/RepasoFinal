#include <stdio.h>
#include <string.h>

#define MaximoAlumnos 50
#define MaximoNombre 50
#define MaximoDireccion 50
#define MaximoCarrera 50

struct InformacionAlumnos {
    int matricula;
    char nombre[MaximoNombre];
    char direccion[MaximoDireccion];
    char carrera[MaximoCarrera];
    float promedio;
};

void ingresarInformacion(struct InformacionAlumnos alumnos[], int *CantAlumnos);
void mostrarInformacion(struct InformacionAlumnos alumnos[], int CantAlumnos);
void guardarDatos(struct InformacionAlumnos alumnos[], int CantAlumnos);
void cargarDatos(struct InformacionAlumnos alumnos[], int *CantAlumnos);
void editarAlumno(struct InformacionAlumnos alumnos[], int CantAlumnos);
void eliminarAlumno(struct InformacionAlumnos alumnos[], int *CantAlumnos);

int main() {
    struct InformacionAlumnos alumnos[MaximoAlumnos];
    int CantAlumnos = 0;
    int opcion;

    cargarDatos(alumnos, &CantAlumnos);

    do {
        printf("\nMenu De Seleccion:\n");
        printf("1. Ingresar nuevos\n");
        printf("2. Mostrar guardados\n");
        printf("3. Guardar en archivo\n");
        printf("4. Editar alumno\n");
        printf("5. Eliminar alumno\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        fflush(stdin);

        switch (opcion) {
            case 1:
                ingresarInformacion(alumnos, &CantAlumnos);
                break;
            case 2:
                mostrarInformacion(alumnos, CantAlumnos);
                break;
            case 3:
                guardarDatos(alumnos, CantAlumnos);
                break;
            case 4:
                editarAlumno(alumnos, CantAlumnos);
                break;
            case 5:
                eliminarAlumno(alumnos, &CantAlumnos);
                break;
            case 6:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}

void ingresarInformacion(struct InformacionAlumnos alumnos[], int *CantAlumnos) {
    if (*CantAlumnos < MaximoAlumnos) {
        printf("Ingrese el nombre de este alumno: ");
        fflush(stdin);
        fgets(alumnos[*CantAlumnos].nombre, MaximoNombre, stdin);
        alumnos[*CantAlumnos].nombre[strcspn(alumnos[*CantAlumnos].nombre, "\n")] = '\0';  // Eliminar el carácter de nueva línea

        printf("\nIngrese la matricula correspondiente: ");
        scanf("%d", &alumnos[*CantAlumnos].matricula);
        fflush(stdin);

        printf("Ingrese la direccion: ");
        fgets(alumnos[*CantAlumnos].direccion, MaximoDireccion, stdin);
        alumnos[*CantAlumnos].direccion[strcspn(alumnos[*CantAlumnos].direccion, "\n")] = '\0';  // Eliminar el carácter de nueva línea

        printf("Ingrese el nombre carrera : ");
        fgets(alumnos[*CantAlumnos].carrera, MaximoCarrera, stdin);
        alumnos[*CantAlumnos].carrera[strcspn(alumnos[*CantAlumnos].carrera, "\n")] = '\0';  // Eliminar el carácter de nueva línea

        printf("Ingrese el promedio de la carrera: ");
        scanf("%f", &alumnos[*CantAlumnos].promedio);

        (*CantAlumnos)++;
        printf("\tDatos guardados.\n");
    } else {
        printf("Se alcanzo el limite.\n");
    }
}

void mostrarInformacion(struct InformacionAlumnos alumnos[], int CantAlumnos) {
    if (CantAlumnos > 0) {
        // Imprimir títulos
        printf("\n%-20s %-10s %-20s %-20s %-10s\n", "Nombre", "Matricula", "Direccion", "Carrera", "Promedio");
        // Imprimir línea horizontal
        printf("--------------------------------------------------------------\n");

        for (int i = 0; i < CantAlumnos; i++) {
            // Imprimir datos del alumno en formato tabular
            printf("%-20s %-10d %-20s %-20s %-10.2f\n",
                    alumnos[i].nombre, alumnos[i].matricula,
                    alumnos[i].direccion, alumnos[i].carrera,
                    alumnos[i].promedio);
        }
    } else {
        printf("No hay datos para mostrar.\n");
    }
}

void guardarDatos(struct InformacionAlumnos alumnos[], int CantAlumnos) {
    FILE *archivo;
    char nombreArchivo[] = "Informacion.txt";  // Nombre del archivo

    archivo = fopen(nombreArchivo, "w");

    if (archivo != NULL) {
        // Imprimir títulos en el archivo
        fprintf(archivo, "%s|;%s;%s;%s;%s\n", "Nombre", "Matricula", "Direccion", "Carrera", "Promedio");

        for (int i = 0; i < CantAlumnos; i++) {
            // Imprimir datos del alumno en formato tabular
            fprintf(archivo, "%s;%d;%s;%s;%.2f\n",
                    alumnos[i].nombre, alumnos[i].matricula,
                    alumnos[i].direccion, alumnos[i].carrera,
                    alumnos[i].promedio);
        }

        fclose(archivo);
        printf("Datos guardados en el archivo \"%s\".\n", nombreArchivo);
    } else {
        printf("Error al abrir el archivo para escritura.\n");
    }
}

void cargarDatos(struct InformacionAlumnos alumnos[], int *CantAlumnos) {
    FILE *archivo;
    char nombreArchivo[] = "Informacion.txt";  // Nombre del archivo

    archivo = fopen(nombreArchivo, "r");

    if (archivo != NULL) {
        while (fscanf(archivo, "%49[^;];%d;%49[^;];%49[^;];%f",
                      alumnos[*CantAlumnos].nombre,
                      &alumnos[*CantAlumnos].matricula,
                      alumnos[*CantAlumnos].direccion,
                      alumnos[*CantAlumnos].carrera,
                      &alumnos[*CantAlumnos].promedio) == 5) {
            (*CantAlumnos)++;
        }

        fclose(archivo);
        printf("Datos cargados desde el archivo \"%s\".\n", nombreArchivo);
    }
}

void editarAlumno(struct InformacionAlumnos alumnos[], int CantAlumnos) {
    int matricula;
    printf("Ingrese la matricula del alumno a editar: ");
    scanf("%d", &matricula);

    for (int i = 0; i < CantAlumnos; i++) {
        if (alumnos[i].matricula == matricula) {
            printf("Ingrese el nuevo nombre: ");
            fflush(stdin);
            fgets(alumnos[i].nombre, MaximoNombre, stdin);
            alumnos[i].nombre[strcspn(alumnos[i].nombre, "\n")] = '\0';  // Eliminar el carácter de nueva línea

            printf("Ingrese la nueva direccion: ");
            fflush(stdin);
            fgets(alumnos[i].direccion, MaximoDireccion, stdin);
            alumnos[i].direccion[strcspn(alumnos[i].direccion, "\n")] = '\0';  // Eliminar el carácter de nueva línea

            printf("Ingrese la nueva carrera: ");
            fflush(stdin);
            fgets(alumnos[i].carrera, MaximoCarrera, stdin);
            alumnos[i].carrera[strcspn(alumnos[i].carrera, "\n")] = '\0';  // Eliminar el carácter de nueva línea

            printf("Ingrese el nuevo promedio: ");
            scanf("%f", &alumnos[i].promedio);

            printf("Datos del alumno editados.\n");
            return;
        }
    }

    printf("No se encontró un alumno con la matricula proporcionada.\n");
}

void eliminarAlumno(struct InformacionAlumnos alumnos[], int *CantAlumnos) {
    int matricula;
    printf("Ingrese la matricula del alumno a eliminar: ");
    scanf("%d", &matricula);

    for (int i = 0; i < *CantAlumnos; i++) {
        if (alumnos[i].matricula == matricula) {
            // Mover los elementos restantes una posición hacia atrás
            for (int j = i; j < *CantAlumnos - 1; j++) {
                strcpy(alumnos[j].nombre, alumnos[j + 1].nombre);
                strcpy(alumnos[j].direccion, alumnos[j + 1].direccion);
                strcpy(alumnos[j].carrera, alumnos[j + 1].carrera);
                alumnos[j].matricula = alumnos[j + 1].matricula;
                alumnos[j].promedio = alumnos[j + 1].promedio;
            }

            (*CantAlumnos)--;
            printf("Alumno eliminado.\n");
            return;
        }
    }

    printf("No se encontró un alumno con la matricula proporcionada.\n");
}