#include <stdio.h>

int cadastrarLaboratorio(void);


// Funções para usar em outras funções
int dataValida(Data *dt);
int horarioInicioValido(Horario *hi);
int horarioFinalValido(Horario *hf, Horario *hi);
int aumentarCapacidadeReservas(VetReservasLab *reservas);

// Funções para usar na função principal
void cadastrarReserva(VetReservasLab *reservas);
void inicializarReservas(VetReservasLab *vet);
