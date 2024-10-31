A = imagem
array = np.array(A, dtype=np.float64)
At = np.transpose(A)

#Calcular a matriz de covariância e obtenha os valores singulares e vetores
mult = np.dot(array, array.T)
sigma, U = np.linalg.eigh(mult)

# Ordenar os valores singulares e autovetores
sorted_indices = np.argsort(sigma)[::-1]
sigma = sigma[sorted_indices]
sigma[sigma < 0] = 0  # Definir valores negativos como zero (em caso de pequenas imprecisões)
sigma = np.sqrt(sigma)  # Valores singulares são a raiz quadrada dos autovalores
U = U[:, sorted_indices]  # Reordene as colunas de U
# U[sorted_indices, :] ordenaria as linhas 

# Calcule V utilizando U e A
V = np.dot(U.T, A) / sigma[:, np.newaxis]  # Normalizando cada linha de V

k = 50 #qto de informação queremos armazenar 

# Reduzir as dimensões de U, sigma e V para k
U_k = U[:, :k]  # m x k
sigma_k = np.diag(sigma[:k])  # k x k
VT = V[:k, :] # k x n

# Reconstruir a imagem comprimida
# A = U*sigma*VT
# sigma = autovalores 
# U => autovetores de A*AT 
# V => autovetores de AT*A  
Ak = np.dot(U_k, np.dot(sigma_k, VT))

# Exibir a imagem reconstruída
plt.axis('off')
plt.imshow(Ak, cmap='gray')
plt.show()
