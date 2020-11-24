#include <iostream>
#include "ac_int.h"

void graph_color(ac_int<1,false> Adg_G[6][6]){
    int color[6] = {0,0,0,0,0,0};
    int c;
    for(int i=0;i<6;++i){
        c = 1;
        for(int j=0;j<6;++j){
            
            if(Adg_G[i][j] == 1){
                if(color[j] == c){
                    ++c;
                }
            }
        }
        color[i] = c;
        
    }
    std::cout << "Colors: ";
    for(int k=0;k<6;++k){
         std::cout << color[k];
    }
    std::cout << std::endl;
}

int main() {
    ac_int<1,false> Adg_G[6][6] =  {{0,1,0,0,1,1},
                                    {1,0,1,0,0,1},
                                    {0,1,0,1,0,0},
                                    {0,0,1,0,1,0},
                                    {1,0,0,1,0,1},
                                    {1,1,0,0,1,0}
                                   };

    graph_color(Adg_G);

}