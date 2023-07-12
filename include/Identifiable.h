#ifndef TRADUNGEON_IDENTIFIABLE_H
#define TRADUNGEON_IDENTIFIABLE_H

#include "Polymorphic.h"

namespace tradungeon
{

class Identifiable : public Polymorphic
{
public:
    virtual int id() const = 0;
};

}

#endif
