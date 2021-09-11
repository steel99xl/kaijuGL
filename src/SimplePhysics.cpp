#include "SimplePhysics.hpp"

SimplePhysics::SimplePhysics(float GravityForce, float GravityX, float GravityY, float GravityZ){
    float Length = std::sqrt(GravityX * GravityX + GravityY * GravityY + GravityZ * GravityZ);

    if(Length != 0.){
        GravityX /= Length;
        GravityY /= Length;
        GravityZ /= Length;
    }

    m_Gravity.Direction.X = GravityX;
    m_Gravity.Direction.Y = GravityY;
    m_Gravity.Direction.Z = GravityZ;

    m_Gravity.Power = GravityForce;
}

SimplePhysics::~SimplePhysics(){}

std::vector<QuadPhysicsBody> SimplePhysics::MakePhysicsBods(std::vector<PhysicsPos> Pos, std::vector<PhysicsPos> Normal, std::vector<float>Weights){
    std::vector<QuadPhysicsBody> Output;

    QuadPhysicsBody TempQuad;
    PhysicsPoint PointA;
    PhysicsPoint PointB;
    PhysicsPoint PointC;
    PhysicsPoint PointD;

    for(long unsigned int i = 0; i < Pos.size(); i+=4){
        PointA.X = Pos[i].X;
        PointA.Y = Pos[i].Y;
        PointA.Z = Pos[i].Z;
        PointA.Weight = Weights[i];
        PointA.Energy.Direction.X = 0;
        PointA.Energy.Direction.Y = 0;
        PointA.Energy.Direction.Z = 0;
        PointA.Energy.Power = 0.0f;

        PointB.X = Pos[i+1].X;
        PointB.Y = Pos[i+1].Y;
        PointB.Z = Pos[i+1].Z;
        PointB.Weight = Weights[i+1];
        PointB.Energy.Direction.X = 0;
        PointB.Energy.Direction.Y = 0;
        PointB.Energy.Direction.Z = 0;
        PointB.Energy.Power = 0.0f;


        PointC.X = Pos[i+2].X;
        PointC.Y = Pos[i+2].Y;
        PointC.Z = Pos[i+2].Z;
        PointC.Weight = Weights[i+2];
        PointC.Energy.Direction.X = 0;
        PointC.Energy.Direction.Y = 0;
        PointC.Energy.Direction.Z = 0;
        PointC.Energy.Power = 0.0f;


        PointD.X = Pos[i+3].X;
        PointD.Y = Pos[i+3].Y;
        PointD.Z = Pos[i+3].Z;
        PointD.Weight = Weights[i+3];
        PointD.Energy.Direction.X = 0;
        PointD.Energy.Direction.Y = 0;
        PointD.Energy.Direction.Z = 0;
        PointD.Energy.Power = 0.0f;

        TempQuad.PosA = PointA;
        TempQuad.PosB = PointB;
        TempQuad.PosC = PointC;
        TempQuad.PosD = PointD;
        TempQuad.PlaneNorm.X = Normal[i].X;
        TempQuad.PlaneNorm.Y = Normal[i].Y;
        TempQuad.PlaneNorm.Z = Normal[i].Z;
        Output.push_back(TempQuad);

    }

    return Output;
}

PhysicsPoint SimplePhysics::MovePhysicsObject(PhysicsPoint Object, ForceDirection NormalDir, float Speed){
    Speed *= m_DeltaTime;

    NormalDir.X *= Speed;
    NormalDir.Y *= Speed;
    NormalDir.Z *= Speed;

    Object.X += NormalDir.X;
    Object.Y += NormalDir.Y;
    Object.Z += NormalDir.Z;

    return Object;
}

void SimplePhysics::QuadsToLinesVoid(std::vector<QuadPhysicsBody> Object ,std::vector<PhysicsLine> *Output){
    PhysicsLine Temp;

    for(long unsigned int i = 0; i < Object.size(); i++){
        Temp.PosA = Object[i].PosA;
        Temp.PosB = Object[i].PosB;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output->push_back(Temp);

        Temp.PosA = Object[i].PosB;
        Temp.PosB = Object[i].PosC;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output->push_back(Temp);

        Temp.PosA = Object[i].PosC;
        Temp.PosB = Object[i].PosD;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output->push_back(Temp);

        Temp.PosA = Object[i].PosD;
        Temp.PosB = Object[i].PosA;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output->push_back(Temp);

    }

    //return Output;
}

