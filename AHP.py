#//class AHP (AnalyticHierachyProcess)

import numpy as np

class AHP:
    def __init__(self, criterios,subCriterios, alternativas, matrizesPreferencias , method, log = False, precisao = 3):
        self.method = method                                # Método de cálculo
        self.precision = precisao                           # Precisão
        self.criterios = criterios                          # Lista de critérios
        self.subCriterios = subCriterios                    # Subcritérios
        self.alternativas = alternativas                    # Lista de alternativas
        self.matrizesPreferencias = matrizesPreferencias    # Matrizes de preferências
        
        self.nAlternatives = len(self.alternativas)
        self.nCriterios = len(self.criterios)
        self.log = log

        self.prioridadesGlobais = []

    
    @staticmethod
    def Aproximate(matrix, precision):
        columnSum = matrix.sum(axis=0) # Soma das colunas
        matrix_norm = np.divide(matrix, columnSum) # Normaliza a matriz
        meanRows = matrix_norm.mean(axis=1) # Calcula a média das linhas

        return np.round(meanRows, precision) # Retorna autovetor
    
    @staticmethod
    def GeoMetricMean(matrix, precision):
        media_geometrica =  [np.prod(row) ** (1/len(row)) for row in matrix] # Média Geométrica -> Retorna produto das linhas elevado a 1/n sendo n o número de elementos da linha
        media_geometrica_norm = media_geometrica / np.sum(media_geometrica) # Normaliza a média geométrica

        return np.round(media_geometrica_norm, precision)
    
    @staticmethod
    def EigenValue(matrix, precision, iterations = 100, beforeEigenVector = None):
        matrix_square = np.linalg.matrix_power(matrix, 2) # Eleva a matriz ao quadrado
        rowSum = np.sum(matrix_square,axis=1) # Soma das linhas
        columnSum = np.sum(rowSum,axis=0) # Soma das colunas das linhas
        
        actualEigenVector = np.divide(rowSum, columnSum)

        if beforeEigenVector is None:
            beforeEigenVector = np.zeros(matrix.shape[0])
       

        diferenca = np.subtract(actualEigenVector,beforeEigenVector).round(precision)

        if not np.any(diferenca):
            return actualEigenVector.round(precision)
        
        iterations -= 1
        if iterations > 0:
            return AHP.EigenValue(matrix_square, precision, iterations, actualEigenVector)
        else:
            return actualEigenVector.round(precision)
        
    @staticmethod
    def ConsistencyIndex(matrix):
        if matrix.shape[0] and matrix.shape[1] > 2:
            lambdaMax = np.real(np.linalg.eigvals(matrix).max()) # Teorema de Perron-Frobenius
            ic = (lambdaMax - len(matrix)) / (len(matrix) - 1) # indice de consistência
            ri = {3: 0.52, 4: 0.89, 5: 1.11, 6: 1.25, 7: 1.35, 8: 1.40, 9: 1.45, 10: 1.49, 11: 1.52, 12: 1.54, 13: 1.56, 14: 1.58, 15: 1.59} # indice randomico
            rc = ic / ri[len(matrix)]
        else:
            lambdaMax = 0
            ic = 0
            rc = 0
        return lambdaMax, ic, rc
    
    def vetorPrioridadesLocais(self):
        vetorPrioridadesLocais = {}
        for criterio in self.matrizesPreferencias:                              # Para cada critério escolher um metodo apropriado
            matriz = np.array(self.matrizesPreferencias[criterio])
            if self.method == 'aproximado':
                prioridadesLocais = self.Aproximate(matriz, self.precision)
            elif self.method == 'geometrico':
                prioridadesLocais = self.GeoMetricMean(matriz, self.precision)
            else:
                if matriz.shape[0] and matriz.shape[1] > 2:
                    prioridadesLocais = self.EigenValue(matriz, self.precision)
                    self.method = 'autovalor'
                else :
                    prioridadesLocais = self.Aproximate(matriz, self.precision)
                    self.method = 'aproximado'
            
            vetorPrioridadesLocais[criterio] = prioridadesLocais

            lambdaMax, ic, rc = self.ConsistencyIndex(matriz)

            if self.log:
                if(criterio == 'criterios'):
                    print('\nPrioridades locais critérios x objetivo :\n', prioridadesLocais)
                else:
                    print('\nPrioridades locais alternativas x critério ' + criterio + ':\n', prioridadesLocais)
                print('Soma das prioridades locais: ', np.round(np.sum(prioridadesLocais), self.precision))
                print('Lambda Max: ', lambdaMax)
                print('Indice de Consistencia ' + criterio + ':', np.round(ic,self.precision))
                print('Razão de Consistencia ' + criterio + ':', np.round(rc,self.precision), '(Cosistente)' if rc < 0.1 else '(Inconsistente)')
        
        return vetorPrioridadesLocais
    
    def vetorPrioridadesGlobais(self, prioridades, pesos, criterios):
        for criterio in criterios:
            peso = pesos[criterios.index(criterio)]
            prioridade_local = prioridades[criterio]
            prioridade_global = np.round(peso * prioridade_local, self.precision)

            if criterio in self.subCriterios:
                self.vetorPrioridadesGlobais(prioridades, prioridade_global, self.subCriterios[criterio])
            else:
                self.prioridadesGlobais.append(prioridade_global)
            
            if self.log:
                print('\nPrioridades globais do criterio ' + criterio + ':\n', prioridade_global)
                print('Soma das prioridades globais: ', np.round(np.sum(prioridade_global), self.precision))

        return self.prioridadesGlobais
    
    def Resultado(self):
        prioridades = self.vetorPrioridadesLocais()
        self.vetorPrioridadesGlobais(prioridades, prioridades['criterios'], self.criterios)
        prioridades = np.array(self.prioridadesGlobais).sum(axis=0).round(self.precision)

        return dict(zip(self.alternativas, prioridades))

    
if __name__ == '__main__':
    matriz = np.array([[1, 6, 3],
                    [1/6, 1, 1/6],
                    [1/3, 6, 1]])
    precision = 3
    print('Aproximado', AHP.Aproximate(matriz, precision))
    print('Média Geométrica', AHP.GeoMetricMean(matriz, precision))
    print('Autovalor', AHP.EigenValue(matriz, precision))
    print('Indice de Consistência', AHP.ConsistencyIndex(matriz))
