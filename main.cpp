#include <cstdlib>
#include <ctime>

#include "InputGenerator.h"
#include "ScoreSystem.h"
#include "RewardSystem.h"
#include "ShopSystem.h"
#include "RunSession.h"

/*
 * Swap any of these types to change behavior —
 * RunSession and the phase order never need to change.
 *
 *   Generator : RandomInputGenerator         (uniform 1-10)
 *             | WeightedRandomInputGenerator  (rolls 2 dice, takes best + round bonus)  ← ACTIVE
 *             | FixedInputGenerator           (3, 6, 9)
 *   Scoring   : SimpleScoring        | BonusOddScoring
 *   Reward    : SimpleReward                          (gain == baseScore)
 *             | FlatBonusReward                       (gain == baseScore + 2)           ← ACTIVE
 *             | EvenRoundDoubleReward(currentRound)   (gain == baseScore * 2 on even rounds)
 *             | HalvingReward                         (gain == baseScore / 2)
 */
WeightedRandomInputGenerator inputSystem;
SimpleScoring                scoreSystem;
FlatBonusReward              rewardSystem;
ShopSystem                   shopSystem;

RunSession session(inputSystem, scoreSystem, rewardSystem, shopSystem);

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    session.start();
    return 0;
}
