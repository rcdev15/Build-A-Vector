

#ifndef VECTORTEST_H
#define VECTORTEST_H


/* Test Base Interface */

#include <iostream>
#include <set>
#include <string>
#include <cmath> // for fabsf and fabs

using namespace std;

class VectorTest {
    ostream &os;
    int passed;                             // tests passed
    int total;                              // # tests
    int lastline;                           // line # of most recent test
    set<int> badlines;                      // failed tests
    bool skip;                              // skip a line before title?

public:
    VectorTest(ostream &os);
    ~VectorTest();                         // writes end description

    void desc(const string &message, int line); // write line/description
    void check(bool test, int line);        // record if a check passes
    void result();
    bool ok() const;                        // true iff all tests passed
};


//cpp macro -> https://stackoverflow.com/questions/10582500/c-macro-and-default-arguments-in-function
#define DESC(x) desc(x, __LINE__)
#define CHECK(test) check(test, __LINE__)


inline bool epsilon_equals(float a, float b, float epsilon = 0.00001) {
    return (fabsf(a - b) <= epsilon);
}

inline bool epsilon_equals(double a, double b, double epsilon = 0.00001) {
    return (fabs(a - b) <= epsilon);
}


#endif // TESTBASE_HH
