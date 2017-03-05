#include <iostream>
#include <cstdio>
#include <cstdlib>

//Things I'm including
#include <vector>
#include <algorithm>
#include "lexer.h"

using namespace std;

/****************
 * My variables *
 ****************/
//testing variables
int loopBreak = 0; //to prevent infinite loops while testing
const int loopMax = 10; //In case I need to change loop iterations
int universe_size = 0;
bool testing = true; //to avoid having to comment things out
bool testInput = false;
bool testRules = true;
bool test0 = false;
bool test1 = true;
bool test2 = true;
bool test3 = true;
bool test4 = true;
bool test5 = true;
bool testElement = false;
bool testPrint = false;
bool testGenerating = false;
bool testLabel = false;
bool testReach = true;
bool testUseless = true;


//non-testing variables
LexicalAnalyzer lexer;
Token token;
vector<Token> terms;
vector<Token> nonTerms;
vector< vector<Token> > ruleList;
vector< vector<Token> > RHS_List;
vector< vector<Token> > LHS_List;

vector<Token> universe;
vector<Token> universeFF; //FIRST & FOLLOW universe
//Iterating through vectors
vector<Token>::iterator iter;
vector<Token>::iterator iterNest;
vector< vector<Token> >::iterator vecTokIter;

//From powerpoint
bool is_element(vector<bool> S, int i)
{
    if(testElement)
        cout << "checking elements" << endl;
    int max = (int)S.size();
    if((i >= 0) && (i < max))
    {
        if (testElement)
        {
            cout << "S.size() = " << S.size() << endl;
            cout << "S[" << i << "] = " << S[i] << endl;
        }
        return S[i];
    }
    else
    {
        if(testElement)
            cout << "element out of range" << endl;
        return false;
    }
}

//From powerpoint
//Powerpoint has this as a bool but doesn't return true or false?
void print_set(vector<bool> S)
{
    if(testPrint)
        cout << "printing" << endl;
    int max = (int)S.size();
    for(int i = 0; i < max; i++)
        if(is_element(S, i))
            cout << universe.at(i).lexeme << " ";
    cout << "" << endl;
    if(testPrint)
        cout << "done printing" << endl;
}

//Default function
vector< vector<int> > labelRules()
{
    if(testLabel)
        cout << "Testing labelRules" << endl;

    int tempLoop = 0;
    int ruleNum = -1;
    int uniPosIter = 1;
    vector<vector<int> > rulePos;

    //Look at each rule (vecTokIter)
    for (vecTokIter = ruleList.begin(); vecTokIter != ruleList.end(); ++vecTokIter)
    {
        ruleNum++;
        vector<int> uniPos;
        //Look at each token (iter) in each rule (vecTokIter)
        for (iter = vecTokIter->begin(); iter != vecTokIter->end(); ++iter)
        {
            //Look at each universe item
            for (iterNest = universe.begin() + 2; iterNest != universe.end(); ++iterNest)
            {
                uniPosIter++;

                if(testLabel)
                {
                    cout << "loop #" << to_string(tempLoop) << endl;
                    cout << "Current lexeme = " << iter->lexeme << endl;
                    cout << "uniPosIter = " << to_string(uniPosIter) << endl;
                    tempLoop++;
                }

                //if current universe item (iterNest) matches current token (iter) in current rule (vecTokIter)
                if (iterNest->lexeme == iter->lexeme)
                {
                    //add the universe position to the rules
                    uniPos.push_back(uniPosIter);
                    if(testLabel)
                        cout << "Found! uniPosIter = " << to_string(uniPosIter) << endl;
                }
                else if(testLabel)
                {
                    cout << "no match found" << endl;
                }
            }
            if(testLabel)
            {
                cout << "uniPos = ";
                for (vector<int>::iterator iter = uniPos.begin(); iter != uniPos.end(); ++iter)
                    cout << to_string(*iter) << ' ';
                cout << "" << endl;
            }
            uniPosIter = 1;
        }
        rulePos.push_back(uniPos);

        if(testLabel)
        {
            for (vector<int>::iterator iter = uniPos.begin(); iter != uniPos.end(); ++iter)
                cout << to_string(*iter) << ' ';

            cout << "" << endl;
        }
    }

    if(testLabel)
        cout << "Done testing labelRules" << endl;
    return rulePos;

}

