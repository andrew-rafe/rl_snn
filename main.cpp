#include <iostream>
#include <ctime>
#include <string>
#include <vector>

#include "gridworld/gridworld.h"
#include "snn/network.h"

int main(int argc, char* argv[]) {
    //Seed randomness
    srand(time(0));

    //Create a new game
    int width = 5;
    int height = 5;
    rl_game::Gridworld* game = new rl_game::Gridworld(width, height);

    //Create a new network
    std::cout << "Generating Network" << std::endl;
    std::vector<int> neurons_per_layer = {width * height, int(game->action_space.size())};
    SNN::Network* network = new SNN::Network(neurons_per_layer.size(), neurons_per_layer);
    std::cout << "Network Generated!" << std::endl;

    game->print_game_board();
    std::vector<float> state = game->get_state();
    bool done = false;
    int total_reward = 0;
    int curr_reward = 0;
    long long timestep = 0;
    while (!done && timestep < 100) {
        //process the inputs in the network
        if (timestep == 0) {
            for (int i = 0; i < 20; i++) {
            network->process_inputs(state, timestep, state.size());
            timestep++;
            }
        } else {
            network->process_inputs(state, timestep, state.size());
        }
        
        int action = network->get_action();
        std::cout << "Action: " << action << std::endl;
        state = game->step(action, curr_reward, done);
        total_reward += curr_reward;
        game->print_game_board();
        timestep++;
    }

    std::cout << "Total Reward: " << total_reward << std::endl;

    delete game;
    delete network;

    return EXIT_SUCCESS;
} 

