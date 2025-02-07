/* ANCHOR - Documentação do Módulo
 * Módulo de simulação de sensor analógico
 * Simula a entrega de tensão para um pino analógico,
 * retornando valores normalizados entre 0 e 1024.
 */

/* ANCHOR - Inclusões */
#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

/* ANCHOR - Definições de Tipos */
typedef struct
{
    pin_t pin_out;
    uint32_t moisture_attr;
} chip_state_t;

/* ANCHOR - Protótipos */
static void chip_timer_event(void *user_data);

/* ANCHOR - Implementação: Inicialização
 * Inicializa o módulo do sensor.
 * - Configura estrutura de estado
 * - Inicializa pino de saída analógica
 * - Configura atributo de umidade
 * - Estabelece timer para atualizações periódicas
 */
void chip_init(void)
{
    chip_state_t *chip = malloc(sizeof(chip_state_t));
    chip->pin_out = pin_init("OUT", ANALOG);
    chip->moisture_attr = attr_init_float("moisture", 1.0);

    const timer_config_t timer_config = {
        .callback = chip_timer_event,
        .user_data = chip,
    };
    timer_t timer_id = timer_init(&timer_config);
    timer_start(timer_id, 1000, true);
}

/* ANCHOR - Implementação: Timer
 * Função de callback do timer
 * Atualiza o valor do pino analógico com base no atributo de umidade
 *
 * @param user_data Ponteiro para estrutura de estado do chip
 */
void chip_timer_event(void *user_data)
{
    chip_state_t *chip = (chip_state_t *)user_data;
    float moisture = attr_read_float(chip->moisture_attr);
    pin_dac_write(chip->pin_out, moisture);
}

/* TODO
 * - Implementar liberação de memória
 * - Adicionar suporte multi-pino
 * - Implementar filtro de média móvel
 */