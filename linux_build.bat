del /Q linux_app
wsl `wx-config --cxx --cxxflags` -o linux_app *.cpp `wx-config --libs` -lsqlite3