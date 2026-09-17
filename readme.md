# Carrinho Robô 4WD com ESP32

Victoria Franceschini Pizza rm550609

## 1. Sobre o projeto

Este repositório documenta o processo de desenvolvimento de um **carrinho robótico 4WD controlado por comunicação sem fio**, utilizando microcontroladores ESP32, quatro motores DC, duas pontes H e sensor ultrassônico.

O projeto foi desenvolvido de forma incremental, passando por diferentes versões de montagem mecânica, eletrônica e programação até chegar à versão final.

Mais do que apresentar apenas o resultado final, este repositório registra a **evolução do projeto**, incluindo requisitos, planejamento, decisões tomadas, testes, dificuldades encontradas, alterações no circuito, desenvolvimento da carenagem e melhorias realizadas ao longo do processo.


---

# 3. Objetivo

O objetivo do projeto foi desenvolver um veículo robótico capaz de:

* movimentar-se para frente;
* movimentar-se para trás;
* virar para esquerda;
* virar para direita;
* parar remotamente;
* receber comandos através de comunicação sem fio;
* detectar objetos e obstáculos utilizando sensor ultrassônico;
* controlar quatro motores DC;
* possuir estrutura mecânica estável;
* utilizar alimentação independente adequada aos componentes;
* integrar hardware, software e estrutura mecânica em um único protótipo funcional.

O projeto também teve como objetivo aplicar conceitos trabalhados durante as aulas, principalmente:

* sistemas embarcados;
* eletrônica;
* motores DC;
* ponte H;
* sensores;
* ESP32;
* comunicação sem fio;
* prototipagem;
* fabricação;
* programação;
* testes;
* documentação técnica.

---

# 4. Resultado final

A versão final consiste em um carrinho robótico com **tração 4WD**, equipado com quatro motores DC, duas pontes H, dois ESP32 e sensor ultrassônico.

Um dos principais focos do projeto foi permitir que os motores fossem controlados eletronicamente e que o carrinho pudesse receber comandos sem a necessidade de conexão física com um computador.

O sensor ultrassônico foi adicionado para permitir a medição da distância de objetos posicionados à frente do veículo.

A estrutura recebeu ainda o desenvolvimento de uma **carenagem própria no formato de camionete**, projetada para se adaptar ao chassi utilizado.

### Evidências

As fotografias e vídeos do projeto serão entregues juntamente com a apresentação/evidências finais da atividade.

As evidências incluem:

* carrinho finalizado;
* montagem eletrônica;
* funcionamento dos motores;
* controle remoto;
* funcionamento do sensor ultrassônico;
* testes de movimentação;
* carenagem;
* demonstração completa do projeto.

---

# 5. Principais funcionalidades

O protótipo final possui as seguintes funcionalidades:

### Controle de movimentação

O sistema permite executar os movimentos:

* frente;
* ré;
* esquerda;
* direita;
* parada.

### Controle dos quatro motores

Os quatro motores DC são controlados através de duas pontes H.

As pontes H permitem controlar:

* sentido de rotação;
* acionamento dos motores;
* parada;
* combinação dos motores para realização das curvas.

### Comunicação sem fio

O ESP32 permite realizar a comunicação sem fio necessária para o controle do carrinho.

Isso evita a necessidade de manter o veículo conectado fisicamente a um computador durante sua utilização.

### Detecção de obstáculos

O sensor ultrassônico realiza medições de distância na parte frontal do veículo.

Essas informações podem ser utilizadas pelo sistema para detectar obstáculos próximos e auxiliar na prevenção de colisões.

---

# 6. Componentes utilizados

| Componente          | Quantidade | Função                                        |
| ------------------- | ---------: | --------------------------------------------- |
| ESP32               |          2 | Processamento, controle e comunicação         |
| Ponte H             |          2 | Controle dos motores DC                       |
| Motores DC          |          4 | Movimentação do veículo                       |
| Placa Shield        |          1 | Organização e conexão do circuito             |
| Mini protoboard     |          2 | Distribuição e montagem das conexões          |
| Sensor ultrassônico |          1 | Medição de distância e detecção de obstáculos |
| Pilhas              |         12 | Alimentação elétrica                          |
| Fios/Jumper         |   Diversos | Conexões entre os componentes                 |
| Chassi 4WD          |          1 | Estrutura principal do veículo                |

Além desses componentes, foram utilizados elementos de fixação e materiais para desenvolvimento e adaptação da carenagem.

