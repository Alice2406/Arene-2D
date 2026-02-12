#include "BerserkerDataBase.h"

BerserkerData BerserkerDatabase::GetData(BerserkerSkin skin) {
    BerserkerData data;

    data.moveSpeed = 100.f;
    data.health = 100;

    switch (skin) {
    case BerserkerSkin::BEAR:
        data.idle.texturePath = AssetPaths::Berserker::Bear::IDLE;
        data.idle.frameSize = { 256, 256 };
        data.idle.frameCount = 8;
        data.idle.speed = 0.2f;

        data.walk.texturePath = AssetPaths::Berserker::Bear::WALK;
        data.walk.frameSize = { 256, 256 };
        data.walk.frameCount = 5;
        data.walk.speed = 0.15f;

        data.attack.texturePath = AssetPaths::Berserker::Bear::ATTACK;
        data.attack.frameSize = { 256, 256 };
        data.attack.frameCount = 9;
        data.attack.speed = 0.15f;

        data.scale = { 0.7f, 0.7f };
        data.moveSpeed = 80.f;

        data.hurtboxSize = { 65.f, 85.f };
        data.hurtboxOffset = { 0.f, 0.f };

        data.hitboxSize = { 70.f, 60.f };
        data.hitboxOffset = { 50.f, 0.f };
        data.attackDamage = 20.0f;
        break;

    case BerserkerSkin::GNOME:
        data.idle.texturePath = AssetPaths::Berserker::Gnome::IDLE;
        data.idle.frameSize = { 192, 192 };
        data.idle.frameCount = 8;
        data.idle.speed = 0.2f;

        data.walk.texturePath = AssetPaths::Berserker::Gnome::WALK;
        data.walk.frameSize = { 192, 192 };
        data.walk.frameCount = 6;
        data.walk.speed = 0.15f;

        data.attack.texturePath = AssetPaths::Berserker::Gnome::ATTACK;
        data.attack.frameSize = { 192, 192 };
        data.attack.frameCount = 7;
        data.attack.speed = 0.15f;

        data.scale = { 0.7f, 0.7f };
        data.moveSpeed = 80.f;

        data.hurtboxSize = { 48.f, 65.f };
        data.hurtboxOffset = { 0.f, 0.f };

        data.hitboxSize = { 80.f, 70.f };
        data.hitboxOffset = { 55.f, 0.f };
        data.attackDamage = 25.0f;
        break;

    case BerserkerSkin::LANCER:
        data.idle.texturePath = AssetPaths::Berserker::Lancer::IDLE;
        data.idle.frameSize = { 256, 256 };
        data.idle.frameCount = 7;
        data.idle.speed = 0.2f;

        data.walk.texturePath = AssetPaths::Berserker::Lancer::WALK;
        data.walk.frameSize = { 256, 256 };
        data.walk.frameCount = 6;
        data.walk.speed = 0.15f;

        data.attack.texturePath = AssetPaths::Berserker::Lancer::ATTACK;
        data.attack.frameSize = { 256, 256 };
        data.attack.frameCount = 8;
        data.attack.speed = 0.15f;

        data.scale = { 0.7f, 0.7f };
        data.moveSpeed = 80.f;

        data.hurtboxSize = { 60.f, 90.f };
        data.hurtboxOffset = { 0.f, 0.f };

        data.hitboxSize = { 90.f, 60.f };
        data.hitboxOffset = { 60.f, 0.f };
        data.hitbox2Size = { 90.f, 60.f };
        data.hitbox2Offset = { -60.f, 0.f };
        data.attackDamage = 30.0f;
        break;

    case BerserkerSkin::PADDLEFISH:
        data.idle.texturePath = AssetPaths::Berserker::PaddleFish::IDLE;
        data.idle.frameSize = { 192, 192 };
        data.idle.frameCount = 8;
        data.idle.speed = 0.2f;

        data.walk.texturePath = AssetPaths::Berserker::PaddleFish::WALK;
        data.walk.frameSize = { 192, 192 };
        data.walk.frameCount = 6;
        data.walk.speed = 0.15f;

        data.attack.texturePath = AssetPaths::Berserker::PaddleFish::ATTACK;
        data.attack.frameSize = { 192, 192 };
        data.attack.frameCount = 6;
        data.attack.speed = 0.15f;

        data.scale = { 0.7f, 0.7f };
        data.moveSpeed = 80.f;

        data.hurtboxSize = { 50.f, 70.f };
        data.hurtboxOffset = { 0.f, 0.f };

        data.hitboxSize = { 65.f, 55.f };
        data.hitboxOffset = { 45.f, 0.f };
        data.attackDamage = 22.0f;
        break;

    case BerserkerSkin::THIEF:
        data.idle.texturePath = AssetPaths::Berserker::Thief::IDLE;
        data.idle.frameSize = { 192, 192 };
        data.idle.frameCount = 6;
        data.idle.speed = 0.2f;

        data.walk.texturePath = AssetPaths::Berserker::Thief::WALK;
        data.walk.frameSize = { 192, 192 };
        data.walk.frameCount = 6;
        data.walk.speed = 0.15f;

        data.attack.texturePath = AssetPaths::Berserker::Thief::ATTACK;
        data.attack.frameSize = { 192, 192 };
        data.attack.frameCount = 6;
        data.attack.speed = 0.15f;

        data.scale = { 0.7f, 0.7f };
        data.moveSpeed = 80.f;

        data.hurtboxSize = { 45.f, 68.f };
        data.hurtboxOffset = { 0.f, 0.f };

        data.hitboxSize = { 50.f, 45.f };
        data.hitboxOffset = { 40.f, 0.f };
        data.attackDamage = 15.0f;
        break;

    case BerserkerSkin::TROLL:
        data.idle.texturePath = AssetPaths::Berserker::Troll::IDLE;
        data.idle.frameSize = { 384, 384 };
        data.idle.frameCount = 12;
        data.idle.speed = 0.2f;

        data.walk.texturePath = AssetPaths::Berserker::Troll::WALK;
        data.walk.frameSize = { 384, 384 };
        data.walk.frameCount = 10;
        data.walk.speed = 0.15f;

        data.attack.texturePath = AssetPaths::Berserker::Troll::ATTACK;
        data.attack.frameSize = { 384, 384 };
        data.attack.frameCount = 6;
        data.attack.speed = 0.15f;

        data.scale = { 0.7f, 0.7f };
        data.moveSpeed = 80.f;

        data.hurtboxSize = { 100.f, 130.f };
        data.hurtboxOffset = { 0.f, -10.f };

        data.hitboxSize = { 110.f, 100.f };
        data.hitboxOffset = { 80.f, 0.f };
        data.attackDamage = 35.0f;
        break;
    }
    return data;
}