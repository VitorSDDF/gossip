
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
 
#DEFINE ENTER 13
#DEFINE ESC 27

using namespace std;
 
int main()
{

    int cliente, servidor;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
 
    struct sockaddr_in server_addr;
    socklen_t size;
 
    //Criando o Socket
 
    if ((client = socket(AF_INET, SOCK_STREAM,0)) < 0);
    {
        cout << "\nErro na criação do socket" << endl;
        exit(1);
    }

memset((char *)&server_addr, 0, sizeof(server_addr));//Deixa sinalizado que o S.O pode escolher o IP
myaddr.sin_family = AF_INET;
myaddr.sin_addr.s_addr = htonl(INADDR_ANY);//atribui endereço IP ao socket tratando endianees do processador com relação a rede
myaddr.sin_port = htons(portNum);//atribui numero de porta ao socket tratando endianees do processador com relação a rede

if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {

	cout << "=>Erro ao vincular socket" << endl;

}

hostent *hp;     /* host information */
sockaddr_in servaddr;    /* server address */

/* look up the address of the server given its name */
hp = gethostbyname(host);
if (!hp) {
	fprintf(stderr, "could not obtain address of %s\n", host);
        cout << "=>Erro ao obter endereço de %s" << host endl;
}

/* put the host's address into the server address structure */
memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);

/* send a message to the server */
if (sendto(fd, my_message, strlen("HELLO_CLT"), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
	cout << "Falha ao contactar servidor" << endl;
	exit(0);
}
 
    // first check if it is valid or not
    if (server < 0)
        cout << "=> Error on accepting..." << endl;
 
    while (1)
    {
        strcpy(buffer, "=> Servidor...\n");
        send(server, buffer, bufsize, 0);
        cout << "=> Connected with the client #" << clientCount << ", you are good to go..." << endl;
        cout << "\n=> Enter # to end the connection\n" << endl;
 
        /*
            Note that we would only get to this point after a
            client has successfully connected to our server.
            This reads from the socket. Note that the read()
            will block until there is something for it to read
            in the socket, i.e. after the client has executed a
            the send().
 
            It will read either the total number of characters
            in the socket or 1024
        */
 
        cout << "Cliente: ";
        do {
            recv(server, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == 27) {
                *buffer = 13;
                sair = true;
            }
        } while (*buffer != '27');
 
        do {
            cout << "\nServidor: ";
            do {
                cin >> buffer;
                send(server, buffer, bufsize, 0);
                if (*buffer == '#') {
                    send(server, buffer, bufsize, 0);
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');
 
            cout << "Client: ";
            do {
                recv(server, buffer, bufsize, 0);
                cout << buffer << " ";
                if (*buffer == '#') {
                    *buffer == '*';
                    isExit = true;
                }
            } while (*buffer != '*');
        } while (!isExit);
 
        /*
            Once a connection has been established, both ends
            can both read and write to the connection. Naturally,
            everything written by the client will be read by the
            server, and everything written by the server will be
            read by the client.
        */
 
        /* ---------------- CLOSE CALL ------------- */
        /* ----------------- close() --------------- */
 
        /*
            Once the server presses # to end the connection,
            the loop will break and it will close the server
            socket connection and the client connection.
        */
 
        // inet_ntoa converts packet data to IP, which was taken from client
        cout << "\n\n=> Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
        close(server);
        cout << "\nGoodbye..." << endl;
        isExit = false;
        exit(1);
    }
 
    close(client);
    return 0;
}
