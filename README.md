<!-- markdownlint-disable MD033 -->
# Projeto final da cadeira de computação física

## Análise sentimental de plantas através de um sensor de umidade

O MVP (Minimum Viable Product) do projeto é o seguinte:

- Sensor de umidade
- Tela LCD de 16x2
- Arduino Uno
- Buzzer
- Potenciômetro

<span style="text-align: justify; -webkit-hyphens: auto; -moz-hyphens: auto; -ms-hyphens: auto; hyphens: auto;">
O projeto tem como objetivo analisar a umidade do ambiente em que o sensor está inserido, afim de lembrar o usuário de regar a espécime de planta que está sendo monitorada conforme as configurações setadas anteriormente pelo próprio usuário (volume de água necessário para a planta monitorada e intervalo de  tempo entre as regas).
</span>

### Como funciona?

<span style="text-align: justify; -webkit-hyphens: auto; -moz-hyphens: auto; -ms-hyphens: auto; hyphens: auto;">
O sensor de umidade é um sensor de umidade do tipo capacitivo, que é capaz de detectar a umidade do ambiente em que está inserido. O sensor é conectado ao Arduino Uno, que é responsável por receber as informações do sensor e enviar para o LCD, que é responsável por exibir as informações para o usuário. O buzzer é responsável por emitir um sinal sonoro quando a umidade do ambiente está abaixo do valor mínimo configurado pelo usuário ou quando o intervalo de tempo entre as regas é ultrapassado. O potenciômetro é responsável por configurar o valor mínimo de umidade do ambiente para que o buzzer emita um sinal sonoro.
</span>

### Onde está o código?

<span style="text-align: justify; -webkit-hyphens: auto; -moz-hyphens: auto; -ms-hyphens: auto; hyphens: auto;">
O código está armazenado no repositório dedicado ao projeto no <a href="https://github.com/araujosemacento/Projeto-Final-de-Computacao-Fisica">GitHub</a>. Seu modelo foi projetado através da plataforma de simulação <a href="https://www.wokwi.com">Wokwi</a> aonde foi possível testar o funcionamento do projeto e está disponível para visualização através deste <a href="https://wokwi.com/projects/421645799385602049">link</a>.
</span>
