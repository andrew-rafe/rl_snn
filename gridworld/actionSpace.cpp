#include "actionSpace.hpp"

using namespace rl_game;

ActionSpace::ActionSpace(int num_actions) {
    m_num_actions = num_actions;
}

std::size_t ActionSpace::size() {
    return m_num_actions;
}

int ActionSpace::sample() {
    //using rand to calculate a random move
    //DO I ASSUME SRAND HAS BEEN CALLED OR SHOULD I DO IT HERE?
    return rand() % m_num_actions;
}