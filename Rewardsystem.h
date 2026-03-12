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
