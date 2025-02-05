#include <wx/wx.h>
#include <sqlite3.h>
#include <iostream>

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Hello, wxWidgets & SQLite!");
        frame->Show(true);

        sqlite3* db;
        if (sqlite3_open("test.db", &db) == SQLITE_OK) {
            std::cout << "SQLite database opened successfully!" << std::endl;
        } else {
            std::cout << "Failed to open database." << std::endl;
        }
        sqlite3_close(db);

        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