// Each Quad has 6 PhysicsLines generated from the 4 points
std::vector<PhysicsLine> SimplePhysics::QuadsToLines(std::vector<QuadPhysicsBody> Object){
    std::vector<PhysicsLine> Output;
    PhysicsLine Temp;

    for(long unsigned int i = 0; i < Object.size(); i++){
        Temp.PosA = Object[i].PosA;
        Temp.PosB = Object[i].PosB;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output.push_back(Temp);

        Temp.PosA = Object[i].PosB;
        Temp.PosB = Object[i].PosC;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output.push_back(Temp);

        Temp.PosA = Object[i].PosC;
        Temp.PosB = Object[i].PosD;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output.push_back(Temp);

        Temp.PosA = Object[i].PosD;
        Temp.PosB = Object[i].PosA;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output.push_back(Temp);
        // IDK if i need these
        /*
        Temp.PosA = Object[i].PosA;
        Temp.PosB = Object[i].PosC;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output.push_back(Temp);

        Temp.PosA = Object[i].PosB;
        Temp.PosB = Object[i].PosD;
        Temp.Diff = std::sqrt( ((Temp.PosB.X - Temp.PosA.X)*(Temp.PosB.X - Temp.PosA.X)) + ((Temp.PosB.Y - Temp.PosA.Y)*(Temp.PosB.Y - Temp.PosA.Y)) + ((Temp.PosB.Z - Temp.PosA.Z)*(Temp.PosB.Z - Temp.PosA.Z)) );
        Temp.Normal = Object[i].PlaneNorm;

        Output.push_back(Temp);
        */


    }

    return Output;
}

void SimplePhysics::FullQuadLineColisionVoid(std::vector<PhysicsLine> ObjectALines, PhysicsPoint ObjectAPos, std::vector<PhysicsLine> ObjectBLines, PhysicsPoint ObjectBPos, float Offset, ColisionInfo *Output){
    // Assume no colision
    Output->IsColision = false;
    float A,B,C,D;

    PhysicsPos Line1A, Line1B, Line2A, Line2B;

    for(long unsigned int i = 0; i < ObjectALines.size(); i++){
        for(long unsigned int j = 0; j < ObjectBLines.size(); j++){
            Line1A.X = ObjectALines[i].PosA.X + ObjectAPos.X;
            Line1A.Y = ObjectALines[i].PosA.Y + ObjectAPos.Y;
            Line1A.Z = ObjectALines[i].PosA.Z + ObjectAPos.Z;

            Line1B.X = ObjectALines[i].PosB.X + ObjectAPos.X;
            Line1B.Y = ObjectALines[i].PosB.Y + ObjectAPos.Y;
            Line1B.Z = ObjectALines[i].PosB.Z + ObjectAPos.Z;

            Line2A.X = ObjectBLines[j].PosA.X + ObjectBPos.X;
            Line2A.Y = ObjectBLines[j].PosA.Y + ObjectBPos.Y;
            Line2A.Z = ObjectBLines[j].PosA.Z + ObjectBPos.Z;

            Line2B.X = ObjectBLines[j].PosB.X + ObjectBPos.X;
            Line2B.Y = ObjectBLines[j].PosB.Y + ObjectBPos.Y;
            Line2B.Z = ObjectBLines[j].PosB.Z + ObjectBPos.Z;

            A =  std::sqrt( (Line2A.X - Line1A.X)*(Line2A.X-Line1A.X) + (Line2A.Y - Line1A.Y)*(Line2A.Y - Line1A.Y) + (Line2A.Z - Line1A.Z)*(Line2A.Z - Line1A.Z));
            B =  std::sqrt( (Line2B.X - Line1A.X)*(Line2B.X-Line1A.X) + (Line2B.Y - Line1A.Y)*(Line2B.Y - Line1A.Y) + (Line2B.Z - Line1A.Z)*(Line2B.Z - Line1A.Z));
            C =  std::sqrt( (Line2A.X - Line1B.X)*(Line2A.X-Line1B.X) + (Line2A.Y - Line1B.Y)*(Line2A.Y - Line1B.Y) + (Line2A.Z - Line1B.Z)*(Line2A.Z - Line1B.Z));
            D =  std::sqrt( (Line2B.X - Line1B.X)*(Line2B.X-Line1B.X) + (Line2B.Y - Line1B.Y)*(Line2B.Y - Line1B.Y) + (Line2B.Z - Line1B.Z)*(Line2B.Z - Line1B.Z));

            if((A+B) <= (ObjectBLines[j].Diff * Offset) && (C+D) <= (ObjectBLines[j].Diff * Offset)){
                Output->IsColision = true;
                Output->MovmentDirectionA = ObjectALines[i].Normal;
                Output->MovmentDirectionB = ObjectBLines[j].Normal;
                Output->Force = 2.0f;
                break;
            }

        }
        if(Output->IsColision){
            break;
        }

    }

}

