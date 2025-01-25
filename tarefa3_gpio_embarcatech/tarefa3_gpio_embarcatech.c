#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "matriz_led.pio.h"

// Tipos de dados.
struct pixel_t
{
    uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Constantes
#define LED_COUNT 25
#define LED_PIN 9
#define BUZZER_FREQUENCY 100
#define BUZZER_PIN 21
#define CLK_DIV 4.0f
#define RGB_MAX 255
#define PIXEL_DELAY 200
#define ANIMATION_DELAY 1000

// Protótipos das funções.
void init_matrix_pins();
char get_pressed_key();
void np_init(uint pin);
void np_set_led(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);
void np_clear();
void np_write();
void init_buzzer();
void play_buzzer(uint freq, uint duration_ms);
void draw_V(void); // Protótipo da função draw_V
void fill_color(uint8_t r, uint8_t g, uint8_t b);
void draw_snake();
void draw_checkerboard_pattern(int r1, int g1, int b1, int r2, int g2, int b2);
void animate_checkerboard_pattern(int delay_ms);
void draw_heart_animation();
void animate_subgrupo3();
void draw_arrow_animation();
void handle_key_b();

// Variáveis globais
npLED_t leds[LED_COUNT]; // Declaração do buffer de pixels que formam a matriz.
PIO np_pio;              // Ponteiro para a máquina PIO.
uint sm;                 // Número da máquina state machine.

int rows[4] = {8, 7, 6, 5};     // Pinos GPIO do teclado matricial.
int columns[4] = {4, 3, 2, 28}; // Pinos GPIO do teclado matricial.
char keypad[4][4] = {{'1', '2', '3', 'A'},
                     {'4', '5', '6', 'B'},
                     {'7', '8', '9', 'C'},
                     {'*', '0', '#', 'D'}};

int main()
{
    char key;

    // Inicializa entradas e saídas.
    stdio_init_all();

    // Inicializa matriz de LEDs NeoPixel.
    np_init(LED_PIN);
    np_clear();

    init_matrix_pins(); // chama a função do GPIO do teclado matricial
    init_buzzer();      // Inicializa o Buzzer

    // Loop principal.
    while (true)
    {
        // Ler tecla pressionada
        key = get_pressed_key();

        if (key != '\0')
        {
            switch (key)
            {

            case '0':
                printf("Tecla pressionada: %c\n", key);
                animate_checkerboard_pattern(200); // Animação fluida com atraso de 200 ms
                break;

            case '1':
                printf("Tecla pressionada: %c\n", key);
                animate_subgrupo3(); // Executa animação da palavra "Subgrupo3".
                sleep_ms(200);
                break;

            case '2':
                printf("Tecla pressionada: %c\n", key);
                draw_snake();

                np_clear();
                np_write();
                sleep_ms(ANIMATION_DELAY);
                break;

            case '3':
                printf("Tecla pressionada: %c\n", key);
                draw_arrow_animation();

                np_write();
                sleep_ms(200);
                break;

            case '4':
                printf("Tecla pressionada:4 %c\n", key);
                draw_V();

                np_clear();
                np_write();
                sleep_ms(ANIMATION_DELAY);
                break;

            case '5':
                printf("Tecla pressionada: %c\n", key);
                sleep_ms(200);
                break;

            case '6':
                printf("Tecla pressionada: %c\n", key);
                sleep_ms(200);
                break;
            case '7':
                printf("Tecla pressionada: %c\n", key);
                sleep_ms(200);
                break;

            case '8':
                printf("Tecla pressionada: %c\n", key);
                sleep_ms(200);
                break;

            case '9':
                printf("Tecla pressionada: %c\n", key);
                sleep_ms(200);
                break;

            case 'A':
                np_clear();
                np_write();
                break;

            case 'B':
                handle_key_b(); // Aciona a funcionalidade da tecla B.
                break;

            case 'C':
                fill_color(RGB_MAX * 0.8, 0, 0);
                break;

            case 'D':
                draw_heart_animation(); // Chama a função para desenhar o coração
                np_write();             // Escreve os LEDs na matriz
                sleep_ms(200);          // Atraso para evitar múltiplos acionamentos
                break;

            case '#':
                printf("Tecla pressionada: %c\n", key);
                fill_color(RGB_MAX * 0.2, RGB_MAX * 0.2, RGB_MAX * 0.2); // Acende todos os LEDs na cor branca com 20% de intensidade
                break;

            case '*':
                // Implementar função correspondente

                break;

            default:
                printf("Tecla não reconhecida ou erro na operação!\n");
            }
        }
    }
}

/*Essa função inicializa os pinos GPIO do teclado matricial e
Ativa resistores pull-down nos pinos de entrada para evitar leituras flutuantes */
void init_matrix_pins()
{
    for (int i = 0; i < 4; i++)
    {
        gpio_init(rows[i]);
        gpio_set_dir(rows[i], GPIO_OUT);
        gpio_put(rows[i], 0);
    }

    for (int j = 0; j < 4; j++)
    {
        gpio_init(columns[j]);
        gpio_set_dir(columns[j], GPIO_IN);
        gpio_pull_down(columns[j]);
    }
}

// Essa função verifica o teclado matricial para detectar qual tecla foi pressionada.
char get_pressed_key()
{
    for (int i = 0; i < 4; i++)
    {
        gpio_put(rows[i], 1);
        sleep_ms(20);
        for (int j = 0; j < 4; j++)
        {
            if (gpio_get(columns[j]))
            {
                gpio_put(rows[i], 0);
                return keypad[i][j];
            }
        }
        gpio_put(rows[i], 0);
    }
    return '\0';
}

// Função para inicializar o Buzzer
void init_buzzer()
{
    // Inicializar GPIOs do Buzzer
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM); // Configura o pino como PWM

