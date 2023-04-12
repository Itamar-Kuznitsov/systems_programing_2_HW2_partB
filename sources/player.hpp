#pragma once

// import:
#include <iostream>
#include <string>
#include <stack>
#include "card.hpp"
using namespace std;



namespace ariel{
    class Player{
    public:
        // constructor:
        Player(string);

        // public functions:
        int stacksize();
        int cardesTaken();
        void set_cardesTaken(int);
        void set_cards_stack(stack <Card>);
        Card get_card();
        string get_name();
        void set_num_of_win(); 
        int get_num_of_win();

    private:
        string name;
        stack <Card> cards_stack;
        int cardes_Taken;
        int num_of_win;
    };
}