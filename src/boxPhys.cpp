#include"boxPhys.h"

#include<wx/dcclient.h>
#include<wx/utils.h>
#include<math.h>

#include"boxFrame.h"
#include"Box2D/Box2D.h"

#ifdef __WXMAC__
    #include "OpenGL/glu.h"
    #include "OpenGL/gl.h"
#else
    #include <GL/glu.h>
    #include <GL/gl.h>
#endif

boxDrawer::boxDrawer(boxPhys* phys) : b2Draw(), phys(phys) {
}

void boxDrawer::DrawPolygon(const b2Vec2* verts, int32 count, const b2Color& color) {
    SetColor(color);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
        for(uint16_t i = 0; i < count; i++) {
            glVertex2f(verts[i].x, verts[i].y);
        }
    glEnd();
}

void boxDrawer::DrawSolidPolygon(const b2Vec2* verts, int32 count, const b2Color& color) {
    DrawPolygon(verts, count, color);
}

/// SiegeLord (+someones) Circle Algorithm:
/// http://slabode.exofire.net/circle_draw.shtml
void boxDrawer::DrawCircle(const b2Vec2& point, float32 r, const b2Color& color) {
    int segments = (int) (64);

    float theta = 2 * 3.1415926 / float(segments);
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float x = r;
	float y = 0;

    SetColor(color);
    glLineWidth(1.0f);
	glBegin(GL_LINE_LOOP);
        for(int ii = 0; ii < segments; ii++) {
            glVertex2f((x + point.x), (y + point.y));

            t = x;
            x = c * x - s * y;
            y = s * t + c * y;
        }
	glEnd();
}

void boxDrawer::DrawSolidCircle(const b2Vec2& point, float32 r, const b2Vec2&, const b2Color& color) {
    DrawCircle(point, r, color);
}

void boxDrawer::DrawSegment(const b2Vec2& a, const b2Vec2& b, const b2Color& color) {
    SetColor(color);
    glLineWidth(1.0f);
	glBegin(GL_LINES);
        glVertex2f(a.x, a.y);
        glVertex2f(b.x, b.y);
	glEnd();
}