---

# 7. Arquitetura do sistema

O funcionamento geral pode ser representado da seguinte forma:

```text
                 CONTROLE
                    │
                    │ Comunicação sem fio
                    ▼
                 ESP32
                    │
          ┌─────────┴─────────┐
          │                   │
          ▼                   ▼
      Ponte H 1           Ponte H 2
       │     │             │     │
       ▼     ▼             ▼     ▼
     Motor  Motor        Motor  Motor
       1      2            3      4


          Sensor Ultrassônico
                  │
                  ▼
                ESP32
                  │
                  ▼
         Medição de distância
```

---

# 8. Organização da alimentação

Um dos pontos importantes do desenvolvimento foi a alimentação elétrica.

O projeto utiliza **12 pilhas** para fornecer energia aos componentes e principalmente aos motores, que possuem uma demanda de corrente superior à dos circuitos de controle.

Durante o projeto, foi importante separar conceitualmente dois tipos de carga:

```text
Sistema de controle
ESP32 + sensor + comunicação

Sistema de potência
Pontes H + motores DC
```

As duas pontes H recebem os comandos do ESP32 e realizam o acionamento dos quatro motores.

---

# 9. Projeto mecânico

## Chassi

Foi utilizado um **chassi comercial 4WD** como estrutura mecânica inicial.

O chassi já fornece suporte para os quatro motores e rodas, mas precisou receber adaptações para instalação de:

* ESP32;
* pontes H;
* protoboards;
* shield;
* sensor;
* sistema de alimentação;
* fios;
* carenagem.

O desenvolvimento mecânico não se limitou ao chassi comercial.

Foi realizada também a criação de uma carenagem própria para o veículo.

---

# 10. Carenagem

Foi desenvolvido um modelo de carenagem inspirado em uma **camionete**.

As dimensões utilizadas como referência durante o desenvolvimento foram aproximadamente:

* **comprimento:** 25 cm;
* **largura:** 14,5 cm;
* **altura mínima:** 4,5 cm.

A carenagem precisava considerar espaço para:

* quatro rodas;
* motores;
* portas;
* parte frontal;
* vidro dianteiro;
* vidro traseiro;
* retrovisores;
* eletrônica interna;
* sensor ultrassônico.

---

# 11. Evolução da carenagem

A carenagem também passou por diferentes versões.

## Versão inicial

A primeira proposta foi criada considerando apenas as dimensões gerais do chassi.

Foi definido o formato de camionete e a posição aproximada das rodas.

### Problema identificado

Durante a análise do primeiro modelo foi percebido que **os vidros da carenagem estavam posicionados/incorretos em relação ao formato esperado**.

Isso prejudicava visualmente o modelo e também a proporção da estrutura.

### Solução

O modelo foi redesenhado.

Foram alteradas principalmente:

* posição dos vidros;
* proporção lateral;
* região traseira;
* estrutura da cabine;
* encaixe visual da carenagem.

Essa alteração originou uma nova versão do molde.

---

# 12. Processo de desenvolvimento

O projeto não foi construído diretamente em sua configuração final.

Foram realizadas várias etapas até chegar à versão atual.

---

## Versão 0.1 — Ideia inicial

A primeira etapa foi definir o objetivo do projeto.

Foi decidido desenvolver um carrinho:

* com quatro rodas;
* quatro motores;
* controle eletrônico;
* comunicação sem fio;
* ESP32;
* capacidade de detectar obstáculos.

Nesta etapa ainda não existia uma montagem definitiva.

---

## Versão 0.2 — Chassi 4WD

Foi escolhido um chassi comercial 4WD.

A escolha permitiu utilizar:

* quatro motores DC;
* quatro rodas;
* melhor distribuição mecânica;
* possibilidade de realizar curvas controlando os motores dos dois lados.

Nesta etapa foi realizada a montagem inicial da estrutura mecânica.

---

## Versão 0.3 — Controle dos motores

Na etapa seguinte foram integradas as **duas pontes H**.

Como existem quatro motores, tornou-se necessário organizar o controle dos motores de cada lado do veículo.

A lógica passou a considerar:

```text
Lado esquerdo
Motor dianteiro esquerdo
Motor traseiro esquerdo

Lado direito
Motor dianteiro direito
Motor traseiro direito
```

Assim, diferentes combinações de rotação passaram a produzir os movimentos do veículo.

---

## Versão 0.4 — ESP32 e comunicação

