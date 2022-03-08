//
// Created by steel99xl on 1/2/22.
//
#pragma once
#include "SimplePhysics.hpp"


// Some basic physics objects useing the SimplePhysicsObject struct

struct SimplePhysicsSphereObject : public SimplePhysics::SimplePhysicsObject{
    explicit SimplePhysicsSphereObject(std::string UniqueID = "NULL", std::string TypeID = "NULL", const std::vector<unsigned int> *PhysicsTypeReactionList = nullptr, std::vector<SimplePhysics::PhysicsPos> *RenderObjPointsPos = nullptr, std::vector<SimplePhysics::PhysicsPos> *RenderObjPointsNormal = nullptr, std::vector<float> *RenderObjPointsWeight = nullptr, bool IsPlayer = false) : SimplePhysicsObject(UniqueID, TypeID, PhysicsTypeReactionList, RenderObjPointsPos, RenderObjPointsNormal, RenderObjPointsWeight, IsPlayer) {
        // Junk number that hopfully wont conflict with other peoples
        this->TYPE = 42069;
    };

    void OnUpdate() override{
        std::cout << "uwu Sphere Update" << std::endl;
    };
};

struct SimplePhysicsBoxObject : public SimplePhysics::SimplePhysicsObject{
    explicit SimplePhysicsBoxObject(std::string UniqueID = "NULL", std::string TypeID = "NULL", const std::vector<unsigned int> *PhysicsTypeReactionList = nullptr, std::vector<SimplePhysics::PhysicsPos> *RenderObjPointsPos = nullptr, std::vector<SimplePhysics::PhysicsPos> *RenderObjPointsNormal = nullptr, std::vector<float> *RenderObjPointsWeight = nullptr, bool IsPlayer = false) : SimplePhysicsObject(UniqueID, TypeID, PhysicsTypeReactionList, RenderObjPointsPos, RenderObjPointsNormal, RenderObjPointsWeight, IsPlayer){
        // Junk number to identify type
        this->TYPE = 69420;
    };

    void OnUpdate() override{
        std::cout << "uwu Box Update" << std::endl;
    };
};
