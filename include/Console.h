#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

namespace tradungeon
{

class Console
{
public:
    Console(int width, int height);
    void print() const;
    void setChar(char value, int x, int y);
    char getChar(int x, int y) const;

private:
    int pos2Ind(int x, int y) const;

    int width;
    int height;
    std::string buffer;
};

} // namespace tradungeon

#endif