//Parameterized function
vector< vector<int> > labelRules(vector<bool> usedSymbols)
{
    if(testLabel)
        cout << "Testing labelRules" << endl;

    vector<Token> newUni;


    for(int i = 0; i < universe_size; i++)
        if(usedSymbols[i])
            newUni.push_back(universe[i]);

    int tempLoop = 0;
    int ruleNum = -1;
    int uniPosIter = 1;
    vector<vector<int> > rulePos;

    //Look at each rule (vecTokIter)
    for (vecTokIter = ruleList.begin(); vecTokIter != ruleList.end(); ++vecTokIter)
    {
        ruleNum++;
        vector<int> uniPos;
        //Look at each token (iter) in each rule (vecTokIter)
        for (iter = vecTokIter->begin(); iter != vecTokIter->end(); ++iter)
        {
            //Look at each universe item
            for (iterNest = newUni.begin() + 2; iterNest != newUni.end(); ++iterNest)
            {
                uniPosIter++;

                if(testLabel)
                {
                    cout << "loop #" << to_string(tempLoop) << endl;
                    cout << "Current lexeme = " << iter->lexeme << endl;
                    cout << "uniPosIter = " << to_string(uniPosIter) << endl;
                    tempLoop++;
                }

                //if current universe item (iterNest) matches current token (iter) in current rule (vecTokIter)
                if (iterNest->lexeme == iter->lexeme)
                {
                    //add the universe position to the rules
                    uniPos.push_back(uniPosIter);
                    if(testLabel)
                        cout << "Found! uniPosIter = " << to_string(uniPosIter) << endl;
                }
                else if(testLabel)
                {
                    cout << "no match found" << endl;
                }
            }
            if(testLabel)
            {
                cout << "uniPos = ";
                for (vector<int>::iterator iter = uniPos.begin(); iter != uniPos.end(); ++iter)
                    cout << to_string(*iter) << ' ';
                cout << "" << endl;
            }
            uniPosIter = 1;
        }
        rulePos.push_back(uniPos);

        if(testLabel)
        {
            for (vector<int>::iterator iter = uniPos.begin(); iter != uniPos.end(); ++iter)
                cout << to_string(*iter) << ' ';

            cout << "" << endl;
        }
    }

    if(testLabel)
        cout << "Done testing labelRules" << endl;
    return rulePos;

}

string ruleCounter()
{
    string output = "";
    bool counted = false;
    int useCount = 0;
    int ruleNum = -1;
    int uniPos = 1;
    vector< vector<int> > rulePos;


    //Look at each item in universe
    for(iter = universe.begin() + 2; iter != universe.end(); ++iter)
    {
        uniPos++;
        //Look at each rule (vecTokIter)
        for(vecTokIter = ruleList.begin(); vecTokIter != ruleList.end(); ++vecTokIter)
        {
            ruleNum++;
            vector<int> lPos;
            //Look at each token (iterNest) in each rule (vecTokIter)
            for(iterNest = vecTokIter->begin(); iterNest != vecTokIter->end(); ++iterNest)
            {
                //if current token (iterNest) in current rule (vecTokIter) matches current token in universe (iter)
                if(iterNest->lexeme == iter->lexeme)
                {
                    //counting # of rules it appears in, not # of times it appears
                    if(!counted)
                    {
                        useCount++;
                        counted = true;
                    }

                    //add the universe position to the rules
                    lPos.push_back(uniPos);
                }

            }
            counted = false;
        }

        output += iter->lexeme;
        output += ": ";
        output += to_string(useCount);
        output += "\n";
        useCount = 0;
    }

    return output;
}

