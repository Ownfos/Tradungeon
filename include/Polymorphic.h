#ifndef TRADUNGEON_POLYMORPHIC_H
#define TRADUNGEON_POLYMORPHIC_H

namespace tradungeon
{

// A helper class inspired by boost::noncopyable.
// Private inheritance to this class makes sure that
// polymorphic classes do not cause object slicing
// nor omitting child class destructor on destruction.
class Polymorphic
{
public:
    Polymorphic() = default;

    // Prevent object slicing.
    Polymorphic(const Polymorphic&) = delete;
    Polymorphic(Polymorphic&&) = delete;
    Polymorphic& operator=(const Polymorphic&) = delete;
    Polymorphic& operator=(Polymorphic&&) = delete;

    // Guarantee child class destructor to be called.
    virtual ~Polymorphic() = default;
};

} // namespace tradungeon

#endif
