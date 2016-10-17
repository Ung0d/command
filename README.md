# command
A convenient, single-header implementation of the command-pattern with modern c++.

The command pattern provides an easy way to undo and redo actions - wrapped as objects. I use it for a game-level-editor of
myself but others may find use-cases in their own projects.

To use command, just include the header and make sure you have a c++14-compiler ready.

Quick how-to:

All starts with an arbitrary free function - lets call it our action.
```
void action(/* arbitrary arguments */) {...}
```

Corresponding to each of our actions, we need an undo function taking the same arguments as 
the action. In that function we revert the stuff we did in action(..).
```
void undo(/* the same arbitrary arguments */) {...}
```

Now create a manager object that 'remembers' all executed actions...
```
command::ActionManager manager;
```

... and execute actions. We state our action-method, our undo-method and all parameters we need.
```
manager.execute(action, undo, /* arbitrary arguments */);
```

The above line does indeed the very same as just calling the action method with our arguments.
However, if you feel like you did something bad, you can undo the last performed action like this:
```
manager.undo();
```

The above code will call the undo method with the same parameters we called the action with.
If you ever feel like "hey, the last stuff wasnt that bad at all", you can redo (undo of and undo) like this:
```
manager.redo();
```

Undo and redo work just like in any other program you may know. You can undo the n last performed actions and redo them as you like.
Note that a call of execute<..>(..) will clear the redo-memory (removes all undo()ne actions so far).
