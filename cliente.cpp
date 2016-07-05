#include "gossip.h"
using namespace std;
 
void cliente(int porta)
{
   	char buffer[BUFFSIZE];
	int descritor;
        char hello_clt[10] = "HELLO_CLT";
        char hello_srv[10] = "HELLO_SRV";
        char bye_srv[10] = "BYE_SRV";
        char bye_clt[10] = "BYE_CLT";
	char aux[8];
	struct sockaddr_in meuEndereco;
	socklen_t cltlen;
	 
	//Criando o Socket
	 
	if ((descritor = socket(AF_INET, SOCK_DGRAM,0)) < 0){

		cout << "\nErro na criação do socket" << endl;
		exit(0);

	}

	meuEndereco.sin_family = AF_INET;
	//atribui endereço IP ao socket tratando endianees do processador com relação a rede
	meuEndereco.sin_addr.s_addr = htonl(INADDR_ANY);
	meuEndereco.sin_port = htons(porta);//atribui numero de porta ao socket tratando endianees do processador com relação a rede
        

	bzero(buffer,BUFFSIZE);

	cout << "\n********************* Cliente ************************" << endl;
	do{		
                //Envia a mensagem de inicio para o server
		sendto(descritor, hello_srv, strlen(hello_srv) , 0, (struct sockaddr *)&meuEndereco, sizeof(struct sockaddr_in));

	        //Recebe comfirmação do servidor
                cltlen = sizeof(struct sockaddr_in);
		recvfrom(descritor, buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr *)&meuEndereco, &cltlen);
       
	}while(strcmp(buffer,hello_clt));
 	cout << "\nHandshake concluido com o servidor" << endl;
	do {
		cout << "\nCliente: ";
                bzero(buffer,BUFFSIZE);
		cin.getline(buffer,BUFFSIZE);
                sendto(descritor, buffer, strlen(buffer) , 0, (struct sockaddr *)&meuEndereco, sizeof(struct sockaddr_in));    
		memcpy(aux,buffer,8);
            	aux[8] = '\0';
            	if (!strcmp(aux,bye_srv)) {

                        break;

		    	}
		 
		cout << "\nServidor: ";
                bzero(buffer,BUFFSIZE);
                cltlen = sizeof(struct sockaddr_in);
		recvfrom(descritor, buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr *)&meuEndereco, &cltlen);
		cout << buffer << " ";
 		memcpy(aux,buffer,8);
            	aux[8] = '\0';
            	if (!strcmp(aux,bye_clt)) {
				
                        sendto(descritor, bye_srv, strlen(bye_srv) , 0, (struct sockaddr *)&meuEndereco, sizeof(struct sockaddr_in)); 
                        break;

		}
	 
 
    	} while (1);
 

        cout << "\n\n=> Fim de papo" << endl;
        close(descritor);
      
        exit(1);
}
