#include <stdio.h>

// STRUCTS
typedef struct {
    int dia, mes, ano; // DD/MM/AAAA
} Data;

typedef struct {
    int hora, minuto; //24h
} Horario;

typedef enum {
    LAB_ATIVO = 1,
    LAB_INDISPONIVEL = 0 // manutenção, bloqueio, etc.
} StatusLab;

typedef struct {
    int id; 
    char nome[64];
    int capacidade;
    char equipamentos[256]; // texto informativo
    StatusLab status;
} Laboratorio;

typedef struct {
    int id;
    char solicitante[64]; // nome ou matrícula
    int idLaboratorio;
    Data data;
    Horario inicio; // início do uso
    Horario fim; // fim do uso
} ReservaLab;

// Coleções dinâmicas
typedef struct {
    Laboratorio *itens;
    int qtd, cap;
} VetLaboratorios;

typedef struct {
    ReservaLab *itens;
    int qtd, cap;
} VetReservasLab;


// FUNCOES
void cadastrarReserva();
int cadastrarLaboratorio(Laboratorio *lab, VetLaboratorios *vetLab);

void listarLaboratorios(VetLaboratorios *vetLab);
void exibirCabecalhoTabela();
void exibirLaboratorioLinha(Laboratorio lab);
void exibirRodapeTabela();
char* obterStatusTexto(int status);

void removerLaboratorio(VetLaboratorios *vetLab);
int encontrarID(int id, VetLaboratorios *vetLab);
void reindexarLaboratorios(VetLaboratorios *vetLab, int posicaoDeletar);

int escolherLaboratorio(VetLaboratorios *vetLab);

void atualizarLaboratorio(VetLaboratorios *vetLab);

void verificarMemoria(VetLaboratorios *vetLab);
void alocarMemoria(VetLaboratorios *vetLab);
void retirarMemoria(VetLaboratorios *vetLab);

// Funções para usar em outras funções
int dataValida(Data *dt);
int horarioInicioValido(Horario *hi);
int horarioFinalValido(Horario *hf, Horario *hi);
int aumentarCapacidadeReservas(VetReservasLab *reservas);
int proximoIdReserva(VetReservasLab *vet);

// Funções para usar na função principal
void cadastrarReserva(VetReservasLab *reservas, VetLaboratorios *laboratorios);
void inicializarReservas(VetReservasLab *vet);
