#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int checksum(int input){
    int output = 0;
    int number[32];
    int x;
    for(int i=0;i<10;++i){
        x = pow(10,i);
        number[i] = input / x % 10 ;
        if(i % 2 != 0){
            if(2*number[i] >=10 ){
                output = output + 2*number[i] % 10 + 2*number[i] / 10 % 10;
            }
            else{
                output = output + 2*number[i];
            }
        }
        else{
            output = output + number[i];
        }
        //std::cout << output << "\n";
    }
    
return output;
}

int main(){
    int number_in;
    srand (time(NULL));
    number_in = rand() % 4294967295;
    std::cout << number_in << "\n";
    int out;
    out = checksum(number_in);
    std::cout << "\n" << out << "\n";
    
    return 0;

}
/*
int main(){
    int number;
    number = 3561;
    int checksm;
    checksm = checksum(number);
    std::cout << checksm << "\n";
    return 0;
}
*/