//Alternate ruleCounter function
/**
 * bitvector marking rule numbers for LHSs
 * bitVector marking rule numbers for RHSs
 *
 * return bitvector<vector> containing LHS and RHS bitvectors
 * task 1: print size of each vector
 *
 * Idea: use bitVector???
 */
/*
vector <vector< vector<int> > > ruleCount()
{
    //ruleNum starts at 0 because I don't feel like dealing with off-by-one errors later
    int ruleNum = -1;
    vector< vector<int> > ruleLHS; //2D vector purely for storage purposes
    vector< vector<int> > ruleRHS;
    vector< vector< vector<int> > > ruleCounter;


    //Look at each element in universe
    for(iter = universe.begin(); iter != universe.end(); ++iter)
    {
        ruleNum = -1;
        vector<int> singRHS;
        //Look at each rule (vecTokIter)
        for(vecTokIter = ruleList.begin(); vecTokIter != ruleList.end(); ++vecTokIter, ruleNum++)
        {
            ruleNum++;

            //For rules that go to epsilon
            if((vecTokIter->size() == 2) && (iter == universe.begin()))
            {
                singRHS.push_back(ruleNum);
            }
            else
            {
                //Look at each token (iterNest) in each rule (vecTokIter)
                for (iterNest = vecTokIter->begin(); iterNest != vecTokIter->end(); ++iterNest)
                {
                    //if current token (iterNest) in current rule (vecTokIter)
                    // matches current element in universe (iter)
                    if (iterNest->lexeme == iter->lexeme)
                    {
                        //If first element (iterNest) in rule (vecTokIter), add to LHS
                        if (iterNest == vecTokIter->begin())
                            ruleLHS.push_back(ruleNum);
                        //else if element not already on RHS
                        else if(!(find(singRHS.begin(), singRHS.end(), ruleNum) != singRHS.end()))
                            singRHS.push_back(ruleNum);
                    }
                }
            }
        }
        ruleRHS.push_back(singRHS);
    }

    ruleCounter.push_back(ruleLHS);
    ruleCounter.push_back(ruleRHS);

    return ruleCounter;
}
*/

void printRules(vector < vector<int> > rulesInts, vector<Token> universe, vector<bool> vecBool)
{

}

/*
 * Pseudocode:
 *
 * find intersection of universe and universeFF
 * universe[0] = true
 * universe[2] through (end of universeFF) = true
 * //after universeFF are variables
 * //universe[1] = eof, cannot generate anything
 *
 * for each variable in LHS
 *      bool generating = true
 *      for each token in RHS
 *          if token is NOT generating
 *              generating = false
 *      universe[variable] = generating
 */

