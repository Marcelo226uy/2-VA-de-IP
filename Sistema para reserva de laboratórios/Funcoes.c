#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Funcoes.h"

int cadastrarLaboratorio(Laboratorio *lab, VetLaboratorios *vetLab) {
    // ESTRUTURA DE LABORATORIO
    // typedef struct {
    //     int id; 
    //     char nome[64];
    //     int capacidade;
    //     char equipamentos[256]; // texto informativo
    //     StatusLab status;
    // } Laboratorio;


    // ESTRUTURA DE STATUSLAB
    // typedef enum {
    //     LAB_ATIVO = 1,
    //     LAB_INDISPONIVEL = 0 // manutenção, bloqueio, etc.
    // } StatusLab;


    // Leitura de informações
    printf("Insira o ID:\n");
    scanf("%d", &lab[vetLab->qtd].id);

    printf("Insira o nome do lab:\n");
    scanf("%s", lab[vetLab->qtd].nome);

    printf("Insira a capacidade:\n");
    scanf("%d", &lab[vetLab->qtd].capacidade);

    printf("Insira uma descrição do lab:\n");
    scanf("%s", lab[vetLab->qtd].equipamentos);

    do {
        printf("Insira a situação do lab: [1] Ativo / [0] Inativo\n");
        scanf("%d", (int *) &lab[vetLab->qtd].status);
    } while (
        lab[vetLab->qtd].status != LAB_ATIVO && 
        lab[vetLab->qtd].status != LAB_INDISPONIVEL
    );
    
    vetLab->qtd++; // incrementando +1 lab ao total de cadastrados

    return 0;
}

void listarLaboratorios(VetLaboratorios *vetLab) {
    exibirCabecalhoTabela();

    for (int i = 0; i < vetLab->qtd; i++) {
        exibirLaboratorioLinha(vetLab->itens[i]);
    }

    exibirRodapeTabela();
}







void exibirCabecalhoTabela() {
    printf("+-----+--------------------------------+------------+---------------+----------------------------------+\n");
    printf("| ID  | Nome                           | Capacidade | Status        | Equipamentos                     |\n");
    printf("+-----+--------------------------------+------------+---------------+----------------------------------+\n");
}

void exibirLaboratorioLinha(Laboratorio lab) {
    // %.30s limita a exibicao para nao quebrar a estrutura da tabela
    printf("| %-3d | %-30s | %-10d | %-13s | %-32.30s |\n", 
           lab.id, 
           lab.nome, 
           lab.capacidade, 
           obterStatusTexto(lab.status),
           lab.equipamentos);
}

void exibirRodapeTabela() {
    printf("+-----+--------------------------------+------------+---------------+----------------------------------+\n\n");
}

char* obterStatusTexto(int status) {
    switch (status) {
        case 0:
            return "Inativo";
            break;
        case 1:
            return "Ativo";
            break;
    }
}





void removerLaboratorio(VetLaboratorios *vetLab) {
    printf("Selecione qual laboratório dos seguintes deletar:\n");
    
    listarLaboratorios(vetLab);
    
    int id;
    bool repetiu = false;
    do {
        if (repetiu == true) {
            printf("Insira um ID válido!\n");
        }

        printf("Insira o ID do lab: ");
        scanf("%d", &id);

        repetiu = true;
    } while (encontrarID(id, vetLab) == -1);

    reindexarLaboratorios(vetLab, encontrarID(id, vetLab));
}

int encontrarID(int id, VetLaboratorios *vetLab) { // ID encontrado retorna o índice
    for (int i = 0; i < vetLab->qtd; i++) {
        if (id == vetLab->itens[i].id) {
            return i;
        }
    }

    return -1;
}

void reindexarLaboratorios(VetLaboratorios *vetLab, int posicaoDeletar) {
    vetLab->itens[posicaoDeletar] = vetLab->itens[vetLab->qtd - 1];
    vetLab->qtd--;
}






int horarioInicioValido(Horario *hi) {
// Função para ver se o horário de início é válido
	if (hi->hora < 7 || hi->hora > 20) {
		return 0;
	}
	if (hi->minuto < 0 || hi->minuto > 59) {
		return 0;
	}
	return 1;
}

int horarioFinalValido(Horario *hf, Horario *hi) {
// Função para ver se o horário de término é válido
	if (hf->hora < 8 || hf->hora > 21) {
		return 0;
	}
	if (hf->minuto < 0 || hf->minuto > 59) {
		return 0;
	}
	if (hf->hora < hi->hora || hf->hora == hi->hora && hf->minuto < hi->minuto || hf->hora == hi->hora && hf->minuto == hi->minuto){
	    return 0;
	}
	return 1;
}

int dataValida(Data *dt) {
// Função para ver se a data é válida
	if (dt->dia < 1 || dt->dia > 31) {
		return 0;
	}
	if (dt->mes < 1 || dt->mes > 12) {
		return 0;
	}
	if (dt->ano != 2026) {
		return 0;
	}
	return 1;
}

void inicializarReservas(VetReservasLab *vet) {
// Função para alocar a memória inicial das reservas
    vet->qtd = 0;
    vet->cap = 10;

    vet->itens = malloc(vet->cap * sizeof(ReservaLab));

    if (vet->itens == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
}

int aumentarCapacidadeReservas(VetReservasLab *reservas) {
// Função para aumentar o número possivel de reservas
    int novaCapacidade;
    ReservaLab *temporario;

    novaCapacidade = reservas->cap + 10;

    temporario = realloc(reservas->itens, novaCapacidade * sizeof(ReservaLab));

    if (temporario == NULL) {
        printf("Erro ao aumentar memoria.\n");
        return 0;
    }

    reservas->itens = temporario;
    reservas->cap = novaCapacidade;

    return 1;
}

void cadastrarReserva(VetReservasLab *reservas) {
// Função para fazer a reserva
    ReservaLab *r;

    if (reservas->qtd == reservas->cap) {
        if (!aumentarCapacidadeReservas(reservas)){
             return;
        }
    }
    

    r = &reservas->itens[reservas->qtd];

    while (1) {
        printf("Defina o dia, mes e ano para sua reserva:\n");
        scanf("%d %d %d", &r->data.dia, &r->data.mes, &r->data.ano);

        if (dataValida(&r->data))
            break;

        printf("Data invalida! Tente novamente.\n");
    }

    while (1) {
        printf("Defina o horario de inicio da sua reserva:\n");
        scanf("%d %d", &r->inicio.hora, &r->inicio.minuto);

        if (horarioInicioValido(&r->inicio))
            break;

        printf("Horario invalido! Tente novamente.\n");
    }

    while (1) {
        printf("Defina o horario final da sua reserva:\n");
        scanf("%d %d", &r->fim.hora, &r->fim.minuto);

        if (horarioFinalValido(&r->fim, &r->inicio))
            break;

        printf("Horario invalido! Tente novamente.\n");
    }

    reservas->qtd++;

    printf("Reserva realizada com sucesso!\n");
}
