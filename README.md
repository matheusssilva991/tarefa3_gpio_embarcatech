Controle de LEDs, Animações e Buzzer com Raspberry Pi Pico
Descrição do Projeto
Este projeto implementa um sistema interativo de controle para uma matriz de LEDs 5x5, utilizando o microcontrolador Raspberry Pi Pico. O sistema responde às entradas de um teclado matricial, exibindo diferentes animações na matriz de LEDs, controlando cores, intensidade e adicionando funcionalidades adicionais, como o uso de um buzzer e comandos específicos para reset e configuração.

Cada tecla do teclado matricial aciona uma animação ou funcionalidade específica, conforme descrito na seção de funcionamento. O projeto foi desenvolvido em equipe, com cada integrante responsável por implementar uma animação ou funcionalidade.

Funcionalidades
Animações Personalizadas:

Teclas de 0 a 9: Disparam animações únicas e configuráveis na matriz de LEDs (mínimo de 5 frames cada, com FPS ajustável).
As animações incluem controle de cor (RGB), luminosidade e fluidez.
Comandos Específicos:

Tecla A: Desliga todos os LEDs.
Tecla B: Liga todos os LEDs na cor azul com 100% de luminosidade.
Tecla C: Liga todos os LEDs na cor vermelha com 80% de luminosidade.
Tecla D: Liga todos os LEDs na cor verde com 50% de luminosidade.
Tecla #: Liga todos os LEDs na cor branca com 20% de luminosidade.
Especificações Opcionais:

Buzzer: Um som é gerado em uma das animações.
Modo de gravação: A tecla * reinicia o sistema e habilita o modo de gravação via software (reboot).
Requisitos
Software
Visual Studio Code
Pico SDK configurado
Git para versionamento
Compilador C compatível com ARM
Hardware
Raspberry Pi Pico
Matriz de LEDs 5x5
Teclado matricial
Buzzer (opcional)
Computador com Windows/Linux/MacOS
Cabos para conexão GPIO
Instalação
Clone o Repositório:

bash
Copiar
Editar
git clone https://github.com/seu-repositorio/aqui.git
Configure o Ambiente Pico SDK:

Siga a documentação oficial do Raspberry Pi Pico para configurar o SDK.
Compile o Código:

bash
Copiar
Editar
mkdir build
cd build
cmake ..
make
Como Executar o Projeto
Conecte a Raspberry Pi Pico ao computador via cabo USB.
Carregue o arquivo .uf2 gerado para a placa.
Utilize o simulador Wokwi ou um ambiente físico para testar as funcionalidades.
Pressione as teclas no teclado matricial para acionar as animações e comandos conforme descrito.
Funcionamento do Sistema
Tecla	Funcionalidade
0 a 9	Animações personalizadas na matriz de LEDs
A	Desliga todos os LEDs
B	Liga todos os LEDs na cor azul (100% de luminosidade)
C	Liga todos os LEDs na cor vermelha (80% de luminosidade)
D	Liga todos os LEDs na cor verde (50% de luminosidade)
#	Liga todos os LEDs na cor branca (20% de luminosidade)
*	Reinicia o sistema e entra no modo de gravação
Contribuição
Criação de Branch:

Cada membro da equipe deve criar um branch específico para sua tarefa.
bash
Copiar
Editar
git checkout -b feature/nova-funcionalidade
Commits e Pull Requests:

Realize commits regulares com mensagens claras e descritivas.
Abra pull requests para revisão e aprovação do código.
Equipe
Membro da Equipe	Responsabilidade
Matheus	Gerenciamento do repositório e revisão de PRs
Tiago	Animação na matriz de LED (Número 0) + tecla A
Suiane	Animação na matriz de LED (Número 1) + tecla B
Matheus	Animação na matriz de LED (Número 2) + tecla C
Davi	Animação na matriz de LED (Número 3) + tecla D
Ailton	Animação na matriz de LED (Número 4) + tecla #
Pedro	Animação na matriz de LED (Número 5) + tecla D
Keylla	Animação na matriz de LED (Número 6) + buzzer
Membro 8	Animação na matriz de LED (Número 7)
Membro 9	Animação na matriz de LED (Número 8)
