#include "gossip.h"
using namespace std;
 
void cliente(int porta)
{
	bool sair = false;
   	char buffer[BUFFSIZE];
	int descritor;
        char hello_clt[10] = "HELLO_CLT";
        char hello_srv[10] = "HELLO_SRV";
        char bye_srv[8] = "BYE_SRV";
        char bye_clt[8] = "BYE_CLT";
	 
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

	
	do{		
                //Envia a mensagem de inicio para o server
		sendto(descritor, hello_srv, strlen(hello_srv) , 0, (struct sockaddr *)&meuEndereco, sizeof(struct sockaddr_in));

	        //Recebe comfirmação do servidor
                cltlen = sizeof(struct sockaddr_in);
		recvfrom(descritor, buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr *)&meuEndereco, &cltlen);
       
	}while(strcmp(buffer,hello_clt));
 	cout << "Handshake!" << endl;
	do {
		cout << "Cliente: ";
		do {
			cin >> buffer;
                        sendto(descritor, buffer, strlen(buffer) , 0, (struct sockaddr *)&meuEndereco, sizeof(struct sockaddr_in));    

		    	if (!strcmp(buffer,bye_srv)) {

				sendto(descritor, buffer, strlen(buffer) , 0, (struct sockaddr *)&meuEndereco, sizeof(struct sockaddr_in));
				sair = true;
                                break;

		    	}
		} while (1);
		 
		cout << "Servidor: ";
		do {
                        cltlen = sizeof(struct sockaddr_in);
			recvfrom(descritor, buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr *)&meuEndereco, &cltlen);
			cout << buffer << " ";

		    	if (!strcmp(buffer,bye_clt)) {
				
				sair = true;
				break;
		    	}
	 
		} while (1);
 
    	} while (!sair);
 

        cout << "\n\n=> Fim de papo com" << endl;
        close(descritor);
      
        exit(1);
}
