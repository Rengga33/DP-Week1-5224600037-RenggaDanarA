#pragma once

#include "TurnInput.h"

class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput generate(int round) const = 0;
};

class RandomInputGenerator : public IInputGenerator {
public:
    TurnInput generate(int round) const override;
};

class FixedInputGenerator : public IInputGenerator {
public:
    TurnInput generate(int round) const override;
};

/*
 * WeightedRandomInputGenerator
 *   New replacement generator — draws a value in 1-10 but weights
 *   higher values more likely each round (simulates card hand scaling).
 *   Replaces RandomInputGenerator in main.cpp.
 *   RunSession is NOT modified.
 */
class WeightedRandomInputGenerator : public IInputGenerator {
public:
    TurnInput generate(int round) const override;
};
