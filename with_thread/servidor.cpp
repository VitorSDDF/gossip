#include "utils.h"
using namespace std;

pthread_t tlkSrv_thread, lstSrv_thread;

struct sockaddr_in meuEndereco; //Meu endereço
struct sockaddr_in enderecoRemoto;//Endereço remoto
int socketSrv;// socketSrv do socket 
char bufferSrv[BUFFSIZE];//bufferSrv para troca de mensagens

int controlSrv;
socklen_t remlen;

void *tlkServidor(void *arg) {
    while(1) {
        //Servidor fala    
        cout << ">> Servidor:" << endl;        
        bzero(bufferSrv,BUFFSIZE);
        cin.getline(bufferSrv,BUFFSIZE);
        sendto(socketSrv, bufferSrv, strlen(bufferSrv), 0, (struct sockaddr *)&enderecoRemoto, sizeof(struct sockaddr_in));
        // if(strcmp(bufferSrv, bye_srv)==0) {controlSrv=1; break;}        
    }
    return NULL;
}

void *lstServidor(void *arg) {
    while(1) {
        //Servidor ouve
        remlen = sizeof(enderecoRemoto);
        recvfrom(socketSrv, bufferSrv, BUFFSIZE, MSG_WAITALL, (struct sockaddr*)&enderecoRemoto, &remlen);
        cout << ">> Cliente:" << endl;
        cout << bufferSrv << endl;
        //BYE_SRV
        if(strcmp(bufferSrv, bye_srv)==0) {
            sendto(socketSrv, bye_clt, strlen(bye_clt), 0, (struct sockaddr *)&enderecoRemoto, sizeof(struct sockaddr_in));
            controlSrv=1;
            break;
        }        
    }
    return NULL;
}
 
void servidor()
{
	//criando um socket UDP
	if ((socketSrv = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
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
	if (bind(socketSrv, (struct sockaddr *)&meuEndereco, sizeof(meuEndereco)) < 0){
		cout <<"Erro ao criar socket"<< endl;
	}

	cout << "\n********************* Servidor ************************" << endl;
	do{

		//Recebe requisição do cliente
		remlen = sizeof(enderecoRemoto);
		recvfrom(socketSrv, bufferSrv, BUFFSIZE, MSG_WAITALL, (struct sockaddr*)&enderecoRemoto, &remlen);

	}while(strcmp(bufferSrv,hello_srv));

    //Envia Confirmação de recebimento
	sendto(socketSrv, hello_clt, strlen(hello_clt), 0, (struct sockaddr *)&enderecoRemoto, sizeof(struct sockaddr_in));
    cout << "Handshake concluido com o cliente" << endl;
    controlSrv = 0;

    //Inicia a troca de mensagens pelo teclado
    int lst_thread = pthread_create(&(lstSrv_thread), NULL, &lstServidor, NULL);
    if(lst_thread!=0) {cout << "Erro criacao lst_thread Servidor" << endl;}

    int tlk_thread = pthread_create(&(tlkSrv_thread), NULL, &tlkServidor, NULL);
    if(tlk_thread!=0) {cout << "Erro criacao lst_thread Servidor" << endl;}

    while(!controlSrv);
  
    cout << "\n=> Fim de papo" << endl; 
    close(socketSrv);
    exit(1);
}

