//============================================================================
// Name        : main.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "menuparser/ShellMenuParser.h"

using namespace std;


int main(int argc, char* argv[]) {

	ShellMenuParser* menuParser = new ShellMenuParser();
	menuParser->parseAndExecute(argc,argv);

	return 0;
}
