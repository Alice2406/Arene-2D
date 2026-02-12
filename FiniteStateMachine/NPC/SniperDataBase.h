#pragma once
#include "SniperData.h"
#include "../Animation-Assets/AssetPath.h"

class SniperDatabase {
public:
    static SniperData GetData(SniperSkin skin);
};