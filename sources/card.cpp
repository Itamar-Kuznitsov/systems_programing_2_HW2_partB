// import:
#include "card.hpp"
#include <string>
#include <iostream>

using namespace std;


/**
 * @about: Card class for CardWar game
 * @author Itamar Kuznitsov
 * @since 2023  
*/


// constructor: 
Card:: Card(int value, string type)
    : value(value), type(type) {
        // Error check for wrong card value 
        if (value > 13 || value < 1){
            throw "Error: card value out of range";
        }
        // Error check for wrong card type 
        if (type != "Clubs" && type != "Hearts" && type != "Spades" && type != "Diamonds"){
            throw "Error: card type invalid";
        }
    }

Card:: Card()
    : value(0), type(""){}


// type eof cards can be: Clubs, Hearts, Spades, Diamonds
string Card:: get_card_type(){
    return this->type;

}

// value of card can be 1 to 13
int Card:: get_card_value(){
    return this->value;
}

