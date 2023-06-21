#ifndef TRADUNGEON_SCROLL_VIEW_H
#define TRADUNGEON_SCROLL_VIEW_H

namespace tradungeon
{

class ScrollView
{
public:
    ScrollView(int content_size, int view_size, int offset = 0);

    int begin() const;
    int end() const;

    void scrollUp();
    void scrollDown();
    void scrollTop();
    void scrollBottom();

private:
    int maxOffset() const;

    int m_content_size;
    int m_view_size;
    int m_offset;
};

} // namespace tradungeon

#endif
