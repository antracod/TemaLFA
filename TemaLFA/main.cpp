#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <list>

#include "write.h";


using namespace std;

ifstream in("automata.in");
ifstream inW("cuvant.in");

string states;
string alphabet;
string intitialState;
string finalStatesString;
string transition;

set<string> finalStates;
map<string, map<string, string> > allTransitions;
void createTransition(string transition)
{
    if (transition != "")
    {
        string fromState = "", toState = "", symbol = "";
        int i = 0;
        while (transition[i] != ',')
        {
            fromState = fromState + transition[i++];
        }
        i++;
        map<string, string> currentTransitionList = allTransitions[fromState];
        while (transition[i] != ',')
        {
            symbol = symbol + transition[i++];
        }
        i++;
        while (transition[i])
        {
            toState = toState + transition[i++];
        }

        currentTransitionList.emplace(symbol, toState);
        allTransitions[fromState] = currentTransitionList;
    }
}

void createFinalStatesList(string states)
{
    if (states != "")
    {
        string state = "";
        int i = 0;
        while (states[i])
        {
            if (states[i] == ',')
            {

                finalStates.emplace(state);
                state = "";
                i++;
            }
            else
            {
                state += states[i];
                i++;
            }
        }
        if (state != "")
        {

            finalStates.emplace(state);
            state = "";
            i++;
        }
    }
}




void createStatesList(string states)
{
    if (states != "")
    {
        string state = "";
        int i = 0;
        while (states[i])
        {
            if (states[i] == ',')
            {
                map<string, string> newTransitionList;

                allTransitions.emplace(state, newTransitionList);
                state = "";
                i++;
            }
            else
            {
                state += states[i];
                i++;
            }
        }
        if (state != "")
        {
            map<string, string> newTransitionList;

            allTransitions.emplace(state, newTransitionList);
            state = "";
            i++;
        }
    }
}




bool finalState(string state)
{
    if (finalStates.find(state) != finalStates.end())
    {
        return true;
    }
    return false;
}


void read()
{
    in >> states;
    in >> alphabet;
    in >> intitialState;
    in >> finalStatesString;
    while (in >> transition)
    {
        createTransition(transition);
    }
    createStatesList(states);
    createFinalStatesList(finalStatesString);
}


bool wordValidation(string word, string currentState, list<string> visitedStates, int counter, bool &hasFinished)
{
    visitedStates.push_back(currentState);
    if (counter == word.size())
    {
        if (finalState(currentState) == true)
        {
            display(visitedStates);
            hasFinished = true;
        }
    }

    string symbol = word.substr(counter, 1); //getting a letter
    auto range = allTransitions[currentState].equal_range(symbol);

    for (auto it = range.first; it != range.second; ++it)
    {
        wordValidation(word, it->second, visitedStates, counter + 1, hasFinished);
    }

    return hasFinished;
}

int main()
{
    read();

    bool finished = false;
    string word;
    inW >> word;
    if (word == "&")
    {
        if (finalStates.find(intitialState) != finalStates.end())
        {
            finished = true;
            out << intitialState << "\n";
        }
    }
    else
    {
        list<string> visitedStates;

        finished = wordValidation(word, intitialState, visitedStates, 0, finished);
    }

    final_write(finished);

    return 0;
}
