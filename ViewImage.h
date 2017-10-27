#ifndef VIEWIMAGE_H
#define VIEWIMAGE_H

/*
ViewImage - View to loag, save and show images on openLamp.
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

#include "edk/ViewController.h"
#include "edk/ViewSprite.h"
#include "edk/Image2D.h"
//
#include "OpenSaveName.h"


namespace openLamp{
class ViewImage : public edk::ViewController{
public:
    ViewImage();
    ~ViewImage();

    //set the rectPercent
    void setRectPercent(edk::rectf32 percent);

    //Events
    void eventMousePressed(edk::vec2f32 point,edk::uint32 button);
    void eventMouseMoved(edk::vec2f32 point,edk::uint32 button);
    void eventMouseReleased(edk::vec2f32 point,edk::uint32 button);
    //Mouse go Inside Outside
    void eventMouseEntryInsideView(edk::vec2f32 point);
    void eventMouseLeftView(edk::vec2f32 point);
    void eventMouseMovingInsideView(edk::vec2f32 point);

    //create the sprite from image
    bool createSprite();

    void load(edk::rectf32 outsideViewOrigin);
    void unload();

    void update(edk::WindowEvents* events);

    void draw(edk::rectf32 outsideViewOrigin);

    //Image
    edk::Image2D image;
    //set if can load the image
    bool canLoad;
private:
    //save the outsideView
    edk::rectf32 saveFrame;
    //pressed buttons inside
    bool pressLeft,pressRight;
    //sprite view
    class ViewSpriteClick : public edk::ViewSprite{
    public:
        ViewSpriteClick(){
            this->haveImage=false;
            this->haveImage = false;
            this->canSaveImage = false;
        }
        ~ViewSpriteClick(){}
        void eventMousePressed(edk::vec2f32 point,edk::uint32 button){
            //test the button pressed
            switch(button){
            case edk::mouse::left:
                if(this->isMouseInside()){
                    //
                    this->pressLeft=true;
                }
                break;
            case edk::mouse::right:
                if(this->isMouseInside()){
                    //
                    this->pressRight=true;
                }
                break;
            }
        }
        void eventMouseReleased(edk::vec2f32 point,edk::uint32 button){
            //test if the mouse is inside
            if(this->isMouseInside()){
                //test the button pressed
                switch(button){
                case edk::mouse::left:
                    if(this->pressLeft && this->canSaveImage){
                        //save the image
                        this->saveImage=true;
                    }
                    break;
                case edk::mouse::right:
                    if(this->pressRight){
                        //remove the image
                        this->deleteSprite();
                        this->frame = 0.f;
                        this->haveImage = false;
                    }
                    break;
                }
            }
            this->pressRight=false;
        }
        bool haveImage;
        //pressed buttons inside
        bool pressLeft,pressRight;
        //save image
        bool saveImage;
        //can save Image
        bool canSaveImage;
    }sprite;

    //save the percent of the image
    edk::rectf32 percent;
    //set if this view is loading the image
    static edk::classID loading;
    bool saving;

    //update the frame of the view
    void updateViewFrame();
};
}

#endif // VIEWIMAGE_H
