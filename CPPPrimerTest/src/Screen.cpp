#include "Screen.h"
 
Screen::Screen(pos ht,pos wd):
                height(ht),width(wd),contents(ht*wd,' '){};

Screen::Screen(pos ht,pos wd,char c):
                height(ht),width(wd),contents(ht*wd,c){};
    
inline char Screen::get() const
{
    return contents[cursor];
}

inline char Screen::get(pos row,pos col) const
{
    return contents[row*width+col];
}
    
inline Screen& Screen::move(pos row,pos col)
{
    cursor = row*width + col;
    return *this;
}

inline Screen& Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen& Screen::set(pos row,pos col,char c)
{
    contents[row*width + col] = c;
    return *this;
}

inline void Screen::do_display(std::ostream& os) const
{
    os << contents;
}

inline Screen& Screen::display(std::ostream& os)
{
    do_display(os);
    return *this;
}

inline const Screen& Screen::display(std::ostream& os) const
{
    do_display(os);
    return *this;
}