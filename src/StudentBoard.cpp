#include "Board.hpp"
#include "BoardValues.hpp"
#include <algorithm>
#include <iostream>

/**
 * This is a template for a Battleship game
 * board, used for both the player and PC
 */
Board::Board(){
    // Creating grid
    grid = new int[WIDTH*HEIGHT];
    for(int i = 0; i < WIDTH*HEIGHT; i++){
        grid[i] = 32; // Filling grid with ASCII of "SPACES"
    }

}

Board::Board(const Board& other){
}

Board& Board::operator=(const Board& other){
}

Board::~Board(){
    delete(grid);
}

void Board::setVisible(bool v){
    visible = v;
}

int& Board::Internal::operator[](int index){
    return _grid[index];
}

Board::Internal Board::operator[](int index){
    return Board::Internal(grid+(index * WIDTH));
}

/**
 * Overloads stream operator so you can print the
 * current board with formatting
 *
 * @param os current stream
 * @param b current board
 * @return returns stream
 */
std::ostream& operator<<(std::ostream& os, Board const& b){
    std::string value;

    // Add space between board and previous line
    os << std::endl;

    // Display first line of header
    os << "++===";
    for (int i = 0; i < WIDTH; i++) os << "====";
    if (WIDTH-1 > 9) os << "=";
    os << "++" << std::endl;

    // Display title
    os << "||";
    for (int i = 0; i < (WIDTH*2 - 8); i++) os << " ";
    os << "B A T T L E S H I P";
    for (int i = 0; i < (WIDTH*2 - 8); i++) os << " ";
    if (WIDTH-1 > 9) os << " ";
    os << "||" << std::endl;

    // Display third line of header
    os << "++===";
    for (int i = 0; i < WIDTH; i++) os << "====";
    if (WIDTH-1 > 9) os << "=";
    os << "++" << std::endl;

    // Display column numbers
    os << "|   |";
    for (int i = 0; i < WIDTH; i++) os << "   " << i;
    os << " |" << std::endl;

    // Space separators
    os << "|   |";
    for (int i = 0; i < WIDTH; i++) os << " - -";
    if (WIDTH-1 > 9) os << " ";
    os << " |" << std::endl;

    // Print each row
    for(int i = 0; i < HEIGHT; i++){
        os << "| " << i << " |";
        for(int j = 0; j < WIDTH; j++){
            if (b.visible) { // If visible print the whole board
                os << "   " << (char)b.grid[j+(i*WIDTH)];
            } else { // If not visible, exclude the ships
                int tile = b.grid[j+(i*WIDTH)];

                if (tile == CARRIER || tile == BATTLESHIP|| tile == DESTROYER
                                    || tile == SUBMARINE || tile == PATROLBOAT) {
                    os << "   " << (char)32; // Print Empty Space
                } else {
                    os << "   " << (char)b.grid[j+(i*WIDTH)]; // Printing the hits & misses
                }
            }

        }
        if (WIDTH-1 > 9) os << " ";
        os << " |"<< std::endl;
    }

    // Space separators
    os << "+ - +";
    for (int i = 0; i < WIDTH; i++) os << " - -";
    if (WIDTH-1 > 9) os << " ";
    os << " +" << std::endl;

    // Return stream once finished
    return os;
}

// Returns the amount of total hits on the board
int Board::count() const{
    int numOfHits = 0;
    for(int i = 0; i < WIDTH*HEIGHT; i++){
        if (grid[i] == HIT) numOfHits++;
    }
    return numOfHits;
}

bool Board::operator< (const Board& other){

}