    // Slice PWM do pino
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    // Configuração do PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f); // Definindo o divisor de clock
    pwm_init(slice_num, &config, true);

    // Define o PWM inicialmente no nível baixo
    pwm_set_gpio_level(BUZZER_PIN, 0);
}

// Função para tocar o Buzzer
void play_buzzer(uint freq, uint duration_ms)
{
    if (freq == 0)
    {
        printf("Frequência inválida: %u Hz\n", freq);
        return; // Evita divisão por zero ou comportamento inesperado
    }

    // Obtém o slice PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    // Frequência do PWM pela BUZZER_FREQUENCY
    uint clock_freq = clock_get_hz(clk_sys);  // Frequência do clock                   // Divisor do clock
    uint top = clock_freq / (freq * CLK_DIV); // Cálculo do TOP

    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(BUZZER_PIN, top / 2);

    // Duração do som emitido
    sleep_ms(duration_ms);

    // Desliga o Buzzer
    pwm_set_gpio_level(BUZZER_PIN, 0);

    sleep_ms(100); // Entrepausa de 100ms
}

// Inicializa a máquina PIO para controle da matriz de LEDs.
void np_init(uint pin)
{

    // Cria programa PIO.
    uint offset = pio_add_program(pio0, &matriz_led_program);
    np_pio = pio0;

    // Toma posse de uma máquina PIO.
    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0)
    {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
    }

    // Inicia programa na máquina PIO obtida.
    matriz_led_program_init(np_pio, sm, offset, pin, 800000.f);

    // Limpa buffer de pixels.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

