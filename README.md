# command
A convenient, single-header implementation of the command-pattern with modern c++.

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
