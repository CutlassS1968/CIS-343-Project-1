#include "Board.hpp"
#include "Direction.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include <iostream>
#include <random>
#include <vector>
#include <ctime>

// TODO: Something is off with the placement of ships for the PC, need to look it over
/**
 * Constructor will create the ships vector and add ships to it.
 */
Game::Game(){
    // Adding player ships to the ships vector
    ships.emplace_back(5, "Carrier", CARRIER);
    ships.emplace_back(4, "Battleship", BATTLESHIP);
    ships.emplace_back(3, "Destroyer", DESTROYER);
    ships.emplace_back(3, "Submarine", SUBMARINE);
    ships.emplace_back(2, "Patrol Boot", PATROLBOAT);

    // Adding computer ships to the ships vector
    ships.emplace_back(5, "Carrier", CARRIER);
    ships.emplace_back(4, "Battleship", BATTLESHIP);
    ships.emplace_back(3, "Destroyer", DESTROYER);
    ships.emplace_back(3, "Submarine", SUBMARINE);
    ships.emplace_back(2, "Patrol Boot", PATROLBOAT);
    // Set up boards

}

/**
 * Begin Game let's user and then computer setup boards then calls run()
 */
void Game::beginGame(){

    std::cout << "|------------------BATTLESHIP------------------|\n\n" <<
                 "You are playing against an AI, good luck player!\n\n" <<
                 "The Pieces are:\n" << std::endl;

    // List player ships (0-4)
    for(int i = 0; i < 5; i++) {
        std::cout << "\t" << ships.at(i) << std::endl;
    }

    // Place Human Ships
    player.setVisible(true);
    placeShips();
    //std::cout << player << std::endl;
    // Place Computer Ships
    computer.setVisible(true);
    placeShipsPC();
    std::cout << computer << std::endl;
    computer.setVisible(false);
   // std::cout << computer << std::endl;

    // Finally Runs the Game
    run();
}

/**
 * Handle the human placing ships.
 */
void Game::placeShips(){
    bool tryPlacement;
    int x, y, int_dir;
    Direction dir;

    // Loops through all 5 ships a player can place
    for(int i = 0; i < 5; i++){
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
        } while (!tryPlacement);
    }
}

/**
 * Handle the computer placing ships.
 */
void Game::placeShipsPC(){
    // We found this article to help with the implementation of the uniform distribution:
    //  https://spc.unige.ch/en/teaching/courses/algorithmes-probabilistes/random-numbers-week-1/

    // Set up two uniform distributions with bounds appropriate to each use
    // Seed each distribution with a random engine.
    std::default_random_engine coordGen;
    std::uniform_int_distribution<int> coordDist(0,9);

    std::default_random_engine dirGen;
    std::uniform_int_distribution<int> dirDist(0,1);

    bool tryPlacement;
    int x, y, int_dir;
    Direction dir;

    // Computer ships are from index 5 to 9
    for(int i = 5; i < 10; i++){
        do {
            // Set coords of ship
            x = coordDist(coordGen);
            y = coordDist(coordGen);

            // Set direction of ship
            if (dirDist(dirGen)==1) dir = VERTICAL;
            else dir = HORIZONTAL;

            // Pray that it works, if not, try again
            tryPlacement = place(x, y, dir, ships.at(i), computer);
        } while(!tryPlacement);
    }
}


/**
 * Helper method that checks if it is safe to put a ship
 * at a particular spot with a particular direction.
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b){
    if(x>WIDTH-1 || y>HEIGHT-1) return false;
    if(d == HORIZONTAL){
        // Makes sure theres not a ship there and doesn't overlap border
        for (int i = 0; i < s.getSpaces(); i++) if((b[y][x+i] != 32)||(x+i>(WIDTH-1))) return false;
        // Place Ships
        for (int i = 0; i < s.getSpaces(); i++) b[y][x+i] = s.getChr();
        return true;
    } else {
        // Makes sure theres not a ship there and doesn't overlap border
        for (int i = 0; i < s.getSpaces(); i++) if((b[y+i][x] != 32)||(y+i>(HEIGHT-1))) return false;
        // Place Ships
        for (int i = 0; i < s.getSpaces(); i++) b[y+i][x] = s.getChr();
        return true;
    }
}

/**
 * Call human turn/computer turn until someone wins.
 */
void Game::run(){

    // Prints the boads every turn
    bool endGame = false;

    // Gets total number of spaces hit needed to win
    int win = 0;
    for (int i = 0; i < 5; i++) {
        win += ships.at(i).getSpaces();
    }

    do {
        std::cout << player << std::endl;
        std::cout << computer << std::endl;
        std::cout << "Score: " << win-computer.count() << " to " << win-player.count() << std::endl;

        // Do the human turn
        humanTurn();

        computerTurn();

        // TODO: make winning not scuffed
        /** NEED TO ACTUALLY MAKE IT SO THAT THERE ARE WINS OR DRAWS AND STUFF BETTER IF STATEMENT HERE **/
        if (player.count() == win)  {
            std::cout << "\n\n\n\n\nYOU LOSE\n\n\n\n";
            endGame = true;
        }

        // If the person has won
        if (computer.count() == win)  {
            std::cout << "\n\n\n\n\nYOU WIN\n\n\n\n";
            endGame = true;
        }

    } while (!endGame);
    // Display both boards with visible function

}

void Game::humanTurn(){
    std::cout << "What coordinate would you like to attack: " << std::endl;
    int x, y;
    while (!(std::cin>>x && std::cin>>y)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input, Please enter values between 0 and 9" << std::endl;
    }

    if (computer[y][x] != 32) { // If not a space must have sunk a ship
        int ship_index = -1;

        // Gets the ship you just hit!
        for (int i = 5; i < 10; i++) {
            if (computer[y][x] == ships.at(i).getChr()) {
                ship_index = i;
                break;
            }
        }

        // If you find the ship
        if (ship_index != -1) {
            try {
                ships.at(ship_index).addHit(); // Adds hit to ship
            } catch (SunkShipException e) {
                std::cout << "Congrats you sank a " << ships.at(ship_index).getName() << std::endl;
            }
            computer[y][x] = HIT; // Adds hit to board
        } else { // You must have hit a MISS or an already HIT ship
            std::cout << "You already hit there are you dumb? Oh well you wasted a turn" << std::endl;
        }

    } else {
        computer[y][x] = MISS;
    }

}

void Game::computerTurn(){
    std::default_random_engine coordGen;
    std::uniform_int_distribution<int> coordDist(0,9);

    int x = coordDist(coordGen);
    int y = coordDist(coordGen);

    if (player[y][x] != 32) { // If not a space must have sunk a ship
        int ship_index = -1;

        // Gets the ship you just hit!
        for (int i = 0; i < 5; i++) {
            if (player[y][x] == ships.at(i).getChr()) {
                ship_index = i;
                break;
            }
        }

        // If you find the ship
        if (ship_index != -1) {
            try {
                ships.at(ship_index).addHit(); // Adds hit to ship
            } catch (SunkShipException e) {
                std::cout << "The Computer sank your " << ships.at(ship_index).getName() << std::endl;
            }
            player[y][x] = HIT; // Adds hit to board
        } else { // You must have hit a MISS or an already HIT ship
            std::cout << "The Computer hit you in the same spot! Sucks for them! Your turn now" << std::endl;
        }

    } else {
        player[y][x] = MISS;
    }
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