// Atribui uma cor RGB a um LED.
void np_set_led(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

// Limpa o buffer de pixels.
void np_clear()
{
    for (uint i = 0; i < LED_COUNT; ++i)
        np_set_led(i, 0, 0, 0);
}

// Escreve os dados do buffer nos LEDs.
void np_write()
{
    // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

// Preenche a matriz de LEDs com uma cor RGB por um tempo determinado.
void fill_color(uint8_t r, uint8_t g, uint8_t b)
{
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        np_set_led(i, r, g, b);
    }

    np_write();
}

void draw_V()
{
    np_clear(); // Limpa a matriz antes de acender os LEDs
    np_write(); // Envia os dados para o display

    // Acende os LEDs em azul, de cima para baixo
    for (int i = 0; i < LED_COUNT; i++)
    {                             // Linha 1
        np_set_led(i, 0, 0, 255); // Acende o LED em azul
        np_write();               // Envia os dados para o display
        sleep_ms(PIXEL_DELAY);    // Aguarda 100 ms antes de acender o próximo LED
    }
}

void draw_snake()
{
    int len_snake = 3;

    np_clear();
    np_write();

    for (int i = 0; i < LED_COUNT; i++)
    {
        for (int j = 0; j < len_snake; j++)
        {
            if (i - j >= 0)
            {
                np_set_led(i - j, 0, 255, 0);
            }
        }

        np_write();
        sleep_ms(PIXEL_DELAY);

        np_clear();
        np_write();
    }
}

// Desenha um padrão nos LEDs com duas cores alternadas.
void draw_checkerboard_pattern(int r1, int g1, int b1, int r2, int g2, int b2)
{
    np_clear();
    for (int i = 0; i < LED_COUNT; i++)
    {
        if (i >= 0 && i <= 4)
            np_set_led(i, r1, g1, b1);
        else if (i >= 10 && i <= 14)
            np_set_led(i, r2, g2, b2);
        else if (i >= 20 && i <= 24)
            np_set_led(i, r2, g2, b2);
        else
            np_set_led(i, 0, 0, 0);
    }
    np_write();
}

// A função faz a animação entre dois padrões de cores, após isso, aplica duas cores sólidas
void animate_checkerboard_pattern(int delay_ms)
{
    for (int i = 0; i < 4; i++)
    {
        if (i % 2 == 0)
        {
            draw_checkerboard_pattern(255, 0, 255, 0, 255, 255); // Padrão 1
        }
        else
        {
            draw_checkerboard_pattern(0, 255, 255, 255, 0, 255); // Padrão 2
        }
        sleep_ms(delay_ms);
    }

    np_clear();
    // matriz totalmente preenchida
    for (int i = 0; i < LED_COUNT; i++)
    {
        np_set_led(i, 0, 255, 255);
    }
    np_write();
    sleep_ms(delay_ms);

    for (int i = 0; i < LED_COUNT; i++)
    {
        np_set_led(i, 255, 0, 255);
    }
    np_write();
    sleep_ms(delay_ms);

    for (int i = 0; i < LED_COUNT; i++)
    {
        if (i == 6 || i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 16 || i == 17 || i == 18)
            np_set_led(i, 0, 255, 255);
        else
            np_set_led(i, 255, 0, 255);
    }
    np_write();
    sleep_ms(delay_ms + 1600);

    np_clear();
    np_write();
}

void draw_heart_animation()
{
    // Define os 5 padrões de animação do coração
    uint8_t heart_patterns[5][5][5] = {
        {// Frame 1 (pequeno)
         {0, 0, 1, 0, 0},
         {0, 1, 0, 1, 0},
         {1, 0, 0, 0, 1},
         {0, 1, 0, 1, 0},
         {0, 0, 1, 0, 0}},
        {// Frame 2 (maior)
         {0, 1, 1, 1, 0},
         {1, 0, 0, 0, 1},
         {1, 0, 0, 0, 1},
         {0, 1, 0, 1, 0},
         {0, 0, 1, 0, 0}},
        {// Frame 3 (cheio)
         {0, 1, 1, 1, 0},
         {1, 1, 1, 1, 1},
         {1, 1, 1, 1, 1},
         {0, 1, 1, 1, 0},
         {0, 0, 1, 0, 0}},
        {// Frame 4 (maior)
         {0, 1, 1, 1, 0},
         {1, 0, 0, 0, 1},
         {1, 0, 0, 0, 1},
         {0, 1, 0, 1, 0},
         {0, 0, 1, 0, 0}},
        {// Frame 5 (pequeno)
         {0, 0, 1, 0, 0},
         {0, 1, 0, 1, 0},
         {1, 0, 0, 0, 1},
         {0, 1, 0, 1, 0},
         {0, 0, 1, 0, 0}}};

    // Executa os 5 quadros da animação
    for (int frame = 0; frame < 5; frame++)
    {
        // Percorre cada linha e coluna do padrão atual
        for (int row = 0; row < 5; row++)
        {
            for (int col = 0; col < 5; col++)
            {
                if (heart_patterns[frame][row][col] == 1)
                {
                    // Acende o LED na cor vermelha
                    np_set_led(row * 5 + col, 255, 0, 0); // Cor vermelha
                }
                else
                {
                    // Desliga o LED
                    np_set_led(row * 5 + col, 0, 0, 0); // Cor apagada
                }
            }
        }
        np_write();    // Atualiza a matriz de LEDs
        sleep_ms(200); // Atraso entre os quadros
    }
}

void animate_subgrupo3()
{
    // Frames da animação para a palavra "SUBGRUPO3".
    uint8_t frames[11][25] = {
        // Frame 1: Todos os LEDs acesos
        {255, 255, 255, 255, 255,
         255, 255, 255, 255, 255,
         255, 255, 255, 255, 255,
         255, 255, 255, 255, 255,
         255, 255, 255, 255, 255},

        // Frame 2: Letra "S"
        {255, 255, 255, 255, 255,
         255, 0, 0, 0, 0,
         255, 255, 255, 255, 255,
         0, 0, 0, 0, 255,
         255, 255, 255, 255, 255},

        // Frame 3: Letra "U"
        {255, 0, 0, 0, 255,
         255, 0, 0, 0, 255,
         255, 0, 0, 0, 255,
         255, 0, 0, 0, 255,
         255, 255, 255, 255, 255},

        // Frame 4: Letra "B"
        {255, 255, 255, 255, 255,
         255, 0, 0, 0, 255,
         255, 255, 255, 255, 255,
         255, 0, 0, 0, 255,
         255, 255, 255, 255, 255},

        // Frame 5: Letra "G"
        {255, 255, 255, 255, 255,
         255, 0, 0, 0, 0,
         255, 0, 255, 255, 255,
         255, 0, 0, 0, 255,
         255, 255, 255, 255, 255},

        // Frame 6: Letra "R"
        {255, 255, 255, 255, 255,
         255, 0, 0, 0, 255,
         255, 255, 255, 255, 255,
         255, 0, 255, 0, 255,
         255, 0, 0, 255, 255},

        // Frame 7: Letra "U"
        {255, 0, 0, 0, 255,
         255, 0, 0, 0, 255,
         255, 0, 0, 0, 255,
         255, 0, 0, 0, 255,
         255, 255, 255, 255, 255},

        // Frame 8: Letra "P"
        {255, 255, 255, 255, 255,
         255, 0, 0, 0, 255,
         255, 255, 255, 255, 255,
         255, 0, 0, 0, 0,
         255, 0, 0, 0, 0},

        // Frame 9: Letra "O"
        {255, 255, 255, 255, 255,
         255, 0, 0, 0, 255,
         255, 0, 0, 0, 255,
         255, 0, 0, 0, 255,
         255, 255, 255, 255, 255},

        // Frame 10: Número "3"
        {255, 255, 255, 255, 255,
         0, 0, 0, 0, 255,
         255, 255, 255, 255, 255,
         0, 0, 0, 0, 255,
         255, 255, 255, 255, 255},

        // Frame 11: Todos os LEDs apagados
        {0, 0, 0, 0, 0,
         0, 0, 0, 0, 0,
         0, 0, 0, 0, 0,
         0, 0, 0, 0, 0,
         0, 0, 0, 0, 0}};

    for (int frame = 0; frame < 11; frame++)
    {
        // Atualiza os LEDs conforme o frame atual.
        for (int i = 0; i < LED_COUNT; i++)
        {
            np_set_led(i, frames[frame][i], 0, 0); // Vermelho
        }

        np_write();    // Atualiza a matriz de LEDs.
        sleep_ms(500); // Pausa de 500ms entre os frames.
    }
}

void draw_arrow_animation()
{
    uint8_t frames[5][5][5] = {
        {// Frame 1: Base da seta
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0},
         {0, 1, 1, 1, 0}},
        {// Frame 2: Preenche a haste
         {0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0},
         {0, 1, 1, 1, 0},
         {1, 1, 1, 1, 1}},
        {// Frame 3: Preenche a ponta
         {0, 0, 1, 0, 0},
         {0, 1, 1, 1, 0},
         {1, 1, 1, 1, 1},
         {0, 1, 1, 1, 0},
         {0, 0, 1, 0, 0}},
        {// Frame 4: Seta completa
         {0, 0, 1, 0, 0},
         {0, 1, 1, 1, 0},
         {1, 1, 1, 1, 1},
         {0, 1, 1, 1, 0},
         {0, 0, 1, 0, 0}},
        {// Frame 5: Pisca a ponta
         {0, 0, 1, 0, 0},
         {0, 0, 1, 0, 0},
         {1, 1, 1, 1, 1},
         {0, 1, 1, 1, 0},
         {0, 0, 1, 0, 0}}};
    for (int frame = 0; frame < 5; frame++)
    {
        for (int row = 0; row < 5; row++)
        {
            for (int col = 0; col < 5; col++)
            {
                if (frames[frame][row][col] == 1)
                {
                    np_set_led(row * 5 + col, 0, 255, 0); // Verde
                }
                else
                {
                    np_set_led(row * 5 + col, 0, 0, 0); // Apaga
                }
            }
        }
        np_write();
        sleep_ms(100); // 10 FPS
    }
}
void handle_key_b()
{
    printf("Tecla B pressionada: iluminando LEDs em azul.\n");

    // Acender todos os LEDs em azul com intensidade máxima.
    for (int i = 0; i < LED_COUNT; i++)
    {
        np_set_led(i, 0, 0, 255); // Azul.
    }

    np_write();    // Atualiza a matriz de LEDs.
    sleep_ms(500); // Mantém a iluminação por 500ms.
}