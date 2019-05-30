#include <stdio.h>
#include <stdbool.h>

//define functions 
void isaleapyear(int);
bool LeapCheck(int year);

int main(int argc, char*argv[]){
    int n;
    
    scanf("%d",&n);    
    isaleapyear(n);

    return 0;
}

bool LeapCheck(int year){
    return year % 4 == 0 && (!(year % 100 == 0) || year % 400 == 0);
}

void isaleapyear(int i){
    if(LeapCheck(i)){
        printf("%d was a leap year", i);
    }
    else{
        printf("%d was not a leap year", i);
    }
}