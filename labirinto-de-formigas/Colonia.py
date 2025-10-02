import random
import copy
import queue
import pygame

pygame.init()   #Innicia Pygame

NC=30           #Número de Cíclos
NF=5            #Número de Formigas 
px = 3          #Tamanho do pixel

FeromInit=125   #Valor inicial de feromônio
FeromMin=50     #Valor minimo de ferômonio
FeromMax=300    #Valor maximo de feromônio
FeromRate=9     #Taxa de feromônio
EvapoRate=4     #Taxa de evaporação
Plus = 2        #Bonificação para caminhos menores

# ------------------ Formiga ------------------

class Ant:

    def __init__(self,origin,objective):
        
        self.posJ=origin[0]             # Posição da formiga na linha da matriz
        self.posI=origin[1]             # Posição da formiga na coluna da matriz
        self.ObjetivoJ=objective[0]
        self.ObjetivoI=objective[1]
        self.PosDispo=[]
        self.Caminho=[]
        self.iteracao=0
        self.no=[]
        self.Caminho.append([self.posJ,self.posI])

    def eat(self):
        while self.no and self.Caminho and self.Caminho[-1] != self.no[-1]:
            self.Caminho.pop()
        if self.Caminho:
            self.posJ, self.posI = self.Caminho[-1]
        if self.closedWay():
            if self.no:
                self.no.pop()
       
    def reeset(self,origin):
        self.posJ = origin[0]
        self.posI = origin[1]
        self.PosDispo = []
        self.no = []
        self.Caminho = [[self.posJ,self.posI]]
        
    def walk(self,next_pos):
        self.posJ = next_pos[0]
        self.posI = next_pos[1]
        self.Caminho.append([self.posJ,self.posI])
        self.PosDispo.clear()
           
    def find(self):
        return (self.posI == self.ObjetivoI) and (self.posJ == self.ObjetivoJ)

    def _inside(self, M, i, j):
        return 0 <= i < len(M) and 0 <= j < len(M[0])
         
    def availableWay(self,matrix):
        
        self.PosDispo.clear()
        M= matrix.PathMatrix
        
        neighbors = [(1,0), (-1,0), (0,1), (0,-1)]
        for di, dj in neighbors:
            ni, nj = self.posI + di, self.posJ + dj
            if self._inside(M, ni, nj) and (M[ni][nj] in (0, 3)):
                
                    if len(self.Caminho) >= 2 and [nj, ni] == self.Caminho[-2]:
                        continue  # Evita voltar para a posição anterior imediata
                    if [nj, ni] not in self.Caminho:
                        self.PosDispo.append([nj, ni])
        
        if [self.ObjetivoJ,self.ObjetivoI] in self.PosDispo:
            self.PosDispo.clear()
            self.walk([self.ObjetivoJ,self.ObjetivoI])
            return       

    def closedWay(self):
        return (len(self.PosDispo)==0 and (not self.find()))
    
    def _add_fork_to_node(self):
        if(len(self.PosDispo)>1):
            self.no.append(self.Caminho[-1])
            
    def _choose_by_pheromone(self, maze):
        weights = []
        for pnt in self.PosDispo:
            w = max(maze.getFeromon(pnt), 1)  # Evita pesos zero
            weights.append(w)
        
        s = sum(weights)
        if s <= 0:
            self.walk(random.choice(self.PosDispo))
            return
        
        r = random.uniform(0, s)
        acc = 0
        for pnt, w in zip(self.PosDispo, weights):
            acc += w
            if r <= acc:
                self.walk(pnt)
                return
                
                
    def choose(self, maze):
        if self.find() or not self.PosDispo:
            return
        
        self._add_fork_to_node()
        self._choose_by_pheromone(maze)

        
#-------Funções do Labirinto-------------------

