#include "ViewSoftware.h"

/*
ViewSoftware - View root to manage all openLamp Views.
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

openLamp::ViewSoftware::ViewSoftware()
{

}
//update the frame
void openLamp::ViewSoftware::updateFrame(){
    this->frame = edk::rectf32(2.f,
                               2.f,
                               this->saveFrame.size.width - 4.f,
                               this->saveFrame.size.height - 4.f
                               );
}

void openLamp::ViewSoftware::load(edk::rectf32 outsideViewOrigin){
    this->saveFrame = outsideViewOrigin;
    this->updateFrame();

    this->backgroundColor = edk::color4f32(0.5f,0.5f,0.5f,1.0f);

    //add the viewOpenLamp
    this->addSubview(&this->view);
}
void openLamp::ViewSoftware::unload(){
    //
    this->removeAllSubview();
}

void openLamp::ViewSoftware::update(edk::WindowEvents* events){
    //
}

void openLamp::ViewSoftware::draw(edk::rectf32 outsideViewOrigin){
    //resize the view
    if(this->saveFrame!=outsideViewOrigin){
        this->saveFrame = outsideViewOrigin;
        this->updateFrame();
    }
    edk::ViewController::draw(outsideViewOrigin);
}

