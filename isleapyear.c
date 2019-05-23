#include <stdio.h>

int main(){
    int n[5] = {1900, 2000, 2004, 2012, 2018};

    for(int i = 0; i < 5; i++){
        if(n[i] % 4 == 0){
            if(n[i] % 100 == 0){
                if(n[i] % 400 == 0){
                    printf("%d was a leap year", n[i]);
                }
                else{
                    printf("%d was not a leap year", n[i]);
                }
            }
            else{
                printf("%d was not a leap year", n[i]);
            }
        }
        else{
            printf("%d was not a leap year", n[i]);
        }
    }
    
    return 0;
}