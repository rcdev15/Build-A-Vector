
#include "vectortest.h"

#include <cassert>
#include <cstdlib>
#include <sstream>


VectorTest::VectorTest(ostream &os) : os(os), passed(0), total(0),
    lastline(0), skip(false) {

    os << "line: ";
    os.width(65);
    os.setf(ios::left, ios::adjustfield);
    os << "description" << " result" << endl;
    os.width(78);
    os.fill('~');
    os << "~" << endl;
    os.fill(' ');
    os.setf(ios::right, ios::adjustfield);
}

void VectorTest::desc(const string &message, int line) {
    if ((lastline != 0) || ((message[0] == '-') && skip))
        os << '\n';

    os.width(4);
    os << line << ": ";
    os.width(65);
    os.setf(ios::left, ios::adjustfield);
    os << message << " ";
    os.setf(ios::right, ios::adjustfield);
    os.flush();

    lastline = line;
    skip = true;
}


void VectorTest::check(bool test, int line) {
    if (!test)
        badlines.insert(line);
}


void VectorTest::result() {
    assert(lastline != 0);

    // See if i havent added any more values to the badlines collection
    auto iter = badlines.lower_bound(lastline);
    if (iter == badlines.end()) {
        os << "ok" << '\n';
        passed++;
    }
    else {
        os << "ERROR\n";
        while (iter != badlines.end()) {
            os << "\tFailure detected on line " << *iter << '\n';
            iter++;
        }
    }
    total++;
    lastline = 0;
}

VectorTest::~VectorTest() {
    os << "\nPassed " << passed << "/" << total << " tests.\n\n";
    if (badlines.size() > 2) {
        os << "fix fails";
    }
}

bool VectorTest::ok() const {
    return passed == total;
}
