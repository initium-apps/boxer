#include"boxFrame.h"

boxFrame::boxFrame() : wxFrame(NULL, wxID_ANY, "Boxer", wxDefaultPosition, wxSize(640, 480)) {
    this->aui.SetManagedWindow(this);

    // the order is important

    this->phys = new boxPhys(this);
    this->aui.AddPane(phys, wxCENTER);

    this->toolbar = new boxToolbar(this);
    this->aui.AddPane(toolbar, wxLEFT, wxT("Toolbar"));

    this->properties = new boxProperties(this);
    this->aui.AddPane(properties, wxRIGHT, wxT("Properties"));

    this->phystree = new boxPhystree(this);
    this->aui.AddPane(phystree, wxAuiPaneInfo().Right().MinSize(128, 1).Caption("Phystree"));

    this->aui.Update();
}

boxFrame::~boxFrame() {
    this->aui.UnInit();
}
