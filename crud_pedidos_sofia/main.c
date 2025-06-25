#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PEDIDOS 100

typedef struct {
    int id;
    int idVeiculo;
    int idLocalEntrega;
    char descricao[100];
    int entregue; // 0 = não entregue, 1 = entregue
} Pedido;

Pedido pedidos[MAX_PEDIDOS];
int totalPedidos = 0;

// Função para cadastrar novo pedido
void cadastrarPedido() {
    if (totalPedidos >= MAX_PEDIDOS) {
        printf("Limite de pedidos atingido.\n");
        return;
    }

    Pedido novo;
    novo.id = totalPedidos + 1;

    printf("Digite o ID do veiculo: ");
    scanf("%d", &novo.idVeiculo);

    printf("Digite o ID do local de entrega: ");
    scanf("%d", &novo.idLocalEntrega);

    printf("Digite a descricao do pedido: ");
    getchar(); // Limpa o buffer do teclado
    fgets(novo.descricao, 100, stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = '\0'; // Remove \n final

    novo.entregue = 0;

    pedidos[totalPedidos] = novo;
    totalPedidos++;

    printf("Pedido cadastrado com sucesso!\n");
}

// Função para listar todos os pedidos
void listarPedidos() {
    if (totalPedidos == 0) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalPedidos; i++) {
        printf("\nPedido ID: %d\n", pedidos[i].id);
        printf("Veiculo: %d\n", pedidos[i].idVeiculo);
        printf("Local: %d\n", pedidos[i].idLocalEntrega);
        printf("Descricao: %s\n", pedidos[i].descricao);
        printf("Entregue: %s\n", pedidos[i].entregue ? "Sim" : "Nao");
    }
}

// Função para atualizar um pedido
void atualizarPedido() {
    int id;
    printf("Digite o ID do pedido a ser atualizado: ");
    scanf("%d", &id);

    for (int i = 0; i < totalPedidos; i++) {
        if (pedidos[i].id == id) {
            printf("Digite a nova descricao: ");
            getchar();
            fgets(pedidos[i].descricao, 100, stdin);
            pedidos[i].descricao[strcspn(pedidos[i].descricao, "\n")] = '\0';

            printf("Digite o novo status (0 = nao entregue, 1 = entregue): ");
            scanf("%d", &pedidos[i].entregue);

            printf("Pedido atualizado!\n");
            return;
        }
    }

    printf("\nPedido nao encontrado.\n");
}

// Função para excluir um pedido
void excluirPedido() {
    int id;
    printf("Digite o ID do pedido a ser excluido: ");
    scanf("%d", &id);

    int encontrado = 0;
    for (int i = 0; i < totalPedidos; i++) {
        if (pedidos[i].id == id) {
            encontrado = 1;
            for (int j = i; j < totalPedidos - 1; j++) {
                pedidos[j] = pedidos[j + 1];
            }
            totalPedidos--;
            printf("Pedido excluido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Pedido nao encontrado.\n");
    }
}

// Menu principal
int main() {
    int opcao;
    do {
        printf("\n=== MENU DE PEDIDOS ===\n");
        printf("1. Cadastrar pedido\n");
        printf("2. Listar pedidos\n");
        printf("3. Atualizar pedido\n");
        printf("4. Excluir pedido\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPedido();
                break;
            case 2:
                listarPedidos();
                break;
            case 3:
                atualizarPedido();
                break;
            case 4:
                excluirPedido();
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
