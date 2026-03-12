#pragma once

#include "InputGenerator.h"
#include "ScoreSystem.h"
#include "RewardSystem.h"
#include "ShopSystem.h"

/*
 * RunSession — THE INVARIANT
 *
 * Rules:
 *   • Owns the phase ORDER — this never changes.
 *   • Contains NO scoring logic.
 *   • Contains NO reward logic.
 *   • Contains NO input generation logic.
 *   • Delegates all mutable behavior via abstract interfaces.
 */
class RunSession {
public:
    RunSession(IInputGenerator& gen,
               IScoringRule&    scorer,
               IRewardRule&     reward,
               ShopSystem&      shop,
               int totalRounds = 3);

    void start();

private:
    void runOneRound();

    IInputGenerator& generator_;
    IScoringRule&    scorer_;
    IRewardRule&     reward_;
    ShopSystem&      shop_;

    int totalRounds_;
    int currentRound_;
    int money_;
};
