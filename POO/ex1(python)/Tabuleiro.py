class Tabuleiro: 
    
    def __init__(self, n):
        self.xvazio = 0
        self.yvazio = 0 
        self.n = n
        self.matriz = []
        for _ in range(n):
            linha = []
            for _ in range(n):
                linha.append(0) #coloca 0 no final de linha 
            self.matriz.append(linha) #coloca a linha na matriz
    
    def preencher_tabuleiro(self, numeros):
        ct = 0
        for i in range(self.n):
            for j in range(self.n):
                #print(numeros[ct])
                if(numeros[ct]==0):
                    self.xvazio = i
                    self.yvazio = j 
                self.matriz[i][j] = numeros[ct]
                ct += 1
    
    def valid(self, x, y):
        return x >= 0 and y >= 0 and x < len(self.matriz) and y < len(self.matriz[x])
    
    def getLeft(self):
        if not (self.valid(self.xvazio, self.yvazio+1)): return
        bx = self.matriz[self.xvazio][self.yvazio+1]
        self.matriz[self.xvazio][self.yvazio+1] = 0 
        self.matriz[self.xvazio][self.yvazio] = bx
        self.yvazio+=1
    
    def getRight(self):
        if not (self.valid(self.xvazio, self.yvazio-1)): return
        poscima = self.matriz[self.xvazio][self.yvazio-1] 
        self.matriz[self.xvazio][self.yvazio-1] = 0
        self.matriz[self.xvazio][self.yvazio] = poscima
        self.yvazio-=1

    def getUp(self):
        if not( self.valid(self.xvazio+1, self.yvazio)): return 
        dr = self.matriz[self.xvazio+1][self.yvazio]
        self.matriz[self.xvazio+1][self.yvazio] = 0
        self.matriz[self.xvazio][self.yvazio] = dr
        self.xvazio+=1

    def getDown(self):
        if not (self.valid(self.xvazio-1, self.yvazio)): return
        dir = self.matriz[self.xvazio-1][self.yvazio]
        self.matriz[self.xvazio-1][self.yvazio] = 0
        self.matriz[self.xvazio][self.yvazio] = dir
        self.xvazio-=1
    
    def printMatrix(self):
        
        for _ in range(len(self.matriz)):
            print("+------", end="")
        print("+")

        for i in range(len(self.matriz)):
            print("|", end="")
            for j in range(len(self.matriz)):
                if self.matriz[i][j] == 0:
                    print("      |", end="")
                else:
                    print(" {:3d}  |".format(self.matriz[i][j]), end="")
            print()

            for _ in range(len(self.matriz)):
                print("+------", end="")
            print("+")

        print() # quebra de linha automática no final
        
    def findSolution(self):
        ct = 1 
        if (self.matriz[0][0] != 0): return 0 
        for i in range(len(self.matriz)):
            for j in range(len(self.matriz)):
                if (i == 0 and j == 0): continue 
                if self.matriz[i][j] != ct: return False
                ct += 1 
        return True 
    
