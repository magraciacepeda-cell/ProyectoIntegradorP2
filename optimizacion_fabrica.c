//Arlette Luque, Maria Gracia Cepeda, Camila Vaca
//Sistema para revisar si una fabrica puede cumplir con la produccion solicitada.
//Se usan arreglos paralelos, funciones y punteros como los ejercicios de clase.

#include <stdio.h>
#include <string.h>

#define MAX 5

///Variables globales: los datos de cada producto usan la misma posicion.
char producto[MAX][50];
int demanda[MAX];
float horasUnidad[MAX];
float recurso1[MAX];
float recurso2[MAX];
float recurso3[MAX];
int conpro = 0;

//Prototipos de las funciones.
void ingresar_productos(void);
void mostrar_productos(void);
int buscar_producto(char nombreBuscado[50]);
void editar_producto(void);
void eliminar_producto(void);
void calcular_totales(float *totalHoras, float *totalR1, float *totalR2, float *totalR3);
void revisar_produccion(void);

int main(void)
{
    int op;

    do
    {
        printf("\n======= OPTIMIZACION DE PRODUCCION =======\n");
        printf("1. Ingresar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Revisar si se puede cumplir la demanda\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            ingresar_productos();
            break;
        case 2:
            mostrar_productos();
            break;
        case 3:
            editar_producto();
            break;
        case 4:
            eliminar_producto();
            break;
        case 5:
            revisar_produccion();
            break;
        case 0:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion no valida.\n");
            break;
        }
    } while (op != 0);

    return 0;
}

void ingresar_productos(void)
{
    char nombreNuevo[50];

    if (conpro < MAX)
    {
        printf("Ingrese el nombre del producto: ");
        scanf(" %49[^\n]", nombreNuevo);

        // No se permite registrar dos productos con el mismo nombre.
        if (buscar_producto(nombreNuevo) != -1)
        {
            printf("Ese producto ya esta registrado.\n");
        }
        else
        {
            strcpy(producto[conpro], nombreNuevo);
            printf("Ingrese la cantidad demandada: ");
            scanf("%d", &demanda[conpro]);
            printf("Ingrese las horas por unidad: ");
            scanf("%f", &horasUnidad[conpro]);
            printf("Ingrese el consumo de recurso 1 por unidad: ");
            scanf("%f", &recurso1[conpro]);
            printf("Ingrese el consumo de recurso 2 por unidad: ");
            scanf("%f", &recurso2[conpro]);
            printf("Ingrese el consumo de recurso 3 por unidad: ");
            scanf("%f", &recurso3[conpro]);

            conpro++;
            printf("Producto ingresado correctamente.\n");
        }
    }
    else
    {
        printf("Ya se registro el maximo de cinco productos.\n");
    }
}

void mostrar_productos(void)
{
    int i;

    if (conpro == 0)
    {
        printf("No hay productos registrados.\n");
    }
    else
    {
        printf("\nProducto       Demanda   Horas/unidad   R1/unidad   R2/unidad   R3/unidad\n");
        for (i = 0; i < conpro; i++)
        {
            printf("%-15s %-9d %-14.2f %-11.2f %-11.2f %.2f\n",
                   producto[i], demanda[i], horasUnidad[i],
                   recurso1[i], recurso2[i], recurso3[i]);
        }
    }
}

//Busca el nombre comparando uno por uno. Devuelve la posicion o -1.
int buscar_producto(char nombreBuscado[50])
{
    int i;

    for (i = 0; i < conpro; i++)
    {
        if (strcmp(producto[i], nombreBuscado) == 0)
        {
            return i;
        }
    }

    return -1;
}

