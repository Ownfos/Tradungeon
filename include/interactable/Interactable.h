#ifndef TRADUNGEON_INTERACTABLE_H
#define TRADUNGEON_INTERACTABLE_H

#include "action/Action.h"
#include <vector>
#include <memory>

namespace tradungeon
{

class Interactable
{
public:
    Interactable() = default;

    // Prevent object slicing.
    Interactable(const Interactable&) = delete;
    Interactable(Interactable&&) = delete;
    Interactable& operator=(const Interactable&) = delete;
    Interactable& operator=(Interactable&&) = delete;

    virtual ~Interactable() = default;

    virtual std::string description() const = 0;
    virtual std::vector<std::shared_ptr<Action>> availableActions() const = 0;
};

} // namespace tradungeon

#endif
