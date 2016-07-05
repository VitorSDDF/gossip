#include"gossip.h"

int main(int argc, char **argv){

	if(argc == 0){
		
		cliente(atoi(PORTA_PADRAO));
	
	}
	else if(argc == 1){

		if(!strcmp(argv[1],"-S")){
		
			servidor(atoi(PORTA_PADRAO));
		else{

			cliente(atoi(argv[1]));	
		
		}
		
	}
        else if(argc == 2){
		if(!strcmp(argv[1],"-S")){

			servidor(atoi(argv[2]));		

		}
		else{

			cout << "Erro na chamada do programa" << endl;

		}

	}

	return(0);
}
