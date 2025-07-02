#include "slem.h"// Inclus�o do cabe�alho do projeto, onde est�o definidas as structs e vari�veis globais usadas aqui
#define EPSILON 0.0001 // tolerância para comparar floats
#include <math.h> // no topo do seu arquivo
#include <strings.h>  // para strcasecmp (Linux/macOS)
#include <string.h>
#include <ctype.h>



Local locais[MAX];
int qtdLocais = 0;

Veiculo veiculos[MAX];
int qtdVeiculos = 0;

Pedido pedidos[MAX];
int qtdPedidos = 0;


void calcularRota();



int op_cadastrar_local = 0;
int op_editar_local = 0;
int op_apagar_local = 0;
int op_listar_locais = 0;



int op_cadastrar_pedido = 0;
int op_editar_pedido = 0;
int op_apagar_pedido = 0;
int op_listar_pedidos = 0;


int op_cadastrar_veiculo = 0;
int op_editar_veiculo = 0;
int op_apagar_veiculo = 0;
int op_listar_veiculos = 0;


int op_restaurar_dados = 0; // contador de operações
    int op_salvar_dados = 0; // contador de operações críticas





// Funcoes para locais





// ========================== FUNCOES PARA LOCAIS ===============================


 // Declaracao antecipada da fun��o que ser� implementada mais adiante
void cadastrarLocal() {
    if (qtdLocais == MAX) {
        printf("Limite de locais atingido.\n");
        return;
    }

    char nomeTemp[100];
    float xTemp, yTemp;

    printf("\nNome do local: ");
    scanf(" %[^\n]", nomeTemp);

    for (int i = 0; i < qtdLocais; i++) {
        op_cadastrar_local++;  // comparação de nome
        if (strcasecmp(locais[i].nome, nomeTemp) == 0) {
            printf("Erro: ja existe um local com esse nome.\n");
            return;
        }
    }

    printf("Coordenada X: ");
    scanf("%f", &xTemp);
    printf("Coordenada Y: ");
    scanf("%f", &yTemp);

    for (int i = 0; i < qtdLocais; i++) {
        op_cadastrar_local += 2;  // dx, dy
        float dx = fabs(locais[i].x - xTemp);
        float dy = fabs(locais[i].y - yTemp);
        if (dx < EPSILON && dy < EPSILON) {
            printf("Erro: ja existe um local com essas coordenadas.\n");
            return;
        }
    }

    strcpy(locais[qtdLocais].nome, nomeTemp); op_cadastrar_local++;
    locais[qtdLocais].x = xTemp;              op_cadastrar_local++;
    locais[qtdLocais].y = yTemp;              op_cadastrar_local++;
    qtdLocais++;                              op_cadastrar_local++;

    printf("Local cadastrado com sucesso. Operacoes: %d\n", op_cadastrar_local);
}

// Lista todos os locais cadastrados
void listarLocais() {
    if (qtdLocais == 0) {
        printf("Nenhum local cadastrado.\n");
        return;
    }
    printf("\nLista de Locais:\n");
    for (int i = 0; i < qtdLocais; i++) {
        op_listar_locais++;
        printf("[%d] %s (%.2f, %.2f)\n", i, locais[i].nome, locais[i].x, locais[i].y);
    }
    printf("Total de locais: %d. Operacoes: %d\n", qtdLocais, op_listar_locais);
}


