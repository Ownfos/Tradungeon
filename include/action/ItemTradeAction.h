#ifndef TRADUNGEON_ITEM_TRADE_ACTION_H
#define TRADUNGEON_ITEM_TRADE_ACTION_H

#include "action/Action.h"
#include "Market.h"

namespace tradungeon
{

class ItemTradeAction : public Action
{
public:
    ItemTradeAction(const Order& order);

    virtual void execute() override;
    virtual std::string description() const override;

private:
    Order m_order;
};

} // namespace tradungeon

#endif
