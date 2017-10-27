#ifndef VIEWOPENLAMP_H
#define VIEWOPENLAMP_H

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

#include "edk/ViewController.h"
#include "edk/Image2D.h"
#include "edk/ViewSprite.h"
#include "edk/ViewButton.h"
#include "ViewImage.h"
#include "edk/OpenLamp.h"

#define ViewOpenLampwidthPercent 1.0f

/*
OpenLamp Software View. Here works the graphic version of openLamp.
*/

namespace openLamp{
class ViewOpenLamp : public edk::ViewController, public edk::ButtonCallback{
public:
    ViewOpenLamp();
    ~ViewOpenLamp();

    void pressButton(edk::ViewButton* button,edk::uint32 mouseButton);
    void releaseButton(edk::ViewButton* button,edk::uint32 mouseButton,bool isInside);
    void holdButton(edk::ViewButton* button,edk::uint32 mouseButton);

    void load(edk::rectf32 outsideViewOrigin);
    void unload();

    void update(edk::WindowEvents* events);

    void draw(edk::rectf32 outsideViewOrigin);
private:
    //save the outsideView
    edk::rectf32 saveFrame;

    //Views
    openLamp::ViewImage viewFront;
    openLamp::ViewImage viewLeft;
    openLamp::ViewImage viewRight;
    openLamp::ViewImage viewUp;
    openLamp::ViewImage viewDown;
    openLamp::ViewImage viewNormal;
    edk::ViewButton buttonGenerate;
    //update the frame
    void updateFrame();
};
}

#endif // VIEWOPENLAMP_H
