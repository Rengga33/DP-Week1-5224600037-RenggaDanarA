#include "RewardSystem.h"

int SimpleReward::compute(int baseScore) const {
    return baseScore;
}

int HalvingReward::compute(int baseScore) const {
    return (baseScore + 1) / 2;
}

// reward = baseScore + 2
int FlatBonusReward::compute(int baseScore) const {
    return baseScore + 2;
}

// reward = baseScore * 2 on even rounds, baseScore on odd rounds
EvenRoundDoubleReward::EvenRoundDoubleReward(int& roundRef)
    : round_(roundRef)
{}

int EvenRoundDoubleReward::compute(int baseScore) const {
    return (round_ % 2 == 0) ? baseScore * 2 : baseScore;
}
