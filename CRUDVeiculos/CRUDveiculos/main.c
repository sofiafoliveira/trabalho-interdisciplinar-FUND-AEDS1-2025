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

void cadastrarVeiculo() {
    if (totalVeiculos >= MAX_VEICULOS) {
        printf("Limite de veiculos atingido.\n");
        return;
    }

    Veiculo novo;

    printf("Digite a placa do veiculo: ");
    scanf("%s", novo.placa);

    if (placaExiste(novo.placa)) {
        printf("Placa ja cadastrada!\n");
        return;
    }

    printf("Digite o modelo do veiculo: ");
    getchar();
    fgets(novo.modelo, 50, stdin);
    novo.modelo[strcspn(novo.modelo, "\n")] = '\0';

    printf("Status (0 = disponivel, 1 = ocupado): ");
    scanf("%d", &novo.status);

    printf("Digite o ID do local atual: ");
    scanf("%d", &novo.idLocalAtual);

    veiculos[totalVeiculos] = novo;
    totalVeiculos++;

    printf("Veiculo cadastrado com sucesso!\n");
}

void listarVeiculos() {
    if (totalVeiculos == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalVeiculos; i++) {
        printf("\nVeiculo %d\n", i + 1);
        printf("Placa: %s\n", veiculos[i].placa);
        printf("Modelo: %s\n", veiculos[i].modelo);
        printf("Status: %s\n", veiculos[i].status ? "Ocupado" : "Disponivel");
        printf("ID do Local Atual: %d\n", veiculos[i].idLocalAtual);
    }
}

void atualizarVeiculo() {
    char placa[20];
    printf("Digite a placa do veiculo a ser atualizado: ");
    scanf("%s", placa);

    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(veiculos[i].placa, placa) == 0) {
            printf("Digite o novo modelo: ");
            getchar();
            fgets(veiculos[i].modelo, 50, stdin);
            veiculos[i].modelo[strcspn(veiculos[i].modelo, "\n")] = '\0';

            printf("Novo status (0 = disponivel, 1 = ocupado): ");
            scanf("%d", &veiculos[i].status);

            printf("Novo ID do local atual: ");
            scanf("%d", &veiculos[i].idLocalAtual);

            printf("Veiculo atualizado com sucesso!\n");
            return;
        }
    }

    printf("Veiculo com a placa informada nao encontrado.\n");
}

void excluirVeiculo() {
    char placa[20];
    printf("Digite a placa do veiculo a ser excluido: ");
    scanf("%s", placa);

    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(veiculos[i].placa, placa) == 0) {
            for (int j = i; j < totalVeiculos - 1; j++) {
                veiculos[j] = veiculos[j + 1];
            }
            totalVeiculos--;
            printf("Veiculo excluido com sucesso!\n");
            return;
        }
    }

    printf("Veiculo com a placa informada nao encontrado.\n");
}

