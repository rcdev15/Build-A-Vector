
#include "vector.h"
#include "vectortest.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;


/*===========================================================================
 * TEST FUNCTIONS
 *
 * These are called by the main() function at the end of this file.
 ============================================================================*/


Vector<int> makeTestVector(int n) {
    Vector<int> v;
    for (int i = 0; i < n; i++)
        v.push_back(i);

    return v;
}


/*! Test the Vector constructors. */
void test_constructors(VectorTest &vTest) {
    vTest.DESC("Vector size constructor");
    Vector<int> v1;
    vTest.CHECK(v1.size() == 0);
    vTest.CHECK(v1.capacity() == 0);

    Vector<float> v2(10);
    vTest.CHECK(v2.size() == 10);
    vTest.CHECK(v2.capacity() >= 10);
    vTest.result();

    vTest.DESC("Vector copy constructor / index operator");
    Vector<int> vo;
    vo.push_back(3);
    vo.push_back(5);
    vo.push_back(4);

    Vector<int> v3(vo);
    vTest.CHECK(vo[0] == 3);
    vTest.CHECK(vo[1] == 5);
    vTest.CHECK(vo[2] == 4);
    vTest.CHECK(v3[0] == 3);
    vTest.CHECK(v3[1] == 5);
    vTest.CHECK(v3[2] == 4);

    v3[1] = -2;

    vTest.CHECK(vo[0] == 3);
    vTest.CHECK(vo[1] == 5);
    vTest.CHECK(vo[2] == 4);
    vTest.CHECK(v3[0] == 3);
    vTest.CHECK(v3[1] == -2);
    vTest.CHECK(v3[2] == 4);
    vTest.result();
}


void test_bad_indexes(VectorTest &vTest) {
    Vector<int> v;

    vTest.DESC("Vector indexing reports bad indexes via out_of_range");
    try {
        v[0] = 5;
        vTest.CHECK(false);  // Shouldn't get here.
    } catch (out_of_range &e) {
        vTest.CHECK(true);   // PASS
    } catch (...) {
        vTest.CHECK(false);  // Caught unexpected exception!
    }

    try {
        v[-1];
        vTest.CHECK(false);  // Shouldn't get here.
    } catch (out_of_range &e) {
        vTest.CHECK(true);   // PASS
    } catch (...) {
        vTest.CHECK(false);  // Caught unexpected exception!
    }
    // This should work now.
    v.push_back(5);
    vTest.CHECK(v[0] == 5);

    try {
        v[1] = 5;
        vTest.CHECK(false);  // Shouldn't get here.
    } catch (out_of_range &e) {
        vTest.CHECK(true);   // PASS
    } catch (...) {
        vTest.CHECK(false);  // Caught unexpected exception!
    }
    vTest.result();
}


void test_assignment(VectorTest &vTest) {
    Vector<int> v1, v2;

    vTest.DESC("Vector assignment operator");
    v1 = makeTestVector(30);
    v2 = v1;
    vTest.CHECK(v2.size() == 30);
    for (int i = 0; i < 30; i++) {
        vTest.CHECK(v1[i] == i);
        vTest.CHECK(v2[i] == i);
    }
    v2[12] = -63;
    vTest.CHECK(v1[12] == 12 && v2[12] == -63);

    Vector<int> v3;
    for (int i = 0; i < 1000; i++)
        v3.push_back(i);

    v3 = v1;
    vTest.CHECK(v3.size() == 30);
    for (int i = 0; i < 30; i++) {
        vTest.CHECK(v3[i] == i);
        vTest.CHECK(v1[i] == i);
    }
    v3[12] = -63;
    vTest.CHECK(v1[12] == 12 && v3[12] == -63);
    vTest.result();
}


void test_push_back(VectorTest &vTest) {
    vTest.DESC("push_back() stores values and grows Vector properly");

    Vector<int> v;
    int i;
    const int NUMVALS = 70000;

    // Put 20,000 ints into the vector.
    for (i = 0; i < NUMVALS; i++)
        v.push_back(i);

    // Verify that the values look correct through array indexing.
    for (i = 0; i < NUMVALS; i++)
        vTest.CHECK(v[i] == i);

    vTest.result();
}


/*! This program is a simple test-suite for the Vector class. */
int main() {

    cout << "Testing basic Vector class-template memory "
            "management.\n\n";

    VectorTest vTest(cout);
    test_constructors(vTest);
    test_bad_indexes(vTest);
    test_assignment(vTest);
    test_push_back(vTest);

    // Return 0 if everything passed, nonzero if something failed.
    return !vTest.ok();
}
