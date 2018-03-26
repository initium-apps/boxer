#ifndef BOXPHYS_H
#define BOXPHYS_H

#include<wx/glcanvas.h>
#include"Box2D/Common/b2Draw.h"
#include"Box2D/Dynamics/b2World.h"
#include"b2Separator.h"

class boxFrame;

class boxPhys;

class boxDrawer : public b2Draw {
    private:
        boxPhys* phys;
    public:
        b2Vec2 cam;
        float ppu = 1;

        boxDrawer(boxPhys*);

        void DrawPolygon(const b2Vec2*, int32, const b2Color&);
        void DrawSolidPolygon(const b2Vec2*, int32, const b2Color&);
        void DrawCircle(const b2Vec2&, float32, const b2Color&);
        void DrawSolidCircle(const b2Vec2&, float32, const b2Vec2&, const b2Color&);
        void DrawSegment(const b2Vec2&, const b2Vec2&, const b2Color&);
        void DrawTransform(const b2Transform&);
        void DrawPoint(const b2Vec2&, float32, const b2Color&);

        void Render();

        b2Vec2 Unproject(b2Vec2);
    private:
        void SetColor(const b2Color&);
};

class boxPhys : public wxGLCanvas {
    private:
        wxGLContext* glctx = NULL;

        boxFrame* bframe;
    public:
        boxDrawer* bdrawer;

        b2World* b2w = NULL;
        b2Separator seperator;

        bool creatingTempPolyShape = false;
        std::vector<b2Vec2> tempPolyShape;

        bool creatingTempCircleShape = false;
        b2Vec2 tempCircleShapeOrigin;
        float tempCircleShapeRadius;

        boxPhys(boxFrame*);
        virtual ~boxPhys();

        void Idle(wxIdleEvent&);

        void MouseDown(wxMouseEvent&);
        void MouseDrag(wxMouseEvent&);
        void MouseUp(wxMouseEvent&);
        void MouseRot(wxMouseEvent&);
};

#endif // BOXPHYS_H
