#include "Console.h"

using namespace tradungeon;

int main()
{
    auto console = Console(20, 10);
    console.setChar('#', 0, 0);
    console.setChar('#', 19, 0);
    console.setChar('#', 0, 9);
    console.setChar('#', 19, 9);
    console.print();

    console.setChar('@', 19, 9);
    console.print();
}