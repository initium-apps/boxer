#include"boxDefaultTools.h"

#include"boxToolbar.h"
#include"boxFrame.h"

boxToolCursor::boxToolCursor(boxToolbar* tbar, wxBitmap icon, wxStockCursor cursor) : boxTool(tbar, icon, cursor) {
}

boxToolCursor::~boxToolCursor() {
}

void boxToolCursor::OnMouseDown(wxMouseEvent& ev) {
    this->drag = true;
    this->x = ev.GetX();
    this->y = ev.GetY();
}

void boxToolCursor::OnMouseMotion(wxMouseEvent& ev) {
    if(this->drag) {
        btbar->bframe->phys->bdrawer->cam.x += (ev.GetX() - this->x);
        btbar->bframe->phys->bdrawer->cam.y += (ev.GetY() - this->y);

        this->x = ev.GetX();
        this->y = ev.GetY();
    }
}

void boxToolCursor::OnMouseUp(wxMouseEvent& WXUNUSED(ev)) {
    this->drag = false;
}

//

boxToolPath::boxToolPath(boxToolbar* tbar, wxBitmap icon, wxStockCursor cursor) : boxTool(tbar, icon, cursor) {
}

boxToolPath::~boxToolPath() {
}

void boxToolPath::OnSelect() {
    boxTool::OnSelect();

    btbar->bframe->phys->tempPolyShape.clear();
    btbar->bframe->phys->creatingTempPolyShape = true;
}

void boxToolPath::OnDeselect() {
    boxTool::OnDeselect();

    boxPhys* phys = btbar->bframe->phys;

    if(phys->tempPolyShape.size() < 3) {
        phys->tempPolyShape.clear();
        return;
    }

    phys->creatingTempPolyShape = false;

    b2FixtureDef fdef;
    fdef.density = 10;

    int shapeValidation = phys->seperator.Validate(phys->tempPolyShape);
    if(shapeValidation == 2) {
        std::reverse(phys->tempPolyShape.begin(), phys->tempPolyShape.end());
    }

    b2Body* chosenBody = btbar->bframe->phystree->GetChosenBody();

    phys->seperator.Separate(chosenBody, &fdef, &phys->tempPolyShape, 1);

    /* Center the fixture on the physical center by finding the average point of all shapes */
    /* This breaks if there is more than one shape */
    if(chosenBody->GetType() != b2_dynamicBody) {
        b2Vec2 avg;
        int polygonCount = 0;

        b2Fixture* fixt = chosenBody->GetFixtureList();
        while(fixt != NULL) {
            b2Shape* shape = fixt->GetShape();

            if(shape->GetType() == b2Shape::e_polygon) {
                b2PolygonShape* ps = static_cast<b2PolygonShape*>(shape);

                polygonCount += ps->m_count;

                for(int vi = 0; vi < ps->m_count; vi++) {
                    avg += ps->m_vertices[vi];
                }
            }

            fixt = fixt->GetNext();
        }
        avg *= 1.0f / polygonCount;

        fixt = chosenBody->GetFixtureList();
        while(fixt != NULL) {
            b2Shape* shape = fixt->GetShape();

            if(shape->GetType() == b2Shape::e_polygon) {
                b2PolygonShape* ps = static_cast<b2PolygonShape*>(shape);

                for(int vi = 0; vi < ps->m_count; vi++) {
                    ps->m_vertices[vi] -= avg;
                }
            }

            fixt = fixt->GetNext();
        }

        chosenBody->SetTransform(chosenBody->GetPosition() + avg, chosenBody->GetAngle());
    }

    phys->tempPolyShape.clear();
}

void boxToolPath::OnMouseDown(wxMouseEvent& ev) {
    btbar->bframe->phys->tempPolyShape
        .push_back(btbar->bframe->phys->bdrawer->Unproject(b2Vec2(ev.GetX(), ev.GetY())));
}

//

boxToolCircle::boxToolCircle(boxToolbar* tbar, wxBitmap icon, wxStockCursor cursor) : boxTool(tbar, icon, cursor) {
}

boxToolCircle::~boxToolCircle() {
}

void boxToolCircle::OnMouseDown(wxMouseEvent& ev) {
    btbar->bframe->phys->creatingTempCircleShape = true;
    btbar->bframe->phys->tempCircleShapeOrigin = btbar->bframe->phys->bdrawer->Unproject(b2Vec2(ev.GetX(), ev.GetY()));
    btbar->bframe->phys->tempCircleShapeRadius = 0;
}

void boxToolCircle::OnMouseMotion(wxMouseEvent& ev) {
    boxPhys* phys = btbar->bframe->phys;

    phys->tempCircleShapeRadius = b2Distance(phys->bdrawer->Unproject(b2Vec2(ev.GetX(), ev.GetY())), phys->tempCircleShapeOrigin);
}

void boxToolCircle::OnMouseUp(wxMouseEvent& WXUNUSED(ev)) {
    btbar->bframe->phys->creatingTempCircleShape = false;

    b2CircleShape shape;
    shape.m_radius = btbar->bframe->phys->tempCircleShapeRadius;

    b2FixtureDef fdef;
    fdef.density = 10;
    fdef.shape = &shape;

    b2Body* body = btbar->bframe->phystree->GetChosenBody();
    body->CreateFixture(&fdef);
    body->SetTransform(body->GetPosition() + btbar->bframe->phys->tempCircleShapeOrigin, body->GetAngle());
}
