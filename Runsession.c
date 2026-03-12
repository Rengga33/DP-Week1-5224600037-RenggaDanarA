#include "RunSession.h"
#include <iostream>

RunSession::RunSession(IInputGenerator& gen,
                       IScoringRule&    scorer,
                       IRewardRule&     reward,
                       ShopSystem&      shop,
                       int totalRounds)
    : generator_(gen)
    , scorer_(scorer)
    , reward_(reward)
    , shop_(shop)
    , totalRounds_(totalRounds)
    , currentRound_(1)
    , money_(0)
{}

void RunSession::start() {
    std::cout << "=== RUN START ===\n";

    while (currentRound_ <= totalRounds_) {
        runOneRound();
    }

    std::cout << "\n=== RUN END ===\n";
    std::cout << "Final money: " << money_ << "\n";
}

void RunSession::runOneRound() {
    std::cout << "\n--- Round " << currentRound_ << " ---\n";

    // Phase 1: Generate input
    TurnInput input = generator_.generate(currentRound_);
    std::cout << "[PLAY]   input generated: " << input.value << "\n";

    // Phase 2: Compute base score
    int baseScore = scorer_.compute(input);
    std::cout << "[SCORE]  base score: " << baseScore << "\n";

    // Phase 3: Compute reward
    int gain = reward_.compute(baseScore);
    std::cout << "[REWARD] gain: " << gain;

    // Phase 4: Update money
    money_ += gain;
    std::cout << " | money: " << money_ << "\n";

    // Phase 5: Shop phase
    int spent = shop_.run(currentRound_, money_);
    money_ -= spent;
    if (spent > 0) {
        std::cout << "[MONEY]  after shop: " << money_ << "\n";
    }

    // Phase 6: Advance round
    ++currentRound_;
}
