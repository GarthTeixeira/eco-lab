from AHP import AHP;



exemple = AHP(
    metodo = 'aproximado',
    precisao = 3,
    alternativas = ['A', 'B', 'C'],
    criterios = ['C1', 'C2', 'C3'],
    subCriterios = {},
    mateizesPreferencias = {
        'C1': [
            [1, 6, 3],
            [1/6, 1, 1/6],
            [1/3, 6, 1]
        ],
        'C2': [
            [1, 1/3, 1/5],
            [3, 1, 1/3],
            [5, 3, 1]
        ],
        'C3': [
            [1, 1, 3],
            [1, 1, 3],
            [1/3, 1/3, 1]
        ]
    }
)