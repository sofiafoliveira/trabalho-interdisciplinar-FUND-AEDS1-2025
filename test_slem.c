#define TEST_MODE  // <-- TEM QUE vir antes do #ifdef
#include "munit.h"  // Inclui a biblioteca Munit, usada para testes unit�rios
#include "slem.h"// Inclui o cabe�alho do sistema a ser testado
#include <string.h>
#include <stdio.h>


// Declara um buffer global de 4096 bytes para armazenar a saída das funções testadas
static char buffer[4096];


void executarComSaida(void (*func)(FILE *), char *output_buffer, size_t buffer_size) {
    // Cria um arquivo temporário
    FILE *f = tmpfile();
    if (!f) return; // Se falhar, sai silenciosamente

    // Executa a função fornecida, passando o arquivo temporário
    func(f);

    // Garante que toda a saída foi escrita no arquivo
    fflush(f);

    // Volta o ponteiro do arquivo para o início para poder ler
    rewind(f);

    // Lê a saída da função para o buffer, deixando espaço para o '\0'
    fread(output_buffer, 1, buffer_size - 1, f);

    // Garante terminação nula da string
    output_buffer[buffer_size - 1] = '\0';

    // Fecha e libera o arquivo temporário
    fclose(f);
}

// --------------------- TESTES DE ROTAS ---------------------

// Testa se a função calcularRotaComSaida detecta corretamente um índice de origem inválido em um pedido
static MunitResult test_rota_origem_invalida(const MunitParameter params[], void* data) {
    // Configura o cenário com 1 local, 1 veículo e 1 pedido
    qtdLocais = 1;
    qtdVeiculos = 1;
    qtdPedidos = 1;

    // Define o local de índice 0
    locais[0] = (Local){"Origem", 0, 0};

    // Define o veículo de índice 0
    veiculos[0] = (Veiculo){"XYZ", "Van", 0, 0};

    // Define um pedido com origem inválida (índice 99 não existe)
    pedidos[0] = (Pedido){1, 99, 0, 10.0};

    // Executa a função de cálculo de rota redirecionando a saída para o buffer
    executarComSaida(calcularRotaComSaida, buffer, sizeof(buffer));

    // Verifica se a mensagem de erro esperada está presente na saída
    munit_assert(strstr(buffer, "Indices de origem ou destino invalidos.") != NULL);

    // Retorna sucesso no teste
    return MUNIT_OK;
}


// Testa se a função calcularRotaComSaida detecta corretamente um índice de destino inválido em um pedido
static MunitResult test_rota_destino_invalido(const MunitParameter params[], void* data) {
    // Configura o cenário com 1 local, 1 veículo e 1 pedido
    qtdLocais = 1;
    qtdVeiculos = 1;
    qtdPedidos = 1;

    // Define o local de índice 0
    locais[0] = (Local){"Origem", 0, 0};

    // Define o veículo de índice 0
    veiculos[0] = (Veiculo){"XYZ", "Van", 0, 0};

    // Define um pedido com destino inválido (índice 99 não existe)
    pedidos[0] = (Pedido){1, 0, 99, 10.0};

    // Executa a função de cálculo de rota redirecionando a saída para o buffer
    executarComSaida(calcularRotaComSaida, buffer, sizeof(buffer));

    // Verifica se a mensagem de erro esperada está presente na saída
    munit_assert(strstr(buffer, "Indices de origem ou destino invalidos.") != NULL);

    // Retorna sucesso no teste
    return MUNIT_OK;
}


// Testa se a função calcularRotaComSaida detecta corretamente a ausência de veículos disponíveis
static MunitResult test_rota_sem_veiculo_disponivel(const MunitParameter params[], void* data) {
    // Configura o cenário com 2 locais, 1 veículo e 1 pedido
    qtdLocais = 2;
    qtdVeiculos = 1;
    qtdPedidos = 1;

    // Define os dois locais (origem e destino)
    locais[0] = (Local){"Origem", 0, 0};
    locais[1] = (Local){"Destino", 3, 4};

    // Define o único veículo, que está ocupado (status = 1)
    veiculos[0] = (Veiculo){"ABC", "Caminhao", 1, 0};

    // Define um pedido com origem no local 0 e destino no local 1
    pedidos[0] = (Pedido){1, 0, 1, 5.0};

    // Executa a função de cálculo de rota redirecionando a saída para o buffer
    executarComSaida(calcularRotaComSaida, buffer, sizeof(buffer));

    // Verifica se a mensagem esperada de erro está presente na saída
    munit_assert(strstr(buffer, "Nenhum veiculo disponivel.") != NULL);

    // Retorna sucesso no teste
    return MUNIT_OK;
}


