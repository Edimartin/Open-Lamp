#include "ViewImage.h"

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

edk::classID openLamp::ViewImage::loading=NULL;

openLamp::ViewImage::ViewImage(){
    //
    this->percent.size = edk::size2f32(1,1);
    this->canLoad = true;
    this->pressLeft=false;
    this->pressRight=false;
}
openLamp::ViewImage::~ViewImage(){
    //
}

//update the frame of the view
void openLamp::ViewImage::updateViewFrame(){
    //update the frame
    this->frame = edk::rectf32(this->saveFrame.size.width * this->percent.origin.x,
                               this->saveFrame.size.height * this->percent.origin.y,
                               this->saveFrame.size.width * this->percent.size.width,
                               this->saveFrame.size.height * this->percent.size.height
                               );


    //update the imagem frame
    if(this->image.haveImage()){
        //update if can save the image
        this->sprite.canSaveImage = !this->canLoad;

        this->sprite.haveImage = true;
        //get the image size
        edk::size2ui32 size = this->image.getSize();
        //test if the view is portrait or landscape
        if(this->frame.size.width>this->frame.size.height){
            //landscape
            //calculate the height percent
            edk::float32 percent = this->frame.size.height / this->frame.size.width;
            //test the imagem height percent
            edk::float32 imagePercent = (edk::float32)size.height / (edk::float32)size.width;
            //if the image percent is bigget than percent, then the height is 100%
            if(imagePercent>percent){
                //
                this->sprite.frame.size = edk::size2f32(this->frame.size.width * ((edk::float32)size.width / (edk::float32)size.height)
                                                        * (this->frame.size.height/this->frame.size.width)
                                                        ,this->frame.size.height
                                                        );
                this->sprite.frame.origin = edk::vec2f32((this->frame.size.width*0.5) - (sprite.frame.size.width*0.5f),0.f);
            }
            else{
                //else width is 100%
                this->sprite.frame.size = edk::size2f32(this->frame.size.width
                                                        ,this->frame.size.height * ((edk::float32)size.height / (edk::float32)size.width)
                                                        * (this->frame.size.width/this->frame.size.height)
                                                        );
                this->sprite.frame.origin = edk::vec2f32(0.f,(this->frame.size.height*0.5) - (sprite.frame.size.height*0.5f));
            }
        }
        else{
            //portrait
            //calculate the height percent
            edk::float32 percent = this->frame.size.width / this->frame.size.height;
            //test the imagem height percent
            edk::float32 imagePercent = (edk::float32)size.width / (edk::float32)size.height;
            //if the image percent is bigget than percent, then the width is 100%
            if(imagePercent>percent){
                //
                this->sprite.frame.size = edk::size2f32(this->frame.size.width
                                                        ,this->frame.size.height * ((edk::float32)size.height / (edk::float32)size.width)
                                                        * (this->frame.size.width/this->frame.size.height)
                                                        );
                this->sprite.frame.origin = edk::vec2f32(0.f,(this->frame.size.height*0.5) - (sprite.frame.size.height*0.5f));
            }
            else{
                //else height is 100%
                this->sprite.frame.size = edk::size2f32(this->frame.size.width * ((edk::float32)size.width / (edk::float32)size.height)
                                                        * (this->frame.size.height/this->frame.size.width)
                                                        ,this->frame.size.height);
                this->sprite.frame.origin = edk::vec2f32((this->frame.size.width*0.5) - (sprite.frame.size.width*0.5f),0.f);
            }
        }
    }
    else{
        this->sprite.haveImage = false;
        //
        this->sprite.frame = edk::rectf32(0,0,0,0);
    }
}

//set the rectPercent
void openLamp::ViewImage::setRectPercent(edk::rectf32 rectPercent){
    this->percent = rectPercent;
}

