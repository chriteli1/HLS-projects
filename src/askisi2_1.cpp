#include <iostream>
#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"


int main(){
    ac_int<8,false> a, b;
    ac_int<9,true> c, d;
    ac_fixed<5,2,false> f;
    ac_fixed<5,4,true> g;
    

    //(a)
    std::cout << "(a)" << std::endl;

    std::cout << "First run" << std::endl;
    a = 255;
    b = a;
    c = a;
    d = a;
    ac_int<18,true> e = (a*b) + (c*d);
    std::cout << "a&b&c&d=" << a << "\n";
    std::cout << "e=" << e << "\n";
    
    std::cout << "Second run" << std::endl;

    a = 0;
    b = a;
    c = -255;
    d = -c;
    e = (a*b) + (c*d);
    std::cout << "a&b=" << a << "\n";
    std::cout << "c=" << c << "\n";
    std::cout << "d=" << d << "\n";

    std::cout << "e=" << e << "\n";
    
    //(b)
    std::cout << "(b)" << std::endl;

    f = 3.875;
    g = -7.5;
    std::cout << "f=" << f << "\n";
    std::cout << "g=" << g << "\n";
    ac_fixed<10,6,true> h = f*g;
    std::cout << "h=" << h <<"\n";

return 0;
}