#include<stdio.h>

#define STR_DEL  "bcd"

void str_del_str(char *ptr_t ,const char *ptr_s);
int compare2str(const char *ptr_t,const char *ptr_s,int cunt);
int cunt_words(const char *ptr);

int main()
{
    char del_tst_chr[] = "abcdafd1234abcdadfbcd";
    char cunt_ws[] = " era1 wer avcd ed ab12  $sdf adf in$ cded 12#a  ab cd1"; 

    printf("in string del_tst_chr :\n%s\n\n",del_tst_chr);
    printf("string to delet is :\n%s\n",STR_DEL);

    printf("-------------------------------\n\n");

    str_del_str(del_tst_chr,"bcd");
    printf("in string del_tst_chr :\n%s\n\n",del_tst_chr);

    printf("-------------------------------\n\n");
    
    printf("in cunt_ws \n%s\n", cunt_ws);
//    printf("addr cunt_ws %p\n",cunt_ws);
    printf("ptr %zd\n",sizeof cunt_ws);
    printf("-------------------------------\n");
//    printf("cunt_ws[4] = %c\n",cunt_ws[4]);
    printf("words in cun_ws %d\n",cunt_words(cunt_ws));

    return 0;

}

int compare2str(const char *ptr_t,const char *ptr_s,int cunt)
{
    int iter = 0 ; 

    for( ; *ptr_t == *ptr_s &&iter < cunt;
                                      iter ++, ptr_t++ , ptr_s++) 
                                        ;
//   printf("iter = %d\n",iter) ;

    if( iter >= cunt )
        return 1;
    return 0;

}

void str_del_str(char *ptr_t ,const char *ptr_s)
{
    int cunt = 0 ;
    const char * ptr_s_m = ptr_s;
    char * ptr_res = ptr_t;
//    int ret = 0;

    for( ;*ptr_s ; ptr_s ++,cunt++)
            ;
//    printf("strlen of str to be del = %d\n",cunt);

    ptr_s = ptr_s_m;
    while(*ptr_t)   
    //    for( ; *ptr_t; )    
    //for(   ;*ptr_t;  ptr_t++,ptr_s++ )  there is a bug in this way
    {
//       ret = compare2str(ptr_t,ptr_s,cunt); 
//        printf("ret = %d \n",ret);
//        if( ret )
        if(compare2str(ptr_t,ptr_s,cunt)) 
            ptr_t += cunt;
        else
        {
            ptr_t++;                /////////////////
            ptr_res++;              /////////////////
        }

        *ptr_res = *ptr_t; 
    }
    *ptr_res = '\0';
}

//////////////////////////////////////////////////////////////////////////////////////

int is_chara(const char chr)
{
    if((chr >= 97 && chr <= 122 ) || (chr >= 65 && chr <= 90))
        return 1;
    return 0;
}

int cunt_words(const char *ptr)
{
    // looking for space 
    // checking if the charars before  space is a word
    // if is a word  cunt ++
    // else  go on for looking 
    
    const char *ptr_h = ptr;
    int words_cunt = 0,iter = 0;

    for( ;*ptr ; ptr++ )
    {
//        printf("ptr   %p\n",ptr);
//
        ptr_h = ptr ;  

        for( ;*ptr && *ptr != ' ';ptr++)
                   ;

//        printf("after  looking for space,addr of ptr :\n      %p\n",ptr);
        if(ptr != ptr_h)
        {
            //        for( ;iter < ptr - ptr_h; iter++)
            //            if( !is_chara(ptr_h[iter]) )

            for( ; iter <= ptr - ptr_h && is_chara(ptr_h[iter]);iter ++) 
                           ;

            if ( iter >= ptr - ptr_h )
                words_cunt++;

//            printf("word_cunt = %d\n",words_cunt);

//            printf("iter = %d\n",iter);
            iter = 0;
//            printf("ptr_h %p\n",ptr_h);
//            printf("-----------------------\n");
        }
    }
    return words_cunt;
}

