#include "InputGenerator.h"
#include <cstdlib>

TurnInput RandomInputGenerator::generate(int /*round*/) const {
    return { (std::rand() % 10) + 1 };
}

TurnInput FixedInputGenerator::generate(int round) const {
    return { round * 3 };   // 3, 6, 9 for rounds 1-3
}
