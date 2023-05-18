#include "MessageLog.h"
#include <sstream>
#include <exception>

namespace tradungeon
{

MessageLog::MessageLog(const Size& max_buffer_size)
    : m_max_buffer_size(max_buffer_size)
{}

void MessageLog::push(const std::string& message)
{
    auto offset = 0;
    auto length = 0;
    for (char ch : message)
    {
        if (ch != '\n')
        {
            ++length;
        }

        // There are three cases where a token is stored as a message line:
        // 1. the token length reached maximum buffer size
        // 2. newline character is given
        // 3. the last token (i.e. end of message)
        if (ch == '\n' || length >= m_max_buffer_size.m_width || offset + length == message.length())
        {
            // Save current line
            m_buffer.push_back(message.substr(offset, length));

            // Move to the next token.
            // Since we don't count '\n' to length,
            // additional offset is required to skip the newline character.
            offset += length;
            length = 0;
            if (ch == '\n')
            {
                ++offset;
            }

            // Delete the oldest message if we run out of space.
            if (size() > m_max_buffer_size.m_height)
            {
                m_buffer.pop_front();
            }
        }
    }
}

std::string MessageLog::getLines(int offset, int num_lines) const
{
    if (offset < 0 || offset + num_lines > size())
    {
        throw std::exception("Trying to access message logs out of range");
    }

    // Fetch N lines from the list with offset and append them
    // with '\n' at the end to make a single string block.
    auto rtn = std::ostringstream();
    auto message_it = m_buffer.begin();
    std::advance(message_it, offset);
    while(num_lines-- > 0)
    {
        rtn << *message_it << '\n';
        ++message_it;
    }

    return rtn.str();
}

int MessageLog::size() const
{
    return m_buffer.size();
}


} // namespace tradungeon
