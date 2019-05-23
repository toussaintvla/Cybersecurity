#include <stdio.h>

int main(){
    int x;

    printf("Please enter a year.\n\n");
    scanf("Year: %d\n\n", &x);
    
    if(x % 4 == 0){
        if(x % 100 == 0){
            if(x % 400 == 0){
                printf("%d was a leap year.\n", x);
            }
            else{
                printf("%d was not a leap year.\n", x);
            }
        }
    }
    else{
        printf("%d was not a leap year.\n", x);
    }
    
    return 0;
}