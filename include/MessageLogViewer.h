#ifndef TRADUNGEON_MESSAGE_LOG_VIEWER_H
#define TRADUNGEON_MESSAGE_LOG_VIEWER_H

#include "UI.h"
#include "MessageLog.h"

namespace tradungeon
{

// MessageLogviewer is a scrollable text area.
//
// It stacks all messages that players should see
// and renders a portion of them on the screen.
//
// The message log's buffer width will be 2 tiles smaller than the UI's viewport
// because we don't want to overwrite the boundary.
class MessageLogViewer : public UI
{
public:
    MessageLogViewer(
        const Viewport& viewport,
        int max_buffer_size
    );

    virtual void onRender(Console& console) override;

    void push(const std::string& message);
    void scrollUp();
    void scrollDown();
    void scrollToBottom();

private:
    Viewport m_msg_viewport;
    MessageLog m_msg_log;
    int m_offset = 0;
};

} // namespace tradungeon

#endif