#include"boxProperties.h"

#include"boxFrame.h"

boxProperties::boxProperties(boxFrame* parent) : wxGrid(parent, wxID_ANY) {
    CreateGrid(0, 1, wxGridSelectCells);
    HideColLabels();
}

boxProperties::~boxProperties() {
}
