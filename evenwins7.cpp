// evenwins.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Sanshray Thapa
// St.# : 301456437
// Email: sta150@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Gamestate {
    int player_score;
    int computer_score;
    int num_matches;
    int marbles_in_middle;
    int human_marbles;
    int computer_marbles;

    Gamestate(){
        player_score = 0;
        computer_score = 0;
        num_matches = 0;
        marbles_in_middle = 27;
        human_marbles = 0;
        computer_marbles = 0;
    }
};

    enum class Player {
    human,
    computer
};

Player whose_turn;

void welcome_screen() {
    cout << "+-----------------------+\n";
    cout << "| Welcome to Even Wins! |\n";
     cout << "+-----------------------+\n";
    cout << "Even Wins is a two-person game. You start with\n";
    cout << "27 marbles in the middle of the table.\n";
    cout << "\n";
    cout << "Players alternate taking marbles from the middle.\n";
    cout << "A player can take 1 to 4 marbles on their turn, and\n";
    cout << "turns cannot be skipped. The game ends when there are\n";
    cout << "no marbles left, and the winner is the one with an even\n";
    cout << "number of marbles.";
    cout << "\n";
}

string marbles_str(int n) {
    if (n == 1) return "1 marble";
    return to_string(n) + " marbles";
}

void choose_first_player() {
   for (;;) {
        cout << "\nDo you want to play first? (y/n) --> ";
        string ans;
        cin >> ans;
        if (ans == "y") {
            whose_turn = Player::human;
            return;
        } else if (ans == "n") {
            whose_turn = Player::computer;
            return;
        } else {
            cout << "\nPlease enter 'y' if you want to play first,\n";
            cout << "or 'n' if you want to play second.\n";
        }
    }
} // choose_first_player

void next_player() {
   (whose_turn == Player::human) ? whose_turn = Player::computer : whose_turn = Player::human;
}

void print_board(Gamestate & Game) {
    cout << "\n";
    cout << " marbles in the middle: " << Game.marbles_in_middle
         << " " << string(Game.marbles_in_middle, '*') << "\n";
    cout << "    # marbles you have: " << Game.human_marbles << "\n";
    cout << "# marbles computer has: " << Game.computer_marbles << "\n";
    cout <<  "\n";
}

void computer_taunt(int random){
    if (random == 1){
        cout << "The computer wins: tremble before it's mighty brain!\n";
    }
    else if (random == 2){
        cout << "The computer wins: the probabilty of you winning is 0%\n";
    }
    else if (random == 3){
        cout << "The computer wins: one more point lost!\n";
    }
    else if (random == 4){
        cout << "The computer wins: try again but you'll still lose. \n";
    }
    else{
        cout << "The computer wins: learn how to count next time. \n";
    }
}

// returns true if s is an int, and false otherwise
// https://www.cplusplus.com/reference/string/stoi/
bool is_int(const string& s) {
    try {
        stoi(s); // throws an invalid_argument exception if conversion fails
        return true;
    } catch (...) {
        return false;
    }
}

void human_turn(Gamestate & Game) {
    // get number in range 1 to min(4, marbles_in_middle)
    int max_choice = min(4, Game.marbles_in_middle);
    cout << "It's your turn!\n";
    for(;;) {
        cout << "Marbles to take? (1 - " << max_choice << ") --> ";
        string s;
        cin >> s;
        if (!is_int(s)) {
            cout << "\n  Please enter a whole number from 1 to " << max_choice
                 << "\n";
            continue;
        }

        // convert s to an int so it can be compared
        int n = stoi(s);
        if (n < 1) {
            cout << "\n  You must take at least 1 marble\n";
            continue;
        }
        if (n > max_choice) {
            cout << "\n  You can take at most " << marbles_str(max_choice)
                 << "\n";
            continue;
        }

        cout << "\nOkay, taking " << marbles_str(n) << " ...\n";
        Game.marbles_in_middle -= n;
        Game.human_marbles += n;

        return;
    } // for
} // human_turn


