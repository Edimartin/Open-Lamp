#include "ViewOpenLamp.h"

/*
ViewOpenLamp - View used to process the openLamp algorithm.
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

openLamp::ViewOpenLamp::ViewOpenLamp(){
    //
}
openLamp::ViewOpenLamp::~ViewOpenLamp(){
    //
}

void openLamp::ViewOpenLamp::pressButton(edk::ViewButton* button,edk::uint32 mouseButton){
    //
}
void openLamp::ViewOpenLamp::releaseButton(edk::ViewButton* button,edk::uint32 mouseButton,bool isInside){
    //test the button
    if(button == &this->buttonGenerate){
        //test the mouseButton
        switch(mouseButton){
        case edk::mouse::left:
            if(isInside){
                //generate the normal image
                if(edk::OpenLamp::imageToNormal(&this->viewUp.image,&this->viewDown.image,&this->viewLeft.image,&this->viewRight.image,&this->viewFront.image,&this->viewNormal.image)){
                    //
                    this->viewNormal.createSprite();
                }
            }
        }
    }
}
void openLamp::ViewOpenLamp::holdButton(edk::ViewButton* button,edk::uint32 mouseButton){
    //
}

//update the frame
void openLamp::ViewOpenLamp::updateFrame(){
    edk::float32 saveHeight;
    //update the button position
    this->buttonGenerate.frame = edk::rectf32(this->frame.size.width * ((0.2f * 3.f)+0.001f)
                                              ,this->frame.size.height * ((0.33f)+0.001f)
                                              ,this->frame.size.width * ((0.2f)-0.002f)
                                              ,this->frame.size.height * ((0.33f)-0.002f)
                                              );
    saveHeight = this->buttonGenerate.frame.size.height;
    this->buttonGenerate.frame.size.height*=0.25f;
    this->buttonGenerate.frame = edk::rectf32(this->buttonGenerate.frame.origin.x
                                              ,this->buttonGenerate.frame.origin.y + ((saveHeight*0.5) - (this->buttonGenerate.frame.size.height*0.5f))
                                              ,this->buttonGenerate.frame.size.width
                                              ,this->buttonGenerate.frame.size.height
                                              );
}

void openLamp::ViewOpenLamp::load(edk::rectf32 outsideViewOrigin){
    this->frame.size = outsideViewOrigin.size;

    //set the view color
    this->backgroundColor = edk::color4f32(0.f,0.f,0.f,1.f);
    this->saveFrame = outsideViewOrigin;
    this->frame.size.width*=ViewOpenLampwidthPercent;

    //add the view front
    this->viewFront.setRectPercent(edk::rectf32((0.2f)+0.001f
                                                ,(0.33f)+0.001f
                                                ,(0.2f)-0.002f
                                                ,(0.33f)-0.002f
                                                ));
    this->addSubview(&this->viewFront);
    //add the view front
    this->viewLeft.setRectPercent(edk::rectf32((0.2f *0.f)+0.001f
                                               ,(0.33f)+0.001f
                                               ,(0.2f)-0.002f
                                               ,(0.33f)-0.002f
                                               ));
    this->addSubview(&this->viewLeft);
    //add the view front
    this->viewRight.setRectPercent(edk::rectf32((0.2f * 2.f)+0.001f
                                                ,(0.33f)+0.001f
                                                ,(0.2f)-0.002f
                                                ,(0.33f)-0.002f
                                                ));
    this->addSubview(&this->viewRight);
    //add the view front
    this->viewUp.setRectPercent(edk::rectf32((0.2f)+0.001f
                                             ,(0.33f * 0.f)+0.001f
                                             ,(0.2f)-0.002f
                                             ,(0.33f)-0.002f
                                             ));
    this->addSubview(&this->viewUp);
    //add the view down
    this->viewDown.setRectPercent(edk::rectf32((0.2f)+0.001f
                                               ,(0.33f * 2.f)+0.001f
                                               ,(0.2f)-0.002f
                                               ,(0.33f)-0.002f
                                               ));
    this->addSubview(&this->viewDown);
    //add the view down
    this->viewNormal.setRectPercent(edk::rectf32((0.2f*4.f)+0.001f
                                                 ,(0.33f)+0.001f
                                                 ,(0.2f)-0.002f
                                                 ,(0.33f)-0.002f
                                                 ));
    this->addSubview(&this->viewNormal);
    this->viewNormal.canLoad=false;

    //set the button callBack
    this->buttonGenerate.setCallback(this);
    this->buttonGenerate.addButtonText("Generate");
    this->buttonGenerate.setBorderSize(5);
    this->addSubview(&this->buttonGenerate);

    //update the frame
    this->updateFrame();
}

void openLamp::ViewOpenLamp::unload(){
    //remove button callBack
    this->buttonGenerate.removeCallback();
    this->removeAllSubview();
}

void openLamp::ViewOpenLamp::update(edk::WindowEvents* events){
    //
}

void openLamp::ViewOpenLamp::draw(edk::rectf32 outsideViewOrigin){
    //update the view size if the last is different
    if(this->saveFrame!=outsideViewOrigin){
        this->saveFrame = outsideViewOrigin;
        //update the viewSize
        this->frame.size = outsideViewOrigin.size;
        this->frame.size.width*=ViewOpenLampwidthPercent;

        //update
        this->updateFrame();
    }
    edk::ViewController::draw(outsideViewOrigin);
}
