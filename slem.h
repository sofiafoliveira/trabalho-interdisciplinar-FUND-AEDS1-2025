#ifndef SLEM_H
#define SLEM_H

#include <stdio.h>// Para entrada/saída
#include <stdlib.h>// Para funções de alocação e utilidades gerais
#include <math.h>  // Para a função sqrtf(), usada no cálculo de distância
#define MAX 100 // Define o limite máximo de locais, veículos e pedidos


// ----------------------------
// Definições de Estruturas
// ----------------------------

// Representa um ponto de entrega ou coleta com nome e coordenadas X e Y

typedef struct {
    char nome[50];// Nome do local
    float x, y;// Coordenadas do local
} Local;


// Representa um veículo com informações básicas e posição atual
typedef struct {
    char placa[10];// Placa do veículo
    char modelo[50];// Modelo do veículo
    int status;  // 0 = disponível | 1 = ocupado
    int localAtual;// Índice do local onde o veículo está atualmente
} Veiculo;


// Representa um pedido de entrega entre dois locais, com um peso associado
typedef struct {
    int id;// Identificador único do pedido
    int origem;// Índice do local de origem
    int destino;// Índice do local de destino
    float peso;// Peso da carga
} Pedido;


// ----------------------------
// Variáveis globais
// ----------------------------

// Arrays para armazenar os dados de locais, veículos e pedidos

extern Local locais[MAX];
extern Veiculo veiculos[MAX];
extern Pedido pedidos[MAX];


// Contadores globais para controlar a quantidade de cada tipo
extern int qtdLocais;
extern int qtdVeiculos;
extern int qtdPedidos;


// OBS: Essas variáveis são declaradas aqui com `extern`
// porque serão definidas em outro arquivo (.c), provavelmente no main

// ----------------------------
// Assinaturas das Funções
// ----------------------------

// Locais
void cadastrarLocal();       // Cadastra novo local
void listarLocais();         // Lista todos os locais
void editarLocal();          // Edita um local existente
void apagarLocal();          // Remove um local
void listarLocaisComSaida(FILE *saida);

// === Funções de Veículos ===
void cadastrarVeiculo();     // Cadastra novo veículo
void listarVeiculos();       // Lista todos os veículos
void editarVeiculo();        // Edita um veículo existente
void apagarVeiculo();        // Remove um veículo
void listarVeiculosComSaida(FILE *saida);

// === Funções de Pedidos ===
void cadastrarPedido();      // Cadastra novo pedido
void listarPedidos();        // Lista todos os pedidos
void editarPedido();         // Edita um pedido existente
void apagarPedido();         // Remove um pedido
void listarPedidosComSaida(FILE *saida);
void listarPedidosComSaida(FILE *saida);


// Utilitárias
float distancia(int i, int j);       // Calcula a distância entre dois locais (i e j)
void calcularRota();                 // Executa a lógica para encontrar a melhor rota de entrega
void calcularRotaComSaida(FILE *saida);

// Menus
void menuLocais();          // Menu específico para locais
void menuVeiculos();        // Menu específico para veículos
void menuPedidos();         // Menu específico para pedidos

// Menu principal
void menu();                // Exibe e gerencia o menu principal do sistema

// Backup
void salvarDados();         // Salva os dados em arquivos binários
void restaurarDados();      // Restaura os dados dos arquivos salvos

#endif
