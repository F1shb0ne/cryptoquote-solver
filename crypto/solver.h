#pragma once

#include <iostream>
#include "pthread.h"

#include "../quote.h"
#include "letterset.h"

using namespace std;

class Solver {
private:
    static bool Enabled;
    static pthread_mutex_t mutex;

public:
    static void Init();
    static void Destroy();
    static double Solve(Quote &quote, LetterSet &letterSet, string name, int threadId);
    static void Disable();
    static bool isEnabled();
};

