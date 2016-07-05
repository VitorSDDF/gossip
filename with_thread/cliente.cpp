#include "utils.h"
using namespace std;

pthread_t tlkClt_thread, lstClt_thread;

char bufferClt[BUFFSIZE];
int socketCtl;

//var msg
char hello_clt[10] = "HELLO_CLT";
char hello_srv[10] = "HELLO_SRV";
char bye_srv[10] = "BYE_SRV";
char bye_clt[10] = "BYE_CLT";

//var socket
struct sockaddr_in endClt;
socklen_t cltlen;

int controlClt;

void *tlkCliente(void *arg) {
	while(1) {
		//Cliente fala
		cout << ">> Cliente:" << endl;		
		bzero(bufferClt,BUFFSIZE);
		cin.getline(bufferClt,BUFFSIZE);
		sendto(socketCtl, bufferClt, strlen(bufferClt) , 0, (struct sockaddr *)&endClt, sizeof(struct sockaddr_in));
    }
    return NULL;
}

void *lstCliente(void *arg) {
	while(1) {
		//Cliente escuta		
	    bzero(bufferClt,BUFFSIZE);
	    cltlen = sizeof(struct sockaddr_in);
		recvfrom(socketCtl, bufferClt, BUFFSIZE, MSG_WAITALL, (struct sockaddr *)&endClt, &cltlen);
		cout << ">> Servidor:" << endl;
		cout << bufferClt << endl;
		//BYE_CLT
		if(strcmp(bufferClt, bye_clt)==0) {
			// sendto(socketCtl, bye_srv, strlen(bye_srv) , 0, (struct sockaddr *)&endClt, sizeof(struct sockaddr_in)); 
			controlClt=1;
			break;
		}
	}
	return NULL;
}
 
void cliente()
{ 
	//Criando o Socket	 
	if ((socketCtl = socket(AF_INET, SOCK_DGRAM,0)) < 0){
		cout << "\nErro na criação do socket" << endl;
		exit(0);
	}

	endClt.sin_family = AF_INET;	
	//atribui endereço IP ao socket tratando endianees do processador com relação a rede
	endClt.sin_addr.s_addr = htonl(INADDR_ANY);
	//atribui numero de porta ao socket tratando endianees do processador com relação a rede
	endClt.sin_port = htons(porta);
        

	bzero(bufferClt,BUFFSIZE);

	cout << "\n********************* Cliente ************************" << endl;
	do{		
        //Envia a mensagem de inicio para o servidor
		sendto(socketCtl, hello_srv, strlen(hello_srv) , 0, (struct sockaddr *)&endClt, sizeof(struct sockaddr_in));

	    //Recebe comfirmação do servidor
		cltlen = sizeof(struct sockaddr_in);
		recvfrom(socketCtl, bufferClt, BUFFSIZE, MSG_WAITALL, (struct sockaddr *)&endClt, &cltlen);
       
	}while(strcmp(bufferClt,hello_clt));	
	
 	cout << "\nHandshake concluido com o servidor" << endl;
 	controlClt = 0;

 	//threads
	int tlk_thread = pthread_create(&(tlkClt_thread), NULL, &tlkCliente, NULL);
 	if(tlk_thread!=0) {cout << "Erro criacao tlk_thread Cliente" << endl;}

 	int lst_thread = pthread_create(&(lstClt_thread), NULL, &lstCliente, NULL);
 	if(lst_thread!=0) {cout << "Erro criacao lst_thread Cliente" << endl;}
 	
 	while(!controlClt);
	
    cout << "\n\n=> Fim de papo" << endl;
    close(socketCtl);  
    exit(1);
}
