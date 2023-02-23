#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// function to check if unique characters in a string, does not check uppercase
int is_unique(char *str) {
    // runner o(n^2)
    printf("%c\n",str[0]); 
    int len = strlen(str);
    if (len <= 2){
        return 0;
    }
    int index = 0 ; 
    char *run = str; 
    for(int i = 0; i < strlen(str); i++){
        printf("str[%i]: %c\t",i, str[i]);
        index = i+1;
        for(index; run[index]!='\0'; index++){
            printf("run[%i]: %c\n",index, run[index]);
            if(str[i] == run[index]){
                return 0; 
            }
        }
    }
    return 1; 
}

int permutation(char *str){


}


int main(){
    // string literals are null terminated but char arrays are not
    char *str = "abdcdf";
    
    for(int i=0; i < strlen(str); i++){
        printf("index : %i %c\n", i, str[i]);
    }
    printf("=Spacing=\n");
    // same as
    for(int i=0; str[i] != '\0'; i++){
        printf("index : %i %c\n", i, str[i]);
    }
    // same as
    printf("1 %c\n", *str);
    printf("2 %c\n", *str+1);
    printf("3 %c\n", *str+2);
    printf("4 %c\n", *str+3);
    printf("5 %c\n", *str+4);
    // spacing
    printf("=Spacing=\n");
    printf("%d",is_unique("ABCDDDD"));
    return 0;
}