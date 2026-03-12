#pragma once

#include "TurnInput.h"

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int compute(TurnInput input) const = 0;
};

class SimpleScoring : public IScoringRule {
public:
    int compute(TurnInput input) const override;
};

class BonusOddScoring : public IScoringRule {
public:
    int compute(TurnInput input) const override;
};
