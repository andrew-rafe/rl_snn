#ifndef ACTION_SPACE_HPP
#define ACTION_SPACE_HPP

#include <iostream>

namespace rl_game {
    //Will hold information surrounding the actions that can be taken in an rl_game type
    class ActionSpace {
        private:
            //The number of actions in the action space
            int m_num_actions;
        public:
            //Constructor which takes the number of actions that this action space makes up
            ActionSpace(int num_actions);
            //Will get the number of actions that can be taken
            std::size_t size();
            //Will get a random action from the action space
            int sample();
    };
}

#endif