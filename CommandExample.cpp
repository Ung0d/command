#include "Command.h"
#include <iostream>

//first define a concrete type of command
class Addition : public command::Action
{
private:
    int& mSum;
    int mAdd;

public:
    Addition(int& sum, int add) : mSum(sum), mAdd(add) {}

private:
    virtual void execute() override
    {
        mSum += mAdd;
    }

    virtual void undo() override
    {
        mSum -= mAdd;
    }
};

int main()
{
    //create the manager object
    command::ActionManager manager;

    int sum = 0;

    //execute some actions
    manager.execute<Addition>(sum, 4);
    manager.execute<Addition>(sum, 11);
    manager.execute<Addition>(sum, 7);

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
