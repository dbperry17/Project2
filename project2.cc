#include <iostream>
#include <cstdio>
#include <cstdlib>

//Things I'm including
#include <vector>
#include "lexer.h"

using namespace std;

/****************
 * My variables *
 ****************/
//testing variables
int loopBreak = 0; //to prevent infinite loops while testing
const int loopMax = 10; //In case I need to change loop iterations
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
bool testUseless = true;
bool testLabel = true;


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

string findRules()
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
                else
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

vector<bool> find_useless()
{
    vector<bool> genU(universe.size()); //generating for entire universe
    int maxGen = genU.size();
    int maxTerm = universeFF.size();
    bool noChanges = true;
    if(testUseless)
    {
        cout << "universe size = " << universe.size() << endl;
        cout << "genU size = " << genU.size() << endl;
        cout << "maxGen size = " << maxGen << endl;
        cout << "universeFF size = " << universeFF.size() << endl;
        cout << "maxTerm size = " << maxTerm << endl;
        cout << "Printing Universe" << endl;
        vector<bool> testVector(maxGen);
        fill(testVector.begin(),testVector.end(),true);
        //for(int i = 0; i < maxGen; i++)
          //  cout << "testVector[" << i << "] = " << testVector[i] << endl;
        print_set(testVector);
        cout << "done printing universe\nCONTINUING FUNCTION\n" << endl;
    }

    //make terminals and epsilon generating
    genU[0] = true;

    for(int i = 2, loopBreak = 0; ((i < maxTerm) && (loopBreak < loopMax)) ||
                                  ((i < maxTerm) && (!testUseless)); i++, loopBreak++)
    {
        if(testUseless)
            cout << "filling position " << i << endl;
        genU[i] = true;
    }

    if(testUseless)
    {
        cout << "terminals generating:" << endl;
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
    if(testUseless)
        cout << "checking variables" << endl;
    while((noChanges && (loopBreak < loopMax)) || (noChanges && !testUseless))
    {
        loopBreak ++;
        noChanges = true;
        for (int i = maxTerm, loopBreak = 0; ((i < maxGen) && (loopBreak < loopMax)) ||
                                             ((i < maxGen) && (!testUseless)); i++, loopBreak++)
        {
            //if(universe[i] )
            //for()
            {
                bool tempBool = genU[i];
                if (testUseless)
                {
                    cout << "tempBool = " << tempBool << endl;
                    cout << "loop #" << loopBreak << endl;
                }
                if (is_element(genU, i))
                    genU[i] = true;

                if (testUseless)
                    cout << universe[i].lexeme << " = " << genU[i] << "\n" << endl;


                if (genU[i] != tempBool)
                    noChanges = false;
            }
        }
    }


    if((loopBreak == loopMax) && testUseless)
        cout << "loop forcibly broken" << endl;
    loopBreak = 0;

    if(testUseless)
        cout << "Useless symbols found. Exiting function." << endl;


    return genU;
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
        testUseless = false;
        testLabel = false;
    }

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

    // TODO: Read the input grammar at this point from standard input


    //TESTING
    int ruleCount = 0;
    string termStr = "Terminals = {";
    string nonTermStr = "Non-Terminals = {";
    string singRuleStr = "";
    vector<string> ruleStr;
    ruleStr.push_back("RULES:");
    vector<string>::iterator ruleStrIter;


    /******************************************
     * Task 0: Reading and categorizing input *
     ******************************************/
    //Get terminals
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
        vector<bool> testVector(universe.size());
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

    //Case 2
    vector<bool> genU;
    //Case 3
    //Case 4
    //Case 5

    switch (task) {
        case 1:
            if(test1)
                cout << "\nStarting Task 1" << endl;
            cout << findRules() << endl;

            if(test1)
                cout << "\nTask 1 Complete" << endl;
            break;
        case 2:
            // TODO: perform task 2.
            //Task 2: Find Useless Symbols
            if(test2)
                cout << "\nStarting Task 2" << endl;

            genU = find_useless();
            print_set(genU);

            if(test2)
                cout << "\nTask 2 Complete" << endl;
            break;

        case 3:
            // TODO: perform task 3.
            //Task 3: Calculate FIRST Sets
            if(test3)
                cout << "\nStarting Task 3" << endl;

            if(test3)
                cout << "\nTask 3 Complete" << endl;
            break;

        case 4:
            // TODO: perform task 4.
            //Task 4: Calculate FOLLOW Sets
            if(test4)
                cout << "\nStarting Task 4" << endl;

            if(test4)
                cout << "\nTask 4 Complete" << endl;
            break;

        case 5:
            // TODO: perform task 5.
            //Determine if Grammar Has a Predictive Parser
            if(test5)
                cout << "\nStarting Task 5" << endl;

            if(test5)
                cout << "\nTask 5 Complete" << endl;
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}
