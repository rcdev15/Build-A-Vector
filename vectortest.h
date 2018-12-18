

#ifndef VECTORTEST_H
#define VECTORTEST_H


/* Test Base Interface */

#include <iostream>
#include <set>
#include <string>
#include <cmath>

using namespace std;


class VectorTest {                         // displays test results
    ostream &os;                            // output stream to use
    int passed;                             // # of tests which passed
    int total;                              // total # of tests
    int lastline;                           // line # of most recent test
    set<int> badlines;                      // line #'s of failed tests
    bool skip;                              // skip a line before title?

public:
    VectorTest(ostream &os);               // writes header
    ~VectorTest();                         // writes summary

    void desc(const string &message, int line); // write line/description
    void check(bool test, int line);        // record if a check passes
    void result();
    bool ok() const;                        // true iff all tests passed
};


//TODO: Replace this ugly hack
#define DESC(x) desc(x, __LINE__)
#define CHECK(test) check(test, __LINE__)


inline bool epsilon_equals(float a, float b, float epsilon = 0.00001) {
    return (fabsf(a - b) <= epsilon);
}

inline bool epsilon_equals(double a, double b, double epsilon = 0.00001) {
    return (fabs(a - b) <= epsilon);
}

#endif // TESTBASE_HH
