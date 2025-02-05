# Инструкция по использованию WSL для сборки проектов на C++ с wxWidgets и SQLite

## 1. Установка WSL и выбор дистрибутива
Если WSL уже установлен, переходите к следующему шагу.

1. Проверьте доступные дистрибутивы:
   ```sh
   wsl --list --online
   ```
2. Установите Debian (или Ubuntu, если предпочитаете):
   ```sh
   wsl --install -d Debian
   ```
3. Установите WSL 2 как версию по умолчанию:
   ```sh
   wsl --set-default-version 2
   ```
4. Проверьте установленный дистрибутив:
   ```sh
   wsl --list --verbose
   ```

## 2. Обновление системы и установка зависимостей
Запустите WSL (например, для Debian):
```sh
wsl -d Debian
```
Далее выполните обновление:
```sh
sudo apt update -y
sudo apt upgrade -y
```
Установите необходимые пакеты:
```sh
sudo apt install build-essential libgtk-3-dev gdb wget libsqlite3-dev -y
```
Настройте локализации для нужных вам языков:
```sh
sudo dpkg-reconfigure locales
```

## 3. Скачивание и сборка wxWidgets
Используйте скрипт `wxWidgets_linux_build.sh`, который выполняет следующие действия:
1. Удаляет старую версию wxWidgets.
2. Скачивает и распаковывает `wxWidgets-3.2.6`.
3. Создаёт каталог сборки.
4. Конфигурирует сборку с нужными параметрами.
5. Запускает `make` и `make install`.

Запустите скрипт:
```sh
bash wxWidgets_linux_build.sh
```
Или выполните команды вручную:
```sh
rm -Rf wxWidgets-3.2.6
wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.6/wxWidgets-3.2.6.tar.bz2
tar xf wxWidgets-3.2.6.tar.bz2
cd wxWidgets-3.2.6
mkdir buildgtk
cd buildgtk
../configure --with-gtk --disable-shared --enable-monolithic --enable-unicode
make -j$(nproc --all)
sudo make install
sudo ldconfig
```
После завершения можно удалить архив:
```sh
rm wxWidgets-3.2.6.tar.bz2
```

## 4. Сборка проекта на C++ с wxWidgets и SQLite
Создайте файл `main.cpp`:
```cpp
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
```

### Компиляция с wxWidgets и SQLite:
```sh
wsl `wx-config --cxx --cxxflags` -o linux_app *.cpp `wx-config --libs` -lsqlite3
```

### Запуск:
```sh
wsl ./linux_app
```
