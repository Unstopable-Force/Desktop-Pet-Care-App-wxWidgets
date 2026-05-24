#include "Program.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(Program);

bool Program::OnInit()
{
    auto* frame = new MainFrame("Animal Care");
    frame->SetClientSize(800, 600);
    frame->Center();
    frame->Show();
    return true;
}