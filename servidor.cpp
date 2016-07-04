#include "gossip.h"
using namespace std;
 
void servidor(int porta)
{
	
	bool sair = false;
 	struct sockaddr_in meuEndereco;	//Meu endereço
	struct sockaddr_in enderecoRemoto;//Endereço remoto
	int descritor;// descritor do socket 
	char buffer[BUFFSIZE];//buffer para troca de mensagens
        char hello_clt[10] = "HELLO_CLT";
        char hello_srv[10] = "HELLO_SRV";
        char bye_srv[8] = "BYE_SRV";
        char bye_clt[8] = "BYE_CLT";

	socklen_t remlen;


	//criando um socket UDP

	if ((descritor = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {

		cout <<"Erro ao criar socket"<< endl;

	}

	//Endereço Servidor
	meuEndereco.sin_family = AF_INET;
	meuEndereco.sin_addr.s_addr = htonl(INADDR_ANY);
	meuEndereco.sin_port = htons(porta);
	//Endereco Remoto
	enderecoRemoto.sin_family = AF_INET;
	enderecoRemoto.sin_addr.s_addr = htonl(INADDR_ANY);
	enderecoRemoto.sin_port = htons(porta);


        //Associando o socket a algum ip válido e porta especifica
	if (bind(descritor, (struct sockaddr *)&meuEndereco, sizeof(meuEndereco)) < 0){

		cout <<"Erro ao criar socket"<< endl;

	}

	do{

		//Recebe requisição do cliente
                remlen = sizeof(enderecoRemoto);
		recvfrom(descritor, buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr*)&enderecoRemoto, &remlen);

	}while(strcmp(buffer,hello_srv));

        //Envia Confirmação de recebimento
	sendto(descritor, hello_clt, strlen(hello_clt), 0, (struct sockaddr *)&enderecoRemoto, sizeof(struct sockaddr_in));
        cout << "Handshake!" << endl;
        //Inicia a troca de mensagens pelo teclado
    	cout << "Cliente: ";
        do {

            remlen = sizeof(enderecoRemoto);
	    recvfrom(descritor, buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr*)&enderecoRemoto, &remlen);

            cout << buffer << " ";

            if (!strcmp(buffer,bye_srv)){
                
                sair = true;
		break;
            }
        } while (1);
 
        do {
            cout << "\nServidor: ";
            do {

                cin >> buffer;

                sendto(descritor, buffer, strlen(buffer), 0, (struct sockaddr *)&enderecoRemoto, sizeof(struct sockaddr_in));
          
                if (!strcmp(buffer,bye_clt)) {

                    sendto(descritor, buffer, strlen(buffer), 0, (struct sockaddr *)&enderecoRemoto, sizeof(struct sockaddr_in));              
                    sair = true;
                    break;

                }
            } while (1);
 
            cout << "Cliente: ";
            do {

                remlen = sizeof(enderecoRemoto);
		recvfrom(descritor, buffer, BUFFSIZE, MSG_WAITALL, (struct sockaddr*)&enderecoRemoto, &remlen);

                cout << buffer << " ";

                if (!strcmp(buffer,bye_srv)) {
                  
                    sair = true;
		    break;

                }
            } while (1);
        } while (!sair);
  
    cout << "\n=> Fim de papo!!!.";
 
    close(descritor);
}




