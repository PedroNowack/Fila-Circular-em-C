#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int senha;
    char nome[50];
} Pessoa;

typedef struct {
    int dados[MAX];
    int inicio, fim, qtd;
} Fila;

typedef struct {
    Pessoa dados[MAX];
    int inicio, fim, qtd;
} FilaAtendimento;

int lerNumero() {
    char linha[100];
    fgets(linha, sizeof(linha), stdin);
    return atoi(linha);
}

void mostrarEstado(FilaAtendimento *f) {
    printf("\nInicio: %d | Fim: %d | Quantidade: %d\n",
           f->inicio, f->fim, f->qtd);
}

void inserirInteiro(Fila *f) {
    int valor;

    if (f->qtd == MAX) {
        printf("Fila cheia!\n");
        return;
    }

    printf("Digite o valor: ");
    valor = lerNumero();

    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % MAX;
    f->qtd++;

    printf("Elemento inserido!\n");
}

void removerInteiro(Fila *f) {
    if (f->qtd == 0) {
        printf("Fila vazia!\n");
        return;
    }

    printf("Elemento removido: %d\n", f->dados[f->inicio]);

    f->inicio = (f->inicio + 1) % MAX;
    f->qtd--;
}

void listarInteiros(Fila *f) {
    int i;

    if (f->qtd == 0) {
        printf("Fila vazia!\n");
        return;
    }

    printf("Elementos da fila:\n");

    for (i = 0; i < f->qtd; i++) {
        printf("%d ", f->dados[(f->inicio + i) % MAX]);
    }

    printf("\n");
}

void exercicio1() {
    Fila f = {{0}, 0, 0, 0};
    int opcao;

    do {
        printf("\n--- EXERCICIO 1: FILA CIRCULAR ---\n");
        printf("1 - Inserir elemento\n");
        printf("2 - Remover elemento\n");
        printf("3 - Listar elementos\n");
        printf("4 - Voltar\n");
        printf("Opcao: ");

        opcao = lerNumero();

        switch (opcao) {
            case 1:
                inserirInteiro(&f);
                break;
            case 2:
                removerInteiro(&f);
                break;
            case 3:
                listarInteiros(&f);
                break;
            case 4:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 4);
}

void inserirPessoa(FilaAtendimento *f) {
    if (f->qtd == MAX) {
        printf("Fila cheia! Nao e possivel inserir.\n");
        mostrarEstado(f);
        return;
    }

    Pessoa p;

    printf("Digite o numero da senha: ");
    p.senha = lerNumero();

    printf("Digite o nome da pessoa: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';

    f->dados[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->qtd++;

    printf("Pessoa inserida com sucesso!\n");
    mostrarEstado(f);
}

void chamarPessoa(FilaAtendimento *f) {
    if (f->qtd == 0) {
        printf("Fila vazia! Nao ha pessoas para chamar.\n");
        mostrarEstado(f);
        return;
    }

    printf("Chamando senha %d - %s\n",
           f->dados[f->inicio].senha,
           f->dados[f->inicio].nome);

    f->inicio = (f->inicio + 1) % MAX;
    f->qtd--;

    mostrarEstado(f);
}

void listarPessoas(FilaAtendimento *f) {
    int i, posicao;

    if (f->qtd == 0) {
        printf("Fila de espera vazia!\n");
        mostrarEstado(f);
        return;
    }

    printf("\n--- FILA DE ESPERA ---\n");

    for (i = 0; i < f->qtd; i++) {
        posicao = (f->inicio + i) % MAX;

        printf("Senha: %d | Nome: %s\n",
               f->dados[posicao].senha,
               f->dados[posicao].nome);
    }

    mostrarEstado(f);
}

void exercicio2() {
    FilaAtendimento f = {{{0}}, 0, 0, 0};
    int opcao;

    do {
        printf("\n--- EXERCICIO 2: FILA DE ATENDIMENTO ---\n");
        printf("1 - Inserir pessoa\n");
        printf("2 - Chamar proxima pessoa\n");
        printf("3 - Visualizar fila\n");
        printf("4 - Voltar\n");
        printf("Opcao: ");

        opcao = lerNumero();

        switch (opcao) {
            case 1:
                inserirPessoa(&f);
                break;
            case 2:
                chamarPessoa(&f);
                break;
            case 3:
                listarPessoas(&f);
                break;
            case 4:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 4);
}

int main() {
    int opcao;

    do {
        printf("\n======= FILA CIRCULAR EM C =======\n");
        printf("1 - Exercicio 1\n");
        printf("2 - Exercicio 2\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        opcao = lerNumero();

        switch (opcao) {
            case 1:
                exercicio1();
                break;
            case 2:
                exercicio2();
                break;
            case 0:
                printf("Programa encerrado!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// TESTES OBRIGATORIOS - EXERCICIO 2

// 1. Insercao de elementos ate completar a fila:
// Inserindo cinco pessoas, a fila fica cheia.
// Inicio: 0 | Fim: 0 | Quantidade: 5

// 2. Tentativa de insercao em fila cheia:
// Ao tentar inserir uma sexta pessoa, aparece:
// "Fila cheia! Nao e possivel inserir."
// Inicio: 0 | Fim: 0 | Quantidade: 5

// 3. Remocao de elementos:
// Chamando a proxima pessoa, a primeira da fila e removida.
// Inicio: 1 | Fim: 0 | Quantidade: 4

// 4. Nova insercao utilizando posicoes liberadas:
// Inserindo outra pessoa, a posicao liberada e reaproveitada.
// Inicio: 1 | Fim: 1 | Quantidade: 5

// 5. Remocao de todos os elementos e tentativa de remocao em fila vazia:
// Apos remover todas as pessoas:
// Inicio: 1 | Fim: 1 | Quantidade: 0
// Ao tentar remover novamente, aparece:
// "Fila vazia! Nao ha pessoas para chamar."