ColisionInfo SimplePhysics::FullQuadLineColision(std::vector<PhysicsLine> ObjectALines, PhysicsPoint ObjectAPos, std::vector<PhysicsLine> ObjectBLines, PhysicsPoint ObjectBPos, float Offset){
    ColisionInfo Output;
    Output.IsColision = false;
    float A,B,C,D;

    PhysicsPos Line1A, Line1B, Line2A, Line2B;

  

    for(long unsigned int i = 0; i < ObjectALines.size(); i++){
        for(long unsigned int j = 0; j < ObjectBLines.size(); j++){
            Line1A.X = ObjectALines[i].PosA.X + ObjectAPos.X;
            Line1A.Y = ObjectALines[i].PosA.Y + ObjectAPos.Y;
            Line1A.Z = ObjectALines[i].PosA.Z + ObjectAPos.Z;

            Line1B.X = ObjectALines[i].PosB.X + ObjectAPos.X;
            Line1B.Y = ObjectALines[i].PosB.Y + ObjectAPos.Y;
            Line1B.Z = ObjectALines[i].PosB.Z + ObjectAPos.Z;

            Line2A.X = ObjectBLines[j].PosA.X + ObjectBPos.X;
            Line2A.Y = ObjectBLines[j].PosA.Y + ObjectBPos.Y;
            Line2A.Z = ObjectBLines[j].PosA.Z + ObjectBPos.Z;

            Line2B.X = ObjectBLines[j].PosB.X + ObjectBPos.X;
            Line2B.Y = ObjectBLines[j].PosB.Y + ObjectBPos.Y;
            Line2B.Z = ObjectBLines[j].PosB.Z + ObjectBPos.Z;

            A =  std::sqrt( (Line2A.X - Line1A.X)*(Line2A.X-Line1A.X) + (Line2A.Y - Line1A.Y)*(Line2A.Y - Line1A.Y) + (Line2A.Z - Line1A.Z)*(Line2A.Z - Line1A.Z));
            B =  std::sqrt( (Line2B.X - Line1A.X)*(Line2B.X-Line1A.X) + (Line2B.Y - Line1A.Y)*(Line2B.Y - Line1A.Y) + (Line2B.Z - Line1A.Z)*(Line2B.Z - Line1A.Z));
            C =  std::sqrt( (Line2A.X - Line1B.X)*(Line2A.X-Line1B.X) + (Line2A.Y - Line1B.Y)*(Line2A.Y - Line1B.Y) + (Line2A.Z - Line1B.Z)*(Line2A.Z - Line1B.Z));
            D =  std::sqrt( (Line2B.X - Line1B.X)*(Line2B.X-Line1B.X) + (Line2B.Y - Line1B.Y)*(Line2B.Y - Line1B.Y) + (Line2B.Z - Line1B.Z)*(Line2B.Z - Line1B.Z));
            //std::cout << "Just some Numbers" << std::endl;
            //std::cout << A+B << " | " << ObjectBLines[i].Diff * Offset << std::endl;
            //std::cout << C+D << " | " << ObjectBLines[i].Diff << std::endl;
            if((A+B) <= (ObjectBLines[j].Diff * Offset) && (C+D) <= (ObjectBLines[j].Diff * Offset)){
                //std::cout << A << " | " << B << " | " << C << " | " << D  << std::endl;
                /*
                std::cout << "Colision diffs" << std::endl;
                std::cout << i << "/" << ObjectALines.size() << " | " << j <<"/"<< ObjectBLines.size() << std::endl;
                std::cout << ObjectALines[i].PosA.X << " | " <<  ObjectALines[i].PosA.Y << " | " << ObjectALines[i].PosA.Z << std::endl;
                std::cout << "2 other points" << std::endl;
                std::cout << ObjectBLines[i].PosA.X << " | " <<  ObjectBLines[i].PosA.Y << " | " << ObjectBLines[i].PosA.Z << std::endl;
                std::cout << ObjectBLines[i].PosB.X << " | " <<  ObjectBLines[i].PosB.Y << " | " << ObjectBLines[i].PosB.Z << std::endl;

                
                std::cout << "Added off set" << std::endl;
                std::cout << ObjectAPos.X << " | " << ObjectAPos.Y << " | " << ObjectAPos.Z << std::endl;
                std::cout << ObjectBPos.X << " | " << ObjectBPos.Y << " | " << ObjectBPos.Z << std::endl;  
                std::cout << A << " | " << B << " | " << C << " | " << D  << std::endl;
                std::cout << A+B << " | " << ObjectBLines[j].Diff * Offset << std::endl;
                std::cout << C+D << " | " << ObjectBLines[j].Diff << std::endl; 
                */
                Output.IsColision = true;
                Output.MovmentDirectionA = ObjectALines[i].Normal;
                Output.MovmentDirectionB = ObjectBLines[j].Normal;
                Output.Force = 2.0f;
                break;
            }

        }
        if(Output.IsColision){
            break;
        }

    }

    if(!Output.IsColision){
        for(long unsigned int i = 0; i < ObjectBLines.size(); i++){
            for(long unsigned int j = 0; j < ObjectALines.size(); j++){
                Line1A.X = ObjectALines[j].PosA.X + ObjectAPos.X;
                Line1A.Y = ObjectALines[j].PosA.Y + ObjectAPos.Y;
                Line1A.Z = ObjectALines[j].PosA.Z + ObjectAPos.Z;

                Line1B.X = ObjectALines[j].PosB.X + ObjectAPos.X;
                Line1B.Y = ObjectALines[j].PosB.Y + ObjectAPos.Y;
                Line1B.Z = ObjectALines[j].PosB.Z + ObjectAPos.Z;

                Line2A.X = ObjectBLines[i].PosA.X + ObjectBPos.X;
                Line2A.Y = ObjectBLines[i].PosA.Y + ObjectBPos.Y;
                Line2A.Z = ObjectBLines[i].PosA.Z + ObjectBPos.Z;

                Line2B.X = ObjectBLines[i].PosB.X + ObjectBPos.X;
                Line2B.Y = ObjectBLines[i].PosB.Y + ObjectBPos.Y;
                Line2B.Z = ObjectBLines[i].PosB.Z + ObjectBPos.Z;

                A =  std::sqrt( (Line2A.X - Line1A.X)*(Line2A.X-Line1A.X) + (Line2A.Y - Line1A.Y)*(Line2A.Y - Line1A.Y) + (Line2A.Z - Line1A.Z)*(Line2A.Z - Line1A.Z));
                B =  std::sqrt( (Line2B.X - Line1A.X)*(Line2B.X-Line1A.X) + (Line2B.Y - Line1A.Y)*(Line2B.Y - Line1A.Y) + (Line2B.Z - Line1A.Z)*(Line2B.Z - Line1A.Z));
                C =  std::sqrt( (Line2A.X - Line1B.X)*(Line2A.X-Line1B.X) + (Line2A.Y - Line1B.Y)*(Line2A.Y - Line1B.Y) + (Line2A.Z - Line1B.Z)*(Line2A.Z - Line1B.Z));
                D =  std::sqrt( (Line2B.X - Line1B.X)*(Line2B.X-Line1B.X) + (Line2B.Y - Line1B.Y)*(Line2B.Y - Line1B.Y) + (Line2B.Z - Line1B.Z)*(Line2B.Z - Line1B.Z));

                if((A+C) <= (ObjectALines[j].Diff * Offset) && (B+D) <= (ObjectALines[j].Diff * Offset)){
                    Output.IsColision = true;
                    Output.MovmentDirectionA = ObjectALines[j].Normal;
                    Output.MovmentDirectionB = ObjectBLines[i].Normal;
                    Output.Force = 2.0f;
                    break;
                }

            }
            if(Output.IsColision){
                break;
            }

        }
    }
    


    return Output;
}

