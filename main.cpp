/*
OpenLamp Main
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

/*
valgrind --tool=memcheck --leak-check=yes --log-file="log.txt" ./openLamp
*/

////////////////////////////////////////////////////////////////////////////////////////////////
///LIBS:
/// Windows: -lsfml-system -lsfml-window -lsfml-graphics -lopengl32 -lglu32 -lglew32 -lComdlg32
/// Linux: -lsfml-system -lsfml-window -lsfml-graphics -lpthread -lGL -lGLU -lGLEW -ldl
////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "edk/watch/FPS.h"

#include "edk/OpenLamp.h"
#include "edk/CommandParser.h"
#include "edk/Image2D.h"

#include "edk/Window.h"

#include "OpenSaveName.h"
#include <stdio.h>

//include the graphic version of the openLamp software
#include "ViewSoftware.h"

/*
./headDown.jpg
./headFront.jpg
./headLeft.jpg
./headRight.jpg
./headUp.jpg



-d ./files/headDown.jpg -f ./files/headFront.jpg -l ./files/headLeft.jpg -r ./files/headRight.jpg -u ./files/headUp.jpg -n ./files/normal.jpg

--down=./files/headDown.jpg --front=./files/headFront.jpg --left=./files/headLeft.jpg --right=./files/headRight.jpg --up=./files/headUp.jpg --normal=./files/normal.jpg

*/

