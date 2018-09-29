#pragma once

#include <iostream>

#include "../quote.h"
#include "letterset.h"

using namespace std;

class Solver {
private:
    static bool Enabled;
public:
    static double Solve(int threadid, Quote &, LetterSet &);
    static bool isEnabled();
    static void Disable();
};
