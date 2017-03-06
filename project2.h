//
// Created by Denise Perry on 3/5/17.
//

#ifndef PROJECT2_H
#define PROJECT2_H

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
bool testUseSyms = true;
bool testUseRules = true;
bool testRuleStr = true;
bool testRulePrint = true;

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

void printRules(vector<string> rules)
{}

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

//default method
vector<string> rulesAsString(vector < vector<int> > ruleInts)
{}

//For filtered rules
vector<string> rulesAsString(vector < vector<int> > ruleInts, vector<bool> validRule)
{}

string printSingRule(vector<int> singRule)
{}

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

vector<bool> findReachable(vector < vector<int> > ruleInts, vector<bool> genSyms)
{}

vector<bool> findUsableSyms(vector<vector<int> > ruleInts)
{}

vector<bool> findUsableRules(vector< vector<int> > ruleInts, vector<bool> usableSyms)
{}

/*****************
 * MAIN FUNCTION *
 *****************/

int main (int argc, char* argv[]){}
#endif //PROJECT2_H
