//
// Created by steel99xl on 1/2/22.
//
#pragma once
#include "SimplePhysics.hpp"


// Some basic physics objects useing the SimplePhysicsObject struct

struct SimplePhysicsSphereObject : public SimplePhysics::SimplePhysicsObject{
    explicit SimplePhysicsSphereObject(const char* UniqueID = nullptr, const std::vector<unsigned int> *PhysicsTypeReactionList = nullptr) : SimplePhysicsObject(UniqueID, PhysicsTypeReactionList) {
        // Junk number that hopfully wont conflict with other peoples
        this->TYPE = 42069;
    };

    void OnUpdate() override{
        std::cout << "uwu Sphere Update" << std::endl;
    };
};

struct SimplePhysicsBoxObject : public SimplePhysics::SimplePhysicsObject{
    explicit SimplePhysicsBoxObject(const char* UniqueID = nullptr, const std::vector<unsigned int> *PhysicsTypeReactionList = nullptr) : SimplePhysicsObject(UniqueID, PhysicsTypeReactionList){
        // Junk number to identify type
        this->TYPE = 69420;
    };

    void OnUpdate() override{
        std::cout << "uwu Box Update" << std::endl;
    };
};
