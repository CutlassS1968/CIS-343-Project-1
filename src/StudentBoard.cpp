#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>

Board::Board(){
    // Creating grid
    grid = new int[WIDTH*HEIGHT];
    for(int i = 0; i < WIDTH*HEIGHT; i++){
        grid[i] = 32; // Filling grid with ASCII of "SPACES"
    }

}

// What is this for?  takes in a board called other?
Board::Board(const Board& other){
}

Board& Board::operator=(const Board& other){
}

// Destructor - Free any memory back
Board::~Board(){
    delete(grid);
}

// Not sure how this ties into game will have to watch youtube
void Board::setVisible(bool v){
}

int& Board::Internal::operator[](int index){
    // Temporarily dissabled, error checking is handled in game
//    if(index >= WIDTH){
//        throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid width of " + std::to_string(WIDTH));
//    }
    return _grid[index];
}

Board::Internal Board::operator[](int index){
    // Temporarily dissabled, error checking is handled in game
//    if(index >= HEIGHT){
//        throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid height of " + std::to_string(HEIGHT));
//    }
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
    for (int i = 0; i < WIDTH; i++) os << "\t" << i;
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
            os << "\t" << (char)b.grid[j+(i*WIDTH)];
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

// Not sure probably keeping count of turns
int Board::count() const{
}

// Compares which board is winning sort of i think
bool Board::operator< (const Board& other){

}
