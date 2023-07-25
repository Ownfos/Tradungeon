#ifndef TRADUNGEON_UNUSABLE_ITEMS_H
#define TRADUNGEON_UNUSABLE_ITEMS_H

#include "interactable/Item.h"

namespace tradungeon
{

// Represents items that don't have any available actions.
// Used to reduce boilerplate code through inheritance.
class UnusableItem : public Item
{
public:
    UnusableItem(std::string name, int id, int weight);

    virtual int id() const override;
    virtual int weight() const override;
    virtual std::string description() const override;
    virtual std::vector<std::shared_ptr<Action>> availableActions() override;

private:
    std::string m_name;
    int m_id;
    int m_weight;
};

class WoodStick : public UnusableItem
{
public:
    WoodStick();
};

class IronOre : public UnusableItem
{
public:
    IronOre();
};

class SilverOre : public UnusableItem
{
public:
    SilverOre();
};

class GoldOre : public UnusableItem
{
public:
    GoldOre();
};

class Diamond : public UnusableItem
{
public:
    Diamond();
};

class Coal : public UnusableItem
{
public:
    Coal();
};

class IronBar : public UnusableItem
{
public:
    IronBar();
};

class SilverBar : public UnusableItem
{
public:
    SilverBar();
};

class GoldBar : public UnusableItem
{
public:
    GoldBar();
};


} // namespace tradungeon

#endif
