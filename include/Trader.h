#ifndef TRADUNGEON_TRADER_H
#define TRADUNGEON_TRADER_H

#include "Identifiable.h"
#include "Market.h"

namespace tradungeon
{

class Trader : public Identifiable
{
public:
    virtual const std::vector<Order>& remainingOrders() const = 0;
    virtual void pushOrder(const Order& order) = 0;
    virtual void clearOrders() = 0;
};

} // namespace tradungeon

#endif
