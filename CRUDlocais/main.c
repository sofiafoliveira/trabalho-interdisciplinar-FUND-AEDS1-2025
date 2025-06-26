#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOCAIS 100

typedef struct {
    char nome[100];
    float coordX;
    float coordY;
} Local;

Local locais[MAX_LOCAIS];
int totalLocais = 0;

int nomeExiste(const char* nome) {
    for (int i = 0; i < totalLocais; i++) {
        if (strcmp(locais[i].nome, nome) == 0) {
            return 1;
        }
    }
    return 0;
}

void cadastrarLocal() {
    if (totalLocais >= MAX_LOCAIS) {
        printf("Limite de locais atingido.\n");
        return;
    }

    Local novo;
    printf("Digite o nome do local: ");
    getchar();
    fgets(novo.nome, 100, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    if (nomeExiste(novo.nome)) {
        printf("Este nome de local ja existe.\n");
        return;
    }

    printf("Digite a coordenada X: ");
    scanf("%f", &novo.coordX);

    printf("Digite a coordenada Y: ");
    scanf("%f", &novo.coordY);

    locais[totalLocais++] = novo;
    printf("Local cadastrado com sucesso!\n");
}

void listarLocais() {
    if (totalLocais == 0) {
        printf("Nenhum local cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE LOCAIS ===\n");
    for (int i = 0; i < totalLocais; i++) {
        printf("Nome: %s | Coordenadas: (%.2f, %.2f)\n",
            locais[i].nome, locais[i].coordX, locais[i].coordY);
    }
}

void atualizarLocal() {
    char nomeBusca[100];
    printf("Digite o nome do local a ser atualizado: ");
    getchar();
    fgets(nomeBusca, 100, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalLocais; i++) {
        if (strcmp(locais[i].nome, nomeBusca) == 0) {
            printf("Digite a nova coordenada X: ");
            scanf("%f", &locais[i].coordX);
            printf("Digite a nova coordenada Y: ");
            scanf("%f", &locais[i].coordY);
            printf("Local atualizado com sucesso!\n");
            return;
        }
    }

    printf("Local nao encontrado.\n");
}

void excluirLocal() {
    char nomeBusca[100];
    printf("Digite o nome do local a ser excluido: ");
    getchar();
    fgets(nomeBusca, 100, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalLocais; i++) {
        if (strcmp(locais[i].nome, nomeBusca) == 0) {
            for (int j = i; j < totalLocais - 1; j++) {
                locais[j] = locais[j + 1];
            }
            totalLocais--;
            printf("Local excluido com sucesso!\n");
            return;
        }
    }

    printf("Local nao encontrado.\n");
}

int main() {
    int opcao;
    do {
        printf("\n=== MENU DE LOCAIS ===\n");
        printf("1. Cadastrar local\n");
        printf("2. Listar locais\n");
        printf("3. Atualizar local\n");
        printf("4. Excluir local\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarLocal();
                break;
            case 2:
                listarLocais();
                break;
            case 3:
                atualizarLocal();
                break;
            case 4:
                excluirLocal();
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
