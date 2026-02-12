#pragma once
#include "TankData.h"
#include "../Animation-Assets/AssetPath.h"

class TankDatabase {
public:
    static TankData GetData(TankSkin skin) {
        TankData data;

        data.moveSpeed = 100.f;
        data.health = 100;

        switch (skin) {
        case TankSkin::TURTLE:
            data.idle.texturePath = AssetPaths::Tank::Turtle::IDLE;
            data.idle.frameSize = { 320, 320 };
            data.idle.frameCount = 10;
            data.idle.speed = 0.2f;

            data.walk.texturePath = AssetPaths::Tank::Turtle::WALK;
            data.walk.frameSize = { 320, 320 };
            data.walk.frameCount = 7;
            data.walk.speed = 0.15f;

            data.attack.texturePath = AssetPaths::Tank::Turtle::ATTACK;
            data.attack.frameSize = { 320, 320 };
            data.attack.frameCount = 10;
            data.attack.speed = 0.15f;

            data.guard.texturePath = AssetPaths::Tank::Turtle::GUARD;
            data.guard.frameSize = { 320, 320 };
            data.guard.frameCount = 6;
            data.guard.speed = 0.15f;

            data.scale = { 0.7f, 0.7f };
            data.moveSpeed = 80.f;

            data.hurtboxSize = { 80.f, 100.f };
            data.hurtboxOffset = { 0.f, 0.f };

            // ✅ HITBOX D'ATTAQUE - Turtle (marteau)
            data.hitboxSize = { 100.f, 70.f };
            data.hitboxOffset = { 70.f, 0.f };
            data.attackDamage = 30.0f;
            break;

        case TankSkin::PANDA:
            data.idle.texturePath = AssetPaths::Tank::Panda::IDLE;
            data.idle.frameSize = { 256, 256 };
            data.idle.frameCount = 10;
            data.idle.speed = 0.2f;

            data.walk.texturePath = AssetPaths::Tank::Panda::WALK;
            data.walk.frameSize = { 256, 256 };
            data.walk.frameCount = 6;
            data.walk.speed = 0.15f;

            data.attack.texturePath = AssetPaths::Tank::Panda::ATTACK;
            data.attack.frameSize = { 256, 256 };
            data.attack.frameCount = 13;
            data.attack.speed = 0.15f;

            data.guard.texturePath = AssetPaths::Tank::Panda::GUARD;
            data.guard.frameSize = { 256, 256 };
            data.guard.frameCount = 8;
            data.guard.speed = 0.15f;

            data.scale = { 0.7f, 0.7f };
            data.moveSpeed = 120.f;

            data.hurtboxSize = { 65.f, 85.f };
            data.hurtboxOffset = { 0.f, 0.f };

            // ✅ HITBOX D'ATTAQUE - Panda (spin 360°) - DEUX HITBOX
            data.hitboxSize = { 90.f, 65.f };
            data.hitboxOffset = { 65.f, 0.f };
            data.hitbox2Size = { 90.f, 65.f };
            data.hitbox2Offset = { -65.f, 0.f };
            data.attackDamage = 35.0f;
            break;

        case TankSkin::MINOTAUR:
            data.idle.texturePath = AssetPaths::Tank::Minotaur::IDLE;
            data.idle.frameSize = { 320, 320 };
            data.idle.frameCount = 16;
            data.idle.speed = 0.2f;

            data.walk.texturePath = AssetPaths::Tank::Minotaur::WALK;
            data.walk.frameSize = { 320, 320 };
            data.walk.frameCount = 8;
            data.walk.speed = 0.15f;

            data.attack.texturePath = AssetPaths::Tank::Minotaur::ATTACK;
            data.attack.frameSize = { 320, 320 };
            data.attack.frameCount = 12;
            data.attack.speed = 0.15f;

            data.guard.texturePath = AssetPaths::Tank::Minotaur::GUARD;
            data.guard.frameSize = { 320, 320 };
            data.guard.frameCount = 11;
            data.guard.speed = 0.15f;

            data.scale = { 0.7f, 0.7f };
            data.moveSpeed = 120.f;

            data.hurtboxSize = { 85.f, 110.f };
            data.hurtboxOffset = { 0.f, -5.f };

            // ✅ HITBOX D'ATTAQUE - Minotaur (massue)
            data.hitboxSize = { 95.f, 80.f };
            data.hitboxOffset = { 65.f, 0.f };
            data.attackDamage = 32.0f;
            break;

        case TankSkin::SKULL:
            data.idle.texturePath = AssetPaths::Tank::Skull::IDLE;
            data.idle.frameSize = { 192, 192 };
            data.idle.frameCount = 8;
            data.idle.speed = 0.2f;

            data.walk.texturePath = AssetPaths::Tank::Skull::WALK;
            data.walk.frameSize = { 192, 192 };
            data.walk.frameCount = 6;
            data.walk.speed = 0.15f;

            data.attack.texturePath = AssetPaths::Tank::Skull::ATTACK;
            data.attack.frameSize = { 192, 192 };
            data.attack.frameCount = 7;
            data.attack.speed = 0.15f;

            data.guard.texturePath = AssetPaths::Tank::Skull::GUARD;
            data.guard.frameSize = { 192, 192 };
            data.guard.frameCount = 7;
            data.guard.speed = 0.15f;

            data.scale = { 0.7f, 0.7f };
            data.moveSpeed = 120.f;

            data.hurtboxSize = { 50.f, 70.f };
            data.hurtboxOffset = { 0.f, 5.f };

            // ✅ HITBOX D'ATTAQUE - Skull (dague)
            data.hitboxSize = { 55.f, 50.f };
            data.hitboxOffset = { 45.f, 0.f };
            data.attackDamage = 28.0f;
            break;
        }
        return data;
    }
};