// Testa o caso válido de cálculo de rota: tudo correto (locais, veículo e pedido)
static MunitResult test_rota_valida(const MunitParameter params[], void* data) {
    // Configura o cenário com 2 locais, 1 veículo disponível e 1 pedido
    qtdLocais = 2;
    qtdVeiculos = 1;
    qtdPedidos = 1;

    // Define os dois locais (com coordenadas que geram uma distância de 5.00)
    locais[0] = (Local){"Origem", 0, 0};
    locais[1] = (Local){"Destino", 3, 4};  // distância Euclidiana = sqrt(3² + 4²) = 5.00

    // Define o veículo disponível (status = 0)
    veiculos[0] = (Veiculo){"DEF", "Moto", 0, 0};

    // Define o pedido da origem 0 para o destino 1, peso irrelevante nesse teste
    pedidos[0] = (Pedido){1, 0, 1, 2.0};

    // Executa a função de cálculo de rota, capturando a saída no buffer
    executarComSaida(calcularRotaComSaida, buffer, sizeof(buffer));

    // Verifica se o veículo foi selecionado corretamente
    munit_assert(strstr(buffer, "Veiculo selecionado: DEF") != NULL);

    // Verifica se a distância foi calculada corretamente
    munit_assert(strstr(buffer, "Distancia total: 5.00") != NULL);

    // Verifica se o sistema confirmou a conclusão da entrega
    munit_assert(strstr(buffer, "Entrega concluida.") != NULL);

    // Retorna sucesso no teste
    return MUNIT_OK;
}


// --------------------- TESTES DE LOCAIS ---------------------

// Testa se a função listarLocaisComSaida imprime a mensagem correta quando não há locais cadastrados
static MunitResult test_listar_locais_vazio(const MunitParameter params[], void* data) {
    // Define que não há locais no sistema
    qtdLocais = 0;

    // Executa a função de listagem e captura sua saída no buffer
    executarComSaida(listarLocaisComSaida, buffer, sizeof(buffer));

    // Verifica se a mensagem esperada está presente na saída
    munit_assert(strstr(buffer, "Nenhum local cadastrado.") != NULL);

    // Retorna sucesso no teste
    return MUNIT_OK;
}


// Testa se a função listarLocaisComSaida exibe corretamente os locais cadastrados
static MunitResult test_listar_locais_com_dados(const MunitParameter params[], void* data) {
    // Define dois locais cadastrados
    qtdLocais = 2;
    locais[0] = (Local){"Local A", 1.1, 2.2};
    locais[1] = (Local){"Local B", 3.3, 4.4};

    // Executa a função de listagem e captura a saída no buffer
    executarComSaida(listarLocaisComSaida, buffer, sizeof(buffer));

    // Verifica se os nomes dos locais aparecem na saída
    munit_assert(strstr(buffer, "Local A") != NULL);
    munit_assert(strstr(buffer, "Local B") != NULL);

    // Retorna sucesso no teste
    return MUNIT_OK;
}


// --------------------- TESTES DE VEICULOS ---------------------

// Testa se a função listarVeiculosComSaida imprime a mensagem correta quando não há veículos cadastrados
static MunitResult test_listar_veiculos_vazio(const MunitParameter params[], void* data) {
    // Define que não há veículos cadastrados
    qtdVeiculos = 0;

    // Executa a função de listagem de veículos e captura a saída no buffer
    executarComSaida(listarVeiculosComSaida, buffer, sizeof(buffer));

    // Verifica se a mensagem esperada está presente na saída
    munit_assert(strstr(buffer, "Nenhum veiculo cadastrado.") != NULL);

    // Retorna sucesso no teste
    return MUNIT_OK;
}