O ESP32 foi integrado ao circuito para executar a lógica do carrinho.

Nesta etapa foram implementados os comandos básicos:

```text
FRENTE
TRÁS
ESQUERDA
DIREITA
PARAR
```

A comunicação sem fio permitiu controlar o veículo à distância.

O projeto passou a utilizar **dois ESP32** dentro da arquitetura desenvolvida.

---

## Versão 0.5 — Organização eletrônica

Com o aumento do número de componentes, a montagem começou a exigir uma organização melhor.

Foram adicionados/utilizados:

* duas mini protoboards;
* placa shield;
* fios;
* duas pontes H;
* alimentação;
* ESP32.

Essa etapa foi importante para reduzir conexões improvisadas e facilitar a identificação dos componentes.

---

## Versão 0.6 — Sensor ultrassônico

O sensor ultrassônico foi adicionado à parte frontal.

Sua função passou a ser medir a distância entre o carrinho e objetos posicionados à sua frente.

O funcionamento consiste basicamente em:

1. emitir um pulso ultrassônico;
2. aguardar o retorno do sinal;
3. medir o tempo;
4. calcular a distância;
5. disponibilizar a informação ao sistema.

Essa versão adicionou percepção do ambiente ao projeto.

---

## Versão 0.7 — Revisão da alimentação

Com motores, ESP32, pontes H e sensor funcionando no mesmo projeto, a alimentação passou a ser uma parte importante do desenvolvimento.

A configuração final passou a contar com **12 pilhas**, permitindo fornecer energia ao conjunto de componentes e principalmente aos motores.

Nesta etapa também foram revisadas as conexões elétricas para melhorar a estabilidade da montagem.

---

## Versão 0.8 — Desenvolvimento da carenagem

Com o sistema eletrônico e mecânico definido, começou o desenvolvimento da aparência externa.

Foi elaborado um molde de camionete compatível com aproximadamente:

```text
25 cm x 14,5 cm x 4,5 cm ou mais
```

A primeira versão apresentou problemas principalmente na região dos vidros.

O desenho foi revisado e uma nova versão foi criada.

---

## Versão 0.9 — Integração

Nesta etapa todos os subsistemas passaram a funcionar como um único projeto:

* estrutura;
* motores;
* pontes H;
* ESP32;
* comunicação;
* sensor;
* alimentação;
* carenagem.

Também foram realizados testes de funcionamento conjunto.

---

## Versão 1.0 — Carrinho final

A versão 1.0 representa o protótipo utilizado na apresentação final.

Principais características:

* 4 motores DC;
* tração 4WD;
* 2 pontes H;
* 2 ESP32;
* sensor ultrassônico;
* comunicação sem fio;
* 12 pilhas;
* controle remoto;
* estrutura personalizada;
* carenagem;
* movimentação multidirecional.

---

# 13. Backlog do projeto

Durante o desenvolvimento, as tarefas foram organizadas aproximadamente na seguinte sequência:

| Prioridade | Tarefa                          | Status    |
| ---------- | ------------------------------- | --------- |
| Alta       | Montar chassi                   | Concluído |
| Alta       | Instalar quatro motores         | Concluído |
| Alta       | Integrar pontes H               | Concluído |
| Alta       | Integrar ESP32                  | Concluído |
| Alta       | Programar movimentação          | Concluído |
| Alta       | Testar direção dos motores      | Concluído |
| Alta       | Implementar comunicação sem fio | Concluído |
| Alta       | Integrar sensor ultrassônico    | Concluído |
| Alta       | Testar detecção de obstáculos   | Concluído |
| Média      | Organizar alimentação           | Concluído |
| Média      | Organizar fios                  | Concluído |
| Média      | Instalar protoboards e shield   | Concluído |
| Média      | Desenvolver carenagem           | Concluído |
| Média      | Corrigir carenagem              | Concluído |
| Alta       | Testes finais                   | Concluído |
| Alta       | Documentação                    | Concluído |

---

# 14. Decisões de projeto

## Uso de ESP32

O ESP32 foi escolhido por combinar:

* processamento;
* grande quantidade de GPIOs;
* comunicação sem fio;
* facilidade de programação;
* possibilidade de expansão futura.

---

## Uso de quatro motores

O uso de quatro motores permite maior capacidade de movimentação e melhor distribuição de força.

Além disso, controlar independentemente os motores dos lados esquerdo e direito permite realizar curvas sem a necessidade de um sistema mecânico tradicional de direção.

