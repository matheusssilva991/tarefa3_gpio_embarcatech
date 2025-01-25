# Matriz de LED 5x5 com Teclado Matricial - Projeto Embarcatech

Este projeto implementa um sistema de controle para uma matriz de LED 5x5 RGB utilizando um teclado matricial, desenvolvido como parte do projeto Embarcatech.

## 🎯 Funcionalidades

### Animações (Teclas 0-9)
- Cada tecla numérica (0-9) aciona uma animação diferente na matriz de LED
- Cada animação possui no mínimo 5 frames
- Animações customizadas com diferentes cores RGB e níveis de luminosidade

### Controles Especiais
- **Tecla A**: Desliga todos os LEDs
- **Tecla B**: Aciona todos os LEDs em azul (100% luminosidade)
- **Tecla C**: Aciona todos os LEDs em vermelho (80% luminosidade)
- **Tecla D**: Aciona todos os LEDs em verde (50% luminosidade)
- **Tecla #**: Aciona todos os LEDs em branco (20% luminosidade)
- **Tecla ***: Habilita modo de gravação (reboot) [Opcional]

### Recursos Adicionais
- Sinal sonoro via buzzer para animações específicas [Opcional]

## 🛠️ Tecnologias Utilizadas

- Linguagem C
- Pico SDK
- VS Code
- Simulador Wokwi

## 📋 Pré-requisitos

- VS Code instalado
- Pico SDK configurado
- Simulador Wokwi integrado ao VS Code
- Git instalado

## 🎯 Distribuição das Tarefas

1. **Tiago Alcantara**
   - Animação na matriz de LED (Número 0)
   - Implementação da tecla A (Desligar todos os LEDs)

2. **Suiani Almeida**
   - Animação na matriz de LED (Número 1)
   - Implementação da tecla B (LEDs azuis - 100% luminosidade)
   - Criação do Readme

3. **Matheus Silva**
   - Animação na matriz de LED (Número 2)
   - Implementação da tecla C (LEDs vermelhos - 80% luminosidade)

4. **Davi Aguiar**
   - Animação na matriz de LED (Número 3)
   - Implementação da tecla D (LEDs verdes - 50% luminosidade)
   - Gravação de vídeo demonstrativo

5. **Ailton Gabriel**
   - Animação na matriz de LED (Número 4)
   - Implementação da tecla # (LEDs brancos - 20% luminosidade)
   - Configuração do arquivo diagram.json

6. **Pedro Sena**
   - Animação na matriz de LED (Número 5)
   - Implementação da tecla D (LEDs verdes - 50% luminosidade)

7. **Keylla Kaylla**
   - Animação na matriz de LED (Número 6)
   - Implementação do buzzer em uma das animações

## ✅ Testes

- Implementados testes básicos para cada funcionalidade
- Verificação de funcionamento das animações
- Teste de resposta do teclado
- Validação dos níveis de luminosidade

## 🚀 Como Executar

1. Clone o repositório:
```bash
git clone [https://github.com/matheusssilva991/tarefa3_gpio_embarcatech.git]
```

2. Configure o ambiente de desenvolvimento seguindo as instruções do Pico SDK

3. Abra o projeto no VS Code

4. Execute a simulação através do Wokwi

## 🤝 Equipe

Membros da equipe de desenvolvimento do projeto:
<table>
  <tr>
    <td align="center">
      <a href="https://github.com/matheusssilva991">
        <img src="https://github.com/matheusssilva991.png" width="100px;" alt="Foto de Matheus Santos Silva no GitHub"/><br>
        <b>Matheus Santos Silva (matheusssilva991)</b>
        <p>Desenvolvedor Back-end - NestJS</p>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/suianialmeida">
        <img src="https://github.com/suianialmeida.png" width="100px;" alt="Foto de Suiani Almeida no GitHub"/><br>
        <b>Suiani Almeida</b>
        <p>Desenvolvedora em Sistemas Embarcados e IoT</p>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/davi-aguiar">
        <img src="https://github.com/davi-aguiar.png" width="100px;" alt="Foto do Davi no GitHub"/><br>
        <b>Davi Aguiar</b>
        <p>ML/AI Developer</p>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/KeyllaK">
        <img src="https://github.com/KeyllaK.png" width="100px;" alt="Foto de Keylla Kaylla no GitHub"/><br>
        <b>Keylla Kaylla Silva de Oliveira</b>
        <p>ML/AI Developer</p>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/AiltonGabriel70">
        <img src="https://github.com/AiltonGabriel70.png" width="100px;" alt="Foto de Ailton Gabriel no GitHub"/><br>
        <b>Ailton Gabriel</b>
      </a>
    </td>
     <td align="center">
      <a href="https://github.com/AlcantaracomT">
        <img src="https://github.com/AlcantaracomT.png" width="100px;" alt="Foto de Tiago Alcantara no GitHub"/><br>
        <b>Tiago Alcantara</b>
         <p>Developer</p>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/PedroLSena">
        <img src="https://github.com/PedroLSena.png" width="100px;" alt="Foto de Pedro Sena no GitHub"/><br>
        <b>Pedro Sena</b>
      </a>
    </td>
  <tr>
</table>

## 📝 Licença

Este projeto está licenciado sob a Licença MIT - veja para mais detalhes.

MIT License

Copyright (c) 2024 Embarcatech Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---
Desenvolvido como parte do projeto Embarcatech 2024
