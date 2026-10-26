#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

#define MAX_TERMS 94

static int leer_cantidad(size_t *cantidad)
{
    char entrada[128];
    char *fin;
    unsigned long valor;

    printf("Ingrese la cantidad de terminos (1-%d): ",
           MAX_TERMS);

    if (fgets(entrada, sizeof(entrada), stdin) == NULL)
    {
        fprintf(stderr, "Error: no se pudo leer la entrada.\n");
        return 0;
    }

    errno = 0;
    valor = strtoul(entrada, &fin, 10);

    if (fin == entrada || errno == ERANGE)
    {
        fprintf(stderr, "Error: introduzca un numero valido.\n");
        return 0;
    }

    while (*fin == ' ' || *fin == '\t' ||
           *fin == '\n' || *fin == '\r')
    {
        fin++;
    }

    if (*fin != '\0' || valor < 1 || valor > MAX_TERMS)
    {
        fprintf(stderr,
                "Error: la cantidad debe estar entre 1 y %d.\n",
                MAX_TERMS);
        return 0;
    }

    *cantidad = (size_t)valor;
    return 1;
}

static void generar_fibonacci(size_t cantidad)
{
    uint64_t anterior = 0;
    uint64_t actual = 1;

    printf("\n========== SERIE DE FIBONACCI ==========\n");

    for (size_t i = 0; i < cantidad; i++)
    {
        printf("%" PRIu64, anterior);

        if (i + 1 < cantidad)
        {
            printf(", ");
        }

        if (i + 1 < cantidad)
        {
            uint64_t siguiente;

            if (UINT64_MAX - anterior < actual)
            {
                fprintf(stderr,
                        "\nError: desbordamiento numerico detectado.\n");
                return;
            }

            siguiente = anterior + actual;
            anterior = actual;
            actual = siguiente;
        }
    }

    printf("\n========================================\n");
    printf("Total de terminos generados: %zu\n", cantidad);
}

int main(void)
{
    size_t cantidad;

    printf("========================================\n");
    printf("   GENERADOR DE FIBONACCI PROFESIONAL\n");
    printf("========================================\n");

    if (!leer_cantidad(&cantidad))
    {
        return EXIT_FAILURE;
    }

    generar_fibonacci(cantidad);

    return EXIT_SUCCESS;
}