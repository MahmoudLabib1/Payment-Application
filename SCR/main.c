#include "../SCR/Application/app.h"
extern volatile bool Again;
int main(){
	setvbuf(stdout, NULL, _IONBF, 0);

	while(Again == TRUE){
	appStart();
	}
	printf("\n");
	system("pause");
	return 0;
}
