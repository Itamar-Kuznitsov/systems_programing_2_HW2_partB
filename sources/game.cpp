// import:
#include "game.hpp"
#include "card.hpp"
#include <iostream>
#include <stack>
#include <queue>
#include <random>
#include <ctime>

using namespace ariel;
using namespace std;
#define CARDS_ARRAY_SIZE 52
static int count_cards = 0;
bool draw = false;
static int draw_amount = 0;
static int play_amount = 0;

/**
 * @about: Game class for CardWar game
 * @author Itamar Kuznitsov
 * @since  2023  
*/


// constructor:
Game:: Game(Player& player1, Player& player2)
    : p1(player1), p2(player2) {
        // // Logicly - the error check for game with same players should be here, but due to the auto tests I replaced it in the PlayTurn() function...  
        // if (&player1 == &player2){
        //     throw "Error: player1 and player2 are the same player";
        // }

        // init func call
        distribute_cards();
    }
    



// function that shuffle the array of cards - based on self learn from https://www.javatpoint.com/cpp-algorithm-shuffle-function
void Game::shuffle_array(Card* array) {
  std::mt19937 rng(static_cast<uint32_t>(std::time(nullptr)));
  std::shuffle(array, array + CARDS_ARRAY_SIZE, rng);
}


// return array of cards for new packet
Card* Game:: make_cards_packet(){
  string types[4] = {"Clubs", "Hearts", "Spades", "Diamonds"};
  static Card cards_array[CARDS_ARRAY_SIZE];
  string type;
  int idx = 0;

  for(int i=0; i<4; i++){
    type = types[i];  
    
    for(int j=1; j<=13; j++){
      // new card 
      Card tmp(j,type);
      cards_array[idx] = tmp;
      idx++; 
    }
  }

  return cards_array;
}


// make two stacks of cards for game inisialization
void Game:: distribute_cards(){
    Card* cards_array= make_cards_packet();
    shuffle_array(cards_array);

    stack <Card> stack_1;
    stack <Card> stack_2;

    // dividing the array to 2 stacks 
    for(int i=0; i<CARDS_ARRAY_SIZE; i++){
        if (i<CARDS_ARRAY_SIZE/2){
            stack_1.push(cards_array[i]);
        }
        else{
            stack_2.push(cards_array[i]);
        }
    }
   
    // initializtion of player 1 and 2 cards stack 
    this->p1.set_cards_stack(stack_1);
    this->p2.set_cards_stack(stack_2);
}


// assistance function - return string of playing-card nickname
string Game:: card_nickname(int card_value){
    if(card_value == 1)
        return "Ace";

    else if(card_value == 11)
        return "Jack";

    else if(card_value == 12)
        return "Queen";
    
    else if(card_value == 13)
        return "King";
        
    else
        return to_string(card_value);
}



// make (play) one turn
void Game:: playTurn(){
    // Error check for activating another turn after the game is over
    if(this->p1.stacksize() == 0 || this->p2.stacksize() == 0){
        throw "Error: You try to activate another turn after the game is over";
    }
    // Error check for game with same players - logicly should be in the constructore insted of here 
    if (&this->p1 == &this->p2){
        throw "Error: player1 and player2 are the same player";
    }

    // each player pop card from his stack of cards
    Card c1 = this->p1.get_card();
    Card c2 = this->p2.get_card();
    string data = "";
    play_amount+= 1;



    // resposible for the amout of cards that a player will take
    if(!draw){
        count_cards = 2;
    }
    else if(draw){
        count_cards+= 4;
    }

    // case_1: p1 won
    if(c1.get_card_value() > c2.get_card_value()){
        this->p1.set_cardesTaken(count_cards);
        data = p1.get_name() + " played " + card_nickname(c1.get_card_value()) + " of " + c1.get_card_type() + " " + p2.get_name() + " played " + card_nickname(c2.get_card_value()) + " of " + c2.get_card_type() + ". " + p1.get_name() + " wins.";
        draw = false;
        // add 1 to wining counter
        this->p1.set_num_of_win();

        // update game printing log 
        this->last_turn = data;
        this->game_log.push(data);
    }

    // case_2: p2 won
    else if(c1.get_card_value() < c2.get_card_value()){
        this->p2.set_cardesTaken(count_cards);
        data = p1.get_name() + " played " + card_nickname(c1.get_card_value()) + " of " + c1.get_card_type() + " " + p2.get_name() + " played " + card_nickname(c2.get_card_value()) + " of " + c2.get_card_type() + ". " + p2.get_name() + " wins.";
        draw = false;
        // add 1 to wining counter
        this->p2.set_num_of_win();

        // update game printing log 
        this->last_turn = data;
        this->game_log.push(data);
    }

    // case_3: draw
    else if(c1.get_card_value() == c2.get_card_value()){
        draw = true;
        data = p1.get_name() + " played " + card_nickname(c1.get_card_value()) + " of " + c1.get_card_type() + " " + p2.get_name() + " played " + card_nickname(c2.get_card_value()) + " of " + c2.get_card_type() + ". " "Draw.";
        this->last_turn = data;
        this->game_log.push(data);
        draw_amount+= 1;
        draw_accured();
    }
}