class Labrinth:
    
    def __init__(self,file):            # The function trates the Maze, transforming the character maze into a numbermaze
        f = open(file,'r')              # easier to use the Ants, here the function reads the file.
        f_content = f.readlines()       #
        self.PathMatrix=[]              # It's created the Path matrix variable where the Ants can walk on it, with the
                                        # following num interpretations:
                                        # 1-Wall     2-Initial Point      3-End Point    4-Paths Traveled
        self.PheromonMatrix=[]          # Its created the Pheromon Matrix where has the same size of the Path Matrix,
                                        # however the positions are fild with pheromons values,where there walls, the pheromon
                                        # value is 0.
        self.pnt_init=[]                # The initial point coordenates is stored into pnt_init vector as for the ending point into
        self.pnt_end=[]                 # pnt_end vector, the 0 index is the vertical cordenates (line number) and 1 index is stored
                                        # the horizontal cordenate(colum number).
        matrix1_aux=[]                  # These 3 matrix's are used to create the Path and Pheromon Matrix's 
        matrix2_aux=[]
        matrix3_aux=[]

        for i in f_content:
            for  j in i:    
                if(j==' '):
                    matrix2_aux.append(0)
                elif(j=='S'):
                    matrix2_aux.append(2)
                elif(j=='E'):
                    matrix2_aux.append(3)
                else:
                    matrix2_aux.append(1)
            aux=matrix2_aux.copy()
            matrix1_aux.append(aux)
            matrix2_aux.clear()
        
        f.close()
        
        for line in matrix1_aux:
            for i in range(0,len(line),2):
                matrix2_aux.append(line[i])
            aux=matrix2_aux.copy()
            matrix3_aux.append(aux)
            matrix2_aux.clear()
        
        self.PathMatrix=matrix3_aux.copy()
        matrix3_aux.clear()
         
        for i in self.PathMatrix:
            if (2 in i):
                    self.pnt_init.append(i.index(2)) 
                    self.pnt_init.append(self.PathMatrix.index(i)) 
            if (3 in i):
                    self.pnt_end.append(i.index(3))
                    self.pnt_end.append(self.PathMatrix.index(i)) 
            for j in i:
                if(j==1):
                    matrix2_aux.append(0)
                else:
                    matrix2_aux.append(FeromInit)

            aux=matrix2_aux.copy()
            self.PheromonMatrix.append(aux)
            matrix2_aux.clear()

    def Atualizapath(self,Formiga):
            posI=Formiga.Caminho[-1][1]
            posJ=Formiga.Caminho[-1][0]
            self.PathMatrix[posI][posJ]=4
    
    def CleanTrail(self,Formiga):
         for pnt in Formiga.Caminho:
            if( self.PathMatrix[pnt[1]][pnt[0]] == 4 ):
                self.PathMatrix[pnt[1]][pnt[0]] = 0 

    def EvaporaFerom(self):
         for l in self.PheromonMatrix:
            for j in range(len(l)):
                if (l[j] > FeromMin):
                    l[j]=l[j]-EvapoRate
                    if(l[j]<FeromMin):
                        l[j]=FeromMin

    def AtualizaFerom(self,Formiga,plus):
       
        for pnt in Formiga.Caminho:
            if( self.PheromonMatrix[pnt[1]][pnt[0]]<FeromMax):
                self.PheromonMatrix[pnt[1]][pnt[0]]= self.PheromonMatrix[pnt[1]][pnt[0]] + FeromRate + plus
                if( self.PheromonMatrix[pnt[1]][pnt[0]]>FeromMax):
                    self.PheromonMatrix[pnt[1]][pnt[0]]=FeromMax


    def print(self):
        print("Labirinto:")
        print("\n")
        for i in self.PathMatrix:
            print(i)
        print("\n")
        print("Matrix de Feromonio:")
        print("\n")
        for i in self.PheromonMatrix:
            print(i)
        print("\n")



#-------Funções do Algoritmo-------------------
           
def print_result(formiga,map,index):
    if(formiga.find()):
        print("Caminho da Formiga "+str(index) + " : "),
        print("Chegou")
        print("Interações:",end=" ")
        print(formiga.iteracao)
        map.print()
        print("Caminho Resultado:",end=" ")
        for  i in range(10):
            print(formiga.Caminho[i],end=" ")

    if(formiga.closedWay()):
        print("Caminho da Formiga "+str(index) + " : "),
        print("Bateu")
        print("Posição:",end=" ")
        print(formiga.Caminho[-1])
        print("Interações:",end=" ")
        print(formiga.iteracao)
            

            
def PRINTA(formiga,m2,mferomonio):
        
    tela = pygame.display.set_mode((len(m2)*px,len(m2)*px))


    for i in range(len(m2)):
        for j in range(len(m2[0])):

            a=255/(FeromMax-FeromMin)
            b=FeromMin
            x=mferomonio[i][j]
            y=int(a*x-b)
         
            if m2[i][j] == 0:
                pygame.draw.rect(tela, (0, 0, 0),[j*px,i*px,px,px])
            elif m2[i][j] == 1:
                pygame.draw.rect(tela, (255, 255, 255), [j*px,i*px, px, px])
            
            if(mferomonio[i][j]>0):
                pygame.draw.rect(tela, (y,0,0), [j*px,i*px,px,px])
            
            if m2[i][j] == 4:
                pygame.draw.rect(tela, (202, 205, 0), [j*px,i*px, px, px])
            
            if m2[i][j] == 2:
                pygame.draw.rect(tela, (0, 0, 255), [j*px,i*px, px, px])
            pygame.draw.rect(tela, (247,45,221), [formiga.ObjetivoJ*px,formiga.ObjetivoI*px,px,px])
            pygame.draw.rect(tela, (0,255,0), [formiga.posJ*px,formiga.posI*px,px,px])
   
    pygame.display.update()
                        
    
        
#Inicio do programa

mapa = Labrinth("./LabirintoExemplo01.txt")

Colonia=[]
CaminhosEcontrados=[]

for i in range(NF):
    Colonia.append(Ant(mapa.pnt_init,mapa.pnt_end))

for i in range(NC):
    Best = 0

    for m in  Colonia:
        m.availableWay(mapa)
        while(not m.find()):
            m.choose(mapa)
            PRINTA(m,mapa.PathMatrix,mapa.PheromonMatrix)
            mapa.Atualizapath(m)
            m.availableWay(mapa)
          
            while (m.closedWay()):
                print_result(m,mapa,Colonia.index(m))
                m.eat()
                m.availableWay(mapa)
        
        mapa.CleanTrail(m)
        m.iteracao+=1
        print_result(m,mapa,Colonia.index(m))
        
    for m in Colonia:

        CaminhosEcontrados.append(m.Caminho.copy())

        if(len(m.Caminho)>Best):
            mapa.AtualizaFerom(m,0)
        else:
            Best=len(m.Caminho)
            mapa.AtualizaFerom(m,Plus)
        
        mapa.EvaporaFerom()
        m.reeset(mapa.pnt_init)
