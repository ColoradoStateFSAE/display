#ifndef MENUITEM_H
#define MENUITEM_H

class MenuItem {

private:
    bool headingState = false;

public:
    const int id;
    int value;
    const int fast;
    bool selected = false;

    MenuItem() = delete;
    MenuItem(int id, int value=0, int fast=1) : id(id), value(value), fast(fast) {

    }

    bool is_heading() {
        return headingState;
    }

    MenuItem heading() {
        headingState = true;
        return *this;
    }
};

#endif // MENUITEM_H