vector<bool> findGenerating(vector < vector<int> > ruleInts)
{
    if(testGenerating)
    {
        cout << "\nStarting findGenerating" << endl;
    }
    vector<bool> genU(universe_size); //generating for entire universe
    int maxTerm = (int)universeFF.size();
    bool noChanges = false;
    if(false)
    {
        cout << "universe size = " << universe_size << endl;
        cout << "genU size = " << genU.size() << endl;
        cout << "universeFF size = " << universeFF.size() << endl;
        cout << "maxTerm size = " << maxTerm << endl;
        cout << "Printing Universe" << endl;
        vector<bool> testVector(genU.size());
        fill(testVector.begin(),testVector.end(),true);
        print_set(testVector);
        cout << "done printing universe\nCONTINUING FUNCTION\n" << endl;
    }

    //make terminals and epsilon generating
    genU[0] = true;
    if(testGenerating)
    {
        cout << "Setting terminals and epsilon to True." << endl;
        cout << "Element #0: " << universe[0].lexeme << " is generating." << endl;
    }

    for(int i = 2, loopBreak = 0; ((i < maxTerm) && (loopBreak < loopMax)) ||
                                  ((i < maxTerm) && (!testGenerating)); i++, loopBreak++)
    {
        if(testGenerating)
        {
            cout << "Element #" << i << ": " << universe[i].lexeme
                 << " is generating." << endl;
        }
        genU[i] = true;
    }


    if(testGenerating)
    {
        cout << "Items generating: ";
        for(int i = 0; i < maxTerm; i++)
            if(is_element(genU, i))
            {
                cout << universe.at(i).lexeme;
                if(i < maxTerm - 1)
                    cout << ", ";
                else
                    cout << "" << endl;
            }
    }

    //checking variables
    if(testGenerating)
        cout << "\nChecking variables" << endl;
    //While changes have been made
    while((!noChanges && (loopBreak < loopMax)) || (!noChanges && !testGenerating))
    {
        loopBreak++;
        bool generating = true;
        int maxRules = (int)ruleInts.size();
        if(testGenerating)
        {
            cout << "\nLoop #" << loopBreak << endl;
        }
        noChanges = true;

        //For each rule (i) in
        if(testGenerating)
        {
            cout << "Starting loop for each rule" << endl;
        }
        int nestLoop = 0;
        for(int i = 0, nestLoop = 0; ((i < maxRules) && (nestLoop < loopMax)) ||
                ((i < maxRules) && (!testGenerating)); i++, nestLoop++)
        {
            generating = true;
            vector<int> oneRule = ruleInts[i];
            int ruleSize = (int) oneRule.size();
            int ruleNum = oneRule[0];
            bool oldBool = is_element(genU, ruleNum);
            string tempLHS = universe[ruleNum].lexeme;
            if (testGenerating)
            {
                cout << "\nNow testing rule #" << (i + 1) << ": "
                     << tempLHS << endl;
            }
            if(is_element(genU, ruleNum))
            {
                if (testGenerating)
                {
                    cout << tempLHS << " is generating. Skipping RHS loop." << endl;
                }
            }
            else
            {
                if (testGenerating)
                {
                    cout << tempLHS << " is not generating." << endl;
                    cout << "Starting loop for each item in RHS" << endl;
                }
                //for each item on RHS
                //starts at 1 because oneRule[0] = LHS
                int nest2Loop = 0;
                for (int j = 1, nest2loop = 0; ((j < ruleSize) && (nest2loop < loopMax)) ||
                                               ((j < ruleSize) && !testGenerating); j++, nest2loop++)
                {
                    if (testGenerating)
                    {
                        cout << "Is " << universe[oneRule[j]].lexeme
                             << " generating? ";
                    }
                    if (is_element(genU, oneRule[j]))
                    {
                        if (testGenerating)
                        {
                            cout << "Yes" << endl;
                        }
                    }
                    else
                    {
                        if (testGenerating)
                        {
                            cout << "No." << endl;
                        }
                        generating = false;
                    }
                }
                if ((nest2Loop == loopMax) && (testGenerating))
                {
                    cout << "RHS loop forcibly broken." << endl;
                }


                //if entire RHS is generating, say variable is generating
                if (generating)
                {
                    if (testGenerating)
                    {
                        cout << "Rule #" << (i + 1) << ": "
                             << tempLHS << " is generating" << endl;
                    }
                    genU[ruleNum] = true;
                }
                else if (testGenerating)
                {
                    cout << "Rule #" << (i + 1) << ": " << tempLHS
                         << " is not generating." << endl;
                }

                //if changes were made
                if (genU[ruleNum] != oldBool)
                {
                    if (testGenerating)
                    {
                        cout << "genU[ruleNum] = " << genU[ruleNum] << endl;
                        cout << "oldBool = " << oldBool << endl;
                        cout << "Rule status changed." << endl;
                    }
                    noChanges = false;
                }
                else if (testGenerating)
                {
                    cout << "genU[ruleNum] = " << genU[ruleNum] << endl;
                    cout << "oldBool = " << oldBool << endl;
                    cout << "Rule status remains unchanged." << endl;
                }
            }
        }
        if((nestLoop == loopMax) && (testGenerating))
        {
            cout << "LHS rule forcibly broken" << endl;
        }
        else if(testGenerating && noChanges)
        {
            cout << "No changes made. Exiting loop." << endl;
        }
        else if(testGenerating)
        {
            cout << "Changes made. Restarting loop." << endl;
        }
    }


    if((loopBreak == loopMax) && testGenerating)
        cout << "\nWhile loop forcibly broken" << endl;
    else if(testGenerating)
    {
        cout << "\nGenerating symbols found. Exiting function." << endl;
    }

    loopBreak = 0;

    return genU;
}


