#include <stdio.h>
#include <stdlib.h>

int main(){
    int i;

    printf("Please enter a year: ");
    scanf("%d", &i);

    if(i % 4 == 0){
        if(i % 100 == 0){
            if(i % 400 == 0){
                printf("%d was a leap year.\n", i);
            }
            else{
                printf("%d was not a leap year.\n", i);
            }
        }
    }
    else{
        printf("%d was not a leap year.\n", i);
    }
    
    
    return 0;
}