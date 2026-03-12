#include "ShopSystem.h"

int ShopSystem::run(int round, int money) const {
    static const std::vector<ShopOffer> offers = {
        { "Bonus(+2)",      2 },
        { "Multiplier(x2)", 4 },
        { "WildCard",       3 },
    };

    const ShopOffer& offer = offers.at(round - 1);
    std::cout << "[SHOP]   offered: " << offer.name
              << "  cost " << offer.cost << "\n";

    if (money >= offer.cost) {
        std::cout << "[SHOP]   purchased! spent " << offer.cost << "\n";
        return offer.cost;
    }

    std::cout << "[SHOP]   skipped (not enough money)\n";
    return 0;
}