// Testa se a função listarVeiculosComSaida exibe corretamente os dados de veículos cadastrados
static MunitResult test_listar_veiculos_com_dados(const MunitParameter params[], void* data) {
    // Configura 1 local necessário para exibir a localização do veículo (se aplicável)
    qtdLocais = 1;
    locais[0] = (Local){"Base", 0, 0};

    // Cadastra 1 veículo
    qtdVeiculos = 1;
    veiculos[0] = (Veiculo){"AAA0001", "Caminhao", 0, 0};  // status = 0 (livre), local = 0

    // Executa a função de listagem e captura a saída no buffer
    executarComSaida(listarVeiculosComSaida, buffer, sizeof(buffer));

    // Verifica se a placa do veículo aparece na saída
    munit_assert(strstr(buffer, "AAA0001") != NULL);

    // Verifica se o modelo do veículo aparece na saída
    munit_assert(strstr(buffer, "Caminhao") != NULL);

    // Retorna sucesso no teste
    return MUNIT_OK;
}


// --------------------- TESTES DE PEDIDOS ---------------------

// Testa se a função listarPedidosComSaida imprime a mensagem correta quando não há pedidos cadastrados
static MunitResult test_listar_pedidos_vazio(const MunitParameter params[], void* data) {
    // Define que não há pedidos registrados
    qtdPedidos = 0;

    // Executa a função de listagem de pedidos e captura a saída no buffer
    executarComSaida(listarPedidosComSaida, buffer, sizeof(buffer));

    // Verifica se a mensagem esperada está presente na saída
    munit_assert(strstr(buffer, "Nenhum pedido cadastrado.") != NULL);

    // Retorna sucesso no teste
    return MUNIT_OK;
}


// Testa se a função listarPedidosComSaida exibe corretamente os dados de pedidos cadastrados
static MunitResult test_listar_pedidos_com_dados(const MunitParameter params[], void* data) {
    // Cadastra dois locais (necessários para exibir os nomes na origem e destino do pedido)
    qtdLocais = 2;
    locais[0] = (Local){"L1", 0, 0};
    locais[1] = (Local){"L2", 5, 5};

    // Cadastra um pedido com origem em L1, destino em L2 e peso 20.5
    qtdPedidos = 1;
    pedidos[0] = (Pedido){1, 0, 1, 20.5};

    // Executa a função de listagem de pedidos, redirecionando a saída para o buffer
    executarComSaida(listarPedidosComSaida, buffer, sizeof(buffer));

    // Verifica se os dados do pedido aparecem corretamente na saída
    munit_assert(strstr(buffer, "ID: 1") != NULL);            // Confirma exibição do ID
    munit_assert(strstr(buffer, "Origem: L1") != NULL);       // Confirma nome da origem
    munit_assert(strstr(buffer, "Destino: L2") != NULL);      // Confirma nome do destino
    munit_assert(strstr(buffer, "20.50") != NULL);            // Confirma exibição do peso

    // Retorna sucesso no teste
    return MUNIT_OK;
}




// --------------------- REGISTRO DOS TESTES ---------------------

// Declaração do vetor de testes para o framework MUnit
static MunitTest tests[] = {
    // --------------------- TESTES DE ROTA ---------------------
    { "/rota/origem_invalida",       test_rota_origem_invalida,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/rota/destino_invalido",      test_rota_destino_invalido,      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/rota/sem_veiculo",           test_rota_sem_veiculo_disponivel,NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/rota/valida",                test_rota_valida,                NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    // --------------------- TESTES DE LOCAIS ---------------------
    { "/locais/vazio",               test_listar_locais_vazio,        NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/locais/com_dados",           test_listar_locais_com_dados,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    // --------------------- TESTES DE VEÍCULOS ---------------------
    { "/veiculos/vazio",             test_listar_veiculos_vazio,      NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/veiculos/com_dados",         test_listar_veiculos_com_dados,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    // --------------------- TESTES DE PEDIDOS ---------------------
    { "/pedidos/vazio",              test_listar_pedidos_vazio,       NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/pedidos/com_dados",          test_listar_pedidos_com_dados,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    // Fim da lista de testes (obrigatório)
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};


// Define a suíte de testes MUnit com todos os testes definidos no array `tests`
static const MunitSuite suite = {
    "/slem",                  // Prefixo para os nomes dos testes (usado no terminal, ex: /slem/rota/valida)
    tests,                   // Array de testes (definido anteriormente)
    NULL,                    // Sem sub-suites (poderia ser usado para dividir ainda mais os testes)
    1,                       // Número de vezes para repetir cada teste (1 = executar uma vez)
    MUNIT_SUITE_OPTION_NONE  // Nenhuma opção extra da suíte
};


int main(int argc, char* argv[]) {
    int result = munit_suite_main(&suite, NULL, argc, argv);
system("pause");  // Agora isso será executado
    return result;
}

