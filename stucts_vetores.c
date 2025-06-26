#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    float x, y;
} Local;

typedef struct {
    char placa[10];
    char modelo[50];
    int disponivel;
    int localIndex;
} Veiculo;

typedef struct {
    int id;
    int origemIndex;
    int destinoIndex;
    float peso;
} Pedido;

Local* locais = NULL;
int totalLocais = 0;

Veiculo* veiculos = NULL;
int totalVeiculos = 0;

Pedido* pedidos = NULL;
int totalPedidos = 0;
int proximoIdPedido = 1;

int main() {

    free(locais);
    free(veiculos);
    free(pedidos);

    return 0;
}
