#include "OpenSaveName.h"

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

edk::multi::Thread openLamp::OpenSaveName::thread;
edk::char8* openLamp::OpenSaveName::pipeCommand=NULL;
edk::char8* openLamp::OpenSaveName::pipeResult=NULL;

openLamp::OpenSaveName::OpenSaveName(){
    //
}

#if _WIN32 || _WIN64
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

bool OpenFileDialog::ShowOpenDialog()
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

    //if (_tcslen(this->FileName) == 0) return false;

    return true;
}

bool OpenFileDialog::ShowSaveDialog()
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

    GetSaveFileName(&ofn);

    //if (_tcslen(this->FileName) == 0) return false;

    return true;
}

edk::classID openLamp::OpenSaveName::createOpenDialog(edk::classID command){
    OpenFileDialog* openFileDialog1 = new OpenFileDialog();

    if(openFileDialog1){
        //filter
        openFileDialog1->Filter = "Image Files (*.jpg,*.png,*jpeg)\0*.jpg;*.png;*jpeg\0";


        if (openFileDialog1->ShowOpenDialog())
        {
            /*
        MessageBox(0, openFileDialog1->FileName, (TCHAR*)L"Выбран файл",
                   MB_OK | MB_ICONINFORMATION);
*/
            if(openFileDialog1->FileName){
                //
                openLamp::OpenSaveName::pipeResult = edk::String::strCopy(openFileDialog1->FileName);
            }
        }
        delete openFileDialog1;
    }
    return NULL;
}
edk::classID openLamp::OpenSaveName::createSaveDialog(edk::classID command){
    OpenFileDialog* openFileDialog1 = new OpenFileDialog();

    if(openFileDialog1){
        //filter
        openFileDialog1->Filter = "Image Files (*.jpg,*.png,*jpeg)\0*.jpg;*.png;*jpeg\0";

        if (openFileDialog1->ShowSaveDialog())
        {
            /*
            MessageBox(0, openFileDialog1->FileName, (TCHAR*)L"Выбран файл",
                       MB_OK | MB_ICONINFORMATION);
    */
            if(openFileDialog1->FileName){
                //
                openLamp::OpenSaveName::pipeResult = edk::String::strCopy(openFileDialog1->FileName);
            }
        }
        delete openFileDialog1;
    }
    return NULL;
}
#elif __linux__

edk::classID openLamp::OpenSaveName::openPipe(edk::classID command){
    edk::char8* str = (edk::char8*)command;
    //test the string
    if(str){
        edk::File pipe;
        edk::char8* result;
        if(pipe.openPipe(str)){
            result = new char[1];
            do{
                if(result){
                    delete[] result;
                    result=NULL;
                }
                result = pipe.readTextString("\n\10|",false);
                if(result){
                    if(edk::String::strSize(result)>1u){
                        if(openLamp::OpenSaveName::pipeResult){
                            delete[] openLamp::OpenSaveName::pipeResult;
                            openLamp::OpenSaveName::pipeResult=NULL;
                        }
                        openLamp::OpenSaveName::pipeResult = edk::String::strCopy(result);
                    }
                }
            }while(*result);
            if(result){
                delete[] result;
                result=NULL;
            }
            pipe.closeFile();
        }
    }
    return NULL;
}

#endif
bool openLamp::OpenSaveName::haveResult(){
    //test if are running the
    if(!openLamp::OpenSaveName::thread.isAlive())
        if(openLamp::OpenSaveName::pipeResult){
            return true;
        }
    return false;
}
edk::char8* openLamp::OpenSaveName::getResult(){
    //test if are running the
    if(!openLamp::OpenSaveName::thread.isAlive())
        return openLamp::OpenSaveName::pipeResult;
    return NULL;
}
bool openLamp::OpenSaveName::haveThread(){
    if(openLamp::OpenSaveName::thread.isAlive()){
        return true;
    }
    return false;
}

bool openLamp::OpenSaveName::getImageOpenName(){


    //generate the system string on linux
    //system("zenity --file-selection --title=\"Select a Image\" --multiple --file-filter='*.png *.jpeg *.jpg'");

    //test if the thread is running
    if(!openLamp::OpenSaveName::thread.isAlive()){
        if(openLamp::OpenSaveName::pipeCommand){
            delete[] openLamp::OpenSaveName::pipeCommand;
            openLamp::OpenSaveName::pipeCommand=NULL;
        }
        if(openLamp::OpenSaveName::pipeResult){
            delete[] openLamp::OpenSaveName::pipeResult;
            openLamp::OpenSaveName::pipeResult=NULL;
        }

#if _WIN32 || _WIN64
        if(openLamp::OpenSaveName::thread.start(openLamp::OpenSaveName::createOpenDialog,(edk::classID)openLamp::OpenSaveName::pipeCommand)){
            //
            return true;
        }
#elif __linux__
        //create the pipeCommands
        openLamp::OpenSaveName::pipeCommand = edk::String::strCopy("zenity --file-selection --title=\"Select a Image\" --multiple --file-filter='*.png *.jpeg *.jpg'");
        //create a new thread
        if(openLamp::OpenSaveName::thread.start(openLamp::OpenSaveName::openPipe,(edk::classID)openLamp::OpenSaveName::pipeCommand)){
            //
            return true;
        }
#endif
    }
    return false;
}
bool openLamp::OpenSaveName::getImageSaveName(){

    //generate the system string on linux
    //zenity --file-selection --title="Save File" --multiple --file-filter='*.png *.jpeg *.jpg' --save

    //test if the thread is running
    if(!openLamp::OpenSaveName::thread.isAlive()){
        if(openLamp::OpenSaveName::pipeCommand){
            delete[] openLamp::OpenSaveName::pipeCommand;
            openLamp::OpenSaveName::pipeCommand=NULL;
        }
        if(openLamp::OpenSaveName::pipeResult){
            delete[] openLamp::OpenSaveName::pipeResult;
            openLamp::OpenSaveName::pipeResult=NULL;
        }

#if _WIN32 || _WIN64
        //create a new thread
        if(openLamp::OpenSaveName::thread.start(openLamp::OpenSaveName::createSaveDialog,(edk::classID)openLamp::OpenSaveName::pipeCommand)){
            //
            return true;
        }
#elif __linux__
        //create the pipeCommands
        openLamp::OpenSaveName::pipeCommand = edk::String::strCopy("zenity --file-selection --title=\"Save File\" --multiple --file-filter='*.png *.jpeg *.jpg' --save");
        //create a new thread
        if(openLamp::OpenSaveName::thread.start(openLamp::OpenSaveName::openPipe,(edk::classID)openLamp::OpenSaveName::pipeCommand)){
            //
            return true;
        }
#endif
    }
    return false;
}

