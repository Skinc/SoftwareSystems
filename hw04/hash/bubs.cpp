#include <stdio.h>

int main()
{
	int sortable [100];
	int i = 0;
	for (i=0; i<100; i++){
		sortable[i]= rand() % 100;
		printf("%d", sortable[i] );
	}

}