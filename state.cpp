#include "state.h"

State::State(Chat* owner)
    : pChat(owner)
{
    // Nothing here
}


State::~State()
{
    // virtual base class destructor
    // nothing here
    //std::cout << "STATE Destructor called" << std::endl;
}
