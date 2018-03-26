#include"boxTool.h"

#include"boxToolbar.h"
#include"boxFrame.h"

boxTool::boxTool(boxToolbar* btbar, wxBitmap image, wxStockCursor toolCursor) : wxBitmapToggleButton(btbar, wxID_ANY, image), btbar(btbar), toolCursor(toolCursor) {
    Bind(wxEVT_TOGGLEBUTTON, [this](wxCommandEvent ev)->void{
        if(ev.GetInt() == 1)
            this->OnSelect();
        else
            this->OnDeselect();
    });
}

boxTool::~boxTool() {
}

void boxTool::OnSelect() {
    btbar->cursor->SetValue(false);
    btbar->path->SetValue(false);
    btbar->circle->SetValue(false);

    this->SetValue(true);

    if(btbar->selectedTool && btbar->selectedTool != this)
        btbar->selectedTool->OnDeselect();

    btbar->selectedTool = this;
    btbar->bframe->phys->SetCursor(this->toolCursor);
}

void boxTool::OnDeselect() {
    this->SetValue(false);

    if(this != btbar->cursor)
        btbar->cursor->SetValue(true);
}

void boxTool::OnMouseDown(wxMouseEvent& WXUNUSED(ev)) {
}

void boxTool::OnMouseMotion(wxMouseEvent& WXUNUSED(ev)) {
}

void boxTool::OnMouseUp(wxMouseEvent& WXUNUSED(ev)) {
}