void listarLocaisComSaida(FILE *f) {
    if (qtdLocais == 0) {
        fprintf(f, "Nenhum local cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdLocais; i++) {
        fprintf(f, "%d. Nome: %s | Coordenadas: (%.2f, %.2f)\n", i, locais[i].nome, locais[i].x, locais[i].y);
    }
}


// Permite editar um local existente
void editarLocal() {
    listarLocais();
    if (qtdLocais == 0) return;

    int i;
    printf("Digite o indice do local para editar: ");
    scanf("%d", &i);

    if (i < 0 || i >= qtdLocais) {
        printf("Indice invalido.\n");
        return;
    }

    char novoNome[100];
    float novaX, novaY;

    printf("Novo nome do local: ");
    scanf(" %[^\n]", novoNome);

    for (int j = 0; j < qtdLocais; j++) {
        op_editar_local++;  // comparação de nome
        if (j != i && strcasecmp(locais[j].nome, novoNome) == 0) {
            printf("Erro: já existe outro local com esse nome.\n");
            return;
        }
    }

    printf("Nova coordenada X: ");
    scanf("%f", &novaX);
    printf("Nova coordenada Y: ");
    scanf("%f", &novaY);

    for (int j = 0; j < qtdLocais; j++) {
        if (j != i) {
            op_editar_local += 2; // dx, dy
            float dx = fabs(locais[j].x - novaX);
            float dy = fabs(locais[j].y - novaY);
            if (dx < EPSILON && dy < EPSILON) {
                printf("Erro: já existe outro local com essas coordenadas.\n");
                return;
            }
        }
    }

    strcpy(locais[i].nome, novoNome); op_editar_local++;
    locais[i].x = novaX;              op_editar_local++;
    locais[i].y = novaY;              op_editar_local++;

    printf("Local atualizado. Operacoes: %d\n", op_editar_local);
}


// Apaga um local do sistema
void apagarLocal() {
    listarLocais();
    if (qtdLocais == 0) return;
    int i;
    printf("Digite o indice do local para apagar: ");
    scanf("%d", &i);
    if (i < 0 || i >= qtdLocais) {
        printf("Indice invalido.\n");
        return;
    }
    for (int j = i; j < qtdLocais - 1; j++) {
        locais[j] = locais[j + 1];
        op_apagar_local++;
    }
    qtdLocais--;
    op_apagar_local++;
    printf("Local apagado. Operacoes: %d\n", op_apagar_local);
}


// ========================== FUN��ES PARA VEICULOS ===============================


#include <ctype.h>

int validarPlaca(const char *placa) {
    if (strlen(placa) != 8) return 0;

    for (int i = 0; i < 3; i++) {
        if (!isalpha(placa[i])) return 0;
    }

    if (placa[3] != '-') return 0;

    for (int i = 4; i < 8; i++) {
        if (!isdigit(placa[i])) return 0;
    }

    return 1;
}


// Cadastra um novo veiculo
void cadastrarVeiculo() {
    if (qtdLocais == 0) {
        printf("Primeiro, cadastre um local.\n");
        return;
    }

    if (qtdVeiculos == MAX) {
        printf("Limite de veiculos atingido.\n");
        return;
    }

    char placaTemp[20];

    printf("\nPlaca (formato ABC-1234): ");
    scanf(" %[^\n]", placaTemp);

    op_cadastrar_veiculo++; // validação de placa
    if (!validarPlaca(placaTemp)) {
        printf("Erro: placa invalida. Use o formato XXX-0000.\n");
        return;
    }

    for (int i = 0; i < qtdVeiculos; i++) {
        op_cadastrar_veiculo++; // comparação de placa
        if (strcasecmp(veiculos[i].placa, placaTemp) == 0) {
            printf("Erro: ja existe um veiculo com essa placa.\n");
            return;
        }
    }

    printf("Indice do local atual (0 a %d): ", qtdLocais - 1);
    int indiceLocal;
    scanf("%d", &indiceLocal); op_cadastrar_veiculo++;

    if (indiceLocal < 0 || indiceLocal >= qtdLocais) {
        printf("Erro: indice de local invalido. Operacao cancelada.\n");
        return;
    }

    // Somente agora que temos certeza de que está tudo certo, preenchemos os dados:
    strcpy(veiculos[qtdVeiculos].placa, placaTemp); op_cadastrar_veiculo++;
    printf("Modelo: ");
    scanf(" %[^\n]", veiculos[qtdVeiculos].modelo); op_cadastrar_veiculo++;

    veiculos[qtdVeiculos].status = 0; op_cadastrar_veiculo++;
    veiculos[qtdVeiculos].localAtual = indiceLocal; op_cadastrar_veiculo++;

    qtdVeiculos++; op_cadastrar_veiculo++;
    printf("Veiculo cadastrado. Operacoes: %d\n", op_cadastrar_veiculo);
}





// Lista todos os veiculos cadastrados
void listarVeiculos() {
    if (qtdVeiculos == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }
    printf("\nLista de Veiculos:\n");
    for (int i = 0; i < qtdVeiculos; i++) {
        op_listar_veiculos++;
        printf("[%d] Placa: %s | Modelo: %s | Status: %s | LocalAtual: %d\n",
            i,
            veiculos[i].placa,
            veiculos[i].modelo,
            veiculos[i].status == 0 ? "Disponivel" : "Ocupado",
            veiculos[i].localAtual);
    }
    printf("Total de veiculos: %d. Operacoes: %d\n", qtdVeiculos, op_listar_veiculos);
}


// Edita dados de um veiculo
void editarVeiculo() {
    listarVeiculos();
    if (qtdVeiculos == 0) return;

    int i;
    printf("Digite o indice do veiculo para editar: ");
    if (scanf(" %d", &i) != 1 || i < 0 || i >= qtdVeiculos) {
        printf("Indice invalido.\n");
        while (getchar() != '\n');
        return;
    }

    char novaPlaca[20];
    printf("Nova placa (formato ABC-1234): ");
    scanf(" %[^\n]", novaPlaca); op_editar_veiculo++;

    op_editar_veiculo++; // validar placa
    if (!validarPlaca(novaPlaca)) {
        printf("Erro: placa invalida. Use o formato XXX-0000.\n");
        return;
    }

    for (int j = 0; j < qtdVeiculos; j++) {
        op_editar_veiculo++;
        if (j != i && strcasecmp(veiculos[j].placa, novaPlaca) == 0) {
            printf("Erro: já existe outro veiculo com essa placa.\n");
            return;
        }
    }

    printf("Novo modelo: ");
    scanf(" %[^\n]", veiculos[i].modelo); op_editar_veiculo++;

    printf("Status (0 - disponivel, 1 - ocupado): ");
    if (scanf(" %d", &veiculos[i].status) != 1 || (veiculos[i].status != 0 && veiculos[i].status != 1)) {
        printf("Status invalido.\n");
        while (getchar() != '\n');
        return;
    }
    op_editar_veiculo++;

    printf("Indice do local atual (0 a %d): ", qtdLocais - 1);
    int novoLocal;
    if (scanf(" %d", &novoLocal) != 1 || novoLocal < 0 || novoLocal >= qtdLocais) {
        printf("Erro: indice de local invalido. Edicao cancelada.\n");
        while (getchar() != '\n');
        return;
    }
    op_editar_veiculo++;

    // Somente agora fazemos as alterações permanentes:
    strcpy(veiculos[i].placa, novaPlaca); op_editar_veiculo++;
    veiculos[i].localAtual = novoLocal; op_editar_veiculo++;

    printf("Veiculo atualizado. Operacoes: %d\n", op_editar_veiculo);
}



// Apaga um veiculo do sistema
void apagarVeiculo() {
    listarVeiculos();
    if (qtdVeiculos == 0) return;
    int i;
    printf("Digite o indice do veiculo para apagar: ");
    scanf("%d", &i);
    if (i < 0 || i >= qtdVeiculos) {
        printf("Indice invalido.\n");
        return;
    }
    for (int j = i; j < qtdVeiculos - 1; j++) {
        veiculos[j] = veiculos[j + 1];
        op_apagar_veiculo++;
    }
    qtdVeiculos--; op_apagar_veiculo++;
    printf("Veiculo apagado. Operacoes: %d\n", op_apagar_veiculo);
}


// ========================== FUNCOES PARA PEDIDOS ===============================

// Cadastra um pedido
void cadastrarPedido() {
    if (qtdPedidos == MAX) {
        printf("Limite de pedidos atingido.\n");
        return;
    }
    if (qtdLocais == 0) {
        printf("Nenhum local cadastrado para pedido.\n");
        return;
    }

    int origem, destino;
    float peso;

    printf("\nIndice do local de origem (0 a %d): ", qtdLocais - 1);
    if (scanf("%d", &origem) != 1 || origem < 0 || origem >= qtdLocais) {
        printf("Erro: índice de origem inválido.\n");
        while (getchar() != '\n');
        return;
    }
    op_cadastrar_pedido++;

    printf("Indice do local de destino (0 a %d): ", qtdLocais - 1);
    if (scanf("%d", &destino) != 1 || destino < 0 || destino >= qtdLocais) {
        printf("Erro: indice de destino invalido.\n");
        while (getchar() != '\n');
        return;
    }
    op_cadastrar_pedido++;

    printf("Peso (kg): ");
    if (scanf("%f", &peso) != 1 || peso <= 0) {
        printf("Erro: o peso deve ser um numero positivo.\n");
        while (getchar() != '\n');
        return;
    }
    op_cadastrar_pedido++;

    // Agora que tudo foi validado, salva os dados:
    pedidos[qtdPedidos].id = qtdPedidos + 1; op_cadastrar_pedido++;
    pedidos[qtdPedidos].origem = origem;
    pedidos[qtdPedidos].destino = destino;
    pedidos[qtdPedidos].peso = peso;

    qtdPedidos++; op_cadastrar_pedido++;
    printf("Pedido cadastrado. Operacoes: %d\n", op_cadastrar_pedido);
}




// Lista os pedidos
void listarPedidos() {
    if (qtdPedidos == 0) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }
    printf("\nLista de Pedidos:\n");
    for (int i = 0; i < qtdPedidos; i++) {
        op_listar_pedidos++;
        printf("[%d] ID: %d | Origem: %s | Destino: %s | Peso: %.2f kg\n",
            i,
            pedidos[i].id,
            (pedidos[i].origem >= 0 && pedidos[i].origem < qtdLocais) ? locais[pedidos[i].origem].nome : "Invalido",
            (pedidos[i].destino >= 0 && pedidos[i].destino < qtdLocais) ? locais[pedidos[i].destino].nome : "Invalido",
            pedidos[i].peso);
    }
    printf("Total de pedidos: %d. Operacoes: %d\n", qtdPedidos, op_listar_pedidos);
}


