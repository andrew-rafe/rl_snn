#ifndef GRIDWORLD_H
#define GRIDWORLD_H

#include <vector>
#include <string>

#include "actionSpace.hpp"

namespace rl_game {
    class Gridworld {
        private:
            //The game board
            std::vector<int> m_board;
            int m_player_index;
            int m_exit_index;
            int m_num_rows;
            int m_num_columns;


            const int EMPTY = 0;
            const std::string EMPTY_STRING = " ";
            const int PLAYER = 1;
            const std::string PLAYER_STRING = "^";
            const int EXIT = 2;
            const std::string EXIT_STRING = "X";

            //HELPER FUNCTIONS
            std::vector<int> generate_game_board();
            void add_horizontal_gridline(std::string& board);
            unsigned int get_index(unsigned int, unsigned int);
            bool place_item(int x, int y, int object, std::vector<int>& board);
            std::pair<int, int> get_coord_from_index(int index);

        public:
            //Allows for direct calls to action space functions protected through cons
            rl_game::ActionSpace action_space = ActionSpace(4);

            //Default constructor will make a 5x5 game board
            Gridworld();
            //Constructor that allows for custom row and column numbers
            Gridworld(int num_rows, int num_columns);
            //Will destroy the board
            ~Gridworld();

            //Will return the new state given an action
            std::vector<float> step(int action);
            //Will return the new state given an action and will get out the done flag
            std::vector<float> step(int action, bool& done);
            //Will return the new state vector as well as the ability to get out the reward and done flag
            std::vector<float> step(int action, int& reward, bool& done);

            std::vector<float> get_state();

            void new_game();

            //Will print the game board to the screen
            void print_game_board();
    };
}

#endif