---

## Uso de duas pontes H

As pontes H permitem inverter a polaridade aplicada aos motores.

Com isso, é possível alterar o sentido de rotação através do software.

Isso permite implementar:

```text
Frente
Ré
Curva esquerda
Curva direita
Parada
```

---

## Uso do sensor ultrassônico

O sensor foi escolhido por permitir detectar objetos sem contato físico.

Isso adicionou ao projeto uma forma simples de percepção do ambiente.

---

## Uso de chassi comercial

Foi decidido utilizar um chassi 4WD comercial para acelerar o desenvolvimento da parte estrutural.

Porém, foram necessárias adaptações para acomodar toda a eletrônica e a carenagem desenvolvida durante o projeto.

---

# 15. Funcionamento do software

O software pode ser dividido em três partes principais.

## 1. Recebimento dos comandos

O ESP32 recebe o comando enviado pelo sistema de controle.

Exemplos:

```text
Frente
Trás
Esquerda
Direita
Stop
```

---

## 2. Controle dos motores

Depois de identificar o comando, o ESP32 altera os sinais enviados às pontes H.

Exemplo conceitual:

### Frente

```text
Motores esquerdos -> frente
Motores direitos  -> frente
```

### Ré

```text
Motores esquerdos -> trás
Motores direitos  -> trás
```

### Esquerda

```text
Lado esquerdo -> reduz/paralisa/inverte
Lado direito  -> frente
```

### Direita

```text
Lado esquerdo -> frente
Lado direito  -> reduz/paralisa/inverte
```

### Parada

```text
Todos os motores -> desligados
```

---

# 16. Leitura do sensor

Durante a execução do programa, o ESP32 também realiza leituras do sensor ultrassônico.

Fluxo simplificado:

```text
Enviar pulso
     ↓
Sensor ultrassônico
     ↓
Receber eco
     ↓
Calcular tempo
     ↓
Converter em distância
     ↓
Analisar obstáculo
```

A leitura pode ser utilizada para identificar a proximidade de objetos e evitar que o carrinho continue avançando diretamente contra um obstáculo.

---

# 17. Testes realizados

Durante o desenvolvimento foram realizados testes separados antes da validação completa do veículo.

Essa estratégia foi importante porque permitiu identificar problemas em cada subsistema antes de testar tudo simultaneamente.

---

## Teste 01 — Funcionamento individual dos motores

### Objetivo

Verificar se cada um dos quatro motores estava funcionando corretamente.

### Procedimento

Cada motor foi acionado individualmente através do sistema de controle.

### Resultado esperado

Todos deveriam girar.

### Resultado

Os quatro motores responderam aos comandos.

### Importância

Esse teste permitiu separar problemas mecânicos de problemas relacionados ao controle eletrônico.

**Status:** APROVADO.

---

# 18. Teste 02 — Sentido de rotação

### Objetivo

Verificar se todos os motores estavam girando no sentido correto quando o comando de avanço era enviado.

### Problema encontrado

Durante os ajustes iniciais, a orientação/polaridade dos motores precisava ser conferida, pois motores instalados em lados opostos fisicamente não podem ser tratados exatamente da mesma forma.

Caso contrário, um lado poderia tentar andar para frente enquanto o outro girava em sentido contrário.

### Correção

A lógica e as conexões de direção foram organizadas considerando:

```text
Motores do lado esquerdo
Motores do lado direito
```

### Resultado

Após o ajuste, os quatro motores passaram a trabalhar de maneira compatível com o movimento desejado.

**Status:** APROVADO.

---

# 19. Teste 03 — Movimentação para frente e para trás

### Objetivo

Testar o funcionamento conjunto dos quatro motores.

### Procedimento

Foram enviados comandos consecutivos de:

```text
Frente
Parar
Ré
Parar
```

### Resultado

O carrinho conseguiu realizar os movimentos básicos utilizando os quatro motores.

**Status:** APROVADO.

---

# 20. Teste 04 — Curvas

### Objetivo

Verificar se era possível controlar separadamente os dois lados do veículo.

### Procedimento

Foram realizados comandos de:

* esquerda;
* direita;
* parada.

### Problema observado

As curvas exigiram ajuste na forma como cada conjunto de motores era acionado.

Como o sistema não utiliza direção mecânica tradicional, a mudança de direção depende diretamente da diferença entre o movimento das rodas de cada lado.

### Correção

