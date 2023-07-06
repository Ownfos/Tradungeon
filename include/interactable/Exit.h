#ifndef TRADUNGEON_EXIT_H
#define TRADUNGEON_EXIT_H

#include "interactable/Interactable.h"

namespace tradungeon
{

class Exit : public Interactable
{
public:
    virtual std::string description() const override;
    virtual ActionList availableActions() const override;
};

} // namespace tradungeon

#endif
