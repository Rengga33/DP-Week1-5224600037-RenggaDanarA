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
