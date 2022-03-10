#include "Board.hpp"
#include "Direction.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include <iostream>
#include <random>
#include <vector>

/**
 * Constructor will create the ships vector and add ships to it.
 */
Game::Game(){
    // Adding to the ships vector
    ships.push_back(Ship(5, "Carrier", CARRIER));
    ships.push_back(Ship(4, "Battleship", 66));
    ships.push_back(Ship(3, "Destroyer", 68));
    ships.push_back(Ship(3, "Submarine", 83));
    ships.push_back(Ship(2, "Patrol Boot", 80));
    //int s = player[1];
   // std::cout << s;
   std::cout << player[0][0];

}

/**
 * Begin Game let's user and then computer setup boards then calls run()
 */
void Game::beginGame(){

    std::cout << "|------------------BATTLESHIP------------------|\n\n" <<
                 "You are playing against an AI, good luck player!\n\n" <<
                 "The Pieces are:\n" << std::endl;

    for(const Ship& s : ships){
        std::cout << "\t" << s << std::endl;
    }
    std::cout << std::endl;

    // Set up boards

    std::cout << player;
    // Place Human Ships
    placeShips();

    // Place Computer Ships


    // Finally Runs the Game
}

/**
 * Handle the human placing ships.
 */
void Game::placeShips(){
    // Loops through all 5 ships a player can place
    for(int i = 0; i < 5; i++){
        int x, y, int_dir;
        Direction dir;
        do{
            std::cout << "Where do you wish to place the " << ships.at(i) << std::endl;
            std::cin >> x;
            std::cin >> y;
            std::cout << "Horizontally or Vertically (0 or 1)" << std::endl;
            std::cin >> int_dir;

            // Ensures direction is either a 0 or 1 then sets that to the direction enum
            if(int_dir != 0 && int_dir != 1){
                do{
                    std::cout << "Invalid Input, Please enter a 0 or 1" << std::endl;
                    std::cout << "Horizontally or Vertically (0 or 1)" << std::endl;
                    std::cin >> int_dir;
                }while(int_dir != 0 && int_dir != 1);
            }
            else if(int_dir == 1){
                dir = VERTICAL;
            }
            else if(int_dir == 0){
                dir = HORIZONTAL;
            }

        }while(place(x, y, dir, ships.at(i), player));
    }
}

/**
 * Handle the computer placing ships.
 */
void Game::placeShipsPC(){
}

/**
 * Helper method that checks if it is safe to put a ship
 * at a particular spot with a particular direction.
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b){
    if(d = HORIZONTAL){
        for(int i = 0; i < s.getSpaces(); i++){
            //if(player[x][y])
        }
    }else{

    }
}

/**
 * Call human turn/computer turn until someone wins.
 */
void Game::run(){
}

void Game::humanTurn(){
}

void Game::computerTurn(){
}

/**
 * Create a game instance and start.
 */
int main(int argc, char** argv){
	(void)argc;
	(void)argv;
	Game g;
	g.beginGame();

	return 0;
}
