#pragma once
#include <cmath>
#include <vector>
#include <thread>
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

struct SphearPhysicsBody{
    PhysicsPoint Pos;
    float Size;
};


struct PlaneMinMax{
    ForceDirection Min;
    ForceDirection Max;
    ForceDirection Normal;
};



struct ColisionInfo{
    bool IsColision; // Simple "yes" "no" colision
    ForceDirection MovmentDirectionA; //This can be calculated by comparing the dirs of the 2 coliding object
    ForceDirection MovmentDirectionB;
    float Force; // the Force that should applied to the colistion objectA

	operator bool(){return IsColision;}
};


struct MultiThreadPhysUpdate{
	

};


class SimplePhysics{
    private:
        float m_DeltaTime;

        Force m_Gravity;

        


    public:
        inline void SetUpdateTime(float TimePassed){m_DeltaTime = TimePassed;}
        inline float GetUpdateTime(){return m_DeltaTime;}
        inline Force GetGravity(){return m_Gravity;}

        PhysicsPoint MovePhysicsObject(PhysicsPoint Object, ForceDirection NormalDir, float Speed);

        void QuadsToLinesVoid(std::vector<QuadPhysicsBody> Object ,std::vector<PhysicsLine> *Output);
        std::vector<PhysicsLine> QuadsToLines(std::vector<QuadPhysicsBody> Object);

        void FullQuadLineColisionVoid(std::vector<PhysicsLine> ObjectALines, PhysicsPoint ObjectAPos, std::vector<PhysicsLine> ObjectBLines, PhysicsPoint ObjectBPos, float Offset, ColisionInfo *Output);
        ColisionInfo FullQuadLineColision(std::vector<PhysicsLine> ObjectALines,PhysicsPoint ObjectAPos, std::vector<PhysicsLine> ObjectBLines, PhysicsPoint ObjectBPos, float Offset);

        ColisionInfo QuadBodyColision(std::vector<QuadPhysicsBody> ObjectA, PhysicsPoint ObjectAPos, std::vector<QuadPhysicsBody> ObjectB, PhysicsPoint ObjectBPos, float OffSet = 0.0f);
        // Helper functions to make QuadBodyColisoin faster if possible, lol

        // Used for making a vector of PhysicsPoints translated to world space;
        void QuadPosToPoints(std::vector<QuadPhysicsBody> Object, PhysicsPoint ObjectPos, std::vector<PhysicsPoint> *Output);
        void PointsToPoints(std::vector<PhysicsPoint> ObjectA, std::vector<PhysicsPoint> ObjectB, std::vector<PhysicsPoint> *Output);
        // With Normal
        void QuadPosToPointsNormal(std::vector<QuadPhysicsBody> Object, PhysicsPoint ObjectPos, std::vector<PhysicsLine> *Output);
        void PointsToPointsNormal(std::vector<PhysicsLine> ObjectA, std::vector<PhysicsLine> ObjectB, std::vector<PhysicsLine> *Output);

        //Currently breaks on the Z axis (it only works in 2d some how...)
        ColisionInfo SATColision(std::vector<QuadPhysicsBody> ObjectA, PhysicsPoint ObjectAPos, std::vector<QuadPhysicsBody> ObjectB, PhysicsPoint ObjectBPos);

        // The returned minmax is based on world cordinates
        std::vector<PlaneMinMax> MinMaxFromQuads(std::vector<QuadPhysicsBody> Object, PhysicsPoint ObjectPos);

        // This Function only does the comparison 1 way : PointsA to BoxB
        ColisionInfo PointsToAABBColision(std::vector<QuadPhysicsBody> ObjectA, PhysicsPoint ObjectAPos, std::vector<PlaneMinMax> ObjectB);
        ColisionInfo AABBColision(std::vector<QuadPhysicsBody> &ObjectA, PhysicsPoint &ObjectAPos, std::vector<QuadPhysicsBody> &ObjectB, PhysicsPoint &ObjectBPos);

        ColisionInfo SphearColison(PhysicsPoint ObjectAPos, float ObjectASize, PhysicsPoint ObjectBPos, float ObjectBSize);

        std::vector<QuadPhysicsBody> MakePhysicsQuads(std::vector<PhysicsPos> Pos, std::vector<PhysicsPos> Normal, std::vector<float> Weights);

        float DotPointToForce(PhysicsPoint Point, ForceDirection Projection, PhysicsPoint ProjectionPos);

        PhysicsPoint Center2Point(PhysicsPoint PointA, PhysicsPoint PointB);
        PhysicsPoint Center4Point(PhysicsPoint *PointA, PhysicsPoint *PointB, PhysicsPoint *PointC, PhysicsPoint *PointD);

        // Returns froce to move ObjectA to ObjectB
        ForceDirection MakeForceDirection(PhysicsPoint ObjectA, PhysicsPoint ObjectB);

        ForceDirection NormalizeVectorOfForceDirection(std::vector<ForceDirection> VectorOfForces);

        SimplePhysics(float GravityForce, float GravityX, float GravityY, float GravityZ);
        ~SimplePhysics();


        void SimpleThreadTest();
    

};