// if draw accured - try to open another card and then play another turn
void Game:: draw_accured(){
    // if there are still cards in the stacks
    if(this->p1.stacksize() != 0 && this->p2.stacksize() != 0){
        // each player pop card from his stack of cards upsitdown
        this->p1.get_card();
        this->p2.get_card();

        if(this->p1.stacksize() != 0 && this->p2.stacksize() != 0){
            // playing another game
            playTurn();
        }

        // there are not enough cards for another play
        else{
            p1.set_cardesTaken(1);
            p2.set_cardesTaken(1);

            // if there are still cards in stack of one player - add them to his cardesTaken
            if(this->p1.stacksize() != 0){
                p1.set_cardesTaken(p1.stacksize());
            }

            else if(this->p2.stacksize() != 0){
                p2.set_cardesTaken(p2.stacksize());
            }    
        }
    }
    
    // if one stack is empty
    else{
        if(this->p1.stacksize() != 0){
            p1.set_cardesTaken(p1.stacksize());
        }

        else if(this->p2.stacksize() != 0){
            p2.set_cardesTaken(p2.stacksize());
        }
    }

}


// print the last turn data
void Game:: printLastTurn(){
    cout << this->last_turn << "\n";
}


// run the game until one of the player dont have cards 
void Game:: playAll(){
    while(this->p1.stacksize() != 0 && this->p2.stacksize() != 0){
        playTurn();
    }
}


// print the winner of the game based on amount of cardesTaken
void Game:: printWiner(){
    if(this->p1.cardesTaken() > this->p2.cardesTaken()){
        cout << "The winning player is: " + p1.get_name() << "\n";
    }

    else if(this->p1.cardesTaken() < this->p2.cardesTaken()){
        cout << "The winning player is: " + p2.get_name() << "\n";
    }

    else{
        cout << "There is no winner: Draw" << "\n";
    }
}


// print all turns data from the game by game_log queue
void Game:: printLog(){
    while(!game_log.empty()) {
        cout << game_log.front() << "\n";
        game_log.pop();
    }
}


// print for each player statistics data about the game 
void Game:: printStats(){
    cout << "\n\n ########### Player No.1 statistics ########### \n\n";
    cout << "Win rate: " + to_string(this->p1.get_num_of_win()) + "/" + to_string(this->p1.get_num_of_win()+ this->p2.get_num_of_win()) << "\n";
    cout << "Cards won: " + to_string(this->p1.cardesTaken()) << "\n";
    cout << "Draw rate: " + to_string(draw_amount) + "/" + to_string(play_amount-draw_amount) << "\n";
    cout << "Draw amount: " + to_string(draw_amount) << "\n";


    cout << "\n\n ########### Player No.2 statistics ########### \n\n";
    cout << "Win rate: " + to_string(this->p2.get_num_of_win()) + "/" + to_string(this->p1.get_num_of_win()+ this->p2.get_num_of_win()) << "\n";
    cout << "Cards won: " + to_string(this->p2.cardesTaken()) << "\n";
    cout << "Draw rate: " + to_string(draw_amount) + "/" + to_string(play_amount-draw_amount) << "\n";
    cout << "Draw amount: " + to_string(draw_amount) << "\n";
}




