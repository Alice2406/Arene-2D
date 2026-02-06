#include "CollisionBox.h"

CollisionBox::CollisionBox(sf::Vector2f size, sf::Vector2f _offset) : offset(_offset)
{
	bounds.size = size;

	debugShape.setSize(bounds.size);
	debugShape.setFillColor(sf::Color(255, 0, 0, 100));
	debugShape.setOutlineColor(sf::Color::Red);
	debugShape.setOutlineThickness(1.f);
}

void CollisionBox::Update(sf::Vector2f ownerPos, float scaleX)
{
	if (!isActive && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1)) return;

	bounds.position.x = ownerPos.x + (offset.x * scaleX) - (bounds.size.x / 2.f);
	bounds.position.y = ownerPos.y + offset.y - (bounds.size.y / 2.f);

	debugShape.setSize(bounds.size);
	debugShape.setPosition(bounds.position);
}

void CollisionBox::debugDraw(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1))
	{
		if (isActive) {
			debugShape.setFillColor(sf::Color(255, 0, 0, 100));
			debugShape.setOutlineColor(sf::Color::Red);
		}
		else {
			debugShape.setFillColor(sf::Color::Transparent);
			debugShape.setOutlineColor(sf::Color(100, 100, 100)); // Gris
		}

		window.draw(debugShape);
	}
	
}
