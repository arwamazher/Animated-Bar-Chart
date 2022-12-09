/**********************************************************************************************************************
	Program: Animated BarChart
	Description: This application uses BarChartAnimate (which uses BarChart, which uses Bar) to produce 
							 an animated bar chart. 
	Class: CS 251, Wednesday 10am lab
	System used: Replit
	Author: Arwa Mazher

	CREATIVE COMPONENT: Ask the user what playback speed they want. The default is 50000 microseconds.

// Bar Chart Animation
//
// Adam Koehler
// U. of Illinois, Chicago
// Fall 2022
//
// Original iteration of program developed by:
// Shanon Reckinger
// U. of Illinois, Chicago 
**********************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;


int main() {

	string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}
	
	bca.animate(cout, 12, -1);

	// FOR CREATIVE COMPONENT: 
	// Ask the user what playback speed they want. The default is 50000 microseconds.
	// Note: smaller values like 10000 will run faster than larger ones like 80000.
	// Comment out line 46 and uncomment lines below to run creative component.
	
	// int newSpeed = 50000;
	// cout << "The default speed is 50000 microseconds. Enter a new speed you would like to play" << endl;
	// cin >> newSpeed;
	// bca.animate(cout, 12, 10, newSpeed); 

  return 0;
}


// VALGRIND SUMMARY:
// ==1363== 
// ==1363== HEAP SUMMARY:
// ==1363==     in use at exit: 0 bytes in 0 blocks
// ==1363==   total heap usage: 82,196 allocs, 82,196 frees, 8,386,222 bytes allocated
// ==1363== 
// ==1363== All heap blocks were freed -- no leaks are possible
// ==1363== 
// ==1363== For lists of detected and suppressed errors, rerun with: -s
// ==1363== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)