/*
 * Pseudocode:
 *
 * vector<bool> reachU(universe_size)
 * vector< vector<int> > reachRules
 * set S as true in reachU
 *
 * get rules
 * for each rule in ruleInts
 *      for each element in rule
 *          if no non-generating symbols found
 *              add rule to reachRules
 *
 * while changes are being made
 *      for all items i in universe
 *          for all rules in reachRules
 *              if LHS is element in reachU
 *                  for each element in RHS
 *                      add element to reachU
 *
 *
 * return reachU
 */
vector<bool> findReachable(vector < vector<int> > ruleInts, vector<bool> genSyms)
{
    if(testReach)
    {
        cout << "\nStarting findReachable" << endl;
    }
    vector<bool> reachU(universe_size); //reachable for entire universe
    vector<bool> reachRules(ruleInts.size());
    int maxTerm = (int)universeFF.size();
    int maxRules = ruleInts.size();
    bool noChanges = false;

    //make S reachable
    reachU[maxTerm] = true;
    if(testReach)
    {
        cout << "Setting S to True." << endl;
        cout << "Element #" << to_string(maxTerm) << ": " << universe[maxTerm].lexeme << " is reachable." << endl;
    }

    if(testReach)
    {
        cout << "Items reachable: ";
        for(int i = 0; i < (maxTerm + 1); i++)
            if(is_element(reachU, i))
            {
                cout << universe.at(i).lexeme;
                if(i < maxTerm)
                    cout << ", ";
                else
                    cout << "" << endl;
            }
    }

    //for each rule in ruleInts
    for(int i = 0; i < maxRules; i++)
    {
        bool allGen = true;
        vector<int> singRule = ruleInts[i];
        int singRuleSize = (int)singRule.size();

        //for each element in rule
        for(int j = 0; j < singRuleSize; j++)
        {
            int genSize = (int)genSyms.size();
            //if not generating
            if(is_element(genSyms, singRule[j]))
                allGen = false;
        }
        //if no non-generating symbols found
        if(allGen)
            //add rule to reachRules
            reachRules[i] = true;
    }

    /*
     * If  A -> A1 A2 ... Ak is a grammar rule and
     *  ▪ A1 generating  and
     *  ▪ A2 generating  and
     *  ▪ ... and
     *  ▪ ...
     *  ▪ Ak generating
     *
     *  Then A is generating
     *
     *  ---------------------------
     *
     *  If  A -> A1 A2 ... Ak is a grammar rule and A is reachable
     *
     *  Then
     *  A1 and
     *  A2 and
     *  ... and
     *  Ak
     *  are reachable
     */

    //while changes are being made
    while((!noChanges && (loopBreak < loopMax)) || (!noChanges && !testReach))
    {
        loopBreak++;
        noChanges = true;
        //for all items i in universe
        for(int i = 0; i < universe_size; i++)
        {
            bool oldBool = reachU[i];
            //for all rules j in ruleInts
            for (int j = 0;j < maxRules; j++)
            {
                //if rule is reachable
                if(is_element(reachRules, j))
                {
                    vector<int> singRule = ruleInts[j];
                    int singRuleSize = (int)singRule.size();
                    //if LHS is element in reachU
                    if (is_element(reachU, singRule[0]))
                    {
                        //for each element k in RHS
                        //start at 1 because LHS (singRule[0]) already in reachU
                        for (int k = 1; k < singRuleSize; k++)
                        {
                            //add element to reachU
                            reachU[singRule[k]] = true;
                        }
                    }
                }
            }
            if(oldBool != reachU[i])
                noChanges = false;
        }
    }

    return reachU;
}

