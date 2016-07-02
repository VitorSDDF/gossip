#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
 
#define ENTER 13
#define ESC 27
#define BUFFSIZE 2048

using namespace std;
 
int cliente(int porta)
{
	
	bool sair = false;
 	struct sockaddr_in meuEndereco;	//Meu endereço
	struct sockaddr_in enderecoRemoto;//Endereço remoto
	int descritor;// descritor do socket 
	char buffer[BUFFSIZE];//buffer para troca de mensagens

	socklen_t remlen = sizeof(enderecoRemoto);


	//criando um socket UDP

	if ((descritor = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		cout <<"Erro ao criar socket"<< endl;
		return 0;
	}

	

	memset((char *)&meuEndereco, 0, sizeof(meuEndereco));
	meuEndereco.sin_family = AF_INET;
	meuEndereco.sin_addr.s_addr = htonl(INADDR_ANY);
	meuEndereco.sin_port = htons(porta);
        //Associando o socket a algum ip válido e porta especifica
	if (bind(descritor, (struct sockaddr *)&meuEndereco, sizeof(meuEndereco)) < 0) {

		cout <<"Erro ao criar socket"<< endl;

	}

	do{

		//Recebe requisição do cliente
		recvfrom(descritor, buffer, BUFFSIZE, 0, (struct sockaddr *)&enderecoRemoto, &remlen);

	}while(strcmp(buffer,"HELLO_SRV"));
 
        //Envia Confirmação de recebimento
	sendto(descritor, "HELLO_CLT", strlen("HELLO_CLT"), 0, (struct sockaddr *)&enderecoRemoto, sizeof(enderecoRemoto));
        //Inicia a troca de mensagens pelo teclado
    	cout << "Cliente: ";
        do {

            recvfrom(descritor, buffer, BUFFSIZE, 0, (struct sockaddr *)&enderecoRemoto, &remlen);

            cout << buffer << " ";

            if (!strcmp(buffer,"BYE_SRV")){
                
                sair = true;
		break;
            }
        } while (1);
 
        do {
            cout << "\nServidor: ";
            do {

                cin >> buffer;

                sendto(descritor, buffer, strlen(buffer), 0, (struct sockaddr *)&enderecoRemoto, remlen);
          
                if (!strcmp(buffer,"BYE_CLT")) {

                    sendto(descritor, buffer, strlen(buffer), 0, (struct sockaddr *)&enderecoRemoto, remlen);              
                    sair = true;
                    break;

                }
            } while (1);
 
            cout << "Cliente: ";
            do {

                recvfrom(descritor, buffer, BUFFSIZE, 0, (struct sockaddr *)&enderecoRemoto, &remlen);

                cout << buffer << " ";

                if (!strcmp(buffer,"BYE_SRV")) {
                  
                    sair = true;
		    break;

                }
            } while (1);
        } while (!sair);
  
    cout << "\n=> Fim de papo!!!.";
 
    close(descritor);
}




