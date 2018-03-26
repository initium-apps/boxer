#include<wx/wx.h>

#include"boxFrame.h"

class Boxer : public wxApp {
    private:
        boxFrame* frame = NULL;
    public:
        virtual bool OnInit() {
            this->frame = new boxFrame();

            this->frame->Maximize();
            this->frame->Centre();
            this->frame->Show();
            return true;
        }
        virtual int OnExit() {
            return 0;
        }
};

IMPLEMENT_APP(Boxer)
