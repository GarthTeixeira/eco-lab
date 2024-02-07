#//class AHP (AnalyticHierachyProcess)

import numpy as np
import pandas as pd

class AHP:
    def __init__(self, criteria, data, method):
        self.precision = 3
        self.method = method
        self.criteria = criteria
        self.data = data
        self.n = len(self.criteria)
        self.nAlternatives = len(self.data)
        self.nCriteria = len(self.criteria)
        self.eigenVector = []
        self.eigenValue = 0
        self.consistencyIndex = 0
        self.consistencyRatio = 0
        self.weights = []
        self.normalizedWeights = []
        self.consistencyIndex = 0
        self.consistencyRatio = 0
        self.normalizedWeights = []
        self.sortedWeights = []
        self.sortedNormalizedWeights = []
        self.sortedCriteria = []
        self.sortedCriteriaNormalized

    
    @staticmethod
    def Aprroximate(matrix, precision):
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
        

    
if __name__ == '__main__':
    matriz = np.array([[1, 6, 3],
                    [1/6, 1, 1/6],
                    [1/3, 6, 1]])
    precision = 3
    print('Aproximado', AHP.Aprroximate(matriz, precision))
    print('Média Geométrica', AHP.GeoMetricMean(matriz, precision))
    print('Autovalor', AHP.EigenValue(matriz, precision))
    print('Indice de Consistência', AHP.ConsistencyIndex(matriz))
