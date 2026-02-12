#pragma once
#include "SniperData.h"
#include "../Animation-Assets/AssetPath.h"

class SniperDatabase {
public:
    static SniperData GetData(SniperSkin skin) {
        SniperData data;

        data.moveSpeed = 100.f;
        data.health = 100;

        switch (skin) {
        case SniperSkin::GNOLL:
            data.idle.texturePath = AssetPaths::Sniper::Gnoll::IDLE;
            data.idle.frameSize = { 192, 192 };
            data.idle.frameCount = 6;
            data.idle.speed = 0.2f;

            data.walk.texturePath = AssetPaths::Sniper::Gnoll::WALK;
            data.walk.frameSize = { 192, 192 };
            data.walk.frameCount = 8;
            data.walk.speed = 0.15f;

            data.attack.texturePath = AssetPaths::Sniper::Gnoll::ATTACK;
            data.attack.frameSize = { 192, 192 };
            data.attack.frameCount = 8;
            data.attack.speed = 0.15f;

            data.weapon.texturePath = AssetPaths::Sniper::Gnoll::WEAPON;
            data.weapon.frameSize = { 64, 64 };
            data.weapon.frameCount = 4;
            data.weapon.speed = 0.15f;

            data.scale = { 0.7f, 0.7f };
            data.moveSpeed = 80.f;

            data.hurtboxSize = { 42.f, 65.f };
            data.hurtboxOffset = { 0.f, 0.f };

            data.projectileHitboxSize = { 38.4f, 38.4f };  // 64 * 0.6
            data.projectileHitboxOffset = { 0.f, 0.f };
            data.projectileSpeed = 400.0f;
            data.projectileDamage = 12.0f;
            break;

        case SniperSkin::HARPOONFISH:
            data.idle.texturePath = AssetPaths::Sniper::HarpoonFish::IDLE;
            data.idle.frameSize = { 192, 192 };
            data.idle.frameCount = 8;
            data.idle.speed = 0.2f;

            data.walk.texturePath = AssetPaths::Sniper::HarpoonFish::WALK;
            data.walk.frameSize = { 192, 192 };
            data.walk.frameCount = 6;
            data.walk.speed = 0.15f;

            data.attack.texturePath = AssetPaths::Sniper::HarpoonFish::ATTACK;
            data.attack.frameSize = { 192, 192 };
            data.attack.frameCount = 8;
            data.attack.speed = 0.15f;

            data.weapon.texturePath = AssetPaths::Sniper::HarpoonFish::WEAPON;
            data.weapon.frameSize = { 92, 92 };
            data.weapon.frameCount = 1;
            data.weapon.speed = 0.15f;

            data.scale = { 0.7f, 0.7f };
            data.moveSpeed = 80.f;

            data.hurtboxSize = { 50.f, 60.f };
            data.hurtboxOffset = { 0.f, 0.f };

            data.projectileHitboxSize = { 72.f, 30.6f };
            data.projectileHitboxOffset = { 0.f, 0.f };
            data.projectileSpeed = 300.0f;
            data.projectileDamage = 15.0f;
            break;

        case SniperSkin::SHAMAN:
            data.idle.texturePath = AssetPaths::Sniper::Shaman::IDLE;
            data.idle.frameSize = { 192, 192 };
            data.idle.frameCount = 8;
            data.idle.speed = 0.2f;

            data.walk.texturePath = AssetPaths::Sniper::Shaman::WALK;
            data.walk.frameSize = { 192, 192 };
            data.walk.frameCount = 4;
            data.walk.speed = 0.15f;

            data.attack.texturePath = AssetPaths::Sniper::Shaman::ATTACK;
            data.attack.frameSize = { 192, 192 };
            data.attack.frameCount = 10;
            data.attack.speed = 0.15f;

            data.weapon.texturePath = AssetPaths::Sniper::Shaman::WEAPON;
            data.weapon.frameSize = { 128, 128 };
            data.weapon.frameCount = 3;
            data.weapon.speed = 0.15f;

            data.scale = { 0.7f, 0.7f };
            data.moveSpeed = 80.f;

            data.hurtboxSize = { 45.f, 68.f };
            data.hurtboxOffset = { 0.f, 0.f };

            data.projectileHitboxSize = { 30.f, 30.f };
            data.projectileHitboxOffset = { 0.f, 0.f };
            data.projectileSpeed = 250.0f;
            data.projectileDamage = 25.0f;
            break;
        }
        return data;
    }
};