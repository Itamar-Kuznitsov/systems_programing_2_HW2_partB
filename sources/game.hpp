#pragma once

// import:
#include <iostream>
#include <queue>
#include "player.hpp"

using namespace ariel;

namespace ariel{
    class Game{
    public:
        // constructor:
        Game(Player&, Player&);

        // public functions:
        void shuffle_array(Card* arr);
        Card* make_cards_packet();
        void distribute_cards();
        void draw_accured();
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        string card_nickname(int);

    private:
        Player& p1;
        Player& p2;
        string last_turn;
        queue <string> game_log;
    };
}