// Big if statement:
// Computer will match the number of marbles the player.
// Computer will always pick one marble if it goes first.
// The purpose is to make the player have more marbles so the computer can copy.

// Big else statement:
// Computer at human marbles and marbles left.
// It capitalizes on player picking high instead of low number of marbles.
// If the computer can win with remaining marbles left, it will take all.

// Flaws: 
// 1. If both players have even number of marbles near the end, 
// the player can force the computer 
// to have odd marbles and win.
// 2. Player can usually win if they pick 1 or 2
// instead of 3 or 4 once computer stops copying.

void computer_turn(Gamestate & Game) {
    cout << "It's the computer's turn ...\n";
    int max_choice = min(4, Game.marbles_in_middle);
    int n = 0;
    // If statement to narrow scenarios down
    if ( Game.marbles_in_middle > 9){
        if(Game.human_marbles == 0){
            n = 1;
        }
        // If player only picks one marble
         else if(Game.computer_marbles == Game.human_marbles){
            n = 1;
        }
        
        else if (Game.human_marbles != 0){
            n = abs(Game.computer_marbles - Game.human_marbles);
        }
    }
   else {
       // If the computer can win with remaining marbles, it will take all
        if (((Game.marbles_in_middle + Game.computer_marbles) % 2 == 0) && ( Game.marbles_in_middle <= 4)){
            n = Game.marbles_in_middle;
        }
        else if (Game.human_marbles % 2 == 0 && Game.marbles_in_middle % 2 == 0  ){
            n = 1;
        }
         else if(Game.human_marbles % 2 == 1 && Game.marbles_in_middle % 2 == 0  ){
            n = min(2,max_choice);
        }
        else if(Game.human_marbles % 2 == 0 && Game.marbles_in_middle % 2 == 1  ){
            n = min(2,max_choice);
        }
        else if(Game.human_marbles % 2 == 1 && Game.marbles_in_middle % 2 == 1  ){
            n = min(2,max_choice);
        }
    }
    cout << "Computer takes " << marbles_str(n) << " ...\n";
    Game.marbles_in_middle -= n;
    Game.computer_marbles += n;
}

void game_over( Gamestate & Game) {
    cout << "\n";
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
         << "!! All the marbles are taken: Game Over !!\n"
         << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    print_board(Game);
    if (Game.human_marbles % 2 == 0) {
        cout << "You are the winner! Congratulations!\n";
        Game.player_score++;
    } else {
        int random = 1 + rand() % 5;
        computer_taunt(random);
        Game.computer_score++;
    }
}

void play_game(Gamestate & Game) {
    // initialize the game state
    print_board(Game);
    for (;;) {
        if (Game.marbles_in_middle == 0) {
            game_over(Game);
            return;
        } else if (whose_turn == Player::human) {
            human_turn(Game);
            print_board(Game);
            next_player();
        } else if (whose_turn == Player::computer) {
            computer_turn(Game);
            print_board(Game);
            next_player();
        }
        } // for
} // play_game

void reset(Gamestate & Game){
    Game.marbles_in_middle = 27;
    Game.human_marbles = 0;
    Game.computer_marbles = 0;
}

int main() {

    srand(time(NULL));

    Gamestate Game;

    welcome_screen();

    for(;;) {
        choose_first_player();
        play_game(Game);
        Game.num_matches++;

        // ask if the user if they want to play again
        cout << "\nWould you like to play again? (y/n) --> ";
        string again;
        cin >> again;
        if (again == "y") {
            cout << "\nOk, let's play again ...\n";
            reset(Game);
        } else {
            // Final scores
            cout << "\nStatistics";
            cout << "\n----------";
            cout << "\n  Total games = " << Game.num_matches;
            cout << "\n   Human wins = " << Game.player_score;
            cout << "\nComputer wins = " << Game.computer_score;
            cout << "\nOk, thanks for playing ... goodbye!\n\n";
            return 0;
        }
    } // for
} // main