//Events
void openLamp::ViewImage::eventMousePressed(edk::vec2f32 point,edk::uint32 button){
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
void openLamp::ViewImage::eventMouseMoved(edk::vec2f32 point,edk::uint32 button){
    //
}
void openLamp::ViewImage::eventMouseReleased(edk::vec2f32 point,edk::uint32 button){
    //test the button pressed
    switch(button){
    case edk::mouse::left:
        if(this->isMouseInside()){
            //
            if(this->pressLeft){
                if(this->canLoad){
                    if(!this->image.haveImage() && !openLamp::ViewImage::loading){
                        //load the image
                        if(openLamp::OpenSaveName::getImageOpenName()){
                            //set loading
                            openLamp::ViewImage::loading=this;
                        }
                    }
                }
                else{
                    this->sprite.saveImage=true;
                }
            }
        }
        this->pressLeft=false;
        break;
    case edk::mouse::right:
        if(this->isMouseInside()){
            if(this->pressRight){
                //
                if(this->image.haveImage()){
                    this->image.deleteImage();
                    //update the frame
                    this->updateViewFrame();
                }
            }
        }
        this->pressRight=false;
        break;
    }
}
//Mouse go Inside Outside
void openLamp::ViewImage::eventMouseEntryInsideView(edk::vec2f32 point){
    //
}
void openLamp::ViewImage::eventMouseLeftView(edk::vec2f32 point){
    //
}
void openLamp::ViewImage::eventMouseMovingInsideView(edk::vec2f32 point){
    //
}

//create the sprite from image
bool openLamp::ViewImage::createSprite(){
    //test the image
    if(this->image.haveImage()){
        //test the image channels
        switch(this->image.getChannels()){
        case 3u:
        {
            //create a new RGBA image to receive the converted image
            edk::Image2D rgba;
            if(rgba.newImage("nameTEMP",this->image.getSize().width,this->image.getSize().height,4u)){
                if(rgba.haveImage()){
                    //convert RGB to RGBA
                    edk::Image2D::rgbTorgba(this->image.getPixels(),this->image.getSize(),rgba.getPixels());
                    /*
                    this->sprite.createSprite(this->image.getName(),rgba.getSize().width,rgba.getSize().height, GU_RGB,GU_NEAREST);
                    this->sprite.drawSprite(rgba.getPixels(),GU_NEAREST);
*/
                    this->sprite.setTextureFromMemory(this->image.getName(),rgba.getPixels(),rgba.getSize().width,rgba.getSize().height, rgba.getChannels(),GU_NEAREST);
                }
            }
            break;
        }
        case 4:
            this->sprite.createSprite(this->image.getName(),this->image.getSize().width,this->image.getSize().height, GU_RGBA,GU_NEAREST);
            this->sprite.drawSprite(this->image.getPixels(),GU_NEAREST);
            break;
        }
        this->updateViewFrame();
    }
    return false;
}

void openLamp::ViewImage::load(edk::rectf32 outsideViewOrigin){
    this->saveFrame = outsideViewOrigin;

    this->updateViewFrame();

    //set the background as white
    this->backgroundColor = edk::color4f32(1.f,1.f,1.f,1.f);

    //add the sprite
    this->addSubview(&this->sprite);
    this->sprite.backgroundColor = edk::color4f32(1.f,1.f,1.f,1.f);
}
void openLamp::ViewImage::unload(){
    //
    this->removeAllSubview();
}

void openLamp::ViewImage::update(edk::WindowEvents* events){
    //test if need save the image
    if(this->sprite.saveImage){
        //test if have the image
        if(this->image.haveImage()){
            //load the saveName
            if(openLamp::OpenSaveName::getImageSaveName()){
                //
                this->saving=true;
            }
        }
        this->sprite.saveImage=false;
    }


    //test if it's loading
    if(openLamp::ViewImage::loading == this){
        //test if have the fileName
        if(openLamp::OpenSaveName::haveResult()){
            //get the result
            edk::char8* result = openLamp::OpenSaveName::getResult();
            if(result){
                //load the image
                if(this->image.loadFromFile(result)){
                    //set the imagem do the sprite
                    if(this->sprite.loadSprite(result,GU_NEAREST)){
                        //update the frame
                        this->updateViewFrame();
                    }
                    else{
                        //else remove the image
                        this->image.deleteImage();
                    }
                }
            }
            openLamp::ViewImage::loading=NULL;
        }
        if(openLamp::ViewImage::loading == this){
            //test if is running the thread
            if(openLamp::OpenSaveName::haveThread()){
                //change the view color
                this->backgroundColor = edk::color4f32(0.5f,0.5f,1.0f,1.f);
            }
            else{
                openLamp::ViewImage::loading=NULL;
            }
        }
    }
    else {
        //change the view color
        this->backgroundColor = edk::color4f32(1.0f,1.0f,1.0f,1.f);
        if(this->saving){
            //test if have the fileName
            if(openLamp::OpenSaveName::haveResult()){
                //get the result
                edk::char8* result = openLamp::OpenSaveName::getResult();
                if(result){
                    if(this->image.haveImage()){
                        if(this->image.saveToFile(result)){
#if __linux__
                            //set the file to read and write
                            char* commandStr = edk::String::strCatMulti("chmod 777 ",result,NULL);
                            if(commandStr){
                                system(commandStr);
                                delete[] commandStr;
                            }
#endif
                        }
                    }
                }
                this->saving=false;
            }
        }
    }
    if(this->image.haveImage() && !this->sprite.haveImage){
        //remove the image
        this->image.deleteImage();
    }
}

void openLamp::ViewImage::draw(edk::rectf32 outsideViewOrigin){
    //update the view size if the last is different
    if(this->saveFrame!=outsideViewOrigin){
        this->saveFrame = outsideViewOrigin;
        //update the viewSize
        this->updateViewFrame();
    }
    edk::ViewController::draw(outsideViewOrigin);
}
