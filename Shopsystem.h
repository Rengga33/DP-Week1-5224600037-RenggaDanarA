#pragma once

#include <iostream>
#include <string>
#include <vector>

struct ShopOffer {
    std::string name;
    int cost;
};

class ShopSystem {
public:
    // Returns money spent (0 if skipped)
    int run(int round, int money) const;
};
