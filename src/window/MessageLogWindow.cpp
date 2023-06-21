#include "window/MessageLogWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

MessageLogWindow::MessageLogWindow(
    const Viewport& viewport,
    int max_buffer_size
)
    : Window(viewport),
    m_msg_viewport(Viewport{{2, 2}, viewport.m_size - Size{4, 4}}),
    m_msg_log(Size{m_msg_viewport.m_size.m_width, max_buffer_size})
{
    // Grab every message logging event and show the content.
    // Since a unique MessageLogWindow instance exists throughout the game,
    // removing callback on instance destruction is not necessary.
    EventMediator::m_on_message.addCallback([this](const std::string& message){
        push(message);
    });
}

bool MessageLogWindow::onInput(int keycode)
{
    // TODO: implement scrolling
    return false;
}

void MessageLogWindow::onRender(TextBuffer& buffer)
{
    auto num_available_lines = m_scroll_view.end() - m_scroll_view.begin();
    auto msg = m_msg_log.getLines(m_scroll_view.begin(), num_available_lines);
    renderString(buffer, msg, m_msg_viewport);
}
 
void MessageLogWindow::push(const std::string& message)
{
    m_msg_log.push(message);

    // Resize the scroll view and make it display the latest message.
    m_scroll_view = ScrollView(m_msg_log.size(), m_msg_viewport.m_size.m_height);
    m_scroll_view.scrollBottom();
}

void MessageLogWindow::scrollUp()
{
    m_scroll_view.scrollUp();
}

void MessageLogWindow::scrollDown()
{
    m_scroll_view.scrollDown();
}

void MessageLogWindow::scrollBottom()
{
    m_scroll_view.scrollBottom();
}

} // namespace tradungeon
