#include <iostream>
#include <cstdio>
#include <cstdlib>

//Things I'm including
#include <vector>
#include <algorithm>
#include "lexer.h"

using namespace std;
//Testing Visual studio

/****************
 * My variables *
 ****************/
//testing variables
int loopBreak = 0; //to prevent infinite loops while testing
const int loopMax = 2; //In case I need to change loop iterations
bool testing = false; //to avoid having to comment things out
bool testInput;
bool testRules;
bool test0;
bool test1;
bool test2;
bool test3;
bool test4;
bool test5;
bool testElement;
bool testPrint;
bool testGenerating;
bool testLabel;
bool testReach;
bool testUseSyms;
bool testUseRules;
bool testRuleStr;
bool testRulePrint;
bool testSingRuleStr;
bool testFirst;
bool testFollow;




/**
 * Created so that I don't have to change all testing booleans individually when
 * I'm completely done with testing.
 *
 * I know it's probably bad coding style to have a function before I'm done declaring
 * variables, but I don't care. I want all this testing stuff together so that I don't
 * have to scroll or CTRL+F my way through the file
 */
void myTests()
{
	if(testing)
	{
		cout << "\nSTARTING PROGRAM" << endl;
		testInput = false;
		testRules = true;
		test0 = false;
		test1 = false;
		test2 = false;
		test3 = true;
		test4 = true;
		test5 = true;
		testElement = false;
		testPrint = false;
		testGenerating = false;
		testLabel = false;
		testReach = false;
		testUseSyms = false;
		testUseRules = false;
		testRuleStr = false;
		testRulePrint = false;
		testSingRuleStr = false;
		testFirst = false;
		testFollow = true;
	}
	else
	{
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
		testUseSyms = false;
		testUseRules = false;
		testRuleStr = false;
		testRulePrint = false;
		testSingRuleStr = false;
		testFirst = false;
		testFollow = false;
	}
}

//non-testing variables
int universe_size = 0;
int maxRules = 0;
LexicalAnalyzer lexer;
Token token;
vector<Token> terms;
vector<Token> nonTerms;
vector< vector<Token> > ruleList;
vector< vector<Token> > RHS_List;
vector< vector<Token> > LHS_List;
vector < vector<int> > ruleInts;

vector<Token> universe;
vector<Token> universeFF; //FIRST & FOLLOW universe
//Iterating through vectors
vector<Token>::iterator iter;
vector<Token>::iterator iterNest;
vector< vector<Token> >::iterator vecTokIter;

/************************************************
 * 				CODE FROM POWERPOINT 			*
 * 												*
 * Functions:									*
 * 		bool is_element(vector<bool> S, int i)	*
 * 		void print_set(vector<bool> S)			*
 ************************************************/
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
	string output = "";

    if(testPrint)
        cout << "printing" << endl;
    int max = (int)S.size();
	int elements = (int)count(S.begin(), S.end(), true);
	if(elements == 0)
		output = " ";
	else
	{
		for (int i = 0; i < max; i++)
			if (is_element(S, i))
			{
				output += universe.at(i).lexeme;
				output += ", ";
			}

		output.pop_back(); //delete space
		output.pop_back(); //delete comma
		output += " ";
	}
	cout << output;

    if(testPrint)
        cout << "done printing" << endl;
}

/************************************************
 * 					 TASK 1:					*
 *  Find number of productions for each symbol	*
 * 												*
 * Functions:									*
 * 		string ruleCounter() 					*
 ************************************************/
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

/************************************************************************
 * 								TASK 2:									*
 * 						  Find Useless Symbols							*
 * 																		*
 * Functions:															*
 * 		string singRuleString(vector<int> singRule)						*
 * 		void printRules(vector<string> rules)							*
 * 		vector< vector<int> > labelRules()								*
 * 		vector<string> rulesAsString(vector<bool> validRule)			*
 * 		vector<bool> findGenerating()									*
 * 		vector<bool> findReachable(vector<bool> genSyms)				*
 * 		vector<bool> findUsableSyms()									*
 * 		vector<bool> findUsableRules(vector<bool> usableSyms)			*
 *																		*
 ************************************************************************/
string singRuleString(vector<int> singRule)
{
	if(testSingRuleStr)
	{
		cout << "\nStarting singRuleString" << endl;
	}
	string ruleStr = "";
	int singRuleSize = singRule.size();
	if(testSingRuleStr)
	{
		cout << "singRule = ";
		for(int i = 0; i < singRuleSize; i++)
			cout << to_string(singRule[i]) << " ";
		cout << "" << endl;
		cout << "singRuleSize = " << 2 << endl;
	}

	ruleStr = universe[singRule[0]].lexeme;
	ruleStr += " -> ";
	//if rule goes to epsilon
	if (singRuleSize == 1)
		ruleStr += "#";
		//else rule doesn't go to epsilon
	else
		//for each item in RHS in each rule
		//j = 1 because j = 0 is LHS
		for (int j = 1; j < singRuleSize; j++)
		{
			ruleStr += universe[singRule[j]].lexeme;
			if (j != singRuleSize - 1)
				ruleStr += " ";
		}

	if(testSingRuleStr)
	{
		cout << "ruleStr = " << ruleStr << endl;
		cout << "Done testing singRuleString\n" << endl;
	}

	return ruleStr;
}

