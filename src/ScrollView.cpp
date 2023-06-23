#include "ScrollView.h"
#include "Common.h"
#include <algorithm>

namespace tradungeon
{

ScrollView::ScrollView(int content_size, int view_size, bool disable_cursor)
    : m_content_size(content_size),
    m_view_size(view_size),
    m_disable_cursor(disable_cursor)
{}

int ScrollView::begin() const
{
    return m_offset;
}

int ScrollView::end() const
{
    // If view size is greater than content size, m_offset gets fixed to 0.
    // This means that m_offset + m_view_size = m_view_size > m_content_size.
    // To prevent index-out-of-range exception, cap the return value at the content size.
    return std::min(m_content_size, m_offset + m_view_size);
}

int ScrollView::cursorPosition() const
{
    return m_disable_cursor ? begin() : m_cursor_pos;
}

void ScrollView::scrollUp()
{
    // Try to move cursor only.
    --m_cursor_pos;
    
    // If we don't use cursor movement
    // or the cursor went out of visible area,
    // decrease offset by one and put cursor on the first item.
    if (m_disable_cursor || m_cursor_pos < begin())
    {
        m_offset = clamp(0, maxOffset(), m_offset - 1);
        m_cursor_pos = begin();
    }
}

void ScrollView::scrollDown()
{
    // Try to move cursor only.
    ++m_cursor_pos;

    // If we don't use cursor movement
    // or the cursor went out of visible area,
    // increase offset by one and put cursor on the last item.
    // Note that end() returns the next position of last visible element.
    if (m_disable_cursor || m_cursor_pos >= end())
    {
        m_offset = clamp(0, maxOffset(), m_offset + 1);
        m_cursor_pos = end() - 1;
    }
}

void ScrollView::scrollTop()
{
    m_cursor_pos = 0;
    m_offset = 0;
}

void ScrollView::scrollBottom()
{
    m_cursor_pos = m_content_size - 1;
    m_offset = maxOffset();
}

int ScrollView::maxOffset() const
{
    // Content size might be smaller than desired view size (e.g., empty MessageLog).
    // To fix the offset to 0 in such cases, prevent maxOffset from being negative.
    return std::max(0, m_content_size - m_view_size);
}

void ScrollView::updateContentSize(int new_content_size)
{
    m_content_size = new_content_size;

    // If content size shrinked, cap offset and cursor position at their maximum value.
    m_cursor_pos = std::min(m_content_size - 1, m_cursor_pos);
    m_offset = std::min(maxOffset(), m_offset);
}

} // namespace tradungeon
