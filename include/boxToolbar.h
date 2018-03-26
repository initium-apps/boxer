#ifndef BOXTOOLBAR_H
#define BOXTOOLBAR_H

#include"boxTool.h"

#include"boxDefaultTools.h"

#include<wx/wx.h>

class boxFrame;

class boxToolbar : public wxPanel {
    private:
        wxBoxSizer* sizer = NULL;
    public:
        wxBitmapButton* statik = NULL;
        wxBitmapButton* dynamic = NULL;
        wxBitmapButton* kinematic = NULL;

        boxTool* cursor = NULL;
        boxTool* path = NULL;
        boxTool* circle = NULL;

        boxTool* selectedTool = NULL;

        boxFrame* bframe;

        boxToolbar(boxFrame*);
};

#endif // BOXTOOLBAR_H
