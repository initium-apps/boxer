#ifndef BOXDEFAULTTOOLS_H
#define BOXDEFAULTTOOLS_H

#include"boxTool.h"

class boxToolCursor : public boxTool {
    private:
        bool drag = false;
        int x, y;
    public:
        boxToolCursor(boxToolbar*, wxBitmap, wxStockCursor);
        virtual ~boxToolCursor();

        void OnMouseDown(wxMouseEvent&);
        void OnMouseMotion(wxMouseEvent&);
        void OnMouseUp(wxMouseEvent&);
};

class boxToolPath : public boxTool {
    public:
        boxToolPath(boxToolbar*, wxBitmap, wxStockCursor);
        virtual ~boxToolPath();

        void OnSelect();
        void OnDeselect();

        void OnMouseDown(wxMouseEvent&);
};

class boxToolCircle : public boxTool {
    public:
        boxToolCircle(boxToolbar*, wxBitmap, wxStockCursor);
        virtual ~boxToolCircle();

        void OnMouseDown(wxMouseEvent&);
        void OnMouseMotion(wxMouseEvent&);
        void OnMouseUp(wxMouseEvent&);
};

#endif // BOXDEFAULTTOOLS_H
