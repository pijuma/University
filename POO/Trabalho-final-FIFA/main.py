import socket
import threading
import os
import shutil
import subprocess
 
# Diretório onde as cópias dos arquivos serão armazenadas para cada cliente
CLIENT_FILES_DIR = 'client_files'

# Variável global para contar conexões
connection_counter = 0
connection_counter_lock = threading.Lock()

def handle_client(client_socket, addr):
    global connection_counter
    print(f'Conexão de {addr}')

    # Incrementa a variável global de contagem de conexões
    with connection_counter_lock:
        connection_counter += 1
        client_id = connection_counter
    
    while True:
        try:
            # Recebe dados do cliente
            data = client_socket.recv(1024).decode('utf-8').strip()
            if not data:
                break
            command = data.strip()
            print(f'Comando recebido de {addr}: {command}')
            comando = command.split()
            print(f"{comando}")

            # Verifica se a palavra "Carregar" está em qualquer parte do comando
            if any("Carregar" in word for word in comando):
                print("tipo carregar")
                # Extrai o nome do arquivo
                filename = command.split(" ", 1)[1]
                filename = "dados/" + filename

                # Verifica se o arquivo existe
                if os.path.isfile(filename):
                    print("existe!")
                    # Cria um diretório para o cliente se não existir
                    client_dir = os.path.join(CLIENT_FILES_DIR, f'client_{client_id}')
                    os.makedirs(client_dir, exist_ok=True)
                    
                    # Copia o arquivo solicitado para o diretório do cliente
                    dest_file = os.path.join(client_dir, os.path.basename(filename))
                    shutil.copyfile(filename, dest_file)
            
            elif any("Listar" in word for word in comando):
                print("printando") 
                filename = command.split(" ", 1)[1]
                filename = f"../client_files/client_{client_id}/"+filename
                os.chdir("arquivos")
                os.system("make clean")
                os.system("make all")
                result = subprocess.run(['./main'], input = f"2 {filename}", capture_output=True, text=True)
                #a saida ta em result.stdout
                # Verifica o código de saída
                # result.stdout
                result.stdout += '\0'
                output_data = result.stdout.encode('utf-8')
                client_socket.sendall(output_data)
                os.chdir("..")
            
            elif any("Buscar" in word for word in comando):
                print("Tipo buscar")
                # Encontrar a posição da palavra "Buscar" no comando
                pos = 0
                for i in comando:
                    if "Buscar" in i:
                        break
                    print(pos) 
                    pos+=1

                index_buscar = pos
                print(index_buscar)

                # Extrair o nome do arquivo que vem após "Buscar"
                if index_buscar + 1 < len(comando):
                    nome_arquivo = comando[index_buscar + 1]
                    print(f"Nome do arquivo: {nome_arquivo}")

                    # O número de pares (nomeCampo, valorCampo) segue imediatamente após o nome do arquivo
                    if index_buscar + 2 < len(comando):
                        num_pares = int(comando[index_buscar + 2])
                        print(f"Número de pares de campos e valores: {num_pares}")

                        # Lista para armazenar os pares (nomeCampo, valorCampo)
                        pares_campos_valores = []

                        # Ler os pares de campos e valores
                        index = index_buscar + 3
                        for i in range(num_pares):
                            if index < len(comando):
                                nome_campo = comando[index]
                                if index + 1 < len(comando):
                                    valor_campo = comando[index + 1]
                                    pares_campos_valores.append((nome_campo, valor_campo))
                                    index += 2
                                else:
                                    print("Erro: valor do campo ausente")
                                    break
                            else:
                                print("Erro: nome do campo ausente")
                                break

                        # Aqui você pode processar os pares de campos e valores conforme necessário
                        nome_arquivo = f"../client_files/client_{client_id}/"+nome_arquivo
                        input_c = f"3 {nome_arquivo} {num_pares} "
                        for campo, valor in pares_campos_valores:
                            input_c = input_c + f"{campo} {valor} "
                        # Após processar os dados, você pode prosseguir com o processamento do arquivo ou outra lógica desejada
                        os.chdir("arquivos")
                        os.system("make clean")
                        os.system("make all")
                        print(f"input:{input_c}")
                        result = subprocess.run(['./main'], input = input_c, capture_output=True, text=True)
                        output = result.stdout + '\0'
                        
                        print(output)
                        
                        output_data = output.encode('utf-8')
                        client_socket.sendall(output_data)
                        os.chdir("..")
                    else:
                        print("Erro: número de pares de campos e valores ausente após o nome do arquivo")
                else:
                    print("Erro: nome do arquivo ausente após 'Buscar'")
            elif any("Remover" in word for word in comando):
                print("operacao remover")

                pos = 0
                for i in comando:
                    if "Remover" in i:
                        break
                    print(pos) 
                    pos+=1

                index_remover = pos
                filename = comando[index_remover+1]
                id = comando[index_remover+2]

                filename_ind = f"../client_files/client_{client_id}/"+filename[:-4]+"_ind.bin"
                filename = f"../client_files/client_{client_id}/"+filename
                os.chdir("arquivos")
                os.system("make clean")
                os.system("make all")
                input_c = f"5 {filename} {filename_ind} 1 1 id {id}"
                print(input_c)
                result = subprocess.run(['./main'], input = input_c, capture_output=True, text=True)
                #a saida ta em result.stdout
                # Verifica o código de saída
                # result.stdout
                print(result.stdout)
                os.chdir("..")
            
            elif any("Inserir" in word for word in comando):
                print("operacao inserir")
                
                comando = command.split("/#-")
                print(comando)
                pos = 0
                for i in comando:
                    if "Inserir" in i:
                        break
                    print(pos) 
                    pos+=1

                index_inserir = pos
                filename = comando[index_inserir+1]

                filename_ind = f"../client_files/client_{client_id}/"+filename[:-4]+"_ind.bin"
                filename = f"../client_files/client_{client_id}/"+filename
                os.chdir("arquivos")
                os.system("make clean")
                os.system("make all")

                string_insercao = ""
                dados = comando[-5:]
                string_insercao += dados[0] + " "
                if (dados[1] == "NULO"):
                    string_insercao += "NULO "
                else:
                    string_insercao += f"{dados[1]} "
                
                for i in range(2, 5):
                    if dados[i] == "NULO":
                        string_insercao += "NULO "
                    else:
                        string_insercao += f'"{dados[i]}" '
                

                input_c = f"6 {filename} {filename_ind} 1 {string_insercao}"
                print(input_c)
                result = subprocess.run(['./main'], input = input_c, capture_output=True, text=True)
                #a saida ta em result.stdout
                # Verifica o código de saída
                # result.stdout
                print(result.stdout)
                os.chdir("..")
                
        except ConnectionResetError:
            print("deu erro - catch")
            break

    client_socket.close()
    print(f'Conexão fechada de {addr}')

def start_server(host='localhost', port=50000):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((host, port))
    server_socket.listen(5)
    print(f'Servidor ouvindo em {host}:{port}...')
    
    while True:
        client_socket, addr = server_socket.accept()
        client_thread = threading.Thread(target=handle_client, args=(client_socket, addr))
        client_thread.start()

if __name__ == '__main__':
    # Cria o diretório para armazenar as cópias dos arquivos dos clientes
    os.makedirs(CLIENT_FILES_DIR, exist_ok=True)
    start_server()
