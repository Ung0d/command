#include "Command.h"
#include <iostream>

//first define an action an the corresponding undo
void add(int& sum, int add)
{
    sum += add;
}

void undo(int& sum, int add)
{
    sum -= add;
}


int main()
{
    //create the manager object
    command::ActionManager manager;

    int sum = 0;

    //execute some actions
    manager.execute(add, undo, sum, 4);
    manager.execute(add, undo, sum, 11);
    manager.execute(add, undo, sum, 7);

    std::cout << sum << std::endl;
    manager.undo();
    std::cout << sum << std::endl;
    manager.undo();
    std::cout << sum << std::endl;
    manager.redo();
    std::cout << sum << std::endl;
    manager.redo();
    std::cout << sum << std::endl;
    manager.undo();
    manager.undo();
    manager.undo();
    std::cout << sum << std::endl;

}
