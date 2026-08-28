#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
    // Modifiquei pra aceitar apenas IDs positivos maiores que 0
    do { 
        printf("Insira o ID:\n"); 
        scanf("%d", &lab[vetLab->qtd].id); 
        if (lab[vetLab->qtd].id <= 0) { 
            printf("ID inválido! Insira um ID positivo.\n"); 
        } 
    } while (lab[vetLab->qtd].id <= 0);

    // Alterei pra não ter problema com nome compostos
    while (getchar() != '\n'); 
    printf("Insira o nome do laboratório:\n"); 
    fgets(lab[vetLab->qtd].nome, 64, stdin);

    // Modifiquei pra aceitar apenas Capacidades positivas maiores que 0 igual o do ID
    do { 
        printf("Insira a capacidade:\n"); 
        scanf("%d", &lab[vetLab->qtd].capacidade); 
        if (lab[vetLab->qtd].capacidade <= 0) { 
            printf("Capacidade inválida! Insira um valor positivo.\n"); 
        } 
    } while (lab[vetLab->qtd].capacidade <= 0);

    // Alterei pra não ter problema com nome compostos
    while (getchar() != '\n'); 
    printf("Insira uma descrição do laboratório:\n"); 
    fgets(lab[vetLab->qtd].equipamentos, 256, stdin);

    // Modifiquei para caso colocar um valor que não pode ele voltar
    do {
        printf("Insira a situação do lab: [1] Ativo / [0] Inativo\n");
        scanf("%d", (int *) &lab[vetLab->qtd].status);
        if (lab[vetLab->qtd].status != LAB_ATIVO && lab[vetLab->qtd].status != LAB_INDISPONIVEL) { 
            printf("Situação de laboratório inválida! Digite 1 para Ativo ou 0 para Inativo.\n");
        }
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

    int id = escolherLaboratorio(vetLab);

    // CONFIRMAÇÃO
    printf("Confirma a remoção desse laboratório?\n");

    int confirmado;
    do {
        printf("[1] Confirmo\n [0] Não confirmo\n Sua opção: ");
        scanf("%d", &confirmado);
    } while (confirmado < 0 || confirmado > 1);

    if (confirmado == 1) {
        reindexarLaboratorios(vetLab, encontrarID(id, vetLab));
    };
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





int escolherLaboratorio(VetLaboratorios *vetLab) {
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

    return id;
};






void atualizarLaboratorio(VetLaboratorios *vetLab) {
    printf("Escolha um laboratório para editar:\n");

    int id = escolherLaboratorio(vetLab);
    int indice = encontrarID(id, vetLab);

    int escolha;
    do {
        printf("Qual informação deseja editar?\n");
        printf("[1] Nome\n [2] Capacidade\n [3] Detalhes\n [4] Status\n [0] Sair\n");

        do {
            scanf("%d", &escolha);
        } while (escolha < 0 || escolha > 4);
        
        while (getchar() != '\n'); // limpa o buffer do teclado que impede o fgets de ler correto

        switch (escolha) {
            case 1: 
                printf("Insira o nome do lab: ");
                fgets(vetLab->itens[indice].nome, sizeof(vetLab->itens[indice].nome), stdin);
                vetLab->itens[indice].nome[strcspn(vetLab->itens[indice].nome, "\n")] = '\0'; // limpa o "\n" para o fgets não guardar na variável
                break;
            case 2:
                printf("Insira a capacidade do lab: ");
                scanf("%d", &vetLab->itens[indice].capacidade);
                break;
            case 3:
                printf("Insira os detalhes do lab: ");
                fgets(vetLab->itens[indice].equipamentos, sizeof(vetLab->itens[indice].equipamentos), stdin);
                vetLab->itens[indice].equipamentos[strcspn(vetLab->itens[indice].equipamentos, "\n")] = '\0';
                break;
            case 4:
                do {
                    printf("Insira a situação do lab: [1] Ativo / [0] Inativo\n");
                    scanf("%d", (int *) vetLab->itens[indice].status);
                } while (
                    vetLab->itens[indice].status != LAB_ATIVO && 
                    vetLab->itens[indice].status != LAB_INDISPONIVEL
                );
                break;
            case 0:
                break;
        }

    } while (escolha != 0);
}




int proximoIdReserva(VetReservasLab *vet) {
    int maior = 0;

    for (int i = 0; i < vet->qtd; i++) {
        if (vet->itens[i].id > maior)
            maior = vet->itens[i].id;
    }

    return maior + 1;
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

void cadastrarReserva(VetReservasLab *reservas, VetLaboratorios *laboratorios) { // Checar se é realemnte *laboratorios o ponteiro
// Função para fazer a reserva
    ReservaLab *r;
    
    if (reservas->qtd == reservas->cap) {
        if (!aumentarCapacidadeReservas(reservas)) { 
            return;
        }
    }

    r = &reservas->itens[reservas->qtd];

    r->id = proximoIdReserva(reservas); // Ver se está alocando o ID certinho OBS. Aparentemente está agora tem que ver na hora de printar

    printf("Insira o nome ou matrícula do solicitante:\n");
    scanf(" %63[^\n]", r->solicitante);

    printf("Insira o ID do laboratório:\n");
    scanf("%d", &r->idLaboratorio);

    // Colocar alguma função que busque o laboratório pelo id e veja se ele está disponível

    while (1) {
        printf("Defina o dia, mês e ano para sua reserva:\n");
        scanf("%d %d %d", &r->data.dia, &r->data.mes, &r->data.ano);

        if (dataValida(&r->data)) {
            break;
        }

        printf("Data inválida! Tente outra data.\n");
    }

    while (1) {
        printf("Defina o horário de início da sua reserva:\n");
        scanf("%d %d", &r->inicio.hora, &r->inicio.minuto);

        if (horarioInicioValido(&r->inicio)) { 
            break;
        }

        printf("Horário inválido! Tente outro horário.\n");
    }

    while (1) {
        printf("Defina o horário de término da sua reserva:\n");
        scanf("%d %d", &r->fim.hora, &r->fim.minuto);

        if (horarioFinalValido(&r->fim, &r->inicio)) { 
            break;
        }

        printf("Horário inválido! Tente outro horário.\n");
    }

// Colocar uma função pra checar se não dá conflito de Horários nos laboratórios já reservados

    r->id = reservas->qtd + 1;

    reservas->qtd++;

    printf("Reserva realizada com sucesso!\n");
}
