#include "RewardSystem.h"

int SimpleReward::compute(int baseScore) const {
    return baseScore;
}

int HalvingReward::compute(int baseScore) const {
    return (baseScore + 1) / 2;
}
