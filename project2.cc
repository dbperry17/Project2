#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "lexer.h"
#include "inputbuf.h"

using namespace std;

int main (int argc, char* argv[])
{
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
    LexicalAnalyzer lexer;
    Token token;

    token = lexer.GetToken();
    token.Print();
    while (token.token_type != DOUBLEHASH)
    {
        token = lexer.GetToken();
        token.Print();
    }

    cout << "test" << endl;

    //310 STUFF BELOW
/*	int k = 0;	//n = 2^k blocks to be allocated
	int t = 0;	//size of hash table
	int c = 0;	//number of commands
	string temp;

	//Creating a block of memory
	getline(cin, temp, '\n');
	k = stoi(temp);
	int n = pow(2, k);
	char* memBlock = new char[n];
	for(int i = 0; i < n; i++)
		memBlock[i] = BLANK;

	//creating heap
	heapEntry* myHeap = new heapEntry[n+1];
	for(int i = 0; i < n; i++)
	{
		myHeap[i].blockSize = 0;
		myHeap[i].offset = -1;
	}
	myHeap[1].blockSize = n;
	myHeap[1].offset = 0;
	int num = 1;
	int* heapSize = &num;

	//Creating a Symbol Table
	getline(cin, temp, '\n');
	t = stoi(temp);
	symbolTableEntry* syms = new symbolTableEntry[t];
	for(int i = 0; i < t; i++)
	{
		syms[i].type = EMPTY;
		syms[i].noBytes = 1;
		syms[i].symbol[0] = BLANK;
		syms[i].symbol[1] = STRTERM;
	}

	getline(cin, temp, '\n');
	c = stoi(temp);



	parseInstructions(n, c, t, memBlock, syms,myHeap,heapSize);

	delete(myHeap);
	delete(memBlock);
	delete(syms);

	fflush(stdin);
*/	//310 STUFF ABOVE

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
