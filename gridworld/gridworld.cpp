#include "gridworld.h"

using namespace rl_game;




Gridworld::Gridworld() {
    m_num_columns = 5;
    m_num_rows = 5;
    m_board = generate_game_board();
}

Gridworld::Gridworld(int num_rows, int num_columns) {
    m_num_rows = num_rows;
    m_num_columns = num_columns;
    m_board = generate_game_board();
}


Gridworld::~Gridworld() {
    //delete m_board;
}

std::vector<float> Gridworld::step(int action) {
    //Get the player grid location
    std::pair<int,int> player_coord = get_coord_from_index(m_player_index);

    if (action == 0) {
        //Move up
        player_coord.second -= (player_coord.second > 0) ? 1 : 0;
    } else if (action == 1) {
        //Move right
        player_coord.first += (player_coord.first < m_num_columns-1) ? 1 : 0;
    } else if (action == 2) {
        //Move down
        player_coord.second += (player_coord.second < m_num_rows-1) ? 1 : 0;
    } else if (action == 3) {
        //Move left
        player_coord.first -= (player_coord.first > 0) ? 1 : 0;
    }
    //Remove from last position
    //unless that last position was the goal

    m_board[m_player_index] = (m_player_index != m_exit_index) ? EMPTY : EXIT;
    m_player_index = get_index(player_coord.first, player_coord.second);
    m_board[m_player_index] = PLAYER;


    return get_state();
}

std::vector<float> Gridworld::step(int action, bool& done) {
    std::vector<float> world = step(action);
    //if the player is at the exit then the game is over
    done = (m_player_index == m_exit_index) ? true: false;
    return world;
}

std::vector<float> Gridworld::step(int action, int& reward, bool& done) {
    done = false;
    reward = 0;
    std::vector<float> world = step(action, done);
    reward = done ? 20 : -1;

    return world;
}

std::vector<float> Gridworld::get_state() {
    std::vector<float> state(m_board.begin(), m_board.end());
    return state;
}

void Gridworld::print_game_board() {
    std::string string_board = "";
    //Need to go through and populate the string row by row
    add_horizontal_gridline(string_board);
    for (int row = 0; row < m_num_rows; row++) {  
        //Print all of the individual cells for the current row
        for (int col = 0; col < m_num_columns; col++) {
            string_board += "|";
            //Figure out what item it is and add the corresponding string
            int index = get_index(col, row);
            if (m_board[index] == EMPTY) {
                string_board += EMPTY_STRING;
            } else if (m_board[index] == PLAYER) {
                string_board += PLAYER_STRING;
            } else if (m_board[index] == EXIT) {
                string_board += EXIT_STRING;
            }
        }
        string_board += "|\n";
        add_horizontal_gridline(string_board);
    }
    std::cout << string_board << std::endl;
}

//HELPER FUNCTIONS

//Will generate a 2d game board given a set of game parameters
std::vector<int> Gridworld::generate_game_board () {
    //Create the empty game board
    std::vector<int> game_board;
    //Resize the game board to the appropriate size and initialise it with an empty space
    game_board.resize(m_num_columns * m_num_rows, EMPTY);
    //Randomly place the player, pickup and exit

    //Place the player
    int x = rand() % m_num_columns;
    int y = rand() % m_num_rows;
    while(!place_item(x, y, PLAYER, game_board)) {
        x = rand() % m_num_columns;
        y = rand() % m_num_rows;
        std::cout << "Placing Player again" << std::endl;
     }
    //Set the member player index
    m_player_index = get_index(x,y);
    //Place the pickup exit
    x = rand() % m_num_columns;
    y = rand() % m_num_rows;
    while(!place_item(x, y, EXIT, game_board)) { 
        x = rand() % m_num_columns;
        y = rand() % m_num_rows;
        std::cout << "Placing Exit again" << std::endl;
    }
    //Set the member exit index
    m_exit_index = get_index(x,y);
    return game_board;
}

//Will add a horizontal gridline into a string reference
void Gridworld::add_horizontal_gridline(std::string& board) {
    unsigned int num_dashes = m_num_columns * 2 + 1;
    //Add a specific number of dashes to the game board
    for (unsigned int i = 0; i < num_dashes; i++) {
        board += "-";
    }

    //Finally we need to add the new line ready for the next row
    board += "\n";
}

// Will convert a coordinate to an index
unsigned int Gridworld::get_index(unsigned int x, unsigned int y) {
    return y * m_num_rows + x;
}

// Will convert an index into a pair of coordinates
std::pair<int,int> Gridworld::get_coord_from_index(int index) {
    //The x value is the index modded with the number of rows
    int x = index % m_num_rows;
    int y = int(index / m_num_rows);
    return {x,y};
}

//Will place an item on the board given a coordinate object and a reference to the board
bool Gridworld::place_item(int x, int y, int object, std::vector<int>& board) {
    //Get the appropriate board index
    int index = get_index(x,y);
    //Check to make sure the position of the board is empty
    if (board[index] == EMPTY) {
        //If it is then we want to add the object into it
        board[index] = object;
        return true;
    }
    //Otherwise it is an invalid position therefore need to return false
    return false;
}

void Gridworld::new_game() {
    m_board = generate_game_board();
}