#ifndef TRADUNGEON_MESSAGE_LOG_H
#define TRADUNGEON_MESSAGE_LOG_H

#include "Common.h"
#include <list>
#include <string>

namespace tradungeon
{

class MessageLog
{
public:
    MessageLog(const Size& max_buffer_size);

    void push(const std::string& message);
    std::string getLines(int offset, int num_lines) const;

    int size() const;

public:
    Size m_max_buffer_size;
    std::list<std::string> m_buffer;
};

} // namespace tradungeon

#endif