vector< vector<Token> > findUseless(vector<vector<int> > ruleInts)
{
    if(testReach)
    {
        cout << "\nTesting findUseless"  << endl;
    }
    vector <vector<Token> > newRules;

    vector<bool> genSyms = findGenerating(ruleInts);
    //vector<bool> reachSyms = findReachable(ruleInts, genSyms);
    vector<bool> usableSyms(universe_size);
    fill(usableSyms.begin(), usableSyms.end(), false);
    int size = (int)genSyms.size();
    if(testReach)
    {
       // if(size != reachSyms.size())
            cout << "\nSomething got fucked up!\n" << endl;
    }

    for(int i = 0; ((i < size) && (loopBreak < loopMax)) ||
        ((i < size) && (!testUseless)); i++, loopBreak++)
    {
        if(testReach)
        {
            cout << "Testing symbol " << i << ": "
                 << universe[i].lexeme << endl;
        }
        if((genSyms[i] == reachSyms[i]) && testUseless)
        {
            cout << universe[i].lexeme << " is not useless" << endl;
            usableSyms[i] = true;
        }
        else if(testReach)
        {
            cout << universe[i].lexeme << " is useless." << endl;
        }
    }

    if(testReach)
    {
        print_set(usableSyms);
    }

    if(testReach)
    {
        cout << "\nDone testing FindUseless\n" << endl;
    }

    return newRules;
}

/*****************
 * MAIN FUNCTION *
 *****************/

