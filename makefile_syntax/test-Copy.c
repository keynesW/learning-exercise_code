#include "stdio.h"

int geta(int *ptr);

int geta(int *ptr){

	printf("this is *ptr =%d\n",*ptr);
	return * ptr;
}