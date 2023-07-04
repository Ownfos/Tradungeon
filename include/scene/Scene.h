#ifndef TRADUNGEON_SCENE_H
#define TRADUNGEON_SCENE_H

#include "Polymorphic.h"

namespace tradungeon
{

class Scene : private Polymorphic
{
public:
    virtual void onLoad() = 0;
};

} // namespace tradungeon

#endif
