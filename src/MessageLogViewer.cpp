#include "MessageLogViewer.h"

namespace tradungeon
{

MessageLogViewer::MessageLogViewer(
    const Viewport& viewport,
    int max_buffer_size
)
    : UI(viewport),
    m_msg_viewport(Viewport{{1, 1}, viewport.m_size - Size{2, 2}}),
    m_msg_log(Size{m_msg_viewport.m_size.m_width, max_buffer_size})
{}

bool MessageLogViewer::onInput(int keycode)
{
    // TODO: implement scrolling
    return false;
}

void MessageLogViewer::onRender(TextBuffer& console)
{
    auto num_available_lines = m_msg_log.size() - m_offset;
    auto msg = m_msg_log.getLines(m_offset, num_available_lines);
    renderString(console, msg, m_msg_viewport);
}

void MessageLogViewer::push(const std::string& message)
{
    m_msg_log.push(message);
    scrollToBottom();
}

void MessageLogViewer::scrollUp()
{
    if (m_offset > 0)
    {
        --m_offset;
    }
}

void MessageLogViewer::scrollDown()
{
    // If there's something left below
    if (m_offset + m_msg_viewport.m_size.m_height < m_msg_log.size())
    {
        ++m_offset;
    }
}

void MessageLogViewer::scrollToBottom()
{
    m_offset = std::max(0, m_msg_log.size() - m_msg_viewport.m_size.m_height);
}

} // namespace tradungeon
