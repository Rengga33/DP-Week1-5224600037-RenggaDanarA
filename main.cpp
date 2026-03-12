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
 *   Generator : RandomInputGenerator | FixedInputGenerator
 *   Scoring   : SimpleScoring        | BonusOddScoring
 *   Reward    : SimpleReward         | HalvingReward
 */
RandomInputGenerator inputSystem;
SimpleScoring        scoreSystem;
SimpleReward         rewardSystem;
ShopSystem           shopSystem;
a
RunSession session(inputSystem, scoreSystem, rewardSystem, shopSystem);

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    session.start();
    return 0;
}