ColisionInfo SimplePhysics::SATColision(std::vector<PhysicsLine> ObjectA, PhysicsPoint ObjectAPos, std::vector<PhysicsLine> ObjectB, PhysicsPoint ObjectBPos){
    ColisionInfo Output;
    PhysicsPoint edge;


    for(long unsigned int i = 0; i < ObjectA.size(); i++){
        edge.X = (ObjectA[i].PosB.X - ObjectA[i].PosA.X); 
        edge.Y = (ObjectA[i].PosB.Y - ObjectA[i].PosA.Y); 
        edge.Z = (ObjectA[i].PosB.Z - ObjectA[i].PosA.Z); 
        
    } 


    return Output;
}

std::vector<PlaneMinMax> SimplePhysics::MinMaxFromQuads(std::vector<QuadPhysicsBody> Object, PhysicsPoint ObjectPos){
    std::vector<PlaneMinMax> Output;

    PlaneMinMax TempMinMax;
    float XMin, YMin, ZMin, XMax, YMax, ZMax;

    float AX, BX, CX, DX;
    float AY, BY, CY, DY;
    float AZ, BZ, CZ, DZ;

    for(long unsigned int i = 0; i < Object.size(); i++){

        AX = Object[i].PosA.X + ObjectPos.X;
        AY = Object[i].PosA.Y + ObjectPos.Y;
        AZ = Object[i].PosA.Z + ObjectPos.Z;

        BX = Object[i].PosB.X + ObjectPos.X;
        BY = Object[i].PosB.Y + ObjectPos.Y;
        BZ = Object[i].PosB.Z + ObjectPos.Z;

        CX = Object[i].PosC.X + ObjectPos.X;
        CY = Object[i].PosC.Y + ObjectPos.Y;
        CZ = Object[i].PosC.Z + ObjectPos.Z;

        DX = Object[i].PosD.X + ObjectPos.X;
        DY = Object[i].PosD.Y + ObjectPos.Y;
        DZ = Object[i].PosD.Z + ObjectPos.Z;

        if(AX >= BX && AX >= CX && AX >= DX){
            XMax = AX;
        } else if(BX >= AX && BX >= CX && BX >= DX){
            XMax = BX;
        } else if(CX >= AX && CX >= BX && CX >= DX){
            XMax = CX;
        } else if(DX >= AX && DX >= CX && DX >= BX){
            XMax = DX;
        }

        if(AY >= BY && AY >= CY && AY >= DY){
            YMax = AY;
        } else if(BY >= AY && BY >= CY && BY >= DY){
            YMax = BY;
        } else if(CY >= AY && CY >= BY && CY >= DY){
            YMax = CY;
        } else if(DY >= AY && DY >= CY && DY >= BY){
            YMax = DY;
        }

        if(AZ >= BZ && AZ >= CZ && AZ >= DZ){
            ZMax = AZ;
        } else if(BZ >= AZ && BZ >= CZ && BZ >= DZ){
            ZMax = BZ;
        } else if(CZ >= AZ && CZ >= BZ && CZ >= DZ){
            ZMax = CZ;
        } else if(DZ >= AZ && DZ >= CZ && DZ >= BZ){
            ZMax = DZ;
        }


        if(AX <= BX && AX <= CX && AX <= DX){
            XMin = AX;
        } else if(BX <= AX && BX <= CX && BX <= DX){
            XMin = BX;
        } else if(CX <= AX && CX <= BX && CX <= DX){
            XMin = CX;
        } else if(DX <= AX && DX <= CX && DX <= BX){
            XMin = DX;
        }

        if(AY <= BY && AY <= CY && AY <= DY){
            YMin = AY;
        } else if(BY <= AY && BY <= CY && BY <= DY){
            YMin = BY;
        } else if(CY <= AY && CY <= BY && CY <= DY){
            YMin = CY;
        } else if(DY <= AY && DY <= CY && DY <= BY){
            YMin = DY;
        }

        if(AZ <= BZ && AZ <= CZ && AZ <= DZ){
            ZMin = AZ;
        } else if(BZ <= AZ && BZ <= CZ && BZ <= DZ){
            ZMin = BZ;
        } else if(CZ <= AZ && CZ <= BZ && CZ <= DZ){
            ZMin = CZ;
        } else if(DZ <= AZ && DZ <= CZ && DZ <= BZ){
            ZMin = DZ;
        }

        TempMinMax.Min.X = XMin;
        TempMinMax.Min.Y = YMin;
        TempMinMax.Min.Z = ZMin;

        TempMinMax.Max.X = XMax;
        TempMinMax.Max.Y = YMax;
        TempMinMax.Max.Z = ZMax;

        TempMinMax.Normal = Object[i].PlaneNorm;

        Output.push_back(TempMinMax);
    }



    return Output;
}

