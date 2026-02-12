#pragma once

template <typename T>
void EnemyManager::keepInsideMap(T& enemy, sf::Vector2f worldBounds)
{
    sf::Vector2f pos = enemy->getPosition();
    sf::FloatRect bounds = enemy->GetGlobalBounds();

    float originOffsetX = pos.x - bounds.position.x;
    float originOffsetY = pos.y - bounds.position.y;

    float width = bounds.size.x;
    float height = bounds.size.y;

    if (pos.x < originOffsetX)
        pos.x = originOffsetX;
    else if (pos.x > worldBounds.x - (width - originOffsetX))
        pos.x = worldBounds.x - (width - originOffsetX);

    if (pos.y < originOffsetY)
        pos.y = originOffsetY;
    else if (pos.y > worldBounds.y - (height - originOffsetY))
        pos.y = worldBounds.y - (height - originOffsetY);

    enemy->setPosition(pos);
}