A programação foi organizada separando os motores em lado esquerdo e lado direito.

### Resultado

O carrinho passou a executar curvas para os dois lados.

**Status:** APROVADO.

---

# 21. Teste 05 — Comunicação sem fio

### Objetivo

Verificar se o carrinho continuaria respondendo aos comandos sem conexão física com o computador.

### Procedimento

O sistema de comunicação foi conectado e diferentes comandos foram transmitidos ao ESP32.

Foram utilizados comandos de movimentação e parada.

### Resultado

Os comandos foram recebidos e convertidos em ações dos motores.

### Validação

O carrinho pôde ser controlado remotamente.

**Status:** APROVADO.

---

# 22. Teste 06 — Sensor ultrassônico

### Objetivo

Validar se o sensor conseguia identificar objetos em diferentes distâncias.

### Procedimento

Um objeto foi colocado progressivamente mais próximo do sensor.

Foram observadas as alterações das leituras.

### Problema observado

Sensores ultrassônicos podem apresentar pequenas oscilações entre leituras consecutivas, principalmente dependendo do formato e do ângulo do objeto.

### Correção

As leituras foram analisadas considerando uma distância limite em vez de depender de um único valor isolado.

### Resultado

O sistema conseguiu identificar a aproximação dos objetos.

**Status:** APROVADO.

---

# 23. Teste 07 — Alimentação completa

### Objetivo

Verificar o funcionamento do sistema com motores, sensor e comunicação operando simultaneamente.

### Procedimento

O carrinho foi ligado utilizando sua configuração final de alimentação.

Foram realizados:

* movimentos;
* curvas;
* leituras do sensor;
* comandos sem fio.

### Ponto analisado

Os motores apresentam consumo significativamente maior que o ESP32 e o sensor.

Por isso, o sistema precisava ser testado em condições reais e não apenas componente por componente.

### Resultado

A configuração com as **12 pilhas** permitiu realizar os testes integrados do veículo.

**Status:** APROVADO.

---

# 24. Teste 08 — Teste integrado

### Objetivo

Simular a utilização real do carrinho.

### Sequência executada

```text
Ligar carrinho
      ↓
Estabelecer comunicação
      ↓
Movimentar para frente
      ↓
Executar curva
      ↓
Executar outra curva
      ↓
Testar marcha ré
      ↓
Aproximar de obstáculo
      ↓
Verificar sensor
      ↓
Parar veículo
```

### Resultado

Os sistemas principais funcionaram conjuntamente.

Foram validados:

* motores;
* pontes H;
* ESP32;
* comunicação;
* sensor;
* alimentação;
* estrutura.

**Status:** APROVADO.

---

# 25. Problemas e soluções

Registrar os problemas foi uma parte importante do desenvolvimento porque o projeto passou por diferentes ajustes antes da versão final.

| Problema                       | Causa/Análise                                          | Solução                                             |
| ------------------------------ | ------------------------------------------------------ | --------------------------------------------------- |
| Organização dos quatro motores | Necessidade de controlar dois lados diferentes         | Separação lógica entre motores esquerdos e direitos |
| Sentido dos motores            | Motores instalados em posições opostas                 | Ajuste das conexões/lógica das pontes H             |
| Curvas                         | Quatro rodas sem direção mecânica                      | Controle diferente para cada lado                   |
| Organização da eletrônica      | Grande quantidade de componentes e fios                | Uso de duas mini protoboards e shield               |
| Alimentação                    | Motores exigem mais energia que circuitos lógicos      | Revisão da alimentação e utilização das 12 pilhas   |
| Leitura do sensor              | Variações entre medições                               | Uso de limite de distância e leituras sucessivas    |
| Espaço no chassi               | Grande quantidade de componentes                       | Reorganização física dos módulos                    |
| Carenagem inicial              | Vidros e proporções incorretos                         | Redesenho do molde                                  |
| Integração                     | Sistemas funcionavam separadamente antes da integração | Testes por módulos seguidos de teste completo       |

---

# 26. Metodologia de testes

Os testes foram realizados de forma incremental.

A ordem adotada foi:

```text
1. Motor individual
        ↓
2. Direção dos motores
        ↓
3. Quatro motores simultaneamente
        ↓
4. Curvas
        ↓
5. Comunicação
        ↓
6. Sensor
        ↓
7. Alimentação
        ↓
8. Sistema completo
```

Essa estratégia facilitou a localização de problemas.

