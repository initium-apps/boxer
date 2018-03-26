#ifndef BOXPHYSTREE_H
#define BOXPHYSTREE_H

#include<wx/treectrl.h>
#include"Box2D/Dynamics/b2Body.h"

#include"boxProperties.h"

class boxFrame;

class boxPhystreeItemData : public wxTreeItemData {
    public:
        virtual void Load(boxProperties*) = 0;
        virtual void Unload(boxProperties*) = 0;
};

class boxPhystreeBodyData : public boxPhystreeItemData {
    public:
        b2Body* body;

        boxPhystreeBodyData(b2Body*);

        void Load(boxProperties*);
        void Unload(boxProperties*);
};

inline boxPhystreeBodyData::boxPhystreeBodyData(b2Body* body) : boxPhystreeItemData(), body(body) {
}

inline void boxPhystreeBodyData::Load(boxProperties* props) {
    props->AppendRows(1);
    props->SetRowLabelValue(0, "Type");

    switch(this->body->GetType()) {
        case b2_staticBody:
            props->SetCellValue(0, 0, "S");
            break;
        case b2_dynamicBody:
            props->SetCellValue(0, 0, "D");
            break;
        case b2_kinematicBody:
            props->SetCellValue(0, 0, "K");
            break;
    }
}

inline void boxPhystreeBodyData::Unload(boxProperties* props) {
}

class boxPhystree : public wxTreeCtrl {
    private:
        int icon_static, icon_dynamic, icon_kinematic;
    public:
        boxFrame* bframe;

        boxPhystree(boxFrame*);
        virtual ~boxPhystree();

        wxTreeItemId CreateEntry(b2BodyType);

        b2Body* GetChosenBody();
    private:
        void SelectionChange(wxTreeEvent&);
};

#endif // BOXPHYSTREE_H
