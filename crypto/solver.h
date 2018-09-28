#pragma once

#include <iostream>

#include "../quote.h"
#include "letterset.h"

using namespace std;

class Solver {

public:
    static double Solve(int threadid, Quote &, LetterSet &);

};
