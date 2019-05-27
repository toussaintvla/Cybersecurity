#include <stdio.h>

void isleapyear(int);

int main(int argc, char*argv[])
{
    int n[] = {1900, 2000, 2004, 2012, 2018 };
    int l = sizeof(n) / 4;
    int i, y;

    for(i = 0; i < l;i++)
        y = n[i];
        isleapyear(y);

    return 0;
}

void isleapyear(int i){
    if(i % 4 == 0){
        if(i % 100 == 0){
            if(i % 400 == 0){
                printf("%d was a leap year", i);
            }
            else{
                printf("%d was not a leap year", i);
            }
        }
    }
    else{
        printf("%d was not a leap year", i);
    }
}   
