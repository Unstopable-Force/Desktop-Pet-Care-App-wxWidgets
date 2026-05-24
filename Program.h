#pragma once

#include <wx/wx.h>

// Application entry point — initialises the main window
class Program : public wxApp
{
public:
    bool OnInit() override;
};