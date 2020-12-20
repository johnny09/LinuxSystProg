#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>
class Screen
{
typedef std::string::size_type pos;
public:
    Screen() = default;
    Screen(pos height,pos width);
    Screen(pos height,pos width,char c);
    char get() const;
    char get(pos row,pos col) const;
    Screen& move(pos height,pos width);

    Screen& set(char c);
    Screen& set(pos row,pos col,char c);

    Screen& display(std::ostream& os);
    const Screen& display(std::ostream& os) const;
private:
    pos cursor = 0;
    pos height = 0,width = 0;
    std::string contents;
    void do_display(std::ostream& os) const;
    
};

class Window_mgr
{
private:
    std::vector<Screen> screens{Screen(24,80,' ')};
};


#endif