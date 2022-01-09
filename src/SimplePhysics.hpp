#pragma once
#include <cmath>
#include <vector>
#include <thread>
// THis is just for debuging
#include <iostream>
// This file should not really care about anything else in the engine, outside the data directly sent to it

namespace SimplePhysics {
    struct ForceDirection {
        float X;
        float Y;
        float Z;
        float Speed;

        ForceDirection() {}

        ~ForceDirection() {}

        void Input(float x, float y, float z, float speed) {
            X = x;
            Y = y;
            Z = z;
            Speed = speed;
        }

    };

// Yes this is basicaly the same as the ForceDirection But with a diffrent name
    struct PhysicsPos {
        float X;
        float Y;
        float Z;

        PhysicsPos() {}

        ~PhysicsPos() {}

        void Input(float x, float y, float z) {
            X = x;
            Y = y;
            Z = z;
        }
    };

    struct PhysicsPoint {
        PhysicsPos Pos;
        float Weight;
        //ForceDirection Movment;
    };

    struct PhysicsLine {
        PhysicsPoint PosA;
        PhysicsPoint PosB;
        float Diff;
        ForceDirection Normal; // This is just going to be stored here as a referance

    };


    struct QuadPhysicsBody {
        PhysicsPoint PosA;
        PhysicsPoint PosB;
        PhysicsPoint PosC;
        PhysicsPoint PosD;
        ForceDirection PlaneNorm;

    };

    struct TriPhysicsBody {
        PhysicsPoint PosA;
        PhysicsPoint PosB;
        PhysicsPoint PosC;
        ForceDirection PlaneNorm;

    };

    struct SphearPhysicsBody {
        PhysicsPoint PosA;
        float Radius;
    };


    struct PlaneMinMax {
        ForceDirection Min;
        ForceDirection Max;
        ForceDirection Normal;
    };


    struct ColisionInfo {
        bool IsColision; // Simple "yes" "no" colision
        ForceDirection MovmentDirectionA; //This can be calculated by comparing the dirs of the 2 coliding object
        ForceDirection MovmentDirectionB;
        ForceDirection PastMovmentDirectionA;
        ForceDirection PastMovmentDirectionB;

        ForceDirection CurentMovmentDirectionA;
        ForceDirection CurentMovmentDirectionB;
        float Force; // the Force that should applied to the colistion objectA

        operator bool() { return IsColision; }
    };


    struct MultiThreadPhysUpdate {


    };

    struct SimplePhysicsObject{
        // This Will mainly be used for the StepPhysicsEnviroment()
        // This can be anytihng but im calling it UUID cause idk its better than ID
        const char* UUID;

        unsigned int TYPE{};

        SimplePhysics::PhysicsPos Position;
        SimplePhysics::PhysicsPos FuturePosition[4];

        std::vector<unsigned int> *TypeReactionList;
        std::vector<unsigned int> CustomReactionList;

        std::vector<SimplePhysics::QuadPhysicsBody> QuadPhysicsBodyVector;
        std::vector<SimplePhysics::PhysicsPoint> PhysicsPointVector;
        std::vector<SimplePhysics::SphearPhysicsBody> SphearPhysicsBodyVector;

        // I might keep this just to force every Object to have a basic sphear colidor at first
        unsigned int RangeFromCenter{};

        float MinXPos, MinYPos, MaxXPos, MaxYPos;

        // This is just to normalize some expectec/ required inputs for and Physics Objects
        SimplePhysicsObject(const char* UniqueID = nullptr, std::vector<unsigned int> *PhysicsTypeReactionList = nullptr){
            UUID = UniqueID;
            this->TypeReactionList = PhysicsTypeReactionList;
        }
        // Some feneric functons to minipulate the focibly included data

