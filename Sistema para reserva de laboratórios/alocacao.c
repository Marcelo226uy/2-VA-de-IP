// #include <stdlib.h>
// #include "alocacao.h"
// #include "Funcoes.h"

// void verificarMemoriaVetLaboratorios(VetLaboratorios *vetLab) {
//     if (vetLab->cap - vetLab->qtd <= 1) { // pouca memória
//         alocarMemoriaVetLaboratorios(vetLab);
//     } else if (vetLab->cap - vetLab->qtd >= 10) { // muita memória
//         retirarMemoriaVetLaboratorios(vetLab);
//     }
// }

// void alocarMemoriaVetLaboratorios(VetLaboratorios *vetLab) {
//     vetLab->itens = realloc(vetLab, (vetLab->cap + 5) * sizeof(Laboratorio));
//     vetLab->cap += 5;
// }

// void retirarMemoriaVetLaboratorios(VetLaboratorios *vetLab) {
//     vetLab->itens = realloc(vetLab, (vetLab->cap - 5 * sizeof(Laboratorio)));
//     vetLab->cap -= 5;
// }
