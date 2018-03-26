#include"boxToolbar.h"

#include"boxFrame.h"
#include"boxIcons.h"

#include"Box2D/Box2D.h"

#include<algorithm>

boxToolbar::boxToolbar(boxFrame* bframe) : wxPanel(bframe, wxID_ANY), bframe(bframe) {
    this->sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(this->sizer);

    this->statik = new wxBitmapButton(this, wxID_ANY, wxBitmap(icon_static_xpm));
    this->statik->Bind(wxEVT_BUTTON, [bframe](wxCommandEvent&WXUNUSED(ev))->void{
        bframe->phystree->CreateEntry(b2_staticBody);
    });
    this->sizer->Add(statik);

    this->dynamic = new wxBitmapButton(this, wxID_ANY, wxBitmap(icon_dynamic_xpm));
    this->dynamic->Bind(wxEVT_BUTTON, [bframe](wxCommandEvent&WXUNUSED(ev))->void{
        bframe->phystree->CreateEntry(b2_dynamicBody);
    });
    this->sizer->Add(dynamic);

    this->kinematic = new wxBitmapButton(this, wxID_ANY, wxBitmap(icon_kinematic_xpm));
    this->kinematic->Bind(wxEVT_BUTTON, [bframe](wxCommandEvent&WXUNUSED(ev))->void{
        bframe->phystree->CreateEntry(b2_kinematicBody);
    });
    this->sizer->Add(kinematic);

    this->cursor = new boxToolCursor(this, wxBitmap(icon_cursor_xpm), wxCURSOR_DEFAULT);
    this->sizer->Add(cursor);

    this->path = new boxToolPath(this, wxBitmap(icon_path_xpm), wxCURSOR_PENCIL);
    this->sizer->Add(path);

    this->circle = new boxToolCircle(this, wxBitmap(icon_circle_xpm), wxCURSOR_PENCIL);
    this->sizer->Add(circle);

    this->selectedTool = this->cursor;
    this->cursor->SetValue(true);

    this->sizer->Fit(this);
}
