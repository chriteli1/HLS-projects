#include <iostream>
#include "ac_int.h"
#include "ac_channel.h"

typedef ac_int<4,false> dtype;
class RunLengthEncoder {
private:
 // internal state
 dtype count = 0;
 dtype number[10];
 //int num_ind = 0;
 dtype num_hold;
public:
 // constructor - init internal state
 
 RunLengthEncoder() {}
 // top-level interface
 void run (ac_channel<dtype> &in, ac_channel<dtype> &out) {
     
    if(in.available(1)){
        number[count] = in.read();
        if(number[0] != number[count]){
            out.write(number[0]);
            out.write(count);
            num_hold = number[count];
            ac::init_array<AC_VAL_0>(number, 10);
            number[0] = num_hold;
            count = 1;
            
        }
        else ++count;

    }
    else{
        out.write(number[0]);
        out.write(count);
    }
    
    
 }
};


int main(){
    RunLengthEncoder test1;
    RunLengthEncoder test2;
    RunLengthEncoder test3;

    ac_channel<ac_int<4,false> > in;
    ac_channel<ac_int<4,false> > out;
    srand (time(NULL));

//=============================
    for(int j=0;j<10;++j){
        in.write(12);
    }

    for(int j=0;j<11;++j){
        test1.run(in,out);
        
    }
    while(out.available(1)){
            std::cout << out.read() << " ";
        }
        std::cout << "end" << std::endl;


//=========================================
    for(int j=0;j<3;++j){
        in.write(2);
    }
    for(int j=0;j<2;++j){
        in.write(4);
    }
    in.write(2);
    for(int j=0;j<3;++j){
        in.write(3);
    }
    in.write(10);
    for(int j=0;j<11;++j){
        test2.run(in,out);
        
    }
    while(out.available(1)){
            std::cout << out.read() << " ";
        }
        std::cout << "end" << std::endl;
    //===========================================
    ac_int<4,false> random_val = rand();

    for(int j=0;j<2;++j){
        in.write(random_val);
    }
    random_val = rand();
    for(int j=0;j<2;++j){
        in.write(random_val);
    }
    random_val = rand();
    for(int j=0;j<6;++j){
        in.write(random_val);
    }
    

    for(int j=0;j<11;++j){
        test3.run(in,out);
        
    }
    while(out.available(1)){
            std::cout << out.read() << " ";
        }
        std::cout << "end" << std::endl;
    return 0;
}