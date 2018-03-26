#ifndef BOXPROPERTIES_H
#define BOXPROPERTIES_H

#include<wx/grid.h>

class boxFrame;

class boxProperties : public wxGrid {
    private:
    public:
        boxProperties(boxFrame*);
        virtual ~boxProperties();
};

#endif // BOXPROPERTIES_H
