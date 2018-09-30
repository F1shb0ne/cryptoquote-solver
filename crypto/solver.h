#pragma once

#include <iostream>

#include "../quote.h"
#include "letterset.h"

using namespace std;

class Solver {

public:
    static double Solve(Quote &quote, LetterSet &letterSet, string name, int threadId);
    static void Disable();
};