void boxDrawer::DrawTransform(const b2Transform& trans) {
    glPushMatrix();

    glColor3f(0.7f, 0.7f, 0.7f);
    glLineWidth(1.0f);
    glTranslatef(trans.p.x, trans.p.y, 0);
    glRotatef((trans.q.GetAngle()) * 180.0f / 3.14159265358979323846264338327950288f, 0, 0, 1);
    glTranslatef(-trans.p.x, -trans.p.y, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f((trans.p.x - 5), (trans.p.y - 5));
        glVertex2f((trans.p.x + 5), (trans.p.y - 5));
        glVertex2f((trans.p.x + 5), (trans.p.y + 5));
        glVertex2f((trans.p.x - 5), (trans.p.y + 5));
    glEnd();

    glPopMatrix();
}

void boxDrawer::DrawPoint(const b2Vec2& point, float32 size, const b2Color& color) {
    SetColor(color);
    glPointSize(size);
    glBegin(GL_POINTS);
        glVertex2f(point.x, point.y);
    glEnd();
}

void boxDrawer::Render() {
    static int grid = 20;

    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
        float xmod = fmodf(this->cam.x, grid);
        for(int x = 0; x < this->phys->GetSize().x / this->ppu; x += grid) {
            glVertex2f(x + xmod, 0);
            glVertex2f(x + xmod, this->phys->GetSize().y / this->ppu);
        }
        float ymod = fmodf(this->cam.y, grid);
        for(int y = 0; y < this->phys->GetSize().y / this->ppu; y += grid) {
            glVertex2f(0, y + ymod);
            glVertex2f(this->phys->GetSize().x / this->ppu, y + ymod);
        }
    glEnd();

    glTranslatef(this->cam.x, this->cam.y, 0);
    this->phys->b2w->DrawDebugData();

    if(this->phys->creatingTempPolyShape) {
        glBegin(GL_LINE_LOOP);
            for(b2Vec2& v : this->phys->tempPolyShape) {
                glVertex2f(v.x, v.y);
            }
        glEnd();
    } else if(this->phys->creatingTempCircleShape) {
        this->DrawCircle(this->phys->tempCircleShapeOrigin, this->phys->tempCircleShapeRadius, b2Color(0.2f, 0.2f, 0.2f, 0.2f));
    }
    glTranslatef(-this->cam.x, -this->cam.y, 0);
}

b2Vec2 boxDrawer::Unproject(b2Vec2 scrpos) {
    return b2Vec2(-this->cam.x + scrpos.x / this->ppu, -this->cam.y + scrpos.y / this->ppu);
}

void boxDrawer::SetColor(const b2Color& color) {
    glColor4f(color.r, color.g, color.b, color.a);
}

//

boxPhys::boxPhys(boxFrame* bframe) : wxGLCanvas(bframe, wxID_ANY), bframe(bframe) {
    this->glctx = new wxGLContext(this);

    this->b2w = new b2World(b2Vec2(0, 9.8f));
    this->bdrawer = new boxDrawer(this);
    this->bdrawer->AppendFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
    this->b2w->SetDebugDraw(this->bdrawer);

    this->Bind(wxEVT_IDLE, &boxPhys::Idle, this);
    this->Bind(wxEVT_LEFT_DOWN, &boxPhys::MouseDown, this);
    this->Bind(wxEVT_MOTION, &boxPhys::MouseDrag, this);
    this->Bind(wxEVT_LEFT_UP, &boxPhys::MouseUp, this);
    this->Bind(wxEVT_MOUSEWHEEL, &boxPhys::MouseRot, this);

    this->SetCanFocus(true);
    this->SetFocus();
}

boxPhys::~boxPhys() {
    delete this->bdrawer;
    delete this->b2w;
    delete this->glctx;
}

/// Rendering code
void boxPhys::Idle(wxIdleEvent& ev) {
    if(!IsShownOnScreen()) return;

    wxGLCanvas::SetCurrent(*this->glctx);
    wxClientDC(this);

    glViewport(0, 0, GetSize().x, GetSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GetSize().x / this->bdrawer->ppu, GetSize().y / this->bdrawer->ppu, 0, -1, 1);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1);

    static wxLongLong delta = wxGetUTCTimeMillis();
    wxLongLong last = wxGetUTCTimeMillis() - delta;
    delta = wxGetUTCTimeMillis();

    this->bdrawer->Render();
    if(wxGetKeyState(WXK_F1))
        this->b2w->Step((float) last.ToDouble() / 100.0f, 20, 30);

    glFlush();
    SwapBuffers();

    ev.RequestMore();
}

void boxPhys::MouseDown(wxMouseEvent& ev) {
    this->SetFocus();

    if(this->bframe->toolbar->selectedTool)
        this->bframe->toolbar->selectedTool->OnMouseDown(ev);
}

void boxPhys::MouseDrag(wxMouseEvent& ev) {
    if(this->bframe->toolbar->selectedTool)
        this->bframe->toolbar->selectedTool->OnMouseMotion(ev);
}

void boxPhys::MouseUp(wxMouseEvent& ev) {
    if(this->bframe->toolbar->selectedTool)
        this->bframe->toolbar->selectedTool->OnMouseUp(ev);
}

/// \todo: Implement outward zooming and fix inward zooming
/// \todo: aka make zoom
void boxPhys::MouseRot(wxMouseEvent& ev) {
    static float outAmount = 0.5f;
    static float inAmount = 2.0f;

    this->bdrawer->ppu *= ev.GetWheelRotation() < 0 ? outAmount : inAmount;
    this->bdrawer->ppu = fminf(fmaxf(this->bdrawer->ppu, 0.125f), 4.0f);

    if(ev.GetWheelRotation() > 0) {
        this->bdrawer->cam.x -= ev.GetX() * this->bdrawer->ppu;
        this->bdrawer->cam.y -= ev.GetY() * this->bdrawer->ppu;
    }
}
