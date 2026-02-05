#pragma once
#include "NpcContext.h"

namespace NpcAi
{
    class Conditions
    {
    public:
        static bool IsSeeingPlayer(NpcContext context)
        {
            sf::Vector2f npcPos = context.npcShape->getPosition();

            float deltaX = context.playerPos.x - npcPos.x;
            float deltaY = context.playerPos.y - npcPos.y;

            float distance = std::sqrt((deltaX * deltaX) + (deltaY * deltaY));

            return distance < 300.0f;
        }
        static bool IsInAttackRange(NpcContext context)
        {
            sf::Vector2f npcPos = context.npcShape->getPosition();

            float deltaX = context.playerPos.x - npcPos.x;
            float deltaY = context.playerPos.y - npcPos.y;

            float distance = std::sqrt((deltaX * deltaX) + (deltaY * deltaY));

            return distance < 50.0f;
        }
        static bool IsTooClose(NpcContext context)
        {
            sf::Vector2f npcPos = context.npcShape->getPosition();

            float deltaX = context.playerPos.x - npcPos.x;
            float deltaY = context.playerPos.y - npcPos.y;

            float distance = std::sqrt((deltaX * deltaX) + (deltaY * deltaY));

            return distance < 200.0f;
        }
        static bool IsAimingFinished(NpcContext context)
        {
            return context.currentTimer >= 0.5f;
        }
    };
}
