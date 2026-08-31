#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "laboratorios.h"
#include "utils.h"

// Funções principais dos laboratórios
int cadastrarLaboratorio(VetLaboratorios *vetLab) {
    Laboratorio *lab;

    if (vetLab->qtd == vetLab->cap) {
        if (!aumentarCapacidadeLaboratorios(vetLab)) {
            return 0;
        }
    }

    lab = &vetLab->itens[vetLab->qtd];

//      ID do laboratório
    do {

        printf("\nInsira o ID do laboratório: ");

        if (!lerInteiro(&lab->id)) {
            printf("ID inválido. Digite um número.\n");
            continue;
        }

        if (lab->id <= 0) {
            printf("O ID deve ser positivo.\n");
            continue;
        }

        if (encontrarID(lab->id, vetLab) != -1) {
            printf("Esse ID de laboratório já existe. Escolha outro.\n");
            continue;
        }

        break;

    } while (1);

//      Nome do laboratório
    do {
        printf("Insira o nome do laboratório: ");

        lerTexto(lab->nome, sizeof(lab->nome));

        if (strlen(lab->nome) == 0) {
            printf("O nome e obrigatório.\n");
        }

    } while (strlen(lab->nome) == 0);

//      Capacidade do laboratório
    do {

        printf("Insira a capacidade do laboratório: ");

        if (!lerInteiro(&lab->capacidade)) {
            printf("Capacidade inválida.\n");
            continue;
        }

        if (lab->capacidade <= 0) {
            printf("A capacidade deve ser maior que zero.\n");
        }

    } while (lab->capacidade <= 0);

//      Equipamentos do laboratório
    printf("Insira os equipamentos do laboratório: ");

    lerTexto(lab->equipamentos, sizeof(lab->equipamentos));

//      Status do laboratório
    int status;

    do {
        printf("Insira a situação do lab: [1] Ativo / [0] Inativo\n");

        if (!lerInteiro(&status)) {
            printf("Status inválido.\n");
            continue;
        }

        if (status != LAB_ATIVO &&
            status != LAB_INDISPONIVEL) {

            printf("Situação de laboratório inválida! Digite 1 para Ativo ou 0 para Inativo.\n");
        }

    } while (status != LAB_ATIVO &&
             status != LAB_INDISPONIVEL);

    lab->status = (StatusLab)status;

    vetLab->qtd++;

    salvarLaboratorios(vetLab);

    printf("Laboratório cadastrado com sucesso!\n");

    return 1;
}

void listarLaboratorios(VetLaboratorios *vetLab) {

    if (vetLab->qtd == 0) {
        printf("\nNenhum laboratório cadastrado.\n");
        return;
    }

    exibirCabecalhoTabela();

    for (int i = 0; i < vetLab->qtd; i++) {
        exibirLaboratorioLinha(vetLab->itens[i]);
    }

    exibirRodapeTabela();
}

void atualizarLaboratorio(VetLaboratorios *vetLab) {

    if (vetLab->qtd == 0) {
        printf("\nNenhum laboratório cadastrado.\n");
        return;
    }

    int id = escolherLaboratorio(vetLab);

    if (id == -1)
        return;

    int indice = encontrarID(id, vetLab);

    int escolha;

    do {
        printf("\nQual informação deseja editar?\n");
        printf("[1] Nome\n");
        printf("[2] Capacidade\n");
        printf("[3] Equipamentos\n");
        printf("[4] Status\n");
        printf("[0] Voltar\n");
        printf("Opção: ");

        if (!lerInteiro(&escolha)) {
            printf("Opção inválida.\n");
            continue;
        }

        switch (escolha) {
            
            case 1:

                do {
                    printf("Novo nome: ");

                    lerTexto(vetLab->itens[indice].nome, sizeof(vetLab->itens[indice].nome));

                    if (strlen(vetLab->itens[indice].nome) == 0) {
                        printf("O nome não pode ficar vazio.\n");
                    }

                } while (strlen(vetLab->itens[indice].nome) == 0);

                salvarLaboratorios(vetLab);

                printf("Nome atualizado.\n");

                break;

            case 2:

                do {

                    printf("Nova capacidade: ");

                    if (!lerInteiro(&vetLab->itens[indice].capacidade)) {

                        printf("Valor inválido.\n");
                        continue;
                    }

                    if (vetLab->itens[indice].capacidade <= 0) {
                        printf("A capacidade deve ser positiva.\n");
                    }

                } while (vetLab->itens[indice].capacidade <= 0);

                salvarLaboratorios(vetLab);

                printf("Capacidade atualizada.\n");

                break;

            case 3:

                printf("Novos equipamentos: ");

                lerTexto(vetLab->itens[indice].equipamentos,sizeof(vetLab->itens[indice].equipamentos));

                salvarLaboratorios(vetLab);

                printf("Equipamentos atualizados.\n");

                break;


            case 4: {

                int status;

                do {

                    printf("Insira a nova situação do lab: [1] Ativo / [0] Inativo\n");
                    
                    if (!lerInteiro(&status)) {
                        printf("Status inválido.\n");
                        continue;
                    }

                    if (status != 0 && status != 1) {
                        printf("Digite somente 1 ou 0.\n");
                    }

                } while (status != 0 && status != 1);

                vetLab->itens[indice].status = (StatusLab)status;

                salvarLaboratorios(vetLab);

                printf("Status atualizado.\n");

                break;
            }

            case 0:
                break;

            default:
                printf("Opcao inválida.\n");
        }

    } while (escolha != 0);
}

