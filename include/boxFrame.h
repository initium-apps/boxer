#ifndef BOXFRAME_H
#define BOXFRAME_H

#include<wx/wx.h>
#include<wx/aui/framemanager.h>

#include"boxToolbar.h"
#include"boxPhys.h"
#include"boxPhystree.h"
#include"boxProperties.h"

class boxFrame : public wxFrame {
    private:
        wxAuiManager aui;
    public:
        boxToolbar* toolbar = NULL;
        boxPhys* phys = NULL;
        boxPhystree* phystree = NULL;
        boxProperties* properties = NULL;

        boxFrame();
        virtual ~boxFrame();
};

#endif // BOXFRAME_H
