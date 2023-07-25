#ifndef TRADUNGEON_EDIBLE_ITEMS_H
#define TRADUNGEON_EDIBLE_ITEMS_H

#include "interactable/Item.h"

namespace tradungeon
{

// Represents items that restores hunger gauge back to zero when eaten.
class EdibleItem : public Item, public std::enable_shared_from_this<EdibleItem>
{
public:
    EdibleItem(std::string name, int id, int weight, int hunger_restoration);

    virtual int id() const override;
    virtual int weight() const override;
    virtual std::string description() const override;
    virtual std::vector<std::shared_ptr<Action>> availableActions() override;

    int hungerRestoration() const;

private:
    std::string m_name;
    int m_id;
    int m_weight;
    int m_hunger_restoration;
};

class Apple : public EdibleItem
{
public:
    Apple();
};

class GoldenApple : public EdibleItem
{
public:
    GoldenApple();
};

class Clam : public EdibleItem
{
public:
    Clam();
};

class ClamSkewer : public EdibleItem
{
public:
    ClamSkewer();
};

} // namespace tradungeon

#endif
