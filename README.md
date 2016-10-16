# command
A convenient, single-header implementation of the command-pattern with modern c++.

The command pattern provides an easy way to undo and redo actions - wrapped as objects. I use it for a game-level-editor of
myself but others may find use-cases in their own projects.


Quick how-to:

At first, you need a definite action that shall be performed. That action is an object that holds arbitrary parameters
and derives from the command::Action interface.
```
class YourAction : public command::Action
{
private: 
  //your members... 
public:
 YourAction(/* arbitrary parameters */);
 
 //override virtuals
  virtual void execute() override
    {
        //do stuff
    }

    virtual void undo() override
    {
        //revert the stuff
    }
}
```

Now create a manager object that 'remembers' all executed actions...
```
command::ActionManager manager;
```

... and execute actions as you like.
```
manager.execute<YourAction>(/* your arbitrary parameters */);
```

When you feel you did something bad, just do:
```
manager.undo();
```

And when your are like 'hey that wasnt that bad at all', just do:
```
manager.redo();
```

Undo and redo work just like in any other program you may know. You can undo the n last performed actions and redo them as you like.
Note that a call of execute<..>(..) will clear the redo-memory (removes all undo()ne actions so far).
