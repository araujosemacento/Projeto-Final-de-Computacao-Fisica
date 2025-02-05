# Projeto Final de Computação Física

## Monitor de Umidade do Solo com Interface Emocional

Este projeto implementa um sistema interativo para monitoramento de umidade do solo usando Arduino, fornecendo feedback através de uma interface emocional divertida.

### Componentes

- Arduino Uno
- Sensor de umidade do solo capacitivo
- Display LCD I2C 16x2
- LED RGB
- Buzzer
- Potenciômetro

### Funcionalidades

- **Calibração Interativa**: Permite definir o nível ideal de umidade para sua planta
- **Monitoramento Contínuo**: Verifica a umidade do solo a cada hora
- **Feedback Emocional**:
  - LED Verde + Mensagem Feliz: Umidade ideal
  - LED Azul + Alerta: Muito úmido
  - LED Vermelho + Alerta: Muito seco
- **Alarmes Sonoros**: Diferentes tons indicam diferentes estados

### Instalação

1. Clone este repositório
2. Instale as bibliotecas necessárias listadas em [`libraries.txt`](libraries.txt)
3. Carregue o código [`Projeto-Final-de-Computacao-Fisica.ino`](Projeto-Final-de-Computacao-Fisica.ino) no Arduino

### Simulação

O projeto pode ser simulado usando o [Wokwi](https://wokwi.com) no diretório do [Projeto Final](https://wokwi.com/projects/421645799385602049). O arquivo [`diagram.json`](diagram.json) contém a configuração completa do circuito.

### Estrutura do Projeto

```plaintext
├── chip/                                      # Implementação do sensor
│   ├── sensor.chip.c                          # Lógica do sensor
│   └── sensor.chip.json                       # Configuração do sensor
├── Projeto-Final-de-Computacao-Fisica.ino     # Código principal
├── diagram.json                               # Diagrama do circuito
├── libraries.txt                              # Lista de dependências
└── wokwi.toml                                 # Configuração do simulador
```

### Licença

Este projeto está licenciado sob a [GNU General Public License v3.0](LICENSE).
