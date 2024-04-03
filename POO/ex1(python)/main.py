from tabuleiro import Tabuleiro
import math

def main():

    linha = input() #recebe os inteiros (matriz)
    num = linha.split()
    numeros = list(map(int, num))
    k = len(num) #pega o tamanho 
    n = int(math.sqrt(k))
    Tab = Tabuleiro(n)
    Tab.preencher_tabuleiro(numeros)
    Tab.printMatrix()

    mov = input()
    #movimentos = mov.split()

    for car in mov:
        #print(car, end="")
        if car == 'd': Tab.getDown()
        elif car == 'l': Tab.getLeft()
        elif car == 'u': Tab.getUp()
        else: Tab.getRight()
        Tab.printMatrix()
    
    if Tab.findSolution(): print("Posicao final: True")
    else: print("Posicao final: False") 

if __name__ == "__main__":
    main() 
