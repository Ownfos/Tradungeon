#include "ScrollView.h"
#include "Common.h"
#include <algorithm>

namespace tradungeon
{

ScrollView::ScrollView(int content_size, int view_size, int offset)
    : m_content_size(content_size),
    m_view_size(view_size),
    m_offset(clamp(0, maxOffset(), offset))
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

void ScrollView::scrollUp()
{
    m_offset = clamp(0, maxOffset(), m_offset - 1);
}

void ScrollView::scrollDown()
{
    m_offset = clamp(0, maxOffset(), m_offset + 1);
}

void ScrollView::scrollTop()
{
    m_offset = 0;
}

void ScrollView::scrollBottom()
{
    m_offset = maxOffset();
}

int ScrollView::maxOffset() const
{
    // Content size might be smaller than desired view size (e.g., empty MessageLog).
    // To fix the offset to 0 in such cases, prevent maxOffset from being negative.
    return std::max(0, m_content_size - m_view_size);
}

} // namespace tradungeon
