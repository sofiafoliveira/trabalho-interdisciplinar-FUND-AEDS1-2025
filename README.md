# trabalho-interdisciplinar-FUND-AEDS1-2025
Projeto interdisciplinar entre Fundamentos de Engenharia de Software e Algoritmos e Estruturas de Dados I.

Integrantes:
- Sofia Figueiredo de Oliveira
- André Fortini de Mello
- Lucas Maia Marques Pinheiro
- Larissa Monção de Oliveira

## Link demonstrando o funcionamento do sistema:
https://youtu.be/t9HiHqxLNFw

------------------------------------------------------------

CRUD de Pedidos — Módulo de Sofia Figueiredo

Descrição:
Este módulo implementa o CRUD (Create, Read, Update, Delete) para gerenciar os pedidos do sistema de entregas.
Permite cadastrar, listar, atualizar e excluir pedidos armazenados em um vetor estático.

Como usar:
- Compile e execute o código.
- Use o menu apresentado no console para interagir com os pedidos.

Funcionalidades:
- Cadastrar novo pedido com ID do veículo, local de entrega, descrição e status.
- Listar todos os pedidos cadastrados.
- Atualizar a descrição e status de um pedido existente.
- Excluir um pedido pelo ID.

Testes realizados:
- Cadastro de múltiplos pedidos com dados variados.
- Listagem dos pedidos para verificar a inclusão correta.
- Atualização de pedidos existentes, alterando descrição e status.
- Exclusão de pedidos pelo ID e verificação da remoção correta.
- Tentativa de atualizar e excluir pedidos inexistentes para verificar tratamento de erros.

  Exemplo de uso:
1. Cadastrar pedido  
   ID veículo: 101  
   ID local: 55  
   Descrição: Entrega de documentos
2. Listar pedidos  
   (Mostra o pedido cadastrado)
3. Atualizar pedido  
   ID pedido: 1  
   Nova descrição: Entrega urgente de documentos  
   Novo status: 1
4. Excluir pedido  
   ID pedido: 1
5. Listar pedidos  
   (Nenhum pedido cadastrado)
   
------------------------------------------------------------

CRUD de Veículos — Módulo de ANDRÉ FORTINI DE MELLO

Descrição:
Este módulo implementa um CRUD para gerenciar os veículos utilizados no sistema de entregas.
As informações são armazenadas em um vetor estático e manipuladas via menu no console

Funcionalidades:

-Cadastrar um novo veículo com:

*Placa (única)
*Modelo
*Status (0 = disponível, 1 = ocupado)
*ID do local atual
*Listar todos os veículos cadastrados.

-Atualizar dados de um veículo existente (modelo, status, ID local).

-Excluir um veículo com base na placa.

Testes realizados:

*Cadastro de veículos com diferentes placas e dados.
*Verificação de erro ao tentar cadastrar placa repetida.
*Atualização de modelo, status e localização de veículos existentes.
*Exclusão de veículos específicos e verificação da lista após a remoção.
*Tentativa de atualizar/excluir veículos não existentes.

Exemplo de uso:
Cadastrar veículo
Placa: ABC1234
Modelo: Fiorino Branca
Status: 0
ID Local Atual: 12

Listar veículos
→ Exibe o veículo cadastrado

Atualizar veículo
Placa: ABC1234
Novo modelo: Fiorino Branca Turbo
Novo status: 1
Novo ID Local: 22

Excluir veículo
Placa: ABC1234

Listar veículos
→ Nenhum veículo cadastrado

------------------------------------------------------------

CRUD de Locais — Módulo de ANDRÉ FORTINI DE MELLO

Descrição:
Este módulo implementa um CRUD para gerenciar os locais de entrega do sistema, com nome e coordenadas (X, Y), armazenados em vetor estático.

Funcionalidades:

Cadastrar um novo local com:
*Nome (único)
*Coordenadas X e Y
*Listar todos os locais cadastrados.
*Atualizar as coordenadas de um local pelo nome.
*Excluir um local pelo nome.

Testes realizados:

*Cadastro de locais com nomes e coordenadas variadas.
*Verificação de erro ao tentar cadastrar nome duplicado.
*Atualização de coordenadas de locais existentes.
*Exclusão de locais e verificação de remoção.
*Tentativa de atualizar/excluir locais não existentes.

Exemplo de uso:
Cadastrar local
Nome: São Paulo
Coord X: 00.0
Coord Y: 00.0

Listar locais
→ Exibe o local cadastrado