ColisionInfo SimplePhysics::PointsToAABBColision(std::vector<QuadPhysicsBody> ObjectA, PhysicsPoint ObjectAPos, std::vector<PlaneMinMax> ObjectB){
    ColisionInfo Output;
    Output.IsColision = false;

    PhysicsPoint ComparePoint;

    bool XColision = false;
    bool YColision = false;
    bool ZColision = false;


    for(long unsigned int i = 0; i < ObjectA.size(); i++){
        for(long unsigned int j = 0; j < ObjectB.size(); j++){
            for(int n = 0; n < 4; n++){
                switch(n){
                    case 0:
                        ComparePoint.X = ObjectA[i].PosA.X + ObjectAPos.X;
                        ComparePoint.Y = ObjectA[i].PosA.Y + ObjectAPos.Y;
                        ComparePoint.Z = ObjectA[i].PosA.Z + ObjectAPos.Z;
                        break;
                    case 1:
                        ComparePoint.X = ObjectA[i].PosB.X + ObjectAPos.X;
                        ComparePoint.Y = ObjectA[i].PosB.Y + ObjectAPos.Y;
                        ComparePoint.Z = ObjectA[i].PosB.Z + ObjectAPos.Z;
                        break;
                    case 2:
                        ComparePoint.X = ObjectA[i].PosC.X + ObjectAPos.X;
                        ComparePoint.Y = ObjectA[i].PosC.Y + ObjectAPos.Y;
                        ComparePoint.Z = ObjectA[i].PosC.Z + ObjectAPos.Z;
                        break;
                    case 3:
                        ComparePoint.X = ObjectA[i].PosD.X + ObjectAPos.X;
                        ComparePoint.Y = ObjectA[i].PosD.Y + ObjectAPos.Y;
                        ComparePoint.Z = ObjectA[i].PosD.Z + ObjectAPos.Z;
                        break;
                }

                if(ComparePoint.X >= ObjectB[j].Min.X && ComparePoint.X <=ObjectB[j].Max.X){
                    XColision = true;
                } else {
                    XColision = false;
                }

                if(ComparePoint.Y >= ObjectB[j].Min.Y && ComparePoint.Y <=ObjectB[j].Max.Y){
                    YColision = true;
                } else {
                    YColision = false;
                }

                if(ComparePoint.Z >= ObjectB[j].Min.Z && ComparePoint.Z <=ObjectB[j].Max.Z){
                    ZColision = true;
                } else {
                    ZColision = false;
                }

                if(XColision && YColision && ZColision){
                    Output.IsColision = true;
                    Output.MovmentDirectionA = ObjectA[i].PlaneNorm;
                    Output.MovmentDirectionB = ObjectB[j].Normal;
                    return Output;
                }



            }
        } 
    }




    return Output;
}

