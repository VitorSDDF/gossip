#include"gossip.h"
using namespace std;

int main(int argc, char **argv){

	// Servidor ou cliente porta padrao
	if(argc == 2){
		if(!strcmp(argv[1],"-S")){		
			cout << ">> entrou servidor porta default" << endl;
			servidor(PORTA_PADRAO);			
		}
		else if(!strcmp(argv[1],"host")){
			cout << ">> entrou cliente porta default" << endl;
			cliente(PORTA_PADRAO);			
		}
		else{
			cout << "Erro na chamada do programa" << endl;
		}		
	}
	// Servidor ou cliente junto a porta via comando
	else if(argc == 3){
		if(!strcmp(argv[1],"-S")){
			servidor(atoi(argv[2]));
		}
		else if(!strcmp(argv[1],"host")){
			cliente(atoi(argv[2]));		
		}
		else{
			cout << "Erro na chamada do programa" << endl;
		}
	}
	else{
		cout << "Erro na chamada do programa" << endl;
	}
	return(0);
}
