#usando dicionario
class ArvBin: 

    def __init__(self):
        self.dic = {} 
    
    def add_recursive_node(self, node, val):
        if(val <= node): #esq
            if(self.dic[node][0] is None):
                self.dic[node] = (val, self.dic[node][1]) 
                self.dic[val] = (None, None)
            else:
                self.add_recursive_node(self.dic[node][0], val) 
        else:
            if(self.dic[node][1] is None):
                self.dic[node] = (self.dic[node][0], val) 
                self.dic[val] = (None, None)
            else:
                self.add_recursive_node(self.dic[node][1], val)


    def add_node(self, val):
        
        for a in self.dic:
            if a == val:
                encontrada = True 
                return

        if self.dic == {}: 
            self.root = val 
            self.dic[val] = (None, None) 
        
        else:
            self.add_recursive_node(self.root, val)

    def dfs(self, node):
        f_esq = self.dic[node][0]
        if(f_esq is not None):
            self.dfs(f_esq)
        print('', node, '', end = "")
        f_dir = self.dic[node][1]
        if(f_dir is not None):
            self.dfs(f_dir)

    def percorre(self):
        self.dfs(self.root) ; 
        print()

    def __str__(self):
        s = 'digraph {\n'
        for k, v in self.dic.items():
            f_esq = v[0]
            f_dir = v[1]
            if f_esq is not None:
                s += str(k) + ' -> ' + str(f_esq) + '\n'
            if f_dir is not None: 
                s += str(k) + ' -> ' + str(f_dir) + '\n'
        s += '}\n'
        return s 

class Main:

    def iniciar_programa(self):

        nomes = [] #nomes  

        arvore = ArvBin()  

        while True: 
            try: 
                atual = input() #tem input ainda?
                nome = atual.split(" ", 1)[1]
                nomes.append(nome.strip())
            except EOFError: #terminou as entradas 
                break

        for atual in nomes: 
            arvore.add_node(atual)
        
        arvore.percorre()
        print(arvore)

programa = Main()
programa.iniciar_programa()
