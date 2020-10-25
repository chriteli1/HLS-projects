#include <iostream>
#include <stdlib.h>
#include <time.h>

int ones_count(int input){
    std::cout << input << "\n";
    int output = 0;
    int number[32];
    int input_temp = input;
    for(int i=0;i<32;++i){
        number[i] = input_temp%2;
        std::cout << number[i];


        input_temp = input_temp/2;
    }

    for(int j=0;j<32;++j){
        if(number[j]==1){
            ++output;
        }
    }
    return output;
}



int main(){
    int number_in;
    srand (time(NULL));
    number_in = rand() % 500;
    int out;
    out = ones_count(number_in);
    std::cout << "\n" << out << "\n";
    
    return 0;

}