void removerLaboratorio(VetLaboratorios *vetLab) {

    if (vetLab->qtd == 0) {
        printf("\nNenhum laboratório cadastrado.\n");
        return;
    }

    int id = escolherLaboratorio(vetLab);

    if (id == -1)
        return;

    int indice = encontrarID(id, vetLab);

    printf("\nATENÇÃO: Verifique se NÃO existem reservas associadas.\n");

    int confirmado;

    do {
        printf("Confirma a remoção? [1] Sim [0] Não\n");
        printf("Opção: ");

        if (!lerInteiro(&confirmado)) {
            printf("Opcao inválida.\n");
            continue;
        }

        if (confirmado != 0 && confirmado != 1) {
            printf("Digite 1 ou 0.\n");
        }

    } while (confirmado != 0 && confirmado != 1);


    if (confirmado == 0) {
        printf("Remoção cancelada.\n");
        return;
    }

    
//  Preserva a ordem do vetor.
    for (int i = indice; i < vetLab->qtd - 1; i++) {
        vetLab->itens[i] = vetLab->itens[i + 1];
    }

    vetLab->qtd--;

    salvarLaboratorios(vetLab);

    printf("Laboratório removido com sucesso.\n");
}

// Funções auxiliares dos laboratórios

// Relação com alloc e memória
void inicializarLaboratorios(VetLaboratorios *vet) {

    vet->qtd = 0;
    vet->cap = 10;

    vet->itens = malloc(vet->cap * sizeof(Laboratorio));

    if (vet->itens == NULL) {
        printf("Erro ao alocar memoria dos laboratorios.\n");
        exit(1);
    }
}

int aumentarCapacidadeLaboratorios(VetLaboratorios *vet) {

    int novaCapacidade = vet->cap + 10;

// O ponteiro temporário é pra evitar perder o endereço original caso o realloc dê erro.
    Laboratorio *temporario = realloc(vet->itens, novaCapacidade * sizeof(Laboratorio));

    if (temporario == NULL) {
        printf("Erro ao aumentar memoria dos laboratorios.\n");
        return 0;
    }

    vet->itens = temporario;
    vet->cap = novaCapacidade;

    return 1;
}

void liberarLaboratorios(VetLaboratorios *vet) {
// Função para liberar espaço inutil dos laboratórios
    free(vet->itens);

    vet->itens = NULL;
    vet->qtd = 0;
    vet->cap = 0;
}

// Relação com ID
int encontrarID(int id, VetLaboratorios *vetLab) {

    for (int i = 0; i < vetLab->qtd; i++) {
        if (id == vetLab->itens[i].id) {
            return i;
        }
    }

    return -1;
}

int escolherLaboratorio(VetLaboratorios *vetLab) {

    if (vetLab->qtd == 0) {
        printf("\nNenhum laboratório cadastrado.\n");
        return -1;
    }

    listarLaboratorios(vetLab);

    int id;

    while (1) {

        printf("Insira o ID do laboratório: ");

        if (!lerInteiro(&id)) {
            printf("ID inválido.\n");
            continue;
        }

        if (encontrarID(id, vetLab) == -1) {
            printf("Laboratório não foi encontrado.\n");
            continue;
        }

        return id;
    }
}

// Funções para a lista

void exibirCabecalhoTabela(void) {

    printf("+-----+--------------------------------+------------+---------------+----------------------------------+\n");
    printf("| ID  | Nome                           | Capacidade | Status        | Equipamentos                     |\n");
    printf("+-----+--------------------------------+------------+---------------+----------------------------------+\n");
}

void exibirLaboratorioLinha(Laboratorio lab) {

    printf("| %-3d | %-30.30s | %-10d | %-13s | %-32.32s |\n",
           lab.id,
           lab.nome,
           lab.capacidade,
           obterStatusTexto(lab.status),
           lab.equipamentos);
}

void exibirRodapeTabela(void) {

    printf("+-----+--------------------------------+------------+---------------+----------------------------------+\n\n");
}

const char *obterStatusTexto(StatusLab status) {

    switch (status) {
        case LAB_ATIVO:
            return "Ativo";
        case LAB_INDISPONIVEL:
            return "Inativo";
        default:
            return "Desconhecido";
    }
}

// Relação com fopen
void carregarLaboratorios(VetLaboratorios *vet) {

    FILE *arquivo = fopen("laboratorios.txt", "r");

    if (arquivo == NULL) {
        return;
    }

    Laboratorio lab;

    while (fscanf(arquivo, "%d|%63[^|]|%d|%255[^|]|%d\n",
        &lab.id, lab.nome, &lab.capacidade, lab.equipamentos, (int *)&lab.status) == 5) {

        if (vet->qtd == vet->cap) {

            if (!aumentarCapacidadeLaboratorios(vet)) {
                break;
            }
        }

        if (lab.id <= 0 || lab.capacidade <= 0 || (lab.status != LAB_ATIVO && lab.status != LAB_INDISPONIVEL)) {
            continue;
        }

        if (encontrarID(lab.id, vet) != -1) {
            continue;
        }

        vet->itens[vet->qtd] = lab;

        vet->qtd++;
    }

    fclose(arquivo);
}

void salvarLaboratorios(VetLaboratorios *vet) {

    FILE *arquivo = fopen("laboratorios.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao tentar abrir o arquivo\n");
        return;
    }

    for (int i = 0; i < vet->qtd; i++) {
        Laboratorio *lab = &vet->itens[i];

        fprintf(arquivo, "%d|%s|%d|%s|%d\n",
            lab->id, lab->nome, lab->capacidade, lab->equipamentos, lab->status);
    }
    fclose(arquivo);
}

int quantidadeLaboratorios(VetLaboratorios *vet) {
    
    return vet->qtd;
}

