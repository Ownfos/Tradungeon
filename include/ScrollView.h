#ifndef TRADUNGEON_SCROLL_VIEW_H
#define TRADUNGEON_SCROLL_VIEW_H

namespace tradungeon
{

// Simulates a scrollable area.
// Given a fixed width of visible area (i.e., view size),
// calculate the valid range of index which should be shown.
//
// If view size is greater than available content's size,
// remaining empty space is ignored and the whole content will be treated as visible.
//
// It also supports cursor control.
// Cursor is an absolute position in a content representing currently selected item.
// When we try to scroll up or down, cursor will try to move without changing the visible area.
// If the cursor was on the boundary and can't move,
// visible area, instead of cursor, will move by one step.
//
// If you want the visible area to move always,
// set disable_cursor to true at the constructor.
// By enabling this flag, scrollUp() or similar methods will respond immediately.
//
// example diagram:
// ------------------------ content
//        ------            visible area
//        ^                 begin
//              ^           end (last visible position + 1)
//           ^              cursor (gets fixed to 'begin' if disable_cursor is true)
class ScrollView
{
public:
    ScrollView(int content_size = 0, int view_size = 0, bool disable_cursor = false);

    // The range of visible items in a content.
    // begin() points to the first item,
    // while end() points to the item next to the last visible one.
    // These methods correspond to STL containers' begin() and end().
    int begin() const;
    int end() const;

    // The position of currently selected item.
    // Imagine you are using file explorer with keyboard only.
    // Pressing up and down will change what you are 'selecting'.
    int cursorPosition() const;

    void scrollUp();
    void scrollDown();
    void scrollTop();
    void scrollBottom();

    void updateContentSize(int new_content_size);

private:
    // The largest value that m_offset can have.
    // If content size is greater than view size, returns content size - view size.
    // Otherwise, this value is always 0.
    int maxOffset() const;

    int m_content_size; // The size of available content.
    int m_view_size; // The size of visible area. This might be bigger than content size.
    int m_offset = 0; // The starting position of visible area.
    int m_cursor_pos = 0; // The position of selected item. This value is ignored when disable_cursor is true.
    bool m_disable_cursor; // When this flag is set, cursor movement is ignored and any scrolling action will directly affect visible area (i.e., begin() and end() will change)
};

} // namespace tradungeon

#endif
