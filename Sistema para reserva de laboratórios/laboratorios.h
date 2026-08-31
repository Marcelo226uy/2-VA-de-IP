#ifndef LABORATORIOS_H
#define LABORATORIOS_H

// Structs
typedef enum {
    LAB_ATIVO = 1,
    LAB_INDISPONIVEL = 0 // manutenção, bloqueio, etc.
} StatusLab;

typedef struct {
    int id;
    char nome[64];
    int capacidade;
    char equipamentos[256]; // texto livre (ex.: "PCs, GPU, Projetor")
    StatusLab status;
} Laboratorio;

typedef struct {
    Laboratorio *itens;
    int qtd, cap;
} VetLaboratorios;

// Funções principais dos laboratórios
int cadastrarLaboratorio(VetLaboratorios *vetLab);
void listarLaboratorios(VetLaboratorios *vetLab);
void atualizarLaboratorio(VetLaboratorios *vetLab);
void removerLaboratorio(VetLaboratorios *vetLab);

// Funções auxiliares dos laboratórios
void inicializarLaboratorios(VetLaboratorios *vet);
int aumentarCapacidadeLaboratorios(VetLaboratorios *vet);
void liberarLaboratorios(VetLaboratorios *vet);
int encontrarID(int id, VetLaboratorios *vetLab);
int escolherLaboratorio(VetLaboratorios *vetLab);

// Funções para a lista
void exibirCabecalhoTabela(void);
void exibirLaboratorioLinha(Laboratorio lab);
void exibirRodapeTabela(void);
const char *obterStatusTexto(StatusLab status);

// Relação com fopen
void carregarLaboratorios(VetLaboratorios *vet);
void salvarLaboratorios(VetLaboratorios *vet);

// Funções para mostrar quantas reservas e Laboratórios têm
int quantidadeLaboratorios(VetLaboratorios *vet);

#endif
