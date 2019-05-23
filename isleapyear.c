#include <stdio.h>

int main(){
    int i;
    
    scanf("%d", &i);

    if(i % 4 == 0){
        printf("%d was a leap year\n", i);
    }
    else{
        printf("%d was not a leap year\n", i);
    }
    
    return 0;