#pragma once
#include <string>
using namespace std;

class Card{
    public:
        // constructor:
        Card();
        Card(int value, string type);
        
        // public functions:
        string get_card_type();
        int get_card_value(); 
        

    private:
        // type of card - represented by number between 1 to 13 
        int value;
        // type eof cards can be: Clubs, Hearts, Spades, Diamonds
        string type;
};