Se todos os componentes fossem testados apenas no final, seria mais difícil identificar qual parte estava causando determinada falha.

---

# 27. Evolução resumida

```text
IDEIA
  ↓
REQUISITOS
  ↓
CHASSI 4WD
  ↓
4 MOTORES
  ↓
PONTES H
  ↓
ESP32
  ↓
CONTROLE DOS MOTORES
  ↓
COMUNICAÇÃO SEM FIO
  ↓
SENSOR ULTRASSÔNICO
  ↓
ALIMENTAÇÃO
  ↓
TESTES
  ↓
CARENAGEM
  ↓
CORREÇÕES
  ↓
INTEGRAÇÃO
  ↓
VERSÃO FINAL
```

---

# 28. MVP

O MVP do projeto foi definido como a primeira versão capaz de:

* utilizar o chassi;
* controlar quatro motores;
* andar para frente;
* andar para trás;
* virar;
* parar;
* receber comandos remotamente.

Após a conclusão do MVP, foram adicionados:

* sensor ultrassônico;
* melhorias na alimentação;
* organização eletrônica;
* segunda unidade ESP32;
* carenagem;
* melhorias estruturais;
* testes integrados.

---

# 30. Organização do código

O código deve permanecer dentro da pasta:

```text
/software
```

Separando, quando aplicável:

```text
/software/carrinho
/software/controle
```

Isso facilita identificar qual código pertence a cada ESP32 utilizado no projeto.

---

# 31. Instruções básicas de utilização

## Inicialização

1. Verificar as conexões.
2. Verificar a alimentação.
3. Posicionar o carrinho em superfície plana.
4. Ligar o sistema.
5. Inicializar o controle.
6. Estabelecer a comunicação com o ESP32.
7. Testar primeiro o comando de parada.
8. Iniciar os movimentos.

---

## Comandos

O controle permite executar as funções:

```text
Frente
Trás
Esquerda
Direita
Parar
```

Durante o funcionamento, o sensor ultrassônico monitora objetos posicionados à frente do carrinho.

---

# 32. Cuidados

Antes de utilizar o projeto:

* verificar se existem fios soltos;
* conferir as conexões das pontes H;
* verificar as pilhas;
* conferir o encaixe dos componentes;
* não bloquear as rodas durante o acionamento;
* verificar se o sensor ultrassônico está livre;
* iniciar os testes em baixa velocidade;
* deixar espaço ao redor do carrinho.

---

# 33. Resultado

Ao final do desenvolvimento foi possível construir um protótipo funcional reunindo diferentes áreas estudadas durante o projeto.

O carrinho integra:

* mecânica;
* eletrônica;
* sistemas embarcados;
* programação;
* comunicação;
* sensores;
* alimentação;
* fabricação;
* prototipagem.

O processo mostrou que o desenvolvimento não ocorreu em uma única etapa.

O projeto evoluiu através de:

* montagem;
* experimentação;
* testes;
* identificação de problemas;
* correções;
* novas versões;
* integração.

Essa evolução foi essencial para chegar à configuração final do veículo.

---

# 34. Histórico de versões

| Versão | Alteração                                       |
| ------ | ----------------------------------------------- |
| v0.1   | Definição da proposta e requisitos              |
| v0.2   | Montagem do chassi 4WD                          |
| v0.3   | Integração dos quatro motores e pontes H        |
| v0.4   | Integração do ESP32 e controle                  |
| v0.5   | Organização eletrônica com protoboards e shield |
| v0.6   | Integração do sensor ultrassônico               |
| v0.7   | Revisão do sistema de alimentação               |
| v0.8   | Desenvolvimento e revisão da carenagem          |
| v0.9   | Integração e testes completos                   |
| v1.0   | Versão final apresentada                        |

---

# 35. Conclusão

O desenvolvimento do carrinho mostrou na prática que um projeto de robótica precisa ser construído e validado gradualmente.

A versão final é resultado das diferentes decisões, testes e alterações realizadas durante o projeto.

O principal aprendizado não foi apenas construir um veículo que se movimenta, mas entender como diferentes subsistemas precisam trabalhar juntos:

```text
Software
   +
Eletrônica
   +
Mecânica
   +
Comunicação
   +
Sensores
   =
Sistema completo
```

Por esse motivo, este repositório preserva não somente os arquivos finais, mas também o **processo de desenvolvimento, as diferentes versões, decisões tomadas, testes, problemas encontrados e soluções aplicadas pela equipe**.
