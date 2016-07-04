#include"gossip.h"
using namespace std;

int main(int argc, char **argv){

	if(argc == 2){

		if(!strcmp(argv[1],"-S")){
		
			servidor(PORTA_PADRAO);

		}
		else if(!strcmp(argv[1],"host")){

			cliente(PORTA_PADRAO);	
		
		}
              	else{

			cout << "Erro na chamada do programa" << endl;

		}
		
	}
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
