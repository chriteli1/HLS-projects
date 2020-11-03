#include <iostream>
#include "ac_int.h"
#include "ac_fixed.h"

//==============================================================

template <int W>
struct CSD {
 ac_int<W,false> x_p;
 ac_int<W,false> x_m;
};


template <int W>
void csd_encode (ac_int<W,true> &num, CSD<W> &num_csd){

    // num is the input number to be encoded in CSD
    // x_p and x_m are the two bit vectors that represent the CSD number
    //ac_int<W,false> x_p;
    //ac_int<W,false> x_m;

    int carry;
    carry = 0;
    bool flag = 0;
    for(int i=0;i<W;++i) std::cout <<num[i] ;

    //std::cout << "\n" << "1:" <<num << std::endl;

    if(num < 0){
        for(int k=0;k<W-1;++k){
            if(num[k] == 1 && flag == 0) flag = 1;
            else if(flag == 1) num[k] = num[k] + 1;
            }
        
    }
    //for(int i=0;i<W;++i) std::cout <<num[i] ;

    //std::cout << "\n" << "2:" << num << std::endl;
    for(int i=0;i<W;++i){

        
        if(i == W-3){
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
        else if(i < W-3){

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
        //std::cout << "x_p:" << num_csd.x_p[i]  << std::endl;
    }
    ac_int<W,true> CSD;
    CSD = num_csd.x_p - num_csd.x_m;
    //std::cout << "x_p:" << num_csd.x_p  << std::endl;
    //std::cout << "x_m:" << num_csd.x_m  << std::endl;
    if(num < 0) CSD[W-1] = 1;
    //std::cout<< "CSD:" <<std::endl;

    for(int i=0;i<W;++i){
        std::cout << CSD[i] ;
    }
    //std::cout<< std::endl;
}
//===================================================================



template <int W>
ac_int<W,true> csd_mult (ac_int<W,true> &in, CSD<W> &constant_csd){
 // in is the input value (non constant)
 // constant_csd is the CSD representation of a constant
    
    CSD<W> num_csd;
    //csd_encode(constant_csd,num_csd);
    ac_int<W,true> y = 0;
    ac_int<W,false> shifted_in; 
    std::cout << "x_p:" << constant_csd.x_p  << std::endl;
    std::cout << "x_m:" << constant_csd.x_m  << std::endl;

    for(int i=W-3;i>=0;--i){
        if(constant_csd.x_m[i] == 1){
            
            shifted_in = in << i;
            //std::cout << "heyo0" << in  << std::endl;
            //std::cout << "heyo1" << shifted_in  << std::endl;
            y = y - shifted_in ;
            //std::cout << "heyo2" << shifted_in  << std::endl;
            
        }
        else if(constant_csd.x_p[i] == 1){
            shifted_in = in << i;
            //std::cout << "heyo3" << in  << std::endl;
            //std::cout << "heyo4" << shifted_in  << std::endl;
            y = y + shifted_in ;
            //std::cout << "heyo5" << shifted_in  << std::endl;
            
        }
        
    }
    return y;
}


int main(){
    ac_int<10,true> number;
    ac_int<10,true> x;
    ac_int<10,true> y;
    CSD<10> csd_const;
    CSD<10> num_csd;
    number = 15;
    x = -4;
    //csd_const = 10;
    csd_encode(number,num_csd);
    y = csd_mult(x,num_csd);

    std::cout << "y:" << y << std::endl;
    for(int i=0;i<10;++i){
        std::cout << y[i];
    }
    std::cout << std::endl;


    ac_int<6,false> test;
    ac_int<6,false> shifted_test;
    test = 5;
    for(int i=0;i<4;++i){
        shifted_test = test << i;
    }
    
    std::cout << shifted_test << std::endl;



    return 0;
}