void editar_producto(void)
{
    char nombreBuscado[50];
    int posicion;

    printf("Ingrese el nombre del producto que desea editar: ");
    scanf(" %49[^\n]", nombreBuscado);

    posicion = buscar_producto(nombreBuscado);

    if (posicion == -1)
    {
        printf("No se encontro el producto.\n");
    }
    else
    {
        printf("Nuevo nombre del producto: ");
        scanf(" %49[^\n]", producto[posicion]);
        printf("Nueva cantidad demandada: ");
        scanf("%d", &demanda[posicion]);
        printf("Nuevas horas por unidad: ");
        scanf("%f", &horasUnidad[posicion]);
        printf("Nuevo consumo de recurso 1 por unidad: ");
        scanf("%f", &recurso1[posicion]);
        printf("Nuevo consumo de recurso 2 por unidad: ");
        scanf("%f", &recurso2[posicion]);
        printf("Nuevo consumo de recurso 3 por unidad: ");
        scanf("%f", &recurso3[posicion]);
        printf("Producto actualizado.\n");
    }
}

void eliminar_producto(void)
{
    char nombreBuscado[50];
    int posicion, i;

    printf("Ingrese el nombre del producto que desea eliminar: ");
    scanf(" %49[^\n]", nombreBuscado);

    posicion = buscar_producto(nombreBuscado);

    if (posicion == -1)
    {
        printf("No se encontro el producto.\n");
    }
    else
    {
        /* Se recorren los arreglos para llenar el espacio eliminado. */
        for (i = posicion; i < conpro - 1; i++)
        {
            strcpy(producto[i], producto[i + 1]);
            demanda[i] = demanda[i + 1];
            horasUnidad[i] = horasUnidad[i + 1];
            recurso1[i] = recurso1[i + 1];
            recurso2[i] = recurso2[i + 1];
            recurso3[i] = recurso3[i + 1];
        }

        conpro--;
        printf("Producto eliminado.\n");
    }
}

// Los punteros permiten devolver los cuatro totales a la funcion que llama.
void calcular_totales(float *totalHoras, float *totalR1, float *totalR2, float *totalR3)
{
    int i;

    *totalHoras = 0;
    *totalR1 = 0;
    *totalR2 = 0;
    *totalR3 = 0;

    for (i = 0; i < conpro; i++)
    {
        *totalHoras = *totalHoras + demanda[i] * horasUnidad[i];
        *totalR1 = *totalR1 + demanda[i] * recurso1[i];
        *totalR2 = *totalR2 + demanda[i] * recurso2[i];
        *totalR3 = *totalR3 + demanda[i] * recurso3[i];
    }
}

void revisar_produccion(void)
{
    float totalHoras, totalR1, totalR2, totalR3;
    float horasDisponibles, disponibleR1, disponibleR2, disponibleR3;

    if (conpro == 0)
    {
        printf("Primero debe ingresar productos.\n");
    }
    else
    {
        printf("Ingrese las horas disponibles: ");
        scanf("%f", &horasDisponibles);
        printf("Ingrese la cantidad disponible del recurso 1: ");
        scanf("%f", &disponibleR1);
        printf("Ingrese la cantidad disponible del recurso 2: ");
        scanf("%f", &disponibleR2);
        printf("Ingrese la cantidad disponible del recurso 3: ");
        scanf("%f", &disponibleR3);

        calcular_totales(&totalHoras, &totalR1, &totalR2, &totalR3);

        printf("\n--- RESULTADOS ---\n");
        printf("Horas necesarias: %.2f de %.2f disponibles\n", totalHoras, horasDisponibles);
        printf("Recurso 1 necesario: %.2f de %.2f disponibles\n", totalR1, disponibleR1);
        printf("Recurso 2 necesario: %.2f de %.2f disponibles\n", totalR2, disponibleR2);
        printf("Recurso 3 necesario: %.2f de %.2f disponibles\n", totalR3, disponibleR3);

        if (totalHoras <= horasDisponibles &&
            totalR1 <= disponibleR1 &&
            totalR2 <= disponibleR2 &&
            totalR3 <= disponibleR3)
        {
            printf("La fabrica SI puede cumplir con la demanda.\n");
        }
        else
        {
            printf("La fabrica NO puede cumplir con la demanda.\n");
        }
    }
}
