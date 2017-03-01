#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <vector>
#include "lexer.h"
#include "inputbuf.h"

using namespace std;

int main (int argc, char* argv[])
{
    cout << "\nSTARTING PROGRAM" << endl;
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
    int loopBreak = 0; //to prevent infinite loops while testing
    const int loopMax = 10; //In case I need to change loop iterations
    LexicalAnalyzer lexer;
    Token token;
    vector<Token> terms;
    vector<Token> nonTerms;
    vector< vector<Token> > ruleList;
    vector< vector<Token> > RHS_List;
    //Iterating through vectors
    vector<Token>::iterator iter;
    vector<Token>::iterator iterNest;
    vector< vector<Token> >::iterator vecTokIter;

    //TESTING
    int ruleCount = 0;
    string termStr = "Terminals = {";
    string nonTermStr = "Non-Terminals = {";
    string singRuleStr = "";
    vector<string> ruleStr;
    ruleStr.push_back("RULES:");
    vector<string>::iterator ruleStrIter;

    //Get terminals
    //cout << "Getting terminals" << endl;

    token = lexer.GetToken(); //To initiate while loop

    while ((token.token_type != HASH))// && (loopBreak < loopMax))
    {
        loopBreak++; //For testing

        terms.push_back(token);
        termStr += token.lexeme;
        termStr += ", ";

        token = lexer.GetToken();
        //cout << "loopBreak = " << loopBreak << endl;
    }
    token = lexer.GetToken(); //To get past hash

    termStr.pop_back(); //delete space
    termStr.pop_back(); //delete comma
    termStr += "}";

    //TESTING
    if((loopBreak == loopMax))// && (token.token_type != HASH))
        cout << "Loop manually broken for //Get terminals" << endl;
    loopBreak = 0; //for testing


    //cout << "Getting non-terminals" << endl;
    //Get non-terminals
    while ((token.token_type != HASH))// && (loopBreak < loopMax))
    {
        loopBreak++; //For testing

        nonTerms.push_back(token);

        nonTermStr += token.lexeme;
        nonTermStr += ", ";

        token = lexer.GetToken();
        //cout << "loopBreak = " << loopBreak << endl;
    }
    nonTermStr.pop_back(); //delete space
    nonTermStr.pop_back(); //delete comma
    nonTermStr += "}";

    //TESTING
    if((loopBreak == loopMax) && (token.token_type != HASH))
        cout << "Loop manually broken for //Get non-terminals" << endl;
    loopBreak = 0; //for testing

    //Get rules
    //cout << "Getting rules" << endl;
    while ((token.token_type != DOUBLEHASH) && (loopBreak < loopMax))
    {
        //TESTING
        //cout << "loopBreak = " << loopBreak << endl;
        int nestLoop = 0; //for testing; loopBreak for nested loop
        loopBreak++; //For testing
        singRuleStr = "";
        string RHS_string = "";

        vector<Token> singleRule;
        vector<Token> singRHS;
        bool pastArrow = false;

        //Get each rule
        token = lexer.GetToken(); //To get past hash
        //cout << "Getting a rule" << endl;
        while ((token.token_type != HASH) && (token.token_type != DOUBLEHASH) && (nestLoop < loopMax))
        {
            nestLoop++; //For testing

            singleRule.push_back(token);

            if(pastArrow)
            {
                singRHS.push_back(token);
                RHS_string += token.lexeme;
            }

            if(token.token_type == ARROW)
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

        if(token.token_type != DOUBLEHASH)
        {
            if(!RHS_string.compare(""))
                singRuleStr += "ε";

            ruleCount++;
            ruleStr.push_back(singRuleStr);

            ruleList.push_back(singleRule);
            RHS_List.push_back(singRHS);
        }
        //else
        //    cout << "Rule not gotten; end of file" << endl;

        //TESTING
        if((nestLoop == loopMax) && (token.token_type != HASH))
            cout << "Loop manually broken for //Get each rule" << endl;

        //cout << "loopBreak = " << loopBreak << endl;
    }

    //TESTING
    /*
    if((loopBreak == loopMax) && (token.token_type != DOUBLEHASH))
        cout << "Loop manually broken for //Get Rules" << endl;
    else if(loopBreak == loopMax)
        cout << "Weird error" << endl;
    else if(loopBreak == 0)
        cout << "Rule loop never entered" << endl;
    else
        cout << "Rules successfully gotten" << endl;
    */
    loopBreak = 0;

    //TESTING
    /*
    cout << "\n\nTERMINALS:" << endl;
    for(iter = terms.begin(); iter != terms.end(); ++iter)
    {
        iter->Print();
    }

    cout << "\n\nNON-TERMINALS:" << endl;
    for(iter = nonTerms.begin(); iter != nonTerms.end(); ++iter)
    {
        iter->Print();
    }

    cout << "\n\nTotal rules: " << ruleCount << endl;
    cout << "RULES:" << endl;
    int tempRuleCount = 1;
    for(vecTokIter = ruleList.begin(); vecTokIter != ruleList.end(); ++vecTokIter)
    {
        cout << "\nRule #" << tempRuleCount << ":" << endl;
        for(iter = vecTokIter->begin(); iter != vecTokIter->end(); ++iter)
            iter->Print();
        tempRuleCount++;
    }

    cout << "\nRHS:" << endl;
    for(vecTokIter = RHS_List.begin(); vecTokIter != RHS_List.end(); ++vecTokIter)
    {
        for(iter = vecTokIter->begin(); iter != vecTokIter->end(); ++iter)
            iter->Print();
    }
    */

    /*
    cout << "\nGRAMMAR:" << endl;
    cout << termStr << endl;
    cout << nonTermStr << "\n" << endl;

    for(ruleStrIter = ruleStr.begin(); ruleStrIter != ruleStr.end(); ++ruleStrIter)
    {
        cout << *ruleStrIter << endl;
    }
    */

    cout << "\nRHS:" << endl;
    for(vecTokIter = RHS_List.begin(); vecTokIter != RHS_List.end(); ++vecTokIter)
    {
        for(iter = vecTokIter->begin(); iter != vecTokIter->end(); ++iter)
            iter->Print();
    }

    /*
       Hint: You can modify and use the lexer from previous project
       to read the input. Note that there are only 4 token types needed
       for reading the input in this project.

       WARNING: You will need to modify lexer.cc and lexer.h to only
       support the tokens needed for this project if you are going to
       use the lexer.
     */

    switch (task) {
        case 1:
            // TODO: perform task 1.

            //For terminals
            for(iter = terms.begin(); iter != terms.end(); ++iter)
            {

            }


            cout << "\nTask 1 Complete" << endl;
            break;

        case 2:
            // TODO: perform task 2.
            break;

        case 3:
            // TODO: perform task 3.
            break;

        case 4:
            // TODO: perform task 4.
            break;

        case 5:
            // TODO: perform task 5.
            break;

        default:
            cout << "Error: unrecognized task number " << task << "\n";
            break;
    }
    return 0;
}
