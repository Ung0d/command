/**
* Action - A convenient single-file and header only implementation of the Action-pattern with modern c++.
* Copyright (C) 2016 Felix Becker - fb132550@uni-greifswald.de
*
* This software is provided 'as-is', without any express or
* implied warranty. In no event will the authors be held
* liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute
* it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgment
*    in the product documentation would be appreciated but
*    is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any
*    source distribution.
*/

#ifndef Action_H
#define Action_H

#include <deque>
#include <memory>

namespace command
{
    /** \brief An abstract base for all editor Actions than can be executed and made undone. */
    class Action
    {
        friend class ActionManager;

        private:
            /** \brief Invoke the action. */
            virtual void execute() = 0;

            /** \brief Undo the action. */
            virtual void undo() = 0;
    };


    /** \brief A manager-object for Actions that works as a stack holding a predefined number of
    * Actions. The manager offers the possibility to undo the upmost operation on the stack.
    * Access semantics: Client code cant call Action::execute() Action::undo(), only the manager can. */
    class ActionManager
    {
    private:
        unsigned mStackSize; ///<indicates how deep the "memory" of the Action-manager is
        std::deque< std::unique_ptr<Action> > mActionStack;
        std::deque< std::unique_ptr<Action> >::iterator mUndoMaker;

    public:
        ActionManager() : mStackSize(100), mUndoMaker(mActionStack.end()) {}

        /** \brief Executes a new Action of type CT. CT must be derived from the Action base class
        * and its constructor can take an arbitrary amount of parameters that are needed for the execution.
        * The Action is then constructed and executed and stored on the stack. While it is on the stack,
        * it can be undo()ne to revert its action. */
        template<typename CT, typename ... PARAM>
        inline void execute( PARAM&& ... param );

        /** \brief Undo the last performed Action. (the Action that is on top of the stack) */
        inline void undo();

        /** \brief Redo a Action that was undo()ne before. */
        inline void redo();
    };


    template<typename CT, typename ... PARAM>
    void ActionManager::execute( PARAM&& ... param )
    {
        mActionStack.erase(mUndoMaker, mActionStack.end());
        mActionStack.emplace_back(std::unique_ptr<Action>( new CT(std::forward<PARAM>(param)...) )); //constructs a new Action object on top of the stack
        mUndoMaker = mActionStack.end();
        mActionStack.back()->execute();
        if (mActionStack.size() > mStackSize)
            mActionStack.pop_front();
    }

    void ActionManager::undo()
    {
        if (mUndoMaker != mActionStack.begin()) //remember that begin == end when container is empty
        {
            mUndoMaker = std::prev(mUndoMaker);
            mUndoMaker->get()->undo();
        }
    }

    void ActionManager::redo()
    {
        if (mUndoMaker != mActionStack.end())
        {
            mUndoMaker->get()->execute();
            mUndoMaker = std::next(mUndoMaker);
        }
    }
}

#endif // Action_H
