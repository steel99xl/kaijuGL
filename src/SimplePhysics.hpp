#pragma once
#include <cmath>
#include <vector>
// THis is just for debuging
#include <iostream>
// This file should not really care about anything else in the engine, outside the data directly sent to it


struct ForceDirection{
    float X;
    float Y;
    float Z;
};

// Yes this is basicaly the same as the ForceDirection But with a diffrent name
struct PhysicsPos{
    float X;
    float Y;
    float Z;
};



struct Force{
    float Power;
    ForceDirection Direction;
};

struct PhysicsPoint{
    float X;
    float Y;
    float Z;
    float Weight;
    Force Energy;
};

struct PhysicsLine{
    PhysicsPoint PosA;
    PhysicsPoint PosB;
    float Diff;
    ForceDirection Normal; // This is just going to be stored here as a referance

};


struct QuadPhysicsBody{
    PhysicsPoint PosA;
    PhysicsPoint PosB;
    PhysicsPoint PosC;
    PhysicsPoint PosD;
    ForceDirection PlaneNorm;

};

struct TriPhysicsBody{
    PhysicsPoint PosA;
    PhysicsPoint PosB;
    PhysicsPoint PosC;
    ForceDirection PlaneNorm;

};


struct PlaneMinMax{
    ForceDirection Min;
    ForceDirection Max;
};



struct ColisionInfo{
    bool IsColision; // Simple "yes" "no" colision
    ForceDirection MovmentDirectionA; //This can be calculated by comparing the dirs of the 2 coliding object
    ForceDirection MovmentDirectionB;
    float Force; // the Force that should applied to the colistion objectA
};


class SimplePhysics{
    private:
        float m_DeltaTime;

        Force m_Gravity;


    public:
        inline void SetUpdateTime(int TimeInMS){m_DeltaTime = (float)TimeInMS*0.001;}
        inline float GetUpdateTime(){return m_DeltaTime;}
        inline Force GetGravity(){return m_Gravity;}

        PhysicsPoint MovePhysicsObject(PhysicsPoint Object, ForceDirection NormalDir, float Speed);

        void QuadsToLinesVoid(std::vector<QuadPhysicsBody> Object ,std::vector<PhysicsLine> *Output);
        std::vector<PhysicsLine> QuadsToLines(std::vector<QuadPhysicsBody> Object);

        void FullQuadLineColisionVoid(std::vector<PhysicsLine> ObjectALines, PhysicsPoint ObjectAPos, std::vector<PhysicsLine> ObjectBLines, PhysicsPoint ObjectBPos, float Offset, ColisionInfo *Output);
        ColisionInfo FullQuadLineColision(std::vector<PhysicsLine> ObjectALines,PhysicsPoint ObjectAPos, std::vector<PhysicsLine> ObjectBLines, PhysicsPoint ObjectBPos, float Offset);

        ColisionInfo SATColision(std::vector<PhysicsLine> ObjectA, PhysicsPoint ObjectAPos, std::vector<PhysicsLine> ObjectB, PhysicsPoint ObjectBPos);

        ColisionInfo AABBColision(std::vector<QuadPhysicsBody> ObjectA, PhysicsPoint ObjectAPos, std::vector<QuadPhysicsBody> ObjectB, PhysicsPoint ObjectBPos);

        std::vector<QuadPhysicsBody> MakePhysicsBods(std::vector<PhysicsPos> Pos, std::vector<PhysicsPos> Normal, std::vector<float> Weights);

        ForceDirection NormalizeVectorOfForceDirection(std::vector<ForceDirection> VectorOfForces);

        SimplePhysics(float GravityForce, float GravityX, float GravityY, float GravityZ);
        ~SimplePhysics();
    

};