        void AddQuadPhysicsBody(SimplePhysics::PhysicsPoint A, SimplePhysics::PhysicsPoint B , SimplePhysics::PhysicsPoint C, SimplePhysics::PhysicsPoint D, SimplePhysics::ForceDirection PlaneNormal){
            SimplePhysics::QuadPhysicsBody Temp;
            Temp.PosA = A;
            Temp.PosB = B;
            Temp.PosC = C;
            Temp.PosD = D;
            Temp.PlaneNorm = PlaneNormal;

            this->QuadPhysicsBodyVector.push_back(Temp);
        }
        void RemoveQuadPhysicsBody(unsigned int ID){
            this->QuadPhysicsBodyVector.erase(this->QuadPhysicsBodyVector.begin()+ID);
        }

        void AddPhysicsPoint(SimplePhysics::PhysicsPos Pos, float Weight) {
            SimplePhysics::PhysicsPoint Temp;
            Temp.Pos = Pos;
            Temp.Weight = Weight;

            this->PhysicsPointVector.push_back(Temp);
        }
        void RemovePhysicsPoint(unsigned int ID){
            this->PhysicsPointVector.erase(this->PhysicsPointVector.begin()+ID);
        }

        void AddSphearPhysicsBody(SimplePhysics::PhysicsPoint A, float Radius){
            SimplePhysics::SphearPhysicsBody Temp;
            Temp.PosA = A;
            Temp.Radius = Radius;

            this->SphearPhysicsBodyVector.push_back(Temp);
        }
        void RemoveSphearPhysicsBody(unsigned int ID){
            this->SphearPhysicsBodyVector.erase(this->SphearPhysicsBodyVector.begin()+ID);
        }

        void AddCollisionType(unsigned int type){
            this->CustomReactionList.push_back(type);
        }
        void RemoveCollisionType(unsigned int type){
            this->CustomReactionList.erase(this->CustomReactionList.begin() + type);
        }
        const std::vector<unsigned int> *ExportCollisionTypes(){
           return this->TypeReactionList;
        }

        unsigned int CollisionTypeComparison(unsigned int type){
            for(unsigned int i : *this->TypeReactionList){
                if(type == i){
                    return type;
                }
            }
            for(unsigned int i: this->CustomReactionList){
                if(type == i){
                    return type;
                }
            }
            return -1;
        }

        virtual void Update() {};

        // Generic colision type resoluton function and operation
        operator unsigned int(){return TYPE;}
        // This is to give a general idea of a physics update function

        //
    };

    class PhysicsEngine {
    protected:
        float m_DeltaTime;

        ForceDirection m_Gravity;



    public:
        inline void SetUpdateTime(float TimePassed) { m_DeltaTime = TimePassed; }

        std::vector<SimplePhysicsObject *> Objects;

        inline float GetUpdateTime() { return m_DeltaTime; }

        inline ForceDirection GetGravity() { return m_Gravity; }

        PhysicsPos MovePhysicsObject(PhysicsPos Object, ForceDirection NormalDir, float Speed);

        // Returns froce to move ObjectA to ObjectB
        ForceDirection MakeForceDirection(PhysicsPos ObjectA, PhysicsPos ObjectB);

        void QuadsToLinesVoid(std::vector<QuadPhysicsBody> Object, std::vector<PhysicsLine> *Output);

        std::vector<PhysicsLine> QuadsToLines(std::vector<QuadPhysicsBody> Object);

        void FullQuadLineColisionVoid(std::vector<PhysicsLine> ObjectALines, PhysicsPos ObjectAPos,
                                      std::vector<PhysicsLine> ObjectBLines, PhysicsPos ObjectBPos, float Offset,
                                      ColisionInfo *Output);

        ColisionInfo FullQuadLineColision(std::vector<PhysicsLine> ObjectALines, PhysicsPos ObjectAPos,
                                          std::vector<PhysicsLine> ObjectBLines, PhysicsPos ObjectBPos, float Offset);

