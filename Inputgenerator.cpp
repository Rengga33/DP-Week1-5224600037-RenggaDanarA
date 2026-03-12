#include "InputGenerator.h"
#include <cstdlib>

TurnInput RandomInputGenerator::generate(int /*round*/) const {
    return { (std::rand() % 10) + 1 };
}

TurnInput FixedInputGenerator::generate(int round) const {
    return { round * 3 };   // 3, 6, 9 for rounds 1-3
}

// WeightedRandomInputGenerator
// Rolls two dice (1-10) and takes the higher value,
// then adds (round - 1) as a flat bonus — later rounds trend higher.
TurnInput WeightedRandomInputGenerator::generate(int round) const {
    int rollA = (std::rand() % 10) + 1;
    int rollB = (std::rand() % 10) + 1;
    int best  = (rollA > rollB) ? rollA : rollB;
    int value = best + (round - 1);     // round 1: +0, round 2: +1, round 3: +2
    if (value > 10) value = 10;         // cap at 10
    return { value };
}
