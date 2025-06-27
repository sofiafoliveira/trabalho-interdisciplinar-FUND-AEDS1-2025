#include <stdio.h>

void mostrarMenu() {
    printf("\n=== MENU DO SISTEMA DE LOGÍSTICA ===\n");
    printf("1. Cadastrar Local\n");
    printf("2. Listar Locais\n");
    printf("3. Cadastrar Veículo\n");
    printf("4. Listar Veículos\n");
    printf("5. Cadastrar Pedido\n");
    printf("6. Listar Pedidos\n");
    printf("7. Calcular e Exibir Rota de Entrega\n");
    printf("8. Backup de Dados\n");
    printf("9. Restaurar Dados\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao;

    do {
        mostrarMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // cadastrarLocal();
                break;
            case 2:
                // listarLocais();
                break;
            case 3:
                // cadastrarVeiculo();
                break;
            case 4:
                // listarVeiculos();
                break;
            case 5:
                // cadastrarPedido();
                break;
            case 6:
                // listarPedidos();
                break;
            case 7:
                // calcularRota();
                break;
            case 8:
                // salvarBackup();
                break;
            case 9:
                // restaurarBackup();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