Atualizar local
Nome: São Paulo
Nova Coord X: 00.0
Nova Coord Y: 00.0

Excluir local
Nome: São Paulo

Listar locais
→ Nenhum local cadastrado

------------------------------------------------------------

CRUD de Locais — Módulo de ANDRÉ FORTINI DE MELLO

Descrição:
Este módulo implementa um CRUD para gerenciar os locais de entrega do sistema, com nome e coordenadas (X, Y), armazenados em vetor estático.

Funcionalidades:

Cadastrar um novo local com:
*Nome (único)
*Coordenadas X e Y
*Listar todos os locais cadastrados.
*Atualizar as coordenadas de um local pelo nome.
*Excluir um local pelo nome.

Testes realizados:

*Cadastro de locais com nomes e coordenadas variadas.
*Verificação de erro ao tentar cadastrar nome duplicado.
*Atualização de coordenadas de locais existentes.
*Exclusão de locais e verificação de remoção.
*Tentativa de atualizar/excluir locais não existentes.

Exemplo de uso:
Cadastrar local
Nome: São Paulo
Coord X: 00.0
Coord Y: 00.0

Listar locais
→ Exibe o local cadastrado

Atualizar local
Nome: São Paulo
Nova Coord X: 00.0
Nova Coord Y: 00.0

Excluir local
Nome: São Paulo

Listar locais
→ Nenhum local cadastrado

------------------------------------------------------------

Função: restaurarDados — Módulo de Lucas Maia
Descrição
Esta função é executada no início do sistema e carrega os dados dos arquivos salvos para os vetores de memória, restaurando o estado anterior da aplicação.

Como usar
Chamada no início da função main() para garantir que todos os dados estejam carregados antes de interações com o usuário.

Funcionalidade
Abre os arquivos de dados existentes.

Lê o conteúdo e preenche os vetores locais[], veiculos[] e pedidos[].

Atualiza as variáveis globais qtdLocais, qtdVeiculos, qtdPedidos.

Testes realizados
Inicialização do sistema com arquivos contendo dados.

Teste de integridade das estruturas após leitura.

Verificação do comportamento quando os arquivos não existem (tratamento de erro).

Exemplo de uso

restaurarDados(); // Carrega os dados salvos e inicializa o sistema

------------------------------------------------------------

Menu de Funcionalidades — Módulo de Larissa Monção de Oliveira

Descrição:
Menu que será exibido na função main com as funcionalidades do sistema.

Funcionalidades:

 *Cadastrar Local
 *Listar Locais
 *Cadastrar Veículo
 *Listar Veículos
 *Cadastrar Pedido
 *Listar Pedidos
 *Calcular e Exibir Rota de Entrega
 *Backup de Dados
 *Restaurar Dados
 *Sair


Testes realizados -------------------

Teste de Backup e Restauração: 
- Verificar se os dados são salvos e carregados corretamente em arquivos binários.
  

1. Cadastrar Locais, Veículos e Pedidos.
2. Executar "Backup de Dados".
3. Encerrar o programa.
4. Abrir novamente e executar "Restaurar Dados"
5. Verificar se os dados restaurados estão corretos (listagens).


Teste da Rota de Entrega
- Verificar se o cálculo da rota funciona corretamente.

1. Criar 3 Locais (A, B, C) com coordenadas específicas.
2. Cadastrar 2 Veículos, um mais próximo do ponto de origem do pedido.
3. Criar 1 Pedido com origem A e destino B.
4. Ação: Excluir um veículo existente.
5. Resultado Esperado: O veículo não aparece mais na listagem.
6. Resultado Obtido: Sucesso. O veículo foi removido corretamente

Função: calcularDistancia — Módulo de Larissa Monção
Descrição
A função calcularDistancia() retorna a distância euclidiana entre dois pontos, com base nas coordenadas cartesianas (x, y).

-Como usar
É chamada sempre que for necessário exibir ou registrar a distância entre veículo e local de entrega.

-Funcionalidade
Recebe as coordenadas x1, y1 (do veículo) e x2, y2 (do local).

Utiliza a fórmula da distância euclidiana:

distância = √((x2 - x1)²+(y2 - y1)²) 
 
Retorna um float com a distância calculada.

-Testes realizados
Casos com coordenadas positivas e negativas.

Distância entre pontos iguais (resultado zero).

Comparação dos resultados com cálculo manual.

-Exemplo de uso

float d = calcularDistancia(3.0, 4.0, 0.0, 0.0); // Resultado: 5.0

