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
    // Adding player ships to the ships vector
    ships.push_back(Ship(5, "Carrier", CARRIER));
    ships.push_back(Ship(4, "Battleship", BATTLESHIP));
    ships.push_back(Ship(3, "Destroyer", DESTROYER));
    ships.push_back(Ship(3, "Submarine", SUBMARINE));
    ships.push_back(Ship(2, "Patrol Boot", PATROLBOAT));

    // Adding computer ships to the ships vector
    ships.push_back(Ship(5, "Carrier", CARRIER));
    ships.push_back(Ship(4, "Battleship", BATTLESHIP));
    ships.push_back(Ship(3, "Destroyer", DESTROYER));
    ships.push_back(Ship(3, "Submarine", SUBMARINE));
    ships.push_back(Ship(2, "Patrol Boot", PATROLBOAT));
    // Set up boards

}

/**
 * Begin Game let's user and then computer setup boards then calls run()
 */
void Game::beginGame(){

    std::cout << "|------------------BATTLESHIP------------------|\n\n" <<
                 "You are playing against an AI, good luck player!\n\n" <<
                 "The Pieces are:\n" << std::endl;

    for(int i = 0; i < 5; i++) {
        std::cout << "\t" << ships.at(i) << std::endl;
    }
//    for(const Ship& s : ships){
//        std::cout << "\t" << s << std::endl;
//    }
    // Place Human Ships
    placeShips();

    // Place Computer Ships
//    placeShipsPC();


    // Finally Runs the Game
}

/**
 * Handle the human placing ships.
 */
void Game::placeShips(){
    // Loops through all 5 ships a player can place

    for(int i = 0; i < 5; i++){
        bool tryPlacement = false;
        int x, y, int_dir;
        Direction dir;
        do{
            std::cout << player << std::endl;

            // Get ship location, and ensure it is a valid placement
            std::cout << "Where do you wish to place the " << ships.at(i) << std::endl;
            while (!(std::cin>>x && std::cin>>y)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Invalid input, Please enter values between 0 and 9" << std::endl;
            }

            // Get ship location, and ensure it is a valid direction
            std::cout << "Horizontally or Vertically (0 or 1)" << std::endl;
            while (!(std::cin>>int_dir) || (int_dir!=0 && int_dir!=1)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Invalid Input, Please enter a 0 or 1" << std::endl;
            }

            if (int_dir==1) dir = VERTICAL;
            else dir = HORIZONTAL;

            // This is here because we call place from
            // placeShipsPC and don't want error messages to be sent then
            tryPlacement = place(x, y, dir, ships.at(i), player);
            if (!tryPlacement) std::cout << "ERROR: Not enough room or out of bounds, please try again" << std::endl;
        }while(!tryPlacement);
    }
}

/**
 * WARNING: THIS IS SCUFFED AF
 * Handle the computer placing ships.
 */
void Game::placeShipsPC(){
    // seed rand with current time
    time_t t;
    std::srand((unsigned)time(&t));

    // Computer ships are from index 5 to 9
    for(int i = 5; i < 10; i++){
        int x, y, int_dir;
        Direction dir;
        do {
            // Set coords of ship
            x = (std::rand() % 9);
            y = (std::rand() % 9);

            // Set direction of ship
            int_dir = std::rand() % 2;
            if (int_dir==1) dir = VERTICAL;
            else dir = HORIZONTAL;

            // Pray that it works, if not, try again
        } while(!place(x, y, dir, ships.at(i), computer));
    }
}


/**
 * Helper method that checks if it is safe to put a ship
 * at a particular spot with a particular direction.
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b){
    if(d == HORIZONTAL){
        for(int i = 0; i < s.getSpaces(); i++){ // Makes sure theres not a ship there
            if((b[y][x+i] != 32)||(x+i>9)) {
//                std::cout << "ERROR: Not enough room or out of bounds, please try again" << std::endl;
                return false;
            }
        }
        for(int i = 0; i < s.getSpaces(); i++){ // Places ship
            b[y][x+i] = s.getChr();
        }
        return true;
    }else{
        for(int i = 0; i < s.getSpaces(); i++){ // Makes sure theres not a ship there
            if((b[y+i][x] != 32)||(y+i>9)) {
//                std::cout << "ERROR: Not enough room or out of bounds, please try again" << std::endl;
                return false;
            }
        }
        for(int i = 0; i < s.getSpaces(); i++){ // Places ship
            b[y+i][x] = s.getChr();
        }
        return true;
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
