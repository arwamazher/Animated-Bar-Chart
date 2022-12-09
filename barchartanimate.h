// barchartanimate.h
// Adds frames to an array of barcharts and then animates them

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used by graders, do not remove
#include "barchart.h"
  
using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
		int colorIndex;
		string title, xlabel, source;
    map<string, string> colorMap;

 public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
			barcharts = new BarChart[4];
			size = 0;
			capacity = 4;
			colorIndex = 0;
			this->title = title;
			this->xlabel = xlabel;
			this->source = source;
    }

    // destructor:
    // Called automatically by C++ to free the memory associated by BarChartAnimate.
    virtual ~BarChartAnimate() {
			for (int i = 0; i < size; i++) {
				barcharts[i].clear();
			}
			if (barcharts != nullptr) {
				delete[] barcharts;
			}
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity
    void addFrame(ifstream &file) {
			string line;
			int numRecords;
			string frame;
			string name;
			string country;
			int value;
			string category;

			if (size == capacity) {
				int newCapacity = capacity * 2;
				BarChart* newBarChart = new BarChart[newCapacity];

				// copy over elements
				for (int i = 0; i < size; i++) {
					newBarChart[i] = barcharts[i];
				}

				// delete old array and update private data members
				delete[] barcharts;
				barcharts = newBarChart;
				capacity = newCapacity;
			}

			// skip first blank line
			getline(file, line);
			if (file.eof()) {
				return;
			}
			
			// get numRecords
			getline(file, line);
			numRecords = stoi(line);
			
			barcharts[size] = BarChart(numRecords);

			// For each line (bar) in the frame, parse the information into corresponding variables
			for (int i = 0; i < numRecords; i++) {
				getline(file, line);
				stringstream ss(line);
				
				if (line != "") {
					getline(ss, frame, ',');
					getline(ss, name, ',');
					getline(ss, country, ',');
					string tempValue;
					getline(ss, tempValue, ',');
					value = stoi(tempValue);
					getline(ss, category, ',');
				}

				// Add bar and set the frame
				barcharts[size].addBar(name, value, category);
				barcharts[size].setFrame(frame);

				// Assign colors
				if (colorIndex == COLORS.size()) {
					colorIndex = 0;
				}
				
				if (colorMap.count(category) != 1) {
					colorMap[category] = COLORS[colorIndex];
					colorIndex++;
				}

			} // end for (int i...)
			
			size++;
			
    } // end addFrame()

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
		void animate(ostream &output, int top, int endIter) {
			unsigned int microsecond = 50000;
	
			// print out the whole file
			if (endIter == -1) {
				endIter = size;
			}
	
			// print frames
			for (int i = 0; i < endIter; i++) {
				usleep(3 * microsecond);
				output << CLEARCONSOLE;
	
				output << WHITE << this->title << endl;
				output << WHITE << this->source << endl;
				barcharts[i].graph(output, colorMap, top);
				output << WHITE << this->xlabel << endl;
				output << WHITE << "Frame: " << this->barcharts[i].getFrame() << endl;
			}
			
		} // end animate()
	
	// CREATIVE COMPONENT: CHANGE PLAYBACK SPEED
		void animate(ostream &output, int top, int endIter, int newSpeed) {
			unsigned int microsecond = newSpeed;
	
			// print out the whole file
			if (endIter == -1) {
				endIter = size;
			}
	
			// print frames
			for (int i = 0; i < endIter; i++) {
				usleep(3 * microsecond);
				output << CLEARCONSOLE;
	
				output << WHITE << this->title << endl;
				output << WHITE << this->source << endl;
				barcharts[i].graph(output, colorMap, top);
				output << WHITE << this->xlabel << endl;
				output << WHITE << "Frame: " << this->barcharts[i].getFrame() << endl;
			}
			
		} // end animate() for CREATIVE COMPONENT

    // Public member function.
    // Returns the size of the BarChartAnimate object.
    int getSize() {
      return size;  
    }

    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    BarChart& operator[](int i) {
			if (i < 0 || i >= size) {
				throw out_of_range("BarChartAnimate: i out of bounds");
			}
			return this->barcharts[i];
    }
};