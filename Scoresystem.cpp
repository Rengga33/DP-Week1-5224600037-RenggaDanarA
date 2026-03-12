#include "ScoreSystem.h"

int SimpleScoring::compute(TurnInput input) const {
    return input.value;
}

int BonusOddScoring::compute(TurnInput input) const {
    return (input.value % 2 != 0) ? input.value * 2 : input.value;
}