        void QuadBodyColision(std::vector<QuadPhysicsBody> ObjectA, PhysicsPos ObjectAPos,
                              std::vector<QuadPhysicsBody> ObjectB, PhysicsPos ObjectBPos, ColisionInfo *Output,
                              float OffSet = 0.0f);
        // Helper functions to make QuadBodyColisoin faster if possible, lol

        // Used for making a vector of PhysicsPoints translated to world space;
        void
        QuadPosToPoints(std::vector<QuadPhysicsBody> Object, PhysicsPos ObjectPos, std::vector<PhysicsPoint> *Output);

        // With Normal
        void QuadPosToPointsNormal(std::vector<QuadPhysicsBody> Object, PhysicsPos ObjectPos,
                                   std::vector<PhysicsLine> *Output);

        // Normalizes returns normal for ObjectBs points pointing twords ObjectAs points
        void PointsToPointsNormal(std::vector<PhysicsPos> ObjectA, std::vector<PhysicsPos> ObjectB,
                                  std::vector<PhysicsPos> *Output);

        // Effectivly the samthing as the Normal one but for indevidual Positions
        void PointToPoint(PhysicsPos *ObjectA, PhysicsPos *ObjectB, PhysicsPos *Output);

        void LinesToLines(std::vector<PhysicsLine> *ObjectA, std::vector<PhysicsLine> *ObjectB,
                          std::vector<PhysicsLine> *Output);

        //Currently breaks on the Z axis (it only works in 2d some how...)
        ColisionInfo
        SATColision(std::vector<QuadPhysicsBody> ObjectA, PhysicsPos ObjectAPos, std::vector<QuadPhysicsBody> ObjectB,
                    PhysicsPos ObjectBPos);

        // The returned minmax is based on world cordinates
        std::vector<PlaneMinMax> MinMaxFromQuads(std::vector<QuadPhysicsBody> Object, PhysicsPos ObjectPos);

        // This Function only does the comparison 1 way : PointsA to BoxB
        ColisionInfo PointsToAABBColision(std::vector<QuadPhysicsBody> ObjectA, PhysicsPos ObjectAPos,
                                          std::vector<PlaneMinMax> ObjectB);

        void AABBColision(std::vector<QuadPhysicsBody> &ObjectA, PhysicsPos &ObjectAPos,
                          std::vector<QuadPhysicsBody> &ObjectB, PhysicsPos &ObjectBPos, ColisionInfo *Output);

        void SphearColison(PhysicsPos ObjectAPos, float ObjectASize, PhysicsPos ObjectBPos, float ObjectBSize,
                           ColisionInfo *Output);

        // IDK why i didn't make this earlier... 
        float PointToPointDistance(PhysicsPos PointeA, PhysicsPos PointB);

        std::vector<QuadPhysicsBody>
        MakePhysicsQuads(std::vector<PhysicsPos> Pos, std::vector<PhysicsPos> Normal, std::vector<float> Weights);

        float DotPointToForce(PhysicsPos Point, ForceDirection Projection, PhysicsPos ProjectionPos);

        PhysicsPos Center2Point(PhysicsPos PointA, PhysicsPos PointB);

        PhysicsPos Center4Point(PhysicsPos *PointA, PhysicsPos *PointB, PhysicsPos *PointC, PhysicsPos *PointD);

        ColisionInfo SphearToPlane(SphearPhysicsBody ObjectA, QuadPhysicsBody ObjectB, PhysicsPos ObjectBPos);

        ForceDirection NormalizeVectorOfForceDirection(std::vector<ForceDirection> VectorOfForces);

        void NormalizeForceDirection(ForceDirection ForceA, ForceDirection ForceB, ForceDirection *Output);

        PhysicsEngine(float GravityForce, float GravityX, float GravityY, float GravityZ);

        ~PhysicsEngine();

        // The reason this is not just "Update", because this may not be the final "Update" function
        void StepPhysicsEnviroment();


        void SimpleThreadTest();


    };
}