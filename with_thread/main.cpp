#include"utils.h"
using namespace std;

int controlVar = 0;
int porta = PORTA_PADRAO;

int main(int argc, char **argv){

	// Servidor ou cliente porta padrao
	if(argc == 2){
		if(!strcmp(argv[1],"-S")){		
			cout << ">> entrou servidor porta default" << endl;
			// servidor(PORTA_PADRAO);			
			servidor();
		}
		else if(!strcmp(argv[1],"host")){
			cout << ">> entrou cliente porta default" << endl;
			// cliente(PORTA_PADRAO);
			cliente();			
		}
		else{
			cout << "Erro na chamada do programa" << endl;
		}		
	}
	// Servidor ou cliente junto a porta via comando
	else if(argc == 3){
		if(!strcmp(argv[1],"-S")){
			// servidor(atoi(argv[2]));
			porta = atoi(argv[2]);
			servidor();
		}
		else if(!strcmp(argv[1],"host")){
			// cliente(atoi(argv[2]));	
			porta = atoi(argv[2]);
			cliente();
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
