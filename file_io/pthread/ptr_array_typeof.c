#include <stdio.h>

int main()
{
	int a[3][4] = {{90,56,89,77},
				  {93,88,94,85},
				  {88,92,94,62}};
	int * ptr_int = &a[0][0];
	//for(int i = 0 ; i < sizeof a / sizeof (int) ;\
			ptr_int++,i++ )
	for( ;ptr_int < ( typeof(ptr_int) )(&a+1);ptr_int ++ ) 
		printf("%d  " ,*ptr_int);

	putchar('\n');
 	printf("%zd\n",sizeof a / sizeof (int));	
	return 0;
}
