#ifndef OPENSAVENAME_H
#define OPENSAVENAME_H

/*
OpenSaveName - Start operating system dialog's to select file to open and save.
Copyright (C) 2013 Eduardo Moura Sales Martins
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
email: edimartin@gmail.com.br

AV: Walmor M. de Souza 392 Casa
Gravatai RS Brazil 94065100
*/

#include <stdlib.h>
#include <stdio.h>
#include "edk/Types.h"
#include "edk/String.h"
#include "edk/File.h"
#include "edk/thread/Thread.h"

/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms646927(v=vs.85).aspx
 *
This simple class uses GetOpenFileName and maximally standartized with the same class of .NET Framework

-------------------------- OpenFileDialog.h --------------------------

#pragma once

#include <Windows.h>
#include <Commdlg.h>
#include <tchar.h>

class OpenFileDialog
{
public:
    OpenFileDialog(void);

    TCHAR*DefaultExtension;
    TCHAR*FileName;
    TCHAR*Filter;
    intFilterIndex;
    intFlags;
    TCHAR*InitialDir;
    HWNDOwner;
    TCHAR*Title;

    bool ShowDialog();
};

------------------------- OpenFileDialog.cpp -------------------------

#include "OpenFileDialog.h"

OpenFileDialog::OpenFileDialog(void)
{
    this->DefaultExtension = 0;
    this->FileName = new TCHAR[MAX_PATH];
    this->Filter = 0;
    this->FilterIndex = 0;
    this->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    this->InitialDir = 0;
    this->Owner = 0;
    this->Title = 0;
}

bool OpenFileDialog::ShowDialog()
{
    OPENFILENAME ofn ;

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = this->Owner;
    ofn.lpstrDefExt = this->DefaultExtension;
    ofn.lpstrFile = this->FileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = this->Filter;
    ofn.nFilterIndex = this->FilterIndex;
    ofn.lpstrInitialDir = this->InitialDir;
    ofn.lpstrTitle = this->Title;
    ofn.Flags = this->Flags;

    GetOpenFileName(&ofn);

    if (_tcslen(this->FileName) == 0) return false;

    return true;
}

------------------------- How To Use It -------------------------

#include "OpenFileDialog.h"
...
OpenFileDialog* openFileDialog1 = new OpenFileDialog();

if (openFileDialog1->ShowDialog())
{
    MessageBox(0, openFileDialog1->FileName, _T("Выбран файл"),
               MB_OK | MB_ICONINFORMATION);
}
...
openFileDialog1->FilterIndex = 1;
openFileDialog1->Flags |= OFN_SHOWHELP;
openFileDialog1->InitialDir = _T("C:\\Windows\\");
openFileDialog1->Title = _T("Open Text File");

if (openFileDialog1->ShowDialog())
{
    MessageBox(0, openFileDialog1->FileName, _T("Выбран файл"),
               MB_OK | MB_ICONINFORMATION);
}
*/


#if _WIN32 || _WIN64
#include <Windows.h>
#include <Commdlg.h>
#include <tchar.h>
class OpenFileDialog
{
public:
    OpenFileDialog(void);

    TCHAR* DefaultExtension;
    TCHAR* FileName;
    TCHAR* Filter;
    int FilterIndex;
    int Flags;
    TCHAR* InitialDir;
    HWND Owner;
    TCHAR* Title;

    bool ShowOpenDialog();
    bool ShowSaveDialog();
};
#endif

namespace openLamp{
class OpenSaveName
{
public:
    OpenSaveName();

#if _WIN32 || _WIN64
    static edk::classID createOpenDialog(edk::classID command);
    static edk::classID createSaveDialog(edk::classID command);
#elif __linux__
    static edk::classID openPipe(edk::classID command);
#endif
    static bool haveResult();
    static edk::char8* getResult();
    static bool haveThread();

    static bool getImageOpenName();
    static bool getImageSaveName();
private:
    static edk::multi::Thread thread;
    //pipe command
    static edk::char8* pipeCommand;
    //pise result
    static edk::char8* pipeResult;
};
}

#endif // OPENSAVENAME_H