void editarPedido() {
    listarPedidos();
    if (qtdPedidos == 0) return;

    int i;
    printf("Digite o indice do pedido para editar: ");
    if (scanf("%d", &i) != 1 || i < 0 || i >= qtdPedidos) {
        printf("Indice invalido.\n");
        while (getchar() != '\n');
        return;
    }

    int novaOrigem, novoDestino;
    float novoPeso;

    printf("Novo indice do local de origem (0 a %d): ", qtdLocais - 1);
    if (scanf("%d", &novaOrigem) != 1 || novaOrigem < 0 || novaOrigem >= qtdLocais) {
        printf("Indice de origem invalido.\n");
        while (getchar() != '\n');
        return;
    }
    op_editar_pedido++;

    printf("Novo indice do local de destino (0 a %d): ", qtdLocais - 1);
    if (scanf("%d", &novoDestino) != 1 || novoDestino < 0 || novoDestino >= qtdLocais) {
        printf("Indice de destino invalido.\n");
        while (getchar() != '\n');
        return;
    }
    op_editar_pedido++;

    printf("Novo peso (kg): ");
    if (scanf("%f", &novoPeso) != 1 || novoPeso <= 0) {
        printf("Erro: o peso deve ser positivo.\n");
        while (getchar() != '\n');
        return;
    }
    op_editar_pedido++;

    // Tudo válido — agora aplica as mudanças:
    pedidos[i].origem = novaOrigem; op_editar_pedido++;
    pedidos[i].destino = novoDestino; op_editar_pedido++;
    pedidos[i].peso = novoPeso; op_editar_pedido++;

    printf("Pedido atualizado. Operacoes: %d\n", op_editar_pedido);
}



