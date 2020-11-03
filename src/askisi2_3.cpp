#include <iostream>
#include "ac_int.h"
#include "ac_channel.h"


void runlength_encode(ac_channel<ac_int<4,false> > &in,
 ac_channel<ac_int<4,false> > &out){
     
    if(in.available(10)){
        ac_int<4,false> count = 1;
        ac_int<4,false> number ;
        ac_int<4,false> next_number ;
        number = in.read();
            for(int j=0;j<9;++j){
                next_number = in.read();
                if(next_number != number){
                    out.write(number);
                    out.write(count);
                    count = 0;
                }
                number = next_number;
                ++count;
            }
            if(out.available(0)){
                out.write(number);
                out.write(count);
            }
                
        
    }
 }

int main(){
    ac_channel<ac_int<4,false> > in;
    ac_channel<ac_int<4,false> > out;
    for(int i=0;i<10;++i){
        in.write(2);
    
    }
    std::cout << std::endl;

    runlength_encode(in,out);
    do{
        std::cout << out.read() << " ";
    }while(out.available(1));
    std::cout << std::endl;


    for(int j=0;j<3;++j){
        in.write(2);
    }
    for(int j=0;j<2;++j){
        in.write(4);
    }
    for(int j=0;j<4;++j){
        in.write(3);
    }
    in.write(2);
    
    std::cout << std::endl;


    runlength_encode(in,out);
     do{
         std::cout << out.read() << " ";
     }while(out.available(1));
     std::cout << std::endl;

 }