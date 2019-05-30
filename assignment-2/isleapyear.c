#include <stdio.h>

int main(int argc, char*argv[]){
    int i;
    
    scanf("%d",&i);

    if(i % 4 == 0){
        if(i % 100 == 0){
            if(i % 400 == 0){
                printf("%d was a leap year", i);
            }
            else{
                printf("%d was not a leap year", i);
            }
        }
        else{
                printf("%d was a leap year", i);
        }
    }
    else{
        printf("%d was not a leap year", i);
    }

    return 0;
}