int main (int argc, char* argv[])
{
    /***********************
     * INITIALIZING THINGS *
     ***********************/
    if(testing)
        cout << "\nSTARTING PROGRAM" << endl;
    else
    {
        //so that I don't have to change them all individually when I'm completely done with testing
        testInput = false;
        testRules = false;
        test0 = false;
        test1 = false;
        test2 = false;
        test3 = false;
        test4 = false;
        test5 = false;
        testElement = false;
        testPrint = false;
        testGenerating = false;
        testLabel = false;
        testReach = false;
        testUseless = false;
    }

    // NOTE: Below it teacher's code. Do not touch.
    int task;

    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }


    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

    task = atoi(argv[1]);
    //NOTE: Above is teacher's code; do not touch


    /******************************************
     * Task 0: Reading and categorizing input *
     ******************************************/
    //TESTING
    int ruleCount = 0;
    string termStr = "Terminals = {";
    string nonTermStr = "Non-Terminals = {";
    string singRuleStr = "";
    vector<string> ruleStr;
    ruleStr.push_back("RULES:");
    vector<string>::iterator ruleStrIter;

    //Get Terminals
    if(testInput)
        cout << "Starting Task 0" << endl;

    token.lexeme = "#";
    token.token_type = HASH;
    token.line_no = 0;
    universe.push_back(token);
    universeFF.push_back(token);

    token.lexeme = "$";
    token.token_type = DOUBLEHASH;
    universe.push_back(token);
    universeFF.push_back(token);


    token = lexer.GetToken(); //To initiate while loop

    if(testInput)
        cout << "Getting terminals" << endl;
    while (((token.token_type != HASH) && (loopBreak < loopMax)) || ((token.token_type != HASH) && (!testInput)))
    {
        loopBreak++; //For testing

        terms.push_back(token);
        termStr += token.lexeme;
        termStr += ", ";

        universe.push_back(token);
        universeFF.push_back(token);

        token = lexer.GetToken();
        //cout << "loopBreak = " << loopBreak << endl;
    }
    token = lexer.GetToken(); //To get past hash

    termStr.pop_back(); //delete space
    termStr.pop_back(); //delete comma
    termStr += "}";

    //TESTING
    if(testInput)
        if((loopBreak == loopMax))// && (token.token_type != HASH))
            cout << "Loop manually broken for //Get terminals" << endl;
    loopBreak = 0; //for testing

    if(testInput)
        cout << "Getting non-terminals" << endl;
    //Get non-terminals
    while (((token.token_type != HASH) && (loopBreak < loopMax)) || ((token.token_type != HASH) && (!testInput)))
    {
        loopBreak++; //For testing

        nonTerms.push_back(token);

        nonTermStr += token.lexeme;
        nonTermStr += ", ";

        universe.push_back(token);

        token = lexer.GetToken();
        //cout << "loopBreak = " << loopBreak << endl;
    }
    nonTermStr.pop_back(); //delete space
    nonTermStr.pop_back(); //delete comma
    nonTermStr += "}";

    universe_size = universe.size();
    //TESTING
    if(testInput)
        if((loopBreak == loopMax) && (token.token_type != HASH))
            cout << "Loop manually broken for //Get non-terminals" << endl;
    loopBreak = 0; //for testing

    //Get rules
    if(testInput)
        cout << "Getting rules" << endl;
    while (((token.token_type != DOUBLEHASH) && (loopBreak < loopMax)) || ((token.token_type != DOUBLEHASH) && (!testInput)))
    {
        //TESTING
        //cout << "loopBreak = " << loopBreak << endl;
        int nestLoop = 0; //for testing; loopBreak for nested loop
        loopBreak++; //For testing
        singRuleStr = "";
        string RHS_string = "";

        vector<Token> singleRule;
        vector<Token> singRHS;
        vector<Token> singLHS;
        bool pastArrow = false;

        //Get each rule
        token = lexer.GetToken(); //To get past hash
        if (testInput)
            cout << "Getting a rule" << endl;
        while ((((token.token_type != HASH) && (token.token_type != DOUBLEHASH)) && (loopBreak < loopMax))
               || (((token.token_type != HASH) && token.token_type != DOUBLEHASH) && (!testInput)))
        {
            nestLoop++; //For testing

            singleRule.push_back(token);

            if (pastArrow)
            {
                singRHS.push_back(token);
                RHS_string += token.lexeme;
            }
            else if ((!pastArrow) && (token.token_type != ARROW))
                singLHS.push_back(token);

            if (token.token_type == ARROW)
            {
                singRuleStr += "->";
                pastArrow = true;
            }
            else
                singRuleStr += token.lexeme;

            singRuleStr += " ";

            token = lexer.GetToken();
            //cout << "nestLoop = " << nestLoop << endl;
        }

        if (token.token_type != DOUBLEHASH)
        {
            if (!RHS_string.compare(""))
                singRuleStr += "ε";

            ruleCount++;
            ruleStr.push_back(singRuleStr);

            ruleList.push_back(singleRule);
            RHS_List.push_back(singRHS);
            LHS_List.push_back(singLHS);
        } else if (testInput)
            cout << "Rule not gotten; end of file" << endl;

        //TESTING
        if (testInput)
            if ((nestLoop == loopMax) && (token.token_type != HASH))
                cout << "Loop manually broken for //Get each rule" << endl;

        //cout << "loopBreak = " << loopBreak << endl;
    }

    if(testInput)
    {
        if ((loopBreak == loopMax) && (token.token_type != DOUBLEHASH))
            cout << "Loop manually broken for //Get Rules" << endl;
        else if (loopBreak == loopMax)
            cout << "Weird error" << endl;
        else if (loopBreak == 0)
            cout << "Rule loop never entered" << endl;
        else
            cout << "Rules successfully gotten" << endl;
    }
    loopBreak = 0;

    /******************************************
     *                TESTING                 *
     * Task 0: Reading and categorizing input *
     ******************************************/
    //TESTING
    if(test0)
    {
        cout << "\n\nTERMINALS:" << endl;
        for (iter = terms.begin(); iter != terms.end(); ++iter)
        {
            iter->Print();
        }

        cout << "\n\nNON-TERMINALS:" << endl;
        for (iter = nonTerms.begin(); iter != nonTerms.end(); ++iter)
        {
            iter->Print();
        }

        cout << "\n\nTotal rules: " << ruleCount << endl;
        cout << "RULES:" << endl;
        int tempRuleCount = 1;
        for (vecTokIter = ruleList.begin(); vecTokIter != ruleList.end(); ++vecTokIter)
        {
            cout << "\nRule #" << tempRuleCount << ":" << endl;
            for (iter = vecTokIter->begin(); iter != vecTokIter->end(); ++iter)
                iter->Print();
            cout << "Size of Rule: " << vecTokIter->size();
            tempRuleCount++;
        }

        cout << "\nRHS:" << endl;
        for (vecTokIter = RHS_List.begin(); vecTokIter != RHS_List.end(); ++vecTokIter)
        {
            for (iter = vecTokIter->begin(); iter != vecTokIter->end(); ++iter)
                iter->Print();
        }
    }




    if(testRules)
    {
        cout << "\nGRAMMAR:" << endl;
        cout << termStr << endl;
        cout << nonTermStr << "\n" << endl;

        for (ruleStrIter = ruleStr.begin(); ruleStrIter != ruleStr.end(); ++ruleStrIter)
        {
            cout << *ruleStrIter << endl;
        }
    }

    if(test0)
    {
        cout << "\nLHS:" << endl;
        for (vecTokIter = LHS_List.begin(); vecTokIter != LHS_List.end(); ++vecTokIter)
        {
            for (iter = vecTokIter->begin(); iter != vecTokIter->end(); ++iter)
                cout << iter->lexeme << endl;
        }

        cout << "\nRHS:" << endl;
        for (vecTokIter = RHS_List.begin(); vecTokIter != RHS_List.end(); ++vecTokIter)
        {
            for (iter = vecTokIter->begin(); iter != vecTokIter->end(); ++iter)
                cout << iter->lexeme << endl;
        }

    }

    if(testing)
    {
        cout << "Printing Universe" << endl;
        vector<bool> testVector(universe_size);
        fill(testVector.begin(), testVector.end(), true);
        print_set(testVector);
        labelRules();
    }

    /*
       Hint: You can modify and use the lexer from previous project
       to read the input. Note that there are only 4 token types needed
       for reading the input in this project.

       WARNING: You will need to modify lexer.cc and lexer.h to only
       support the tokens needed for this project if you are going to
       use the lexer.
     */

    /*************
     * TASKS 1-5 *
     *************/

    //Variables declared for switch cases:
    //Case 1
    //vector< vector< vector<int> > > ruleCounter;
    //Case 2
    vector<bool> genU;
    vector< vector<int> > ruleInts;
    vector< vector<Token> > newRules;
    //Case 3
    //Case 4
    //Case 5
    if(testing)
        cout << "\nStarting task #" << task << endl;

    switch (task) {
        case 1:
            cout << ruleCounter() << endl;
            break;
        case 2:
            // TODO: perform task 2.
            //Task 2: Find Useless Symbols
            ruleInts = labelRules();
            //newRules = findUseless(ruleInts);
            print_set(genU);
            break;

        case 3:
            // TODO: perform task 3.
            //Task 3: Calculate FIRST Sets
            break;

        case 4:
            // TODO: perform task 4.
            //Task 4: Calculate FOLLOW Sets
            if(test4)
            break;

        case 5:
            // TODO: perform task 5.
            //Determine if Grammar Has a Predictive Parser
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }

    if(testing)
        cout << "Task " << task << " complete" << endl;
    return 0;
}
