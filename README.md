# Simulador de Bolsa de Valores

`PROGRAMAÇÃO E DESENVOLVIMENTO DE SOFTWARE II`

Este projeto se baseia na criação de um simulador de bolsa de valores, uma plataforma virtual que possibilita aos usuários praticarem investimentos financeiros sem arriscar dinheiro real. Ele replica as condições reais do mercado financeiro, oferencendo ferramentas e recursos semelhantes aos que são encontrados em plataformas de negociações reais. Os usuários poderão comprar e vender ações com dinheiro fictício enquanto acompanham o desempenho de seus investimentos. Esse simulador é útil para investidores iniciantes aprenderem sobre o mercado financeiro, experimentarem diferentes estratégias de investimento e ganharem confiança antes de investirem com dinheiro real.

## Integrantes

* Alexandre Rodrigues da Silva
* Eduarda Souza Nunes
* Gabriel Garcia Lamego Rodrigues
* Luiz Fernando de Almeida Dias

## Orientador

* Wagner Cipriano

# Estrutura do Projeto

 Este projeto não possui outros diretórios além do principal. Todos os arquivos do projeto se encontram em um diretório.

# Instruções de Instalação

**Requisitos**:  
- No mínimo, 1.23 MB de espaço disponível
- (Opcional) Ter a linha de comando “make” instalada no computador

Baixe os arquivos do projeto neste repositório e coloque-os em um local de seu pc de sua preferência.
Caso faça modificações no código do programa, ele pode ser compilado utilizando o arquivo “makefile”. Abra a interface de linha de comando de sua preferência (prompt de comando, powershell, etc) operando no diretório em que estão os arquivos do projeto e digite o comando “make”.

# Instruções de Uso

##  Instruções Gerais
Abra o arquivo “stock_simulation.exe” e rode o programa. O programa abrirá em seu menu principal, o qual apresentará diversas opções para o usuário do software escolher como prosseguir:

### Quadro de ações 

Ao digitar “q” no menu principal, você será redirecionado para uma lista com o código, a empresa associada e o valor de cada ação disponível no mercado virtual do programa.

### Histórico de preço de uma ação

Ao digitar “p” no menu principal, você poderá ver o histórico dos últimos 10 ou menos valores registrados de uma ação a qual foi selecionada.

### Consultar disponibilidade de compra

Ao digitar “a” no menu principal, você poderá ver a quantidade disponível no mercado virtual de uma ação selecionada.

### Visualizar carteira de usuário

Ao digitar “u” no menu principal, você poderá visualizar a carteira (saldo e ações que possui) de um usuário registrado no sistema do programa.

### Comprar ação

Ao digitar “b” no menu principal, você poderá comprar uma ação disponível no mercado virtual do programa para a carteira de um usuário selecionado. 

### Vender ação

Ao digitar “s” no menu principal, você poderá vender uma ação disponível na carteira do usuário que você selecionar. 

### Menu do administrador

Ao digitar “d” no menu principal, você será redirecionado para o menu do administrador, nele haverá diversas opções para o usuário do programa ter a capacidade de alterar os dados do programa livremente:

- **Adicionar novo ativo de ação**: 
Digitando “a”, pode-se adicionar um novo ativo de ação ao mercado virtual, informando seu código, empresa associada, valor e quantidade disponível
- **Remover ativo de ação**: 
Digitando “r”, pode-se remover um ativo de ação o qual for selecionado do mercado virtual
- **Cadastrar novo usuário**: 
Digitando “c”, pode-se cadastrar um novo usuário ao sistema do programa, informando seu nome e seu primeiro depósito em sua carteira
- **Remover conta de usuário**: Digitando “e”, pode-se remover um usuário cadastrado o qual foi selecionado do sistema

## Utilizando dados.txt

Caso o usuário queira alterar os dados iniciais do programa, ele pode utilizar o arquivo “dados.txt” localizado no próprio diretório do programa. Esse arquivo contém todos os dados os quais o software terá ao inicializar.
O arquivo é dividido em três partes. A primeira está relacionada aos ativos do mercado virtual e pode-se alterá la baseando-se na seguinte estrutura a qual ela segue:

_Número de ativos diferentes  
Empresa relacionada|Código|Valor|Número total de ações disponíveis|Histórico do ativo  
…_

A segunda parte diz sobre os usuários cadastrados no sistema e suas respectivas carteiras. Ela segue a seguinte estrutura:

_Número de usuários  
Nome|Saldo na carteira|Quantidade de ativos diferentes  
Código do ativo na carteira|Quantidade do ativo  
…_

A terceira parte contém as transações que ocorreram antes da inicialização do programa e possui a seguinte estrutura:

_Número de transações  
Data e hora da transação|Usuário|Tipo de transação|Código|Quantidade do ativo|Valor da transação  
…_

Cada seção do arquivo é dividida por uma linha vazia, assim como cada usuário da segunda parte.

# Principais Dificuldades

A principal dificuldade encontrada no projeto foi relacionada ao arquivo “main.cpp”, que estava ficando muito grande e confuso. Como resolução, tivemos que criar os arquivos “simulation.hpp” e “simulation.cpp” para manter uma programação mais organizada e menos confusa, além de fazer pequenas alterações nos outros arquivos que já estavam prontos.

