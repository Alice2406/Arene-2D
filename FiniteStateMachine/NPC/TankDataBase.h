#pragma once
#include "TankData.h"
#include "../Animation-Assets/AssetPath.h"

class TankDatabase {
public:
    static TankData GetData(TankSkin skin);
};