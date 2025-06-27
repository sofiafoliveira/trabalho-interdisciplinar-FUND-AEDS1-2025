# trabalho-interdisciplinar-FUND-AEDS1-2025
Projeto interdisciplinar entre Fundamentos de Engenharia de Software e Algoritmos e Estruturas de Dados I.

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

