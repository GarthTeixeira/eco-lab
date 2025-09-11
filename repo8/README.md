## Práticas e estudos com AHP

- Analisando métodos: analisei cada método utilizado para obter os valores do autovetor

- Cálculo dos índices de concistência

### Construção de hierarquia

Decompor o problema de decisão em critérios e subcritérios, para o objetivo inicial separamos os critérios  que serão relacionados a cada alternativa e dentro destes podemos apresentar mais camadas de subcritérios.

<img src="/assets/img/AHP-Example_clip_image002.jpg" alt="Exemplo1AHP" style="height: 182px; width:485px;"/>

As alternativas terão uma matriz de comparação relativa a cada critério/subcritério e estes por sua vez terão uma matriz de comparação entre si relativas ao objetovivo principal ( no caso do subcritérios teram uma matriz de comparação entre si relativos a um critério )

```mermaid
flowchart TD
    A{Objetivo} ---|"Matriz \n Criterio x Objetivo"| B[Critério 1]
    A ---|"Matriz \n Criterio x Objetivo"| G[Critério 2]
    A ---|"Matriz \n Criterio x Objetivo"| H[Critério 3]
    H ---|"Matriz \n Subcriterio x Criterio"| I[Subcritério 1]
    H ---|"Matriz \n Subcriterio x Criterio"| J[Subcritério 2]
    B ---|"Matriz \n Criterio x Alternativas"| C{Alternativas}
    G ---|"Matriz \n Criterio x Alternativas"|K{Alternativas}
    I ---|"Matriz \n Criterio x Alternativas"| L{Alternativas}
    J ---|"Matriz \n Criterio x Alternativas"| M{Alternativas}
    C ---D[Alternativa A]
    C ---E[Alternativa B]
    C ---F[Alternativa C]
    K ---N[Alternativa A]
    K ---O[Alternativa B]
    K ---P[Alternativa C]
    L ---Q[Alternativa A]
    L ---R[Alternativa B]
    L ---S[Alternativa C]
    M ---T[Alternativa A]
    M ---U[Alternativa B]
    M ---V[Alternativa C]
```