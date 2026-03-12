#pragma once

class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int compute(int baseScore) const = 0;
};

class SimpleReward : public IRewardRule {
public:
    int compute(int baseScore) const override;
};

class HalvingReward : public IRewardRule {
public:
    int compute(int baseScore) const override;
};

// Modification 2a — always adds a flat +2 bonus on top of base score
class FlatBonusReward : public IRewardRule {
public:
    int compute(int baseScore) const override;
};

// Modification 2b — doubles reward on even rounds, normal on odd rounds
class EvenRoundDoubleReward : public IRewardRule {
public:
    explicit EvenRoundDoubleReward(int& roundRef);
    int compute(int baseScore) const override;
private:
    int& round_;
};
