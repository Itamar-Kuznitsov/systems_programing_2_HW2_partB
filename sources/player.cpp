// imports:
#include "player.hpp"
#include <iostream>
#include <string>
using namespace ariel;
using namespace std;

/**
 * @about: Player class for CardWar game
 * @author Itamar Kuznitsov
 * @since  2023  
*/


// constructor:
Player:: Player(string name)
    : name(name), cardes_Taken(0), num_of_win(0) {}


// retirn the amount of cards in the stack
int Player:: stacksize(){
    return this->cards_stack.size();
}

// return the amount of cards each the player won
int Player:: cardesTaken(){
    return cardes_Taken;
}

// update cardesTaken amount
void Player:: set_cardesTaken(int amount){
    this->cardes_Taken += amount;
}

// set the given stack of cards to be the player play-cards packet
void Player:: set_cards_stack(stack <Card> cards_stack){
    this->cards_stack = cards_stack;
}

// return one card to the game - if there is 
Card Player:: get_card(){
    Card top_card;
    if(!cards_stack.empty()){
        top_card = this->cards_stack.top();
        this->cards_stack.pop();
    }
    return top_card;
}

// return the name of the player 
string Player:: get_name(){
    return this->name;
}

// update the amount of wining turn
void Player:: set_num_of_win(){
    this->num_of_win+= 1;
}

// return the amount of wining turn
int Player:: get_num_of_win(){
    return this->num_of_win;
}