ColisionInfo SimplePhysics::AABBColision(std::vector<QuadPhysicsBody> ObjectA, PhysicsPoint ObjectAPos, std::vector<QuadPhysicsBody> ObjectB, PhysicsPoint ObjectBPos){
    ColisionInfo Temp;

    bool XColision = false;
    bool YColision = false;
    bool ZColision = false;

    std::vector<PlaneMinMax> MinMaxA, MinMaxB;

    int IndexIntersectA, IntexIntersectB;
    bool isColision = false;

    PlaneMinMax TempMinMax;
    float XMin, YMin, ZMin, XMax, YMax, ZMax;

    float AX, BX, CX, DX;
    float AY, BY, CY, DY;
    float AZ, BZ, CZ, DZ;


    for(long unsigned int i = 0; i < ObjectA.size(); i++){

        AX = ObjectA[i].PosA.X + ObjectAPos.X;
        AY = ObjectA[i].PosA.Y + ObjectAPos.Y;
        AZ = ObjectA[i].PosA.Z + ObjectAPos.Z;

        BX = ObjectA[i].PosB.X + ObjectAPos.X;
        BY = ObjectA[i].PosB.Y + ObjectAPos.Y;
        BZ = ObjectA[i].PosB.Z + ObjectAPos.Z;

        CX = ObjectA[i].PosC.X + ObjectAPos.X;
        CY = ObjectA[i].PosC.Y + ObjectAPos.Y;
        CZ = ObjectA[i].PosC.Z + ObjectAPos.Z;

        DX = ObjectA[i].PosD.X + ObjectAPos.X;
        DY = ObjectA[i].PosD.Y + ObjectAPos.Y;
        DZ = ObjectA[i].PosD.Z + ObjectAPos.Z;

        if(AX >= BX && AX >= CX && AX >= DX){
            XMax = AX;
        } else if(BX >= AX && BX >= CX && BX >= DX){
            XMax = BX;
        } else if(CX >= AX && CX >= BX && CX >= DX){
            XMax = CX;
        } else if(DX >= AX && DX >= CX && DX >= BX){
            XMax = DX;
        }

        if(AY >= BY && AY >= CY && AY >= DY){
            YMax = AY;
        } else if(BY >= AY && BY >= CY && BY >= DY){
            YMax = BY;
        } else if(CY >= AY && CY >= BY && CY >= DY){
            YMax = CY;
        } else if(DY >= AY && DY >= CY && DY >= BY){
            YMax = DY;
        }

        if(AZ >= BZ && AZ >= CZ && AZ >= DZ){
            ZMax = AZ;
        } else if(BZ >= AZ && BZ >= CZ && BZ >= DZ){
            ZMax = BZ;
        } else if(CZ >= AZ && CZ >= BZ && CZ >= DZ){
            ZMax = CZ;
        } else if(DZ >= AZ && DZ >= CZ && DZ >= BZ){
            ZMax = DZ;
        }

        if(AX <= BX && AX <= CX && AX <= DX){
            XMin = AX;
        } else if(BX <= AX && BX <= CX && BX <= DX){
            XMin = BX;
        } else if(CX <= AX && CX <= BX && CX <= DX){
            XMin = CX;
        } else if(DX <= AX && DX <= CX && DX <= BX){
            XMin = DX;
        }

        if(AY <= BY && AY <= CY && AY <= DY){
            YMin = AY;
        } else if(BY <= AY && BY <= CY && BY <= DY){
            YMin = BY;
        } else if(CY <= AY && CY <= BY && CY <= DY){
            YMin = CY;
        } else if(DY <= AY && DY <= CY && DY <= BY){
            YMin = DY;
        }

        if(AZ <= BZ && AZ <= CZ && AZ <= DZ){
            ZMin = AZ;
        } else if(BZ <= AZ && BZ <= CZ && BZ <= DZ){
            ZMin = BZ;
        } else if(CZ <= AZ && CZ <= BZ && CZ <= DZ){
            ZMin = CZ;
        } else if(DZ <= AZ && DZ <= CZ && DZ <= BZ){
            ZMin = DZ;
        }

        TempMinMax.Min.X = XMin;
        TempMinMax.Min.Y = YMin;
        TempMinMax.Min.Z = ZMin;

        TempMinMax.Max.X = XMax;
        TempMinMax.Max.Y = YMax;
        TempMinMax.Max.Z = ZMax;

        TempMinMax.Normal = ObjectA[i].PlaneNorm;

        MinMaxA.push_back(TempMinMax);

    }

    for(long unsigned int i = 0; i < ObjectB.size(); i++){

        AX = ObjectB[i].PosA.X + ObjectBPos.X;
        AY = ObjectB[i].PosA.Y + ObjectBPos.Y;
        AZ = ObjectB[i].PosA.Z + ObjectBPos.Z;

        BX = ObjectB[i].PosB.X + ObjectBPos.X;
        BY = ObjectB[i].PosB.Y + ObjectBPos.Y;
        BZ = ObjectB[i].PosB.Z + ObjectBPos.Z;

        CX = ObjectB[i].PosC.X + ObjectBPos.X;
        CY = ObjectB[i].PosC.Y + ObjectBPos.Y;
        CZ = ObjectB[i].PosC.Z + ObjectBPos.Z;

        DX = ObjectB[i].PosD.X + ObjectBPos.X;
        DY = ObjectB[i].PosD.Y + ObjectBPos.Y;
        DZ = ObjectB[i].PosD.Z + ObjectBPos.Z;

        if(AX >= BX && AX >= CX && AX >= DX){
            XMax = AX;
        } else if(BX >= AX && BX >= CX && BX >= DX){
            XMax = BX;
        } else if(CX >= AX && CX >= BX && CX >= DX){
            XMax = CX;
        } else if(DX >= AX && DX >= CX && DX >= BX){
            XMax = DX;
        }

        if(AY >= BY && AY >= CY && AY >= DY){
            YMax = AY;
        } else if(BY >= AY && BY >= CY && BY >= DY){
            YMax = BY;
        } else if(CY >= AY && CY >= BY && CY >= DY){
            YMax = CY;
        } else if(DY >= AY && DY >= CY && DY >= BY){
            YMax = DY;
        }

        if(AZ >= BZ && AZ >= CZ && AZ >= DZ){
            ZMax = AZ;
        } else if(BZ >= AZ && BZ >= CZ && BZ >= DZ){
            ZMax = BZ;
        } else if(CZ >= AZ && CZ >= BZ && CZ >= DZ){
            ZMax = CZ;
        } else if(DZ >= AZ && DZ >= CZ && DZ >= BZ){
            ZMax = DZ;
        }


        if(AX <= BX && AX <= CX && AX <= DX){
            XMin = AX;
        } else if(BX <= AX && BX <= CX && BX <= DX){
            XMin = BX;
        } else if(CX <= AX && CX <= BX && CX <= DX){
            XMin = CX;
        } else if(DX <= AX && DX <= CX && DX <= BX){
            XMin = DX;
        }

        if(AY <= BY && AY <= CY && AY <= DY){
            YMin = AY;
        } else if(BY <= AY && BY <= CY && BY <= DY){
            YMin = BY;
        } else if(CY <= AY && CY <= BY && CY <= DY){
            YMin = CY;
        } else if(DY <= AY && DY <= CY && DY <= BY){
            YMin = DY;
        }

        if(AZ <= BZ && AZ <= CZ && AZ <= DZ){
            ZMin = AZ;
        } else if(BZ <= AZ && BZ <= CZ && BZ <= DZ){
            ZMin = BZ;
        } else if(CZ <= AZ && CZ <= BZ && CZ <= DZ){
            ZMin = CZ;
        } else if(DZ <= AZ && DZ <= CZ && DZ <= BZ){
            ZMin = DZ;
        }

        TempMinMax.Min.X = XMin;
        TempMinMax.Min.Y = YMin;
        TempMinMax.Min.Z = ZMin;

        TempMinMax.Max.X = XMax;
        TempMinMax.Max.Y = YMax;
        TempMinMax.Max.Z = ZMax;

        TempMinMax.Normal = ObjectA[i].PlaneNorm;

        MinMaxB.push_back(TempMinMax);
    }

    for(long unsigned int i = 0; i < MinMaxA.size(); i++){
        for(long unsigned int j = 0; j < MinMaxB.size(); j++){
            if((MinMaxA[i].Min.X <= MinMaxB[j].Min.X && MinMaxA[i].Max.X >= MinMaxB[j].Max.X) || (MinMaxA[i].Min.X >= MinMaxB[j].Min.X && MinMaxA[i].Max.X <= MinMaxB[j].Max.X)){
                XColision = true;
            } else {
                XColision = false;
            }
            if((MinMaxA[i].Min.Y <= MinMaxB[j].Min.Y && MinMaxA[i].Max.Y >= MinMaxB[j].Max.Y) || (MinMaxA[i].Min.Y >= MinMaxB[j].Min.Y && MinMaxA[i].Max.Y <= MinMaxB[j].Max.Y)){
                YColision = true;
            } else {
                YColision = false;
            }
            if((MinMaxA[i].Min.Z <= MinMaxB[j].Min.Z && MinMaxA[i].Max.Z >= MinMaxB[j].Max.Z) || (MinMaxA[i].Min.Z >= MinMaxB[j].Min.Z && MinMaxA[i].Max.Z <= MinMaxB[j].Max.Z)){
                ZColision = true;
            } else {
                ZColision = false;
            }

            if(XColision && ZColision && YColision){
                isColision = true;
                IndexIntersectA = i;
                IntexIntersectB = j;
                break;
            }
        }

        if(isColision){
            break;
        }
    }

    /*char TestChar = 'A';

    switch(TestChar){
            case 'B':
                std::cout << "B" << std::endl;
                break;
            case 'A':
                std::cout << "A" << std::endl;
                break;
    }*/

    Temp.IsColision = isColision;
    if(isColision){
        Temp.MovmentDirectionA = ObjectA[IndexIntersectA].PlaneNorm;
        Temp.MovmentDirectionB = ObjectB[IntexIntersectB].PlaneNorm;
    } else {
        Temp.MovmentDirectionA.X = 0.0f;
        Temp.MovmentDirectionA.Y = 0.0f;
        Temp.MovmentDirectionA.Z = 0.0f;

        Temp.MovmentDirectionB.X = 0.0f;
        Temp.MovmentDirectionB.Y = 0.0f;
        Temp.MovmentDirectionB.Z = 0.0f;
    }

    Temp.Force = 0.0f; // This should be a dynamicly calculated thing maybe 1 for each object

    //std::cout << IndexIntersectA << " | " << IntexIntersectB << std::endl;
    //std::cout << MinMaxA[IndexIntersectA].Min.X << " | " << MinMaxA[IndexIntersectA].Max.X << std::endl;
    //std::cout << MinMaxB[IntexIntersectB].Min.X << " | " << MinMaxB[IntexIntersectB].Max.X << std::endl;

    //std::cout << ObjectA[IndexIntersectA].PosA.X + ObjectAPos.X << std::endl;


    return Temp;
}

