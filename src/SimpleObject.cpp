#include "SimpleObject.hpp"

SimpleObject::SimpleObject(){

}

SimpleObject::~SimpleObject(){

}

std::vector<Vertex> SimpleObject::Create2dQuad(std::vector<Vertex> *target, float X, float Y, float Z, float sizeX, float sizeY, float tX, float tY, float TX, float TY, float TextureID){

        Vertex Temp;
        Temp.Pos = {X, Y, Z};
        Temp.TexCord = {tX, tY};
        Temp.TexID = TextureID;

        target->push_back(Temp);
        

        Temp.Pos = {X+sizeX, Y, Z};
        Temp.TexCord = {TX, tY};
        Temp.TexID = TextureID;


        target->push_back(Temp);

        Temp.Pos = {X+sizeX, Y+sizeY, Z};
        Temp.TexCord = {TX, TY};
        Temp.TexID = TextureID;

        target->push_back(Temp);


        Temp.Pos = {X, Y+sizeY, Z};
        Temp.TexCord = {tX, TY};
        Temp.TexID = TextureID;

        target->push_back(Temp);


        return *target;
}