// Apaga um pedido
void apagarPedido() {
    listarPedidos();
    if (qtdPedidos == 0) return;

    int i;
    printf("Digite o indice do pedido para apagar: ");
    scanf("%d", &i);
    if (i < 0 || i >= qtdPedidos) {
        printf("Indice invalido.\n");
        return;
    }

    for (int j = i; j < qtdPedidos - 1; j++) {
        pedidos[j] = pedidos[j + 1];
        op_apagar_pedido++;
    }
    qtdPedidos--; op_apagar_pedido++;

    printf("Pedido apagado. Operacoes: %d\n", op_apagar_pedido);
}


// ========================== FUN��ES AUXILIARES ===============================

// Calcula a distancia entre dois locais usando formula de distancia euclidiana
float distancia(int i, int j) {
    float dx = locais[i].x - locais[j].x;
    float dy = locais[i].y - locais[j].y;
    return sqrtf(dx * dx + dy * dy);
}

// Calcula a rota ideal para um pedido, escolhendo o veiculo mais proximo dispon�vel
void calcularRota() {
    if (qtdPedidos == 0 || qtdVeiculos == 0) {
        printf("\nNenhum pedido ou veiculo cadastrado.\n");
        return;
    }

    int idPedido;
    printf("\nID do pedido (1 a %d): ", qtdPedidos);
    scanf("%d", &idPedido);
    idPedido--;

    if (idPedido < 0 || idPedido >= qtdPedidos) {
        printf("ID do pedido invalido.\n");
        return;
    }

    int origem = pedidos[idPedido].origem;
    int destino = pedidos[idPedido].destino;

    if (origem < 0 || origem >= qtdLocais || destino < 0 || destino >= qtdLocais) {
        printf("Indices de origem ou destino invalidos.\n");
        return;
    }

    float menorDist = 1e9;
    int indiceVeiculo = -1;

    for (int i = 0; i < qtdVeiculos; i++) {
        if (veiculos[i].status == 0 && veiculos[i].localAtual >= 0) {
            float d = distancia(veiculos[i].localAtual, origem);
            if (d < menorDist) {
                menorDist = d;
                indiceVeiculo = i;
            }
        }
    }

    if (indiceVeiculo == -1) {
        printf("Nenhum veiculo disponivel.\n");
        return;
    }

    float rotaTotal = menorDist + distancia(origem, destino);
    printf("\nVeiculo selecionado: %s\n", veiculos[indiceVeiculo].placa);
    printf("Origem: %s\n", locais[origem].nome);
    printf("Destino: %s\n", locais[destino].nome);
    printf("Distancia total: %.2f\n", rotaTotal);

veiculos[indiceVeiculo].status = 1;
printf("Entregando...\n");

// Mostrar veiculo ocupado aqui
listarVeiculos();

// Simula entrega finalizada
veiculos[indiceVeiculo].status = 0;
veiculos[indiceVeiculo].localAtual = destino;
printf("Entrega concluida.\n");

}