ForceDirection SimplePhysics::MakeForceDirection(PhysicsPoint ObjectA, PhysicsPoint ObjectB){
    ForceDirection Output;
    float Length;
    Output.X = ObjectB.X - ObjectA.X;
    Output.Y = ObjectB.Y - ObjectA.Y;
    Output.Z = ObjectB.Z - ObjectA.Z;

    Length = std::sqrt(Output.X * Output.X + Output.Y * Output.Y + Output.Z * Output.Z);

    if(Length != 0.){
        Output.X /= Length;
        Output.Y /= Length;
        Output.Z /= Length;
    }

    return Output;
}

ForceDirection SimplePhysics::NormalizeVectorOfForceDirection(std::vector<ForceDirection> VectorOfForces){
    ForceDirection Output;
    int VectorSize = VectorOfForces.size();
    float Temp;
    Output.X = 0.0f;
    Output.Y = 0.0f;
    Output.Z = 0.0f;

    if(!VectorSize == 0){
        for(int i = 0; i < VectorSize; i ++){
            Output.X += VectorOfForces[i].X;
            Output.Y += VectorOfForces[i].Y;
            Output.Z += VectorOfForces[i].Z;
        }

        Temp = std::sqrt(Output.X * Output.X + Output.Y * Output.Y + Output.Z * Output.Z);
        
        if(Temp != 0.){
            Output.X /= Temp;
            Output.Y /= Temp;
            Output.Z /= Temp;
        }

    }


    return Output;
}