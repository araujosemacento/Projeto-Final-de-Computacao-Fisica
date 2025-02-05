/* ANCHOR - Definição do Chip Sensor
 * Este módulo implementa um chip sensor analógico que:
 * - Realiza leitura de tensão de um pino analógico
 * - Ou melhor, simula a entrega de tensão pra um pino analógico
 * - Retornando valores normalizados entre 0 e 1024
 * - Utiliza uma única  entrada (saída, pino, sei lá, ficou complicado.
 * Depois de um tempo eu só fui pegando a manha mesmo) analógica configurável.
 */

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

/* ANCHOR - Constantes e Configurações */
#define PIN_NAME "A0"  // Pino analógico padrão
#define MIN_VALUE 0    // Valor mínimo de leitura
#define MAX_VALUE 1024 // Valor máximo de leitura

/* SECTION - Declarações Externas */
extern int32_t analog_read_pin(pin_t pin);

/* ANCHOR - Estrutura de Estado */
typedef struct
{
    pin_t sensor_pin; // Pino do sensor configurado
} chip_state_t;

static chip_state_t *chip;

/* ANCHOR - Funções Principais */
int32_t tick()
{
    /* SECTION - Leitura e Normalização
     * Realiza a leitura do sensor e garante que o valor
     * esteja dentro dos limites estabelecidos
     */
    int32_t value = analog_read_pin(chip->sensor_pin);

    // Normalização dos valores
    if (value < MIN_VALUE)
        value = MIN_VALUE;
    if (value > MAX_VALUE)
        value = MAX_VALUE;

    return value;
}

void chip_init()
{
    /* SECTION - Inicialização
     * Aloca memória e configura o pino do sensor
     */
    chip = malloc(sizeof(chip_state_t));
    chip->sensor_pin = pin_init(PIN_NAME, ANALOG);

    printf("Sensor chip initialized!\n");
}

/* TODO - Implementar função de cleanup para liberar memória alocada
 * TODO - Adicionar suporte para múltiplos pinos analógicos
 * TODO - Implementar filtro de média móvel para reduzir ruído (talvez! Um TALVEZ bem grande, caso um dia eu revisite esse projeto...)
 */