void listarVeiculosComSaida(FILE *saida) {
    if (qtdVeiculos == 0) {
        fprintf(saida, "Nenhum veiculo cadastrado.\n");
        return;
    }
    for (int i = 0; i < qtdVeiculos; i++) {
        fprintf(saida, "[%d] Placa: %s | Modelo: %s | Status: %s | LocalAtual: %d\n",
            i, veiculos[i].placa, veiculos[i].modelo,
            veiculos[i].status == 0 ? "Disponivel" : "Ocupado",
            veiculos[i].localAtual);
    }
}

void calcularRotaComSaida(FILE *saida) {
    if (qtdPedidos == 0 || qtdVeiculos == 0) {
        fprintf(saida, "\nNenhum pedido ou veiculo cadastrado.\n");
        return;
    }

    int idPedido = 0; // usa o primeiro pedido para teste
    int origem = pedidos[idPedido].origem;
    int destino = pedidos[idPedido].destino;

    if (origem < 0 || origem >= qtdLocais || destino < 0 || destino >= qtdLocais) {
        fprintf(saida, "Indices de origem ou destino invalidos.\n");
        return;
    }

    float menorDist = 1e9;
    int indiceVeiculo = -1;

    for (int i = 0; i < qtdVeiculos; i++) {
        if (veiculos[i].status == 0 && veiculos[i].localAtual >= 0) {
            float d = distancia(veiculos[i].localAtual, origem);
            if (d < menorDist) {
                menorDist = d;
                indiceVeiculo = i;
            }
        }
    }

    if (indiceVeiculo == -1) {
        fprintf(saida, "Nenhum veiculo disponivel.\n");
        return;
    }

    float rotaTotal = menorDist + distancia(origem, destino);
    fprintf(saida, "\nVeiculo selecionado: %s\n", veiculos[indiceVeiculo].placa);
    fprintf(saida, "Origem: %s\n", locais[origem].nome);
    fprintf(saida, "Destino: %s\n", locais[destino].nome);
    fprintf(saida, "Distancia total: %.2f\n", rotaTotal);
    fprintf(saida, "Entregando...\n");
    fprintf(saida, "Entrega concluida.\n");

    veiculos[indiceVeiculo].status = 0;
    veiculos[indiceVeiculo].localAtual = destino;
}

