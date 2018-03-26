#include"boxPhystree.h"

#include<wx/imaglist.h>

#include"boxIcons.h"
#include"boxFrame.h"

boxPhystree::boxPhystree(boxFrame* bframe) : wxTreeCtrl(bframe), bframe(bframe) {
    SetWindowStyleFlag(wxTR_HAS_BUTTONS | wxTR_HIDE_ROOT | wxTR_SINGLE | wxTR_NO_LINES);

    wxImageList* l = new wxImageList(16, 16, true, 3);
    icon_static = l->Add(icon_static_small_xpm);
    icon_dynamic = l->Add(icon_dynamic_small_xpm);
    icon_kinematic = l->Add(icon_kinematic_small_xpm);
    this->AssignImageList(l);

    this->AddRoot(wxT("Phystree"));

    this->Bind(wxEVT_TREE_SEL_CHANGED, &boxPhystree::SelectionChange, this);
}

boxPhystree::~boxPhystree() {
}

wxTreeItemId boxPhystree::CreateEntry(b2BodyType type) {
    int icon;
    switch(type) {
        case b2_staticBody:
            icon = this->icon_static;
            break;
        case b2_dynamicBody:
            icon = this->icon_dynamic;
            break;
        case b2_kinematicBody:
            icon = this->icon_kinematic;
            break;
    }

    b2BodyDef bdef;
    bdef.type = type;
    bdef.fixedRotation = false;

    wxTreeItemId id = AppendItem(GetRootItem(), "New Body", icon, -1, new boxPhystreeBodyData(bframe->phys->b2w->CreateBody(&bdef)));
    SelectItem(id);
}

b2Body* boxPhystree::GetChosenBody() {
    wxTreeItemData* data = this->GetItemData(this->GetSelection());

    boxPhystreeBodyData* bdata = dynamic_cast<boxPhystreeBodyData*>(data);
    if(bdata) {
        return bdata->body;
    }

    return NULL;
}

void boxPhystree::SelectionChange(wxTreeEvent& ev) {
    boxPhystreeItemData* oldData = dynamic_cast<boxPhystreeItemData*>(GetItemData(ev.GetOldItem()));
    boxPhystreeItemData* data = dynamic_cast<boxPhystreeItemData*>(GetItemData(ev.GetItem()));

    if(oldData) {
        oldData->Unload(bframe->properties);
    }

    if(bframe->properties->GetNumberRows() > 0) {
        bframe->properties->DeleteRows(0, bframe->properties->GetNumberRows());
    }

    if(data) {
        data->Load(bframe->properties);
    }
}
