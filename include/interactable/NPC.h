#ifndef TRADUNGEON_NPC_H
#define TRADUNGEON_NPC_H

#include "interactable/Interactable.h"
#include "Trader.h"

namespace tradungeon
{

class NPC : public Interactable, public Trader
{
public:
    NPC(int id, std::string name);

    virtual std::string description() const override;
    virtual ActionList availableActions() override;
    
    virtual int id() const override;
    virtual const std::vector<Order>& remainingOrders() const override;
    virtual void pushOrder(const Order& order) override;
    virtual void clearOrders() override;

    // Decrease the quantity of this order by 1.
    // The order will be removed from  was fulfilled.
    void decreaseOrderQuantity(const Order& order);

private:
    int m_id;
    std::string m_name;
    std::vector<Order> m_orders;
};

} // namespace tradungeon

#endif
