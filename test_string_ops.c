#include <string_ops.h>
#include <stdio.h>
#include <malloc.h>

void simple(char *test){
    int len = str_len(test);
    printf("str_len: %i\n", len);
    int tokens = count_tokens(test, ',');
    printf("tokens: %i\n", tokens);
    int to = str_len_to(test,',',0);
    printf("dist: %i\n", to);

    char copy[125] = {'\0'};
    printf("copy init len: %i\n", str_len(copy));
    str_cpy(test, copy);
    printf("copy len: %i\n", str_len(copy));
    printf("copy text: %s\n", copy);
    str_zero(copy);
    printf("copy zeroed: %s len: %i\n", copy, str_len(copy));
}

void complex(char *test){
    int elements;
    char **splits = str_split(test, ',', &elements);
    int i;
    for(i=0; i<elements; i++){
        printf("split %i: %s\n", i, splits[i]);
    }
    free_split(splits, elements);
}

void double_split(char *test){
    int i, el, s_el;
    char **split = str_split(test, ',', &el);
    char **sub;

    for(i=0; i<el; i++){

        sub = str_split(split[i], '=', &s_el);
        if(s_el == 2) printf("key: %s\tval: %s\n",sub[0], sub[1]);
        free_split(sub, s_el);
    }
    
    free_split(split, el);
}

int main(){
    char test[] = "kciks, Hello=10,all=99,loo=89,poo=87,doo=88,90129930i12, like=10,your=11,mmom=12,her=87,girl=100,hu dur=10,x=90";
    malloc_stats();
    simple(test);
    complex(test);
    double_split(test);
    malloc_stats();
    printf("testing complete\n");

    return 0;
}