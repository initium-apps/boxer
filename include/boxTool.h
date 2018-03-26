#ifndef BOXTOOL_H
#define BOXTOOL_H

#include<wx/bmpbuttn.h>
#include<wx/tglbtn.h>

#include<functional>

class boxFrame;
class boxToolbar;

class boxTool : public wxBitmapToggleButton {
    protected:
        wxStockCursor toolCursor;
        boxToolbar* btbar = NULL;
    public:
        boxTool(boxToolbar*, wxBitmap, wxStockCursor);
        virtual ~boxTool();

        virtual void OnSelect();
        virtual void OnDeselect();

        virtual void OnMouseDown(wxMouseEvent&);
        virtual void OnMouseMotion(wxMouseEvent&);
        virtual void OnMouseUp(wxMouseEvent&);
};

#endif // BOXTOOL_H
