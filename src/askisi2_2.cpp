#include <iostream>
#include "ac_int.h"
#include "ac_fixed.h"
#include <stdlib.h>
#include <time.h>
//==============================================================

template <int W>
struct CSD {
 ac_int<W+1,false> x_p;
 ac_int<W,false> x_m;
};


template <int W>
void csd_encode (ac_int<W,true> &num, CSD<W> &num_csd){

    int carry;
    carry = 0;
    bool flag = 0;
    
    
    for(int i=0;i<W;++i){

        if(i == W-1){
            if(carry == 1){
                if(num[i] == 1){
                num_csd.x_p[i] = 0;
                num_csd.x_m[i] = 0;
                num_csd.x_p[i+1] = 1;
                }
                else{
                    num_csd.x_p[i] = 1;
                    num_csd.x_m[i] = 0;
                }
            }
            else {
                if(num[i] == 1){
                    num_csd.x_p[i] = 1;
                    num_csd.x_m[i] = 0;
                }
                else{
                    num_csd.x_p[i] = 0;
                    num_csd.x_m[i] = 0;
                }
            }
            
        }
        else if(i < W-1){

            if(carry == 0){
                if(num[i] == 0){
                    num_csd.x_p[i] = 0;
                    num_csd.x_m[i] = 0;
                    carry = 0; 
                    }
                else {
                    if(num[i+1] == 0){
                        num_csd.x_p[i] = 1;
                        num_csd.x_m[i] = 0;
                        carry = 0;
                    }
                    else{
                        num_csd.x_p[i] = 0;
                        num_csd.x_m[i] = 1;
                        carry = 1;
                    }
                }
                
            }
            else{
                if(num[i] == 1){
                    num_csd.x_p[i] = 0;
                    num_csd.x_m[i] = 0;
                    carry = 1;
                }
                else {
                    if(num[i+1] == 0){
                        num_csd.x_p[i] = 1;
                        num_csd.x_m[i] = 0;
                        carry =0;
                    }
                    else{
                        num_csd.x_p[i] = 0;
                        num_csd.x_m[i] = 1;
                        carry = 1;
                    }
                }
            }
        }
        else{
            num_csd.x_p[i] = 0;
            num_csd.x_m[i] = 0;
            }
        
    }
    ac_int<W,true> CSD;
    CSD = num_csd.x_p - num_csd.x_m;
    std::cout << "x_p:" << num_csd.x_p  << std::endl;
    std::cout << "x_m:" << num_csd.x_m  << std::endl;
    std::cout << "Number after CSD:" << CSD << std::endl;
    std::cout << "Number in Binary:";
    for(int i=0;i<W;++i){
        std::cout << CSD[i] ;
    }
    std::cout << std::endl;
}
//===================================================================



template <int W>
ac_int<2*W,true> csd_mult (ac_int<W,true> &in, CSD<W> &constant_csd){
    
    ac_int<W,true> num_csd;
    num_csd = constant_csd.x_p - constant_csd.x_m;
    ac_int<2*W,true> y = 0;
    ac_int<2*W,false> y2 = 0;
    ac_int<W,false> shifted_in; 
    ac_int<W+1,false> twos_power1 = pow(2,W);
    ac_int<2*W,false> twos_power2 = pow(2,2*W);
    ac_int<W,true> in_temp = in;
    ac_int<W,true> num_temp = num_csd;

    
    if(num_csd < 0){
        num_csd = twos_power1 - num_csd;
        num_csd[W-1] = 0;
    }
    
    if(in < 0){
        in = twos_power1 - in;
        in[W-1] = 0;
    }

    

    csd_encode(num_csd,constant_csd);
    if(constant_csd.x_p[W] == 1){
        shifted_in = in << W;
        y = y + shifted_in ;
    }
    for(int i=W-1;i>=0;--i){
        if(constant_csd.x_m[i] == 1){
            
            shifted_in = in << i;
            
            y = y - shifted_in ;
            
            
        }
        else if(constant_csd.x_p[i] == 1){
            shifted_in = in << i;
            y = y + shifted_in ;
           
        }
    }
    
    bool flag = 0;
    if(in_temp[W-1] != num_temp[W-1]){
        for(int i=0;i<2*W;++i){
            if(y[i] == 1 && flag == 0)flag = 1;
            else if(flag == 1)y[i] = y[i] -1;
            
        }        
        
    }
        
    
    
    
    
   
    return y;
}


int main(){
    ac_int<10,true> number;
    ac_int<10,true> x;
    ac_int<20,true> y;
    
    CSD<10> num_csd;
    srand (time(NULL));

    ac_int<7,true> rand_num = rand();
    number =  rand_num;
    x = -4;
    std::cout << "Mult in:" << x << std::endl;
    std::cout << "Number:" << number << std::endl;
    csd_encode(number,num_csd);
    y = csd_mult(x,num_csd);
    
    
    std::cout << std::endl;
    
    std::cout << "y:" << y << std::endl;
    std::cout << "y(in binary):";
    for(int i=0;i<20;++i){
        std::cout << y[i];
    }
    std::cout << std::endl;

    return 0;
}