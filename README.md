# Controle de Servomotor usando PWM - Raspberry Pi Pico W

Este projeto implementa um sistema de controle de servomotor utilizando modulação PWM (Pulse Width Modulation) no microcontrolador Raspberry Pi Pico W. O sistema permite o controle preciso do ângulo do servomotor através de diferentes ciclos de trabalho PWM.

# Segue o vídeo de demonstração

https://youtu.be/oItIjFv0gb0

## Características

- Controle de servomotor usando PWM na GPIO 22
- Demonstração com LED RGB na GPIO 12
- Frequência PWM de 50Hz (período de 20ms)
- Movimento suave entre ângulos
- Simulação no ambiente Wokwi

## Requisitos de Hardware

- Raspberry Pi Pico W
- Servomotor (motor micro servo padrão)
- LED RGB (GPIO 12)
- Ambiente de simulação Wokwi ou hardware físico equivalente

## Configuração do PWM

- **Frequência**: 50Hz
- **Período**: 20ms
- **Posições do Servo**:
  - 180 graus: 2400µs (ciclo de trabalho 0,12%)
  - 90 graus: 1470µs (ciclo de trabalho 0,0735%)
  - 0 graus: 500µs (ciclo de trabalho 0,025%)

## Funcionalidades

1. **Posicionamento Fixo**
   - Movimento para 180 graus (2400µs)
   - Movimento para 90 graus (1470µs)
   - Movimento para 0 graus (500µs)

2. **Movimento Suave**
   - Varredura automática entre 0 e 180 graus
   - Incrementos de 5µs
   - Atraso de 10ms entre ajustes

3. **Demonstração Visual**
   - LED RGB sincronizado com o movimento do servo
   - Variação de intensidade proporcional ao ciclo de trabalho

## Como Usar

1. **Configuração do Ambiente**
   ```
   - Clone este repositório
   - Abra o projeto no ambiente Wokwi ou configure o hardware físico
   - Conecte o servomotor à GPIO 22
   - Conecte o LED RGB à GPIO 12
   ```

2. **Compilação e Upload**
   ```
   - Use o Pico SDK para compilar o projeto
   - Faça o upload do binário para o Raspberry Pi Pico W
   ```

3. **Observação do Funcionamento**
   - O servo realizará uma sequência de movimentos predefinidos
   - O LED RGB mostrará a variação do ciclo PWM
   - Observe o movimento suave entre os ângulos

## Estrutura do Código

- `pwm_setup()`: Configura os parâmetros do PWM
- `us_to_pwm()`: Converte microssegundos em valores PWM
- `move_servo_smooth()`: Implementa movimento suave entre ângulos
- Loop principal: Executa a sequência de movimentos

## Experimento com BitDogLab

O LED RGB na GPIO 12 permite visualizar o comportamento do PWM através da variação de intensidade luminosa:
- Maior brilho em 180 graus (2400µs)
- Brilho médio em 90 graus (1470µs)
- Menor brilho em 0 graus (500µs)