void printRules(vector<string> rules)
{
    if(testRulePrint)
    {
        cout << "\nTesting printRules" << endl;
    }

    int ruleSize = (int)rules.size();
    for(int i = 0; i < ruleSize; i++)
    {
		if(testRulePrint)
		{
			cout << "ruleSize = " << ruleSize << endl;
        }
        cout << rules[i] << endl;
    }

    if(testRulePrint)
    {
        cout << "Done testing printRules\n" << endl;
    }
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


/*
 * Pseudocode:
 *
 * vector<string> grammar
 * string ruleStr;
 *
 * for each rule in rulesInts
 * {
 *      ruleStr = universe[rule[0]].lexeme;
 *      rulestr += " -> ";
 *      if rule goes to epsilon
 *          ruleStr += "#"
 *      else
 *          for each item in RHS in each rule
 *          {
 *              ruleStr += universe[item].lexeme
 *              if(item != ruleSize - 1)
 *                  ruleStr += " "
 *          }
 *      grammar.push_back(ruleStr)
 * }
 * return grammar;
 */
vector<string> rulesAsString(vector<bool> validRule)
{
    if(testRuleStr)
    {
        cout << "\nTesting rulesAsString (filtered)" << endl;
    }

    vector<string> grammar;
    string ruleStr;
	if(testRuleStr)
	{
		cout << "maxRules = " << maxRules << endl;
	}

    //for each rule in rulesInts
    for(int i = 0; i < maxRules; i++)
    {
		if(testRuleStr)
		{
			cout << "Is Rule " << i << " valid?" << endl;
			cout << singRuleString(ruleInts[i]) << ": " << is_element(validRule, i) << endl;
		}
        //if rule is valid
        if(is_element(validRule, i))
        {
            vector<int> singRule = ruleInts[i];
            int singRuleSize = (int) singRule.size();
            if(testRuleStr)
            {
                cout << "singRuleSize = " << singRuleSize << endl;
            }
            ruleStr = singRuleString(singRule);
            grammar.push_back(ruleStr);
        }
    }

    if(testRuleStr)
    {
		cout << "Final result: " << endl;
		for(int i = 0; i < (int)grammar.size(); i++)
		{
			cout << grammar[i] << endl;
		}

        cout << "\nDone testing rulesAsString\n" << endl;
    }

    return grammar;
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
vector<bool> findGenerating()
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
vector<bool> findReachable(vector<bool> genSyms)
{
    if(testReach)
    {
        cout << "\nStarting findReachable" << endl;
    }
    vector<bool> reachU(universe_size); //reachable for entire universe
    vector<bool> reachRules(ruleInts.size());
    int maxTerm = (int)universeFF.size();
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

        if(testReach)
        {
            cout << "Rule: " << singRuleString(singRule) << endl;
        }

        //for each element in rule
        for(int j = 0; j < singRuleSize; j++)
        {
            if(testReach)
            {
                cout << "Element: " << universe[singRule[j]].lexeme << endl;
            }
            //if not generating
            if(!is_element(genSyms, singRule[j]))
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

    if(testReach)
    {
        cout << "Reachable Symbols:" << endl;
        for(int i = 0; i < universe_size; i++)
        {
            if (is_element(reachU, i))
            {
                cout << universe[i].lexeme;
                if (i != universe_size - 1)
                    cout << ", ";
                else
                    cout << "" << endl;
            }
        }

        cout << "Done testing findReachable\n" << endl;
    }

    return reachU;
}

/**
 * Pseudocode:
 *
 *  vector<bool> newRules;
 *  vector<bool> genSyms = findGenerating();
 *  vector<bool> reachSyms = findReachable(genSyms);
 *  vector<bool> usableSyms(universe_size);
 *  fill(usableSyms.begin(), usableSyms.end(), false);
 *
 *  for each token in universe
 *      if token is in both genSyms and reachSyms
 *          mark reachSyms token as true
 *
 *  return reachSyms
 */
vector<bool> findUsableSyms()
{
    if(testUseSyms)
    {
        cout << "\nTesting findUsableSyms" << endl;
    }

    vector<bool> genSyms = findGenerating();
    vector<bool> reachSyms = findReachable(genSyms);
    vector<bool> usableSyms(universe_size);
    fill(usableSyms.begin(), usableSyms.end(), false);

    //for each token in universe
    for(int i = 0; i < universe_size; i++)
	{
		//if token is in both genSyms and reachSyms
		if (is_element(genSyms, i) && is_element(reachSyms, i))
			//mark useableSyms token as true
			usableSyms[i] = true;
	}
    if(testUseSyms)
    {
        print_set(usableSyms);
        cout << "\nDone testing FindUsableSyms\n" << endl;
    }

    return usableSyms;
}

/*
 * Pseudocode:
 *
 *  for each rule i in ruleInts
 *      bool allUsed = true;
 *      for each item j in rule i in ruleInts
 *          if item j is not in reachSyms
 *              allUsed = false;
 *      if(allUsed)
 *          newRules[i] = true;
 */
vector<bool> findUsableRules(vector<bool> usableSyms)
{
    if(testUseRules)
    {
        cout << "testing findUsableRules" << endl;
    }
    vector<bool> newRules(maxRules);
    fill(newRules.begin(), newRules.end(), false);

    //for each rule i in ruleInts
    for(int i = 0; i < maxRules; i++)
    {
        bool allUsed = true;
        vector<int> singRule = ruleInts[i];
        int singRuleSize = (int)singRule.size();
		if(testUseSyms)
		{
			cout << "Testing Rule #" << i << ": " << singRuleString(singRule) << endl;
			cout << "singRuleSize = " << singRuleSize << endl;
		}
		//for each item j in rule i in ruleInts
        for(int j = 0; j < singRuleSize; j++)
		{
			//if item j is not in usableSyms
			if (testUseSyms)
			{
				cout << "Item: " << singRule[j] << endl;
			}
			if (!is_element(usableSyms, singRule[j]))
				allUsed = false;
		}
		if (allUsed)
            newRules[i] = true;
    }

    if(testUseRules)
    {
        cout << "Done testing usableRules" << endl;
    }

    return newRules;
}

/************************************************
 * 					 TASK 3						*
 * 			  Calculate FIRST Sets				*
 *												*
 * Functions:									*
 * 		vector< vector<bool> > findFirstSets()	*
 ************************************************/

/*
 * I. FIRST(X) = {X} if X is a terminal
 * II.  FIRST(#) = {#}.  Note that this is not covered by the first rule because # is
 * 		not a terminal.
 * III. If A → Xα, then add FIRST(X) − {#} to FIRST(A)
 *	Translation:
 *		If A goes to a token first, add the FIRST of that variable (minus #) to FIRST(A)
 * IV. If A → A_1 A_2 A_3 ... A_iA_(i+1) ... A_k and
 * # ∈ FIRST(A_1) and # ∈ FIRST(A_2) and ... and # ∈ FIRST(A_i),
 * then add FIRST(A_(i+1)) − {#} to FIRST(A)
 *	Translation:
 *		If A goes to more than one thing, and the first i things contain # in their
 *		FIRST sets, then add the FIRST set of the (i+1)th thing to A.
 * V. If A → A_1 A_2 A_3 ... A_k and
 * # ∈ FIRST(A_1) and # ∈ FIRST(A_2) and ... and # ∈ FIRST(A_k),
 * then add # to FIRST(A).
 *	Translation:
 *		If everything that A goes to contains #, then add # to FIRST(A).
 */
vector< vector<bool> > findFirstSets()
{
	if (testFirst)
	{
		cout << "\nStarting findFirstSets" << endl;
	}

	//FIRST Sets initialization
	//Setup
	vector<vector<bool> > firstSets;
	int firstUniSize = (int) universeFF.size();
	bool noChanges = false;


	//I. FIRST(X) = {X} if X is a terminal
	//II.  FIRST(#) = {#}.
	for (int i = 0; i < universe_size; i++)
	{
		vector<bool> firstUni((unsigned long) firstUniSize);
		if (i != 1) //skip $
		{
			fill(firstUni.begin(), firstUni.end(), false);
			firstUni[i] = true;
		}
		else //Set all of $'s first set to false
		{
			fill(firstUni.begin(), firstUni.end(), false);
		}

		firstSets.push_back(firstUni);
	}

	if (testFirst)
	{
		cout << "\nFIRST sets so far:" << endl;
		for (int i = 0; i < universe_size; i++)
		{
			cout << "FIRST(" << universe[i].lexeme << ") = { ";
			print_set(firstSets[i]);
			cout << "}" << endl;
		}
	}


	loopBreak = 0;
	while ((!noChanges && (loopBreak < loopMax)) || (!noChanges && !testFirst))
	{
		loopBreak++;
		if (testFirst)
		{
			cout << "Loop #" << loopBreak << endl;
			cout << "\nFIRST sets so far:" << endl;
			for (int i = firstUniSize; i < universe_size; i++)
			{
				cout << "FIRST(" << universe[i].lexeme << ") = { ";
				print_set(firstSets[i]);
				cout << "}" << endl;
			}
		}
		noChanges = true;
		vector<bool> changeCheck;
		vector<int> singRule;
		//for each rule
		for (int j = 0; j < maxRules; j++)
		{
			singRule = ruleInts[j];
			int ruleLHS = singRule[0];
			changeCheck = firstSets[ruleLHS];
			int singRuleSize = (int) singRule.size();
			if (testFirst)
			{
				cout << "----------" << endl;
				cout << "\nCurrent rule: " << j + 1 << "/" << maxRules
					 << "\n" << singRuleString(singRule) << endl;
				cout << "Rule size: " << singRuleSize << endl;
				cout << "FIRST set at start of loop:" << endl;
				cout << "FIRST(" << universe[ruleLHS].lexeme << ") = { ";
				print_set(firstSets[ruleLHS]);
				cout << "}" << endl;
			}
			vector<bool> firstB;

			//III.	If A goes to a token B first, add the FIRST(B) (minus #)
			// 		to FIRST(A)
			if (testFirst)
			{
				cout << "Testing rule 3" << endl;
			}
			if ((singRuleSize != 1)                //If rule != #
				&& (singRule[1] > 1))            //If first item is not epsilon
			{
				if (testFirst)
					cout << "Applying Rule 3" << endl;
				firstB = firstSets[singRule[1]];
				//for each member k of FIRST(B) (starting from 2)
				//if k = true, then FIRST(A)[k] = true
				for (int k = 2; k < firstUniSize; k++)
					if (is_element(firstB, k))
						firstSets[ruleLHS][k] = true;
			}

			if (testFirst)
			{
				cout << "FIRST(" << universe[ruleLHS].lexeme << ") = { ";
				print_set(firstSets[ruleLHS]);
				cout << "}" << endl;
				cout << "Testing Rule 4" << endl;
			}


			//IV.	If A goes to more than one thing, and the first i things
			// 		contain # in their FIRST sets, then add the FIRST set of the
			// 		(i+1)th thing to A.
			/*
			 *
			 * bool emptyFirst
			 * bool hasHash
			 * int elements = 0;
			 * If A is not empty
			 * 		if A goes to non-Terminal
			 * 			//for each token in singRule A
			 * 			for(int tokenPos = 1; tokenPos < singRuleSize; tokenPos++)
			 * 			{
			 *		 		firstOfToken = singRule[TokenPos]
			 * 				//if frontmost token is not empty
			 * 				if(firstOfToken is not empty)
			 * 				{
			 * 					//if frontMost token has a hash in its FIRST
			 * 					if(firstOfToken hasHash)
			 * 					{
			 * 						//Rule V
			 * 						if next token does not exist
			 * 							firstA[0] = true; //add # to firstA
			 * 						else //rule IV
			 * 							add nextToken's first set to firstA
			 * 					}
			 * 					else	//frontMost does not have hash
			 * 					{
			 * 						add firstOfToken to firstA
			 * 					}
			 * 				}
			 * 				else
			 * 					break;	//break forLoop; examine no other tokens because
			 * 							//frontmost is empty
			 * 			}
			 *
			 */
			int elements = 0;
			elements = (int) count(firstSets[ruleLHS].begin(), firstSets[ruleLHS].end(), true);
			//If A is not empty
			if (elements != 0)
			{
				if(testFirst)
					cout << "FIRST(A) is not empty" << endl;

				vector<bool> firstOfToken;
				int tokenSym; //so universe[tokenSym].lexeme outputs proper lexeme
				if(singRuleSize == 1) //A -> #
				{
					firstSets[ruleLHS][0] = true;
				}
				else
				{
					//for each token in singRule A
					for (int tokenPos = 1; tokenPos < singRuleSize; tokenPos++)
					{
						tokenSym = singRule[tokenPos];
						if (testFirst)
							cout << "\nToken #" << tokenPos << ": "
								 << universe[tokenSym].lexeme << endl;

						tokenSym = singRule[tokenPos];
						firstOfToken = firstSets[tokenSym];
						if (testFirst)
						{
							cout << "FIRST(" << universe[tokenSym].lexeme << ") = { ";
							print_set(firstOfToken);
							cout << "}" << endl;
						}

						//if current token is non-Terminal
						if ((tokenSym >= firstUniSize) && (tokenSym < universe_size))
						{
							if(testFirst)
								cout << "Token is not a terminal" << endl;
							elements = (int) count(firstOfToken.begin(), firstOfToken.end(), true);
							if (testFirst)
							{
								cout << "FIRST(" << universe[tokenSym].lexeme << ") = { ";
								print_set(firstSets[tokenSym]);
								cout << "}" << endl;
								cout << "Elements: " << elements << endl;
							}

							//if frontmost token is not empty
							if (elements != 0)
							{
								//if frontMost token has a hash in its FIRST
								if (is_element(firstOfToken, 0))
								{
									int nextTokenPos = tokenPos + 1;
									if(testFirst)
									{
										cout << "# is an element of " << universe[tokenSym].lexeme << endl;
										cout << "nextTokenPos = " << nextTokenPos << endl;
										cout << "singRuleSize = " << singRuleSize << endl;
									}
									//Rule V
									if (nextTokenPos >= singRuleSize)    // next token does not exist
										for (int k = 0; k < firstUniSize; k++)
										{
											if (is_element(firstSets[singRule[tokenPos]], k))
												firstSets[ruleLHS][k] = true;
										}
									else
									{
										elements = (int) count(firstSets[singRule[nextTokenPos]].begin(),
															   firstSets[singRule[nextTokenPos]].end(), true);
										if(elements == 0)
										{
											if(testFirst)
												cout << "Next token's FIRST set is empty" << endl;
											for (int k = 2; k < firstUniSize; k++)
											{
												if (is_element(firstSets[tokenSym], k))
													firstSets[ruleLHS][k] = true;
											}
										}
										else    //rule IV
										{
											if (testFirst)
											{
												cout << "Next token exists, FIRST set is not empty" << endl;
												cout << "FIRST(" << universe[singRule[nextTokenPos]].lexeme << ") = { ";
												print_set(firstSets[singRule[nextTokenPos]]);
												cout << "}" << endl;
												cout << "Adding FIRST(" << universe[singRule[nextTokenPos]].lexeme
													 << ") to FIRST(" << universe[ruleLHS].lexeme << ")" << endl;
											}
											for (int k = 2; k < firstUniSize; k++)
											{
												if (is_element(firstSets[singRule[nextTokenPos]], k))
													firstSets[ruleLHS][k] = true;
												// TODO: not sure about last line
												//add nextToken's first set to firstA
											}
										}
									}
								}
								else    //frontMost does not have hash
								{
									if(testFirst)
									{
										cout << "# is NOT an element of " << universe[tokenSym].lexeme << endl;
									}
									//add firstOfToken to firstA
									for (int k = 2; k < firstUniSize; k++)
										if (is_element(firstOfToken, k))
											firstSets[ruleLHS][k] = true;
									break;
								}
							}
							else
							{
								if (testFirst)
									cout << "Token is empty" << endl;
								break;    //break forLoop; examine no other tokens because
								//frontmost is empty
							}
						}
						else    //current token is terminal
						{
							if (testFirst)
								cout << "Token is a terminal" << endl;
							//add firstOfToken to firstA
							for (int k = 2; k < firstUniSize; k++)
							{
								if (is_element(firstOfToken, k))
									firstSets[ruleLHS][k] = true;
							}
							if (testFirst)
							{
								cout << "FIRST(" << universe[ruleLHS].lexeme << ") = { ";
								print_set(firstSets[ruleLHS]);
								cout << "}" << endl;
							}
							break;
						}


					}
				}

				if (testFirst)
				{
					cout << "FIRST(" << universe[ruleLHS].lexeme << ") = { ";
					print_set(firstSets[ruleLHS]);
					cout << "}" << endl;
				}
			}
			else
			{
				if(testFirst)
				{
					cout << "FIRST(A) IS EMPTY" << endl;
				}
				if(singRuleSize == 1) //A -> #
				{
					firstSets[ruleLHS][0] = true;
				}
			}

			if(testFirst)
			{
				cout << "COMPARING: " << endl;
				cout << "FIRST(changeCheck) = { ";
				print_set(changeCheck);
				cout << "}" << endl;
				cout << "FIRST(" << universe[ruleLHS].lexeme << ") = { ";
				print_set(firstSets[ruleLHS]);
				cout << "}" << endl;
			}
			//For every item in universeFF
			for(int i = 0; i < firstUniSize; i++)
			{
				/*
				if(testFirst)
				{
					cout << "COMPARING: " << endl;
					cout << "Is " << universeFF[i].lexeme << " in FIRST("
						 << universe[ruleLHS].lexeme << ")? " << boolalpha
						 << is_element(firstSets[ruleLHS], i) << endl;
					cout << "Is " << universeFF[i].lexeme << " in FIRST(changeCheck)? "
						 << boolalpha << is_element(changeCheck, i) << endl;

					cout << "Is " << universeFF[i].lexeme << " in both FIRST sets? "
						 << boolalpha << (is_element(firstSets[ruleLHS], i)
										  == is_element(changeCheck, i)) << endl;
				}
				 */
				if (is_element(firstSets[ruleLHS], i) != is_element(changeCheck, i))
					noChanges = false;
			}

			if (testFirst && !noChanges)
			{
				cout << "Changes made. Loop will be restarted after rules are done.\n" << endl;
				cout << "FIRST(changeCheck) = { ";
				print_set(changeCheck);
				cout << "}" << endl;
				cout << "FIRST(" << universe[ruleLHS].lexeme << ") = { ";
				print_set(firstSets[ruleLHS]);
				cout << "}" << endl;
			}
			else if(testFirst && (j == (maxRules - 1)))
				cout << "No changes made for FIRST(" << universe[ruleLHS].lexeme
					 << ")" << endl;

		}

		if (testFirst && !noChanges)
			cout << "Changes made. Restarting Loop.\n" << endl;
		else if(testFirst)
			cout << "Done. Ending While Loop." << endl;

		if (testFirst)
		{
			cout << "\nFIRST sets so far:" << endl;
			for (int i = firstUniSize; i < universe_size; i++)
			{
				cout << "FIRST(" << universe[i].lexeme << ") = { ";
				print_set(firstSets[i]);
				cout << "}" << endl;
			}
		}

		if(testFirst)
			cout << "-------------------------------------------------------------" << endl;

	}
	if(testFirst && (loopBreak == loopMax))
		cout << "\nWhile loop forcibly broken" << endl;

	if (testFirst)
	{
		cout << "" << endl;
	}


	if (testFirst)
		cout << "\nDone with findFirstSets\n" << endl;


	return firstSets;
}



/************************************************
 * 					  TASK 4					*
 *			  Calculate FOLLOW Sets				*
 *												*
 * Functions:									*
 * 		vector< vector<bool> > findFollowSets()	*
 ************************************************/

/*
I. If S is the start symbol
add eof to FOLLOW(S)
	Translation:
		Put eof in Start Symbol

II. If A -> α B is a grammar rule
add FOLLOW(A) to FOLLOW(B)
	Translation:
		If there's a variable B at the end of A, then whatever follows A will also
		follow B,
		so put FOLLOW(A) in FOLLOW(B).

III. If A -> α B A_1 A_2 ... A_k is a grammar rule and
ɛ ∈ FIRST(A_1) and ɛ ∈ FIRST(A_2) and ... and ɛ ∈ FIRST(A_k)
add FOLLOW(A) to FOLLOW(B)
	Translation:
		If there's a variable B in A, and B is followed by other variables that ALL
		have ɛ in their FIRST sets, then whatever follows A will also follow B in
		the implementation of this rule,
		so put FOLLOW(A) in FOLLOW(B)

IV. If A -> α B A_1 A_2...A_k is a grammar rule
add FIRST(A_1) – {ɛ} to FOLLOW(B)
	Translation:
		If, in A, Variable B is followed by A_1, then the first thing in A_1 will
		follow what's in B in the implementation of this rule,
		so add FIRST(A_1) – {ɛ} to FOLLOW(B)

V. If A -> α B A_1 A_2 ... A_i A_(i+1) ... A_k is a grammar rule and
ɛ ∈ FIRST(A_1) and ɛ ∈ FIRST(A_2) and ... and ɛ ∈ FIRST(A_i)
add FIRST(A_(i+1)) – {ɛ} to FOLLOW(B)
	Translation:
		If there's a variable B in A, and B is followed by i other variables that
		have ɛ in their FIRST sets, which in turn are followed by an (i+1)th item,
		then then the first thing in that (i + 1)th item will also follow B in the
		implementation of this rule,
		so add FIRST(A_(i+1)) – {ɛ} to FOLLOW(B).
 */
vector< vector<bool> > findFollowSets()
{
	if (testFollow)
	{
		cout << "\nStarting findFollowSets" << endl;
	}

/**
 * I.	Put $ in Start Symbol
 *
 * II.	If there's a variable B at the end of A, then whatever follows A will also follow B,
 * 		so put FOLLOW(A) in FOLLOW(B).
 *
 * III.	If there's a variable B in A, and B is followed by other variables that ALL have #
 * 		in their FIRST sets,then whatever follows A will also follow B in the implementation
 * 		of this rule,
 * 		so put FOLLOW(A) in FOLLOW(B)
 *
 * IV. 	If, in A, Variable B is followed by A_1, then the first thing in A_1 will follow
 * 		what's in B in the implementation of this rule,
 * 		so add FIRST(A_1) – {#} to FOLLOW(B)
 *
 * V.	If there's a variable B in A, and B is followed by i other variables that have #
 * 		in their FIRST sets, which in turn are followed by an (i+1)th item, then then the
 * 		first thing in that (i + 1)th item will also follow B in the implementation of this
 * 		rule,
 * 		so add FIRST(A_(i+1)) – {#} to FOLLOW(B).
 */


	//FOLLOW Sets initialization
	//Setup
	vector<vector<bool> > followSets;
	vector< vector< bool> > firstSets = findFirstSets();
	int folUniSize = (int) universeFF.size();
	bool noChanges = false;

	for (int i = 0; i < universe_size; i++)
	{
		vector<bool> folUni((unsigned long) folUniSize);
		followSets.push_back(folUni);
	}

	//I. Put $ in Start Symbol
	followSets[folUniSize][1] = true;

	if (testFollow)
	{
		cout << "\nFOLLOW sets so far:" << endl;
		for (int i = 0; i < universe_size; i++)
		{
			cout << "FOLLOW(" << universe[i].lexeme << ") = { ";
			print_set(followSets[i]);
			cout << "}" << endl;
		}
	}
/*
 * Pseudocode:
 *
 *
 *
 * II.	If there's a variable B at the end of A, then whatever follows A will also follow B,
 * 		so put FOLLOW(A) in FOLLOW(B).
 * 			if(A -> α B)
 * 				FOLLOW(B) += FOLLOW(A)
 *
 * III.	If there's a variable B in A, and B is followed by other variables that ALL have #
 * 		in their FIRST sets, then whatever follows A will also follow B in the implementation
 * 		of this rule,
 * 		so put FOLLOW(A) in FOLLOW(B)
 * 			if(A -> α B A_1 ... A_k)			//B is followed by stuff
 * 				for ALL token A_1 through A_k
 * 					if(FIRST(token) includes #	//and the stuff all has # in their FIRST sets
 * 						FOLLOW(B) += FOLLOW(A)
 *
 *
 * IV. 	If, in A, Variable B is followed by C, then the first thing in C will follow
 * 		what's in B in the implementation of this rule,
 * 		so add FIRST(C) – {#} to FOLLOW(B)
 * 			if(A -> α B C)
 * 				FOLLOW(B) += FIRST(C) - {#}
 *
 * V.	If there's a variable B in A, and B is followed by i other variables that have #
 * 		in their FIRST sets, which in turn are followed by an (i+1)th item, then then the
 * 		first thing in that (i + 1)th item will also follow B in the implementation of this
 * 		rule,
 * 		so add FIRST(A_(i+1)) – {#} to FOLLOW(B).
 * 			if(A -> α B A_1 ...A_i A_(i+1) ... A_k)			//B is followed by stuff
 * 				for each token A_1 through A_i
 * 					if(FIRST(token) includes #
 * 						FOLLOW(B) += FOLLOW(A)
 *
 */

	/*
	    //1. A -> #
	        //Nothing. Ignore rule.
	    //2. A -> B
	        //1. B is terminal
	            //Nothing. Ignore rule.
	        //2. B is a non-terminal
	            //1. B is at end of rule
	                //add FOLLOW(A) to FOLLOW(B)
	            //2. B is followed by C
	                //1. C is a terminal
	                    //add FIRST(C) to FOLLOW(B)
	                //2. C is a non-terminal
	                    //1. # is not in FIRST(C)
	                        //add FIRST(C) - {#} to FOLLOW(B)
	                    //2. # is in FIRST(C)
	                        //1. C is last token in rule
	                            //add FOLLOW(A) to FOLLOW(B)
                            //2. C is followed by more things, all represented as a single D
                                //1. All tokens in D contain # in their FIRST sets
                                    //add FOLLOW(A) to FOLLOW(B)
                                //2. All tokens up until X in D contain #
                                    //add FIRST(X) to FOLLOW(B)
	 */




	loopBreak = 0;
	while ((!noChanges && (loopBreak < loopMax)) || (!noChanges && !testFollow))
	{
		loopBreak++;
		if (testFollow)
		{
			cout << "Loop #" << loopBreak << endl;
			cout << "\nFOLLOW sets so far:" << endl;
			for (int i = folUniSize; i < universe_size; i++)
			{
				cout << "FOLLOW(" << universe[i].lexeme << ") = { ";
				print_set(followSets[i]);
				cout << "}" << endl;
			}
		}


		noChanges = true;
		vector<bool> changeCheck;
		vector<int> singRule;
		//for each rule
		for (int eachRule = 0; eachRule < maxRules; eachRule++)
		{
			singRule = ruleInts[eachRule];
			int ruleLHS = singRule[0];
			changeCheck = followSets[ruleLHS];
			int singRuleSize = (int) singRule.size();
			if (testFollow)
			{
				cout << "----------" << endl;
				cout << "\nCurrent rule: " << eachRule + 1 << "/" << maxRules
					 << "\n" << singRuleString(singRule) << endl;
				cout << "Rule size: " << singRuleSize << endl;
				cout << "FOLLOW set at start of loop:" << endl;
				cout << "FOLLOW(" << universe[eachRule].lexeme << ") = { ";
				print_set(followSets[eachRule]);
				cout << "}" << endl;
			}
			vector<bool> firstB;

			//A -> B
			if (singRuleSize != 1)
			{
				int tokenSym;
				vector<bool> folOfToken;
				//for each token in singRule A
				for (int tokenPos = 1; tokenPos < singRuleSize; tokenPos++)
				{
					tokenSym = singRule[tokenPos];
					int nextTokenSym;
					if (testFollow)
						cout << "\nToken #" << tokenPos << ": "
							 << universe[tokenSym].lexeme << endl;

					tokenSym = singRule[tokenPos];
					folOfToken = followSets[tokenSym];
					if (testFollow)
					{
						cout << "FOLLOW(" << universe[tokenSym].lexeme << ") = { ";
						print_set(folOfToken);
						cout << "}" << endl;
					}
					//B is a non-terminal
					if ((singRule[tokenPos] >= folUniSize)
						&& (singRule[tokenPos] < universe_size))
					{
						//B is at end of rule
						if (tokenPos == (singRuleSize - 1))
						{
							//add FOLLOW(A) to FOLLOW(B)
							for (int k = 1; k < folUniSize; k++)
							{
								if (is_element(followSets[ruleLHS], k))
									folOfToken[k] = true;
							}
						}
						else //B is followed by C
						{
							nextTokenSym = singRule[tokenPos + 1];
							//C is a terminal
							if (nextTokenSym < folUniSize)
							{
								//add FIRST(C) to FOLLOW(B)
								for (int k = 1; k < folUniSize; k++)
								{
									if (is_element(firstSets[nextTokenSym], k))
										folOfToken[k] = true;
								}
							}
							else //C is a non-terminal
							{
								//Regardless of whether # is in FIRST(C)
								//add FIRST(C) - {#} to FOLLOW(B)
								for (int k = 1; k < folUniSize; k++)
								{
									if (is_element(firstSets[nextTokenSym], k))
										folOfToken[k] = true;
								}
								//# is in FIRST(C)
								if (is_element(firstSets[nextTokenSym], 0))

								{
									//C is last token in rule
									if ((tokenPos + 2) == singRuleSize)
									{
										//add FOLLOW(A) to FOLLOW(B)
										for (int k = 1; k < folUniSize; k++)
										{
											if (is_element(followSets[ruleLHS], k))
												folOfToken[k] = true;
										}
									}
									else //C is not last token
									{
										bool allHashes = true;
										int xPos = tokenPos + 2;
										for (int eachToken = (tokenPos + 2); eachToken < singRuleSize; eachToken++)
										{
											if (!(is_element(firstSets[singRule[eachToken]], 0)))
											{
												allHashes = false;
												xPos = eachToken;
												break;
											}
										}

										//All tokens after C contain # in their FIRST sets
										if (allHashes)
										{
											//add FOLLOW(A) to FOLLOW(B)
											for (int k = 1; k < folUniSize; k++)
											{
												if (is_element(followSets[ruleLHS], k))
													folOfToken[k] = true;
											}
										}
										else//All tokens up until X in D contain #
										{
											//add FIRST(X) to FOLLOW(B)
											for (int k = 1; k < folUniSize; k++)
											{
												if (is_element(firstSets[singRule[xPos]], k))
													folOfToken[k] = true;
											}
										}

									}
								}
							}
						}
					}
					followSets[tokenSym] = folOfToken;
				}
				//else B is terminal
				//Nothing. Ignore rule.

				//else A -> #
				//Nothing. Ignore rule.

				if (testFollow)
				{
					cout << "COMPARING: " << endl;
					cout << "FOLLOW(changeCheck) = { ";
					print_set(changeCheck);
					cout << "}" << endl;
					cout << "FOLLOW(" << universe[ruleLHS].lexeme << ") = { ";
					print_set(followSets[ruleLHS]);
					cout << "}" << endl;
				}
				//For every item in universeFF
				for (int i = 0; i < folUniSize; i++)
				{
					/*
					if(testFirst)
					{
						cout << "COMPARING: " << endl;
						cout << "Is " << universeFF[i].lexeme << " in FIRST("
							 << universe[ruleLHS].lexeme << ")? " << boolalpha
							 << is_element(firstSets[ruleLHS], i) << endl;
						cout << "Is " << universeFF[i].lexeme << " in FIRST(changeCheck)? "
							 << boolalpha << is_element(changeCheck, i) << endl;

						cout << "Is " << universeFF[i].lexeme << " in both FIRST sets? "
							 << boolalpha << (is_element(firstSets[ruleLHS], i)
											  == is_element(changeCheck, i)) << endl;
					}
					 */
					if (is_element(followSets[ruleLHS], i) != is_element(changeCheck, i))
						noChanges = false;
				}


				if (testFollow && !noChanges)
				{
					cout << "Changes made. Loop will be restarted after rules are done.\n" << endl;
					cout << "FOLLOW(changeCheck) = { ";
					print_set(changeCheck);
					cout << "}" << endl;
					cout << "FOLLOW(" << universe[tokenSym].lexeme << ") = { ";
					print_set(followSets[tokenSym]);
					cout << "}" << endl;
				}
				else if (testFollow && (eachRule == (maxRules - 1)))
					cout << "No changes made for FIRST(" << universe[ruleLHS].lexeme
						 << ")" << endl;
			}

		}
		if (testFollow && !noChanges)
			cout << "Changes made. Restarting Loop.\n" << endl;
		else if(testFirst)
			cout << "Done. Ending While Loop." << endl;

		if (testFollow)
		{
			cout << "\nFOLLOW sets so far:" << endl;
			for (int i = folUniSize; i < universe_size; i++)
			{
				cout << "FOLLOW(" << universe[i].lexeme << ") = { ";
				print_set(followSets[i]);
				cout << "}" << endl;
			}
		}

		if(testFollow)
			cout << "-------------------------------------------------------------" << endl;

	}
	if(testFollow && (loopBreak == loopMax))
		cout << "\nWhile loop forcibly broken" << endl;

	if (testFollow)
	{
		cout << "" << endl;
	}


	if (testFollow)
		cout << "\nDone with findFollowSets\n" << endl;


	return followSets;
}

/**********
 * TASK 5 *
 **********/

/*****************
 * MAIN FUNCTION *
 *****************/

int main (int argc, char* argv[])
{
    /***********************
     * INITIALIZING THINGS *
     ***********************/
    myTests();

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
                singRuleStr += "#";

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

    maxRules = (int)ruleList.size();

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

	//Originally a vector for task 2, but seems useful for the others,
	//so made global variable and moved up to task 0 to do every time
	ruleInts = labelRules();

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
    //None
    //Case 2
    vector<bool> usableSyms;
    vector<bool> newRules;
    vector<string> ruleStrings;
    //Case 3
	vector< vector<bool> > firstSets;
	int uniFF_Size = universeFF.size();
    //Case 4
	vector< vector<bool> > followSets;
    //Case 5
    if(testing)
		if((task > 0) && (task < 6))
	        cout << "\nStarting task #" << task << endl;

    switch (task) {
        case 1:
            cout << ruleCounter() << endl;
            break;

        case 2:
            //Task 2: Find Useless Symbols
            usableSyms = findUsableSyms();
            newRules = findUsableRules(usableSyms);
            ruleStrings = rulesAsString(newRules);
            printRules(ruleStrings);
            break;

        case 3:
            // TODO: tidy up task 3; 29/30 online
            //Task 3: Calculate FIRST Sets
			firstSets = findFirstSets();
			for(int i = uniFF_Size; i < universe_size; i++)
			{
				cout << "FIRST(" << universe[i].lexeme << ") = { ";
				print_set(firstSets[i]);
				cout << "}" << endl;
			}

			break;

        case 4:
            // TODO: perform task 4.
            //Task 4: Calculate FOLLOW Sets
			followSets = findFollowSets();
			for(int i = uniFF_Size; i < universe_size; i++)
			{
				cout << "FOLLOW(" << universe[i].lexeme << ") = { ";
				print_set(followSets[i]);
				cout << "}" << endl;
			}
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
