# 🔥 TrabalhoED: Sistema de Priorização de Componentes - Estratégia Final

Este código em C é a minha solução para o desafio da missão final – eu fiz a simulação do **Sistema de Priorização e Montagem de Componentes** necessário para organizar as peças essenciais sob pressão.

Eu usei diferentes algoritmos de ordenação e análise de desempenho para escolher a melhor tática para a missão.

---

## 💡 Como Resolvi o Desafio?

O meu sistema foi construído para cumprir todos os requisitos do trabalho:

1.  **Meus Componentes:** Criei a `struct Componente` para gerenciar o nome, o tipo e a prioridade de cada peça essencial.
2.  **Estratégias de Organização (Ordenação):**
    * **Opção Rápida:** Bubble Sort para ordenar por **Nome**.
    * **Opção Tática:** Insertion Sort para ordenar por **Tipo**.
    * **Opção Urgente:** Selection Sort para ordenar por **Prioridade**.
3.  **Análise de Custo (Desempenho):** Medi o tempo de execução (`clock()`) e o número de comparações para que você possa entender o impacto de cada escolha de algoritmo na missão.
4.  **O Item-Chave:** Implementei a Busca Binária para localizar o componente final, mas lembre-se: ela só funciona se a lista estiver ordenada por nome primeiro!

---

## 🛠️ Para Colocar o Código em Ação

Para testar o sistema é simples!

### 1. Compilar (Seu Compilador C)

No terminal, use o GCC e o nome do seu arquivo `Jennifer_Fartes_Procópio202308423754.c` para criar o executável:

```bash
gcc Jennifer_Fartes_Procópio202308423754.c -o sistema_prioridade
