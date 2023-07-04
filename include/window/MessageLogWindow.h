#ifndef TRADUNGEON_MESSAGE_LOG_WINDOW_H
#define TRADUNGEON_MESSAGE_LOG_WINDOW_H

#include "window/Window.h"
#include "MessageLog.h"
#include "ScrollView.h"
#include <any>

namespace tradungeon
{

// MessageLogviewer is a scrollable text area.
//
// It stacks all messages that players should see
// and renders a portion of them on the screen.
//
// The message log's buffer width will be 2 tiles smaller than the UI's viewport
// because we don't want to overwrite the boundary.
class MessageLogWindow : public Window
{
public:
    MessageLogWindow(
        const Viewport& viewport,
        int max_buffer_size
    );

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

    void push(const std::string& message);
    void scrollUp();
    void scrollDown();
    void scrollBottom();

private:
    Viewport m_msg_viewport;
    MessageLog m_msg_log;
    ScrollView m_scroll_view;

    std::any m_callback_handle;
};

} // namespace tradungeon

#endif
