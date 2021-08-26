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

std::vector<QuadPhysicsBody> SimplePhysics::MakePhysicsBods(std::vector<float>X, std::vector<float>Y, std::vector<float>Z, std::vector<float>NormX, std::vector<float>NormY, std::vector<float>NormZ, std::vector<float>Weights){
    std::vector<QuadPhysicsBody> Output;

    QuadPhysicsBody TempQuad;
    PhysicsPoint PointA;
    PhysicsPoint PointB;
    PhysicsPoint PointC;
    PhysicsPoint PointD;

    for(int i = 0; i < X.size(); i+=4){
        PointA.X = X[i];
        PointA.Y = Y[i];
        PointA.Z = Z[i];
        PointA.Weight = Weights[i];
        PointA.Energy.Direction.X = 0;
        PointA.Energy.Direction.Y = 0;
        PointA.Energy.Direction.Z = 0;
        PointA.Energy.Power = 0.0f;

        PointB.X = X[i+1];
        PointB.Y = Y[i+1];
        PointB.Z = Z[i+1];
        PointB.Weight = Weights[i+1];
        PointB.Energy.Direction.X = 0;
        PointB.Energy.Direction.Y = 0;
        PointB.Energy.Direction.Z = 0;
        PointB.Energy.Power = 0.0f;


        PointC.X = X[i+2];
        PointC.Y = Y[i+2];
        PointC.Z = Z[i+2];
        PointC.Weight = Weights[i+2];
        PointC.Energy.Direction.X = 0;
        PointC.Energy.Direction.Y = 0;
        PointC.Energy.Direction.Z = 0;
        PointC.Energy.Power = 0.0f;


        PointD.X = X[i+3];
        PointD.Y = Y[i+3];
        PointD.Z = Z[i+3];
        PointD.Weight = Weights[i+3];
        PointD.Energy.Direction.X = 0;
        PointD.Energy.Direction.Y = 0;
        PointD.Energy.Direction.Z = 0;
        PointD.Energy.Power = 0.0f;

        TempQuad.PosA = PointA;
        TempQuad.PosB = PointB;
        TempQuad.PosC = PointC;
        TempQuad.PosD = PointD;
        TempQuad.PlaneNorm.X = NormX[i];
        TempQuad.PlaneNorm.Y = NormY[i];
        TempQuad.PlaneNorm.Z = NormZ[i];

        Output.push_back(TempQuad);

    }

    return Output;
}

ColisionInfo SimplePhysics::AABBColision(std::vector<QuadPhysicsBody> ObjectA, ForceDirection ObjectAPos, std::vector<QuadPhysicsBody> ObjectB, ForceDirection ObjectBPos){
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


    for(int i = 0; i < ObjectA.size(); i++){

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

        MinMaxA.push_back(TempMinMax);

    }

    for(int i = 0; i < ObjectB.size(); i++){

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

        MinMaxB.push_back(TempMinMax);
    }

    for(int i = 0; i < MinMaxA.size(); i++){
        for(int j = 0; j < MinMaxB.size(); j++){
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

    char TestChar = 'A';

    switch(TestChar){
            case 'B':
                std::cout << "B" << std::endl;
                break;
            case 'A':
                std::cout << "A" << std::endl;
                break;
    }

    Temp.IsColision = isColision;
    if(isColision){
        Temp.MovmentDirectionA = ObjectB[IntexIntersectB].PlaneNorm;
        Temp.MovmentDirectionB = ObjectA[IndexIntersectA].PlaneNorm;
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
