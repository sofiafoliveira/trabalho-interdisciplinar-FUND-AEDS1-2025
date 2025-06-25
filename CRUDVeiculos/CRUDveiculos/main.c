#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VEICULOS 100

typedef struct {
    char placa[20];
    char modelo[50];
    int status;
    int idLocalAtual;
} Veiculo;

Veiculo veiculos[MAX_VEICULOS];
int totalVeiculos = 0;

int placaExiste(const char* placa) {
    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(veiculos[i].placa, placa) == 0) {
            return 1;
        }
    }
    return 0;
}

