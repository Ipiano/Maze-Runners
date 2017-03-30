#ifndef WIDGET_H
#define WIDGET_H

#include "Drawable.h"
#include "KeyPressable.h"
#include "Clickable.h"

class Widget : public virtual Clickable, public virtual KeyPressable, public virtual Drawable
{
public:
    virtual double minWidth() = 0;
    virtual double minHeight() = 0;
};

#endif // WIDGET_H