void listarPedidosComSaida(FILE *saida) {
    if (qtdPedidos == 0) {
        fprintf(saida, "Nenhum pedido cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdPedidos; i++) {
        fprintf(saida, "ID: %d\n", pedidos[i].id);
        fprintf(saida, "Origem: %s\n", locais[pedidos[i].origem].nome);
        fprintf(saida, "Destino: %s\n", locais[pedidos[i].destino].nome);
        fprintf(saida, "Peso: %.2f\n", pedidos[i].peso);
        fprintf(saida, "-------------------\n");
    }
}












// ========================== MENUS ===============================


// Menu de gerenciamento de locais
void menuLocais() {
    int op;
    do {
        printf("\n--- Menu Locais ---\n");
        printf("1 - Cadastrar Local\n");
        printf("2 - Listar Locais\n");
        printf("3 - Editar Local\n");
        printf("4 - Apagar Local\n");
        printf("0 - Voltar\n");
        printf("> ");
        scanf("%d", &op);
        switch(op) {
            case 1: cadastrarLocal(); break;
            case 2: listarLocais(); break;
            case 3: editarLocal(); break;
            case 4: apagarLocal(); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0);
}


// Menu de gerenciamento de veiculos
void menuVeiculos() {
    int op;
    do {
        printf("\n--- Menu Veiculos ---\n");
        printf("1 - Cadastrar Veiculo\n");
        printf("2 - Listar Veiculos\n");
        printf("3 - Editar Veiculo\n");
        printf("4 - Apagar Veiculo\n");
        printf("0 - Voltar\n");
        printf("> ");
        scanf("%d", &op);
        switch(op) {
            case 1: cadastrarVeiculo(); break;
            case 2: listarVeiculos(); break;
            case 3: editarVeiculo(); break;
            case 4: apagarVeiculo(); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0);
}


// Menu de gerenciamento de pedidos
void menuPedidos() {
    int op;
    do {
        printf("\n--- Menu Pedidos ---\n");
        printf("1 - Cadastrar Pedido\n");
        printf("2 - Listar Pedidos\n");
        printf("3 - Editar Pedido\n");
        printf("4 - Apagar Pedido\n");
        printf("0 - Voltar\n");
        printf("> ");
        scanf("%d", &op);
        switch(op) {
            case 1: cadastrarPedido(); break;
            case 2: listarPedidos(); break;
            case 3: editarPedido(); break;
            case 4: apagarPedido(); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0);
}


// Salva todos os dados do sistema em arquivos binários
void salvarDados() {
    FILE *f;

    // === Salvar Locais ===
    f = fopen("locais.bin", "wb"); op_salvar_dados++;
    if (f != NULL) {
        fwrite(&qtdLocais, sizeof(int), 1, f); op_salvar_dados++;
        fwrite(locais, sizeof(Local), qtdLocais, f); op_salvar_dados += qtdLocais;
        fclose(f); op_salvar_dados++;
    }

    // === Salvar Veículos ===
    f = fopen("veiculos.bin", "wb"); op_salvar_dados++;
    if (f != NULL) {
        fwrite(&qtdVeiculos, sizeof(int), 1, f); op_salvar_dados++;
        fwrite(veiculos, sizeof(Veiculo), qtdVeiculos, f); op_salvar_dados += qtdVeiculos;
        fclose(f); op_salvar_dados++;
    }

    // === Salvar Pedidos ===
    f = fopen("pedidos.bin", "wb"); op_salvar_dados++;
    if (f != NULL) {
        fwrite(&qtdPedidos, sizeof(int), 1, f); op_salvar_dados++;
        fwrite(pedidos, sizeof(Pedido), qtdPedidos, f); op_salvar_dados += qtdPedidos;
        fclose(f); op_salvar_dados++;
    }

    printf("Operacoes: %d\n", op_salvar_dados);
}



// Recupera os dados salvos anteriormente nos arquivos bin�rios
void restaurarDados() {
    FILE *f;
    int op_restaurar_dados = 0; // contador de operações

    // === Restaurar Locais ===
    f = fopen("locais.bin", "rb"); op_restaurar_dados++;
    if (f) {
        fread(&qtdLocais, sizeof(int), 1, f); op_restaurar_dados++;
        fread(locais, sizeof(Local), qtdLocais, f); op_restaurar_dados += qtdLocais;
        fclose(f); op_restaurar_dados++;
    } else {
        qtdLocais = 0; op_restaurar_dados++;
    }

    // === Restaurar Veículos ===
    f = fopen("veiculos.bin", "rb"); op_restaurar_dados++;
    if (f) {
        fread(&qtdVeiculos, sizeof(int), 1, f); op_restaurar_dados++;
        fread(veiculos, sizeof(Veiculo), qtdVeiculos, f); op_restaurar_dados += qtdVeiculos;
        fclose(f); op_restaurar_dados++;
    } else {
        qtdVeiculos = 0; op_restaurar_dados++;
    }

    // === Restaurar Pedidos ===
    f = fopen("pedidos.bin", "rb"); op_restaurar_dados++;
    if (f) {
        fread(&qtdPedidos, sizeof(int), 1, f); op_restaurar_dados++;
        fread(pedidos, sizeof(Pedido), qtdPedidos, f); op_restaurar_dados += qtdPedidos;
        fclose(f); op_restaurar_dados++;
    } else {
        qtdPedidos = 0; op_restaurar_dados++;
    }

    // === Se não houver dados, exibe apenas um aviso simples ===
    if (qtdLocais == 0 && qtdVeiculos == 0 && qtdPedidos == 0) {
        printf("\nNenhum dado encontrado. Voce pode comecar a cadastrar agora.\n");
        printf("Operacoes: %d\n", op_restaurar_dados);
        return;
    }

    // === Exibir Resumo ===
    printf("\n================================================================================\n");
    printf("               DADOS RESTAURADOS COM SUCESSO\n");
    printf("================================================================================\n");
    printf(" Locais:   %d\n", qtdLocais);
    printf(" Veiculos: %d\n", qtdVeiculos);
    printf(" Pedidos:  %d\n", qtdPedidos);
    printf("================================================================================\n");

    // === Exibir Locais ===
    if (qtdLocais > 0) {
        printf("\n LOCAIS:\n--------------------------------------------------------------------------------\n");
        for (int i = 0; i < qtdLocais; i++) {
            printf("[%d] %s (%.2f, %.2f)\n", i, locais[i].nome, locais[i].x, locais[i].y);
            op_restaurar_dados++; // conta cada exibição
        }
    }

    // === Exibir Veículos ===
    if (qtdVeiculos > 0) {
        printf("\n VEICULOS:\n--------------------------------------------------------------------------------\n");
        for (int i = 0; i < qtdVeiculos; i++) {
            printf("[%d] Placa: %s | Modelo: %s | Status: %s | Local Atual: %d\n",
                   i,
                   veiculos[i].placa,
                   veiculos[i].modelo,
                   veiculos[i].status == 0 ? "Disponivel" : "Ocupado",
                   veiculos[i].localAtual);
            op_restaurar_dados++; // conta cada exibição
        }
    }

    // === Exibir Pedidos ===
    if (qtdPedidos > 0) {
        printf("\n PEDIDOS:\n--------------------------------------------------------------------------------\n");
        for (int i = 0; i < qtdPedidos; i++) {
            printf("[%d] ID: %d | Origem: %s | Destino: %s | Peso: %.2f kg\n",
                   i,
                   pedidos[i].id,
                   (pedidos[i].origem >= 0 && pedidos[i].origem < qtdLocais) ? locais[pedidos[i].origem].nome : "Invalido",
                   (pedidos[i].destino >= 0 && pedidos[i].destino < qtdLocais) ? locais[pedidos[i].destino].nome : "Invalido",
                   pedidos[i].peso);
            op_restaurar_dados++; // conta cada exibição
        }
    }

    printf("================================================================================\n");

    // Exibe total de operações
    printf("Operacoes: %d\n", op_restaurar_dados);
}






// Menu principal do programa

void menu() {
    int opcao;
    do {
        printf("\n=========== MENU SLEM ===========\n");
        printf("1 - Gerenciar Locais\n");
        printf("2 - Gerenciar Veiculos\n");
        printf("3 - Gerenciar Pedidos\n");
        printf("4 - Calcular Rota\n");
        printf("5 - Backup de Dados\n");
        printf("6 - Restaurar Dados\n");
        printf("0 - Sair\n");
        printf("=================================\n> ");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1: menuLocais(); break;
            case 2: menuVeiculos(); break;
            case 3: menuPedidos(); break;
            case 4: calcularRota(); break;
            case 5: salvarDados(); break;
            case 6: restaurarDados(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}
