// bar.h
// A Bar aggregates related information (name, value, and category) for use in a bar chart.

#include <iostream>
#include <string>
#include "myrandom.h" // used in graders, do not remove
using namespace std;

//
// Bar
//
class Bar {
// Private member variables for a Bar object
 private:
	string name;
	int value;
	string category;

 public:
    // default constructor:
    Bar() {
      name = "";
			value = 0;
			category = "";
    }

    // parameterized constructor:
    Bar(string name, int value, string category) {
			this->name = name;
			this->value = value;
			this->category = category;
    }

    // destructor:
    virtual ~Bar() {}

    // getName:
		string getName() {
			return name;
		}
		
			// getValue:
		int getValue() {
			return value;
		}

    	// getCategory:
		string getCategory() {
	    return category;
		}
	
		// The following operators allow you to compare two Bar objects based on the Bar's value.
			// < operator
		bool operator<(const Bar &other) const {
	        return this->value < other.value;
		}
			// <= operator
		bool operator<=(const Bar &other) const {
	        return this->value <= other.value;
		}
			// > operator
		bool operator>(const Bar &other) const {
	        return this->value > other.value;
		}
			// >= operator
		bool operator>=(const Bar &other) const {
	        return this->value >= other.value;
		}
};