int main(int argc, char* argv[]){
    //
/*
    edk::File pipe;
    edk::char8* str;
    if(pipe.openPipe("zenity --file-selection --title=\"Select a Image\" --multiple --file-filter='*.png *.jpeg *.jpg'")){
        //
        str = new char[1];

        do{
            if(str){
                delete[] str;
                str=NULL;
            }

            str = pipe.readTextString("\0",false);
            if(str){
                printf("\n'%s'",str);fflush(stdout);
            }
        }while(*str);
        if(str){
            delete[] str;
            str=NULL;
        }

        pipe.closeFile();
    }
    exit(0);
*/

    //printf("\n%u %s %s Hello OpenLamp",__LINE__,__FILE__,__func__);fflush(stdout);

    //test if have some argc
    if(argc>1){

        edk::Image2D imageUp;
        edk::Image2D imageDown;
        edk::Image2D imageLeft;
        edk::Image2D imageRight;
        edk::Image2D imageFront;
        edk::Image2D imageNormal;

        //run the command parser
        edk::CommandParser parser;
        if(parser.parseArgcArgv(argc,argv)){
            //test the commands

            //test if have the help command
            if(parser.haveCommand("--help")){
                //print the help
            }

            //front
            if(parser.haveCommand("-f")){
                //
                if(imageFront.loadFromFile(parser.getValue("-f"))){
                    //
                    printf("\nSuccess load front image %s",parser.getValue("-f"));
                }
                else{
                    //
                    printf("\nError: Can't' load front image %s",parser.getValue("-f"));
                }
            }
            else if(parser.haveCommand("--front")){
                if(imageFront.loadFromFile(parser.getValue("--front"))){
                    //
                    printf("\nSuccess load front image %s",parser.getValue("--front"));
                }
                else{
                    //
                    printf("\nError: Can't' load front image %s",parser.getValue("--front"));
                }
            }
            //left
            if(parser.haveCommand("-l")){
                if(imageLeft.loadFromFile(parser.getValue("-l"))){
                    //
                    printf("\nSuccess load left image %s",parser.getValue("-l"));
                }
                else{
                    //
                    printf("\nError: Can't' load left image %s",parser.getValue("-l"));
                }
            }
            if(parser.haveCommand("--left")){
                if(imageLeft.loadFromFile(parser.getValue("--left"))){
                    //
                    printf("\nSuccess load left image %s",parser.getValue("--left"));
                }
                else{
                    //
                    printf("\nError: Can't' load left image %s",parser.getValue("--left"));
                }
            }
            //right
            if(parser.haveCommand("-r")){
                if(imageRight.loadFromFile(parser.getValue("-r"))){
                    //
                    printf("\nSuccess load right image %s",parser.getValue("-r"));
                }
                else{
                    //
                    printf("\nError: Can't' load right image %s",parser.getValue("-r"));
                }
            }
            if(parser.haveCommand("--right")){
                if(imageRight.loadFromFile(parser.getValue("--right"))){
                    //
                    printf("\nSuccess load right image %s",parser.getValue("--right"));
                }
                else{
                    //
                    printf("\nError: Can't' load right image %s",parser.getValue("--right"));
                }
            }
            //up
            if(parser.haveCommand("-u")){
                if(imageUp.loadFromFile(parser.getValue("-u"))){
                    //
                    printf("\nSuccess load up image %s",parser.getValue("-u"));
                }
                else{
                    //
                    printf("\nError: Can't' load up image %s",parser.getValue("-u"));
                }
            }
            if(parser.haveCommand("--up")){
                if(imageUp.loadFromFile(parser.getValue("--up"))){
                    //
                    printf("\nSuccess load up image %s",parser.getValue("--up"));
                }
                else{
                    //
                    printf("\nError: Can't' load up image %s",parser.getValue("--up"));
                }
            }
            //down
            if(parser.haveCommand("-d")){
                if(imageDown.loadFromFile(parser.getValue("-d"))){
                    //
                    printf("\nSuccess load down image %s",parser.getValue("-d"));
                }
                else{
                    //
                    printf("\nError: Can't' load down image %s",parser.getValue("-d"));
                }
            }
            if(parser.haveCommand("--down")){
                if(imageDown.loadFromFile(parser.getValue("--down"))){
                    //
                    printf("\nSuccess load down image %s",parser.getValue("--down"));
                }
                else{
                    //
                    printf("\nError: Can't' load down image %s",parser.getValue("--down"));
                }
            }
            //normal
            char* normalStr=NULL;
            if(parser.haveCommand("-n")){
                if(parser.getValue("-n"))
                    normalStr = edk::String::strCopy(parser.getValue("-n"));
            }
            else if(parser.haveCommand("--normal")){
                if(parser.getValue("--normal"))
                    normalStr = edk::String::strCopy(parser.getValue("--normal"));
            }
            if(normalStr){
                //generate the normal image
                if(edk::OpenLamp::imageToNormal(&imageUp,&imageDown,&imageLeft,&imageRight,&imageFront,&imageNormal)){
                    //
                    printf("\nSuccess to generate Normal Image");

                    //save the normalImage
                    if(imageNormal.saveToFile(normalStr)){
                        printf("\nSuccess to save Normal Image %s",normalStr);

                        //set the file to read and write
                        char* commandStr = edk::String::strCatMulti("chmod 777 ",normalStr,NULL);
                        if(commandStr){
                            system(commandStr);
                            delete[] commandStr;
                        }
                    }
                    else{
                        printf("\nError: Can't save Normal Image %s",normalStr);
                    }
                }
                else{
                    //
                    printf("\nError: Can't generate Normal Image");
                }
                delete[] normalStr;
            }
        }
        return 0;
    }
    else if(argc==1u){
        //
    }


    {
        edk::watch::FPS fps(60);
        bool alt = false;
        bool f4 = false;
        bool escape = false;
        //create the openLamp window
        edk::Window win;
        win.createWindow(800, 600, (edk::char8*)"OpenLamp", EDK_WINDOW_BAR | EDK_WINDOW_BUTTONS | EDK_WINDOW_RESIZE);

        //add the graphic view to the window
        openLamp::ViewSoftware graphicVersion;
        win.addSubview(&graphicVersion);

        win.cleanColor = edk::color3f32(0,0,0);

        fps.start();
        while(win.isOpened()){
            //load the events
            win.loadEvents();
            //test the events
            win.updateViews();

            //test if close the window
            if(win.eventButtonClose()){
                win.closeWindow();
            }
            alt = false;
            f4 = false;
            //test if have pressed alt+f4
            if(win.eventKeyPressed()){
                edk::uint32 size = win.eventGetKeyPressedSize();
                for(edk::uint32 i=0u;i<size;i++){
                    //test if the keyPressed was alt
                    switch(win.eventGetKeyPressed(i)){
                    case edk::key::lAlt:
                    case edk::key::rAlt:
                        alt=true;
                        break;
                    case edk::key::F4:
                        f4=true;
                        break;
                    case edk::key::escape:
                        escape=true;
                        break;
                    }
                }
            }
            if(win.eventKeyHolded()){
                edk::uint32 size = win.eventGetKeyHoldedSize();
                for(edk::uint32 i=0u;i<size;i++){
                    //test if the keyPressed was alt
                    switch(win.eventGetKeyHolded(i)){
                    case edk::key::lAlt:
                    case edk::key::rAlt:
                        alt=true;
                        break;
                    case edk::key::F4:
                        f4=true;
                        break;
                    case edk::key::escape:
                        escape=true;
                        break;
                    }
                }
            }

            //test if press alt+f4
            if((alt&&f4) || escape){
                //close the window
                win.closeWindow();
            }

            win.drawView();

            //render window
            win.render();

            fps.waitForFPS();

        }
        //remove all views
        win.removeAllSubview();
    }

    printf("\n");
    return 0;
}

