from AHP import AHP;
from matplotlib import pyplot as plt

exemplo = AHP(
    method='geometrico',
    precisao=3,
    alternativas=['Tom', 'Dick', 'Harry'],
    criterios=['Experiência', 'Educação', 'Carisma', 'Idade'],
    subCriterios={},
    matrizesPreferencias={
        'Experiência': [
            [1, 1 / 4, 4],
            [4, 1, 9],
            [1 / 4, 1 / 9, 1]
        ],
        'Educação': [
            [1, 3, 1 / 5],
            [1 / 3, 1, 1 / 7],
            [5, 7, 1]
        ],
        'Carisma': [
            [1, 5, 9],
            [1 / 5, 1, 4],
            [1 / 9, 1 / 4, 1]
        ],
        'Idade': [
            [1, 1 / 3, 5],
            [3, 1, 9],
            [1 / 5, 1 / 9, 1]
        ],
        'criterios': [
            [1, 4, 3, 7],
            [1 / 4, 1, 1 / 3, 3],
            [1 / 3, 3, 1, 5],
            [1 / 7, 1 / 3, 1 / 5, 1]
        ]
    },
    log=True
)


#exemplo.vetorPrioridadesLocais()

resultado = exemplo.Resultado();
print(resultado)
plt.bar(resultado.keys(),resultado.values())
plt.ylabel('Prioridade')
plt.show()