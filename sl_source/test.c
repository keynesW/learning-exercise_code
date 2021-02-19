#include <stdio.h>

char* word_cunt(char *s);


int main()
{
    char str[] = "dfadf fdafad dfadfasdjlkljl dfadf";

    printf("%s\n",word_cunt(str));
    
    return 0;
}
char * word_cunt(char *s)
{
    int cunt = 0;
    int cunt_max = 0;
    char *ptr_max = NULL;
    char *ptr_s = NULL;

    for (;*s ;s++)
    {
        ptr_s = s;
        cunt = 0;
        for(;*s != 32&&*s;s++)
            cunt++;
        if(cunt>cunt_max)
        {
            cunt_max = cunt;
            ptr_max = ptr_s;
        }
    }

    return ptr_max;
}
