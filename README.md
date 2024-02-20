## Práticas e estudos com AHP

- Analisando métodos: analisei cada método utilizado para obter os valores do autovetor

- Cálculo dos índices de concistência

### Construção de hierarquia

Decompor o problema de decisão em critérios e subcritérios, para o objetivo inicial separamos os critérios  que serão relacionados a cada alternativa e dentro destes podemos apresentar mais camadas de subcritérios.

<img src="/assets/img/AHP-Example_clip_image002.jpg" alt="Exemplo1AHP" style="height: 182px; width:485px;"/>

As alternativas terão uma matriz de comparação relativa a cada critério/subcritério e estes por sua vez terão uma matriz de comparação entre si relativas ao objetovivo principal ( no caso do subcritérios teram uma matriz de comparação entre si relativos a um critério )

```mermaid
flowchart TD
    A{Objetivo} --> B[Critério 1]
    A --> G[Critério 2]
    A --> H[Critério 3]
    H --> I[Subcritério 1]
    H --> J[Subcritério 2]
    B --> C{Alternativas}
    G --> C
    I --> C
    J --> C
    C -->|One| D[Alternativa A]
    C -->|Two| E[Alternativa B]
    C -->|Three| F[Alternativa C]
```