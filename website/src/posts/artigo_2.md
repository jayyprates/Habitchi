# #2 Arquitetura do Projeto

Definimos, então, que o Habitchi é um bichinho virtual com uma regra simples: ele só cresce se você cumprir o seu hábito. Você marca o check e ele fica mais feliz se continuar. Se você desistir antes de 66 dias, ele morre. O próximo passo do grupo foi definir a arquitetura de hardware e software do Habitchi. 

**Hardware**
- **Microcontrolador:** Arduino Nano (ATmega328P), na fase de protótipo; 
- **Tela:** módulo e-Paper Waveshare de 2.66" (296×152, preto e branco). Escolhemos e-ink de propósito. Ela mantém a imagem sem consumir energia, e o bichinho fica parado na tela o dia inteiro. Só gastamos energia quando algo muda;
- **Entrada:** três botões (cima, baixo e ok) para navegar entre os hábitos e confirmar que você cumpriu o dia;
- **Chave de alimentação da tela:** um MOSFET controlado por um pino do Arduino liga a tela só durante a atualização e a desliga em seguida. Sem essa chave, a placa da tela continuaria consumindo energia parada;
- **Montagem:** protoboard e jumpers por enquanto. O objetivo final é um chaveiro.

**Software (C++)**

Dividimos o código em módulos pequenos, cada um com uma responsabilidade:
- **Entrada:** lê os três botões e trata o debounce (para um aperto contar uma vez só);
- **Lógica do bichinho:** guarda a felicidade, o crescimento e o estado (vivo/morto) de cada hábito. As regras: +1 de felicidade por dia cumprido; −1 e sem crescer por dia perdido; o bichinho morre depois de 10 dias seguidos sem cumprir ou se você desistir do hábito antes dos 66 dias;
- **Armazenamento:** o estado fica salvo na memória não volátil (EEPROM), para não se perder quando a energia acaba;
- **Tela:** liga a alimentação, inicializa a e-ink, desenha, atualiza, coloca a tela para dormir e corta a energia;
- **Menu:** uma máquina de estados simples: tela principal → escolher hábito (↑/↓) → confirmar (ok).

Os 66 dias vêm da pesquisa sobre quanto tempo um hábito leva para se consolidar, e a ideia de o bichinho “morrer” transforma isso em algo que dá vontade de manter vivo. A e-ink e o MOSFET existem pelo mesmo motivo: gastar o mínimo de energia possível, para a versão chaveiro durar na bateria.

