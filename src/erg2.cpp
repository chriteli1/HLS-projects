#include <iostream>
#include "ac_int.h"
class Graph{
private:
bool Adg_G[6][6];
int color[6] = {0,0,0,0,0,0};
int max;
public:
Graph(){};
#pragma hls_design top
int graph_color(bool Adg_G[6][6]){
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
    max = 0;
    for(int m=0;m<6;++m){
        if(color[m] > max){
            max = color[m];
        }
    }
    std::cout << "Colors: ";
    for(int k=0;k<6;++k){
         std::cout << color[k];
    }
    std::cout << std::endl;
    std::cout << "Number of colors needed: " << max << std::endl;
    return max;
}
};
int main() {
    bool Adg_G[6][6] =  {{0,1,0,0,1,1},
                                    {1,0,1,0,0,1},
                                    {0,1,0,1,0,0},
                                    {0,0,1,0,1,0},
                                    {1,0,0,1,0,1},
                                    {1,1,0,0,1,0}
                                   };

    int max;
    Graph test1;
    max = test1.graph_color(Adg_G);


    graph_color(Adg_G);
    return 0;


}
