#include <iostream>
#include "ac_int.h"
#include "ac_channel.h"
#include <stdlib.h>
#include <time.h>

typedef ac_int<4,false> Card;
class BlackJack {
private:
 // internal state
 ac_int<4,false> card_mem[5];
 ac_int<3,false> index = 0;
 ac_int<5,false> tot_points = 0;
 
public:
 // constructor - init internal state
 BlackJack() {}
 // top-level interface
 void run (ac_channel<Card> &in_card,
 bool &end_round,
 bool &win) {
     
     if(in_card.available(1)){
         
            card_mem[index] = in_card.read();
        
            if(card_mem[index] == 1) card_mem[index] = 11;
            tot_points = 0;
            for(int i=0;i<=index;++i){
                tot_points = tot_points + card_mem[i];
                }
            std::cout << "Total: " << tot_points << std::endl;
            if(index == 1 && card_mem[index] == 11 && card_mem[index-1] == 11){
                win = 1;
                end_round = 1;
            }
            else if(tot_points == 21){
                win = 1;
                end_round = 1;
            }
            else if(index == 4 || tot_points > 21){
                win = 0;
                end_round = 1;
            }
            else{
                ++index;
            }

         //}
         //else std::cout << "Game has ended!" << std::endl;
     }
 }
};

int main(){
    ac_channel<Card> in_card;
    bool end = 0;
    bool win = 0;
    ac_int<4,false> x;
    
    /*
    BlackJack game1;
    while(end == 0){
        std::cout << "Please enter the card you drew: ";
        std::cin >> x;
        if(x > 10) {
            std::cout << "Invalid card. Only 10 or below is accepted. Terminating..." << std::endl;
            break;
        }
        std::cout << std::endl;
        in_card.write(x);
        game1.run(in_card,end,win);
    }
    
    std::cout << "Game has ended!" << std::endl;
    if(win == 1) std::cout << "You won!" << std::endl;
    else std::cout << "Unlucky :(" << std::endl;
    */
    BlackJack game2;
    srand (time(NULL));
    //std::cout << x << std::endl;
    while(end == 0){
        x = rand() %10 +1;
        in_card.write(x);
        game2.run(in_card,end,win);
    }
    std::cout << "Game has ended!" << std::endl;
    if(win == 1) std::cout << "You won!" << std::endl;
    else std::cout << "Unlucky :(" << std::endl;

    return 0;
}