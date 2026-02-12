#include "Player.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"
#include "PlayerAttackState.h"
#include "PlayerDeadState.h"
#include <iostream>

Player::Player() :
    frameWidth(0), frameHeight(0), frameCount(0), speed(300.0f),
    animationSpeed(0.1f), isLooping(false),
    sprite(textureIdle),
    health(100.0f),
    hurtbox({ 35.f, 50.f }, { 0.f, 10.f }),
    hitbox({ 0.f, 0.f }, { 0.f, 0.f }),
    hitbox2({ 0.f, 0.f }, { 0.f, 0.f })
{
    context.player = this;

    hurtbox.isPlayer = true;
    hitbox.isPlayer = true;
    hitbox2.isPlayer = true;

    hurtbox.owner = this;
    hitbox.owner = this;
    hitbox2.owner = this;
    hitbox.isActive = false;
    hitbox2.isActive = false;

    if (!textureIdle.loadFromFile("../Assets/Player/Warrior_Idle.png")) {
        std::cerr << "Erreur : Impossible de charger Warrior_Idle.png" << std::endl;
    }
    if (!textureRun.loadFromFile("../Assets/Player/Warrior_Run.png")) {
        std::cerr << "Erreur : Impossible de charger Warrior_Run.png" << std::endl;
    }
    if (!textureAttack.loadFromFile("../Assets/Player/Warrior_Attack1.png")) {
        std::cerr << "Erreur : Impossible de charger Warrior_Attack1.png" << std::endl;
    }
    if (!textureDeath.loadFromFile("../Assets/Player/Dust_02.png")) {
        std::cerr << "Erreur : Impossible de charger Dust_02.png" << std::endl;
    }

    sprite.setTexture(textureIdle);
    sprite.setPosition({ 400, 300 });

    auto* idle = fsm.CreateState<PlayerIdleState>();
    auto* move = fsm.CreateState<PlayerMoveState>();
    auto* attack = fsm.CreateState<PlayerAttackState>();
    auto* dead = fsm.CreateState<PlayerDeadState>();

    auto isDead = [](PlayerContext _c) { return _c.player->getHp() <= 0; };
    idle->AddTransition(isDead, dead);
    move->AddTransition(isDead, dead);
    attack->AddTransition(isDead, dead);

    idle->AddTransition([](PlayerContext _c) { return _c.isAttackPressed; }, attack);
    idle->AddTransition([](PlayerContext _c) { return (_c.moveInputX != 0 || _c.moveInputY != 0); }, move);

    move->AddTransition([](PlayerContext _c) { return _c.isAttackPressed; }, attack);
    move->AddTransition([](PlayerContext _c) { return (_c.moveInputX == 0 && _c.moveInputY == 0); }, idle);

    attack->AddTransition([attack](PlayerContext _c) {
        return attack->IsFinished() && (_c.moveInputX == 0 && _c.moveInputY == 0);
        }, idle);
    attack->AddTransition([attack](PlayerContext _c) {
        return attack->IsFinished() && (_c.moveInputX != 0 || _c.moveInputY != 0);
        }, move);

    fsm.Init(idle, context);
}


void Player::setAnimation(const sf::Texture& tex, int w, int h, int count, float speed, bool loop, int row)
{
    sprite.setTexture(tex);
    frameWidth = w / count;
    frameHeight = h;
    frameCount = count;
    animationSpeed = speed;
    isLooping = loop;
    currentFrame = 0;
    animationTimer = 0.f;

    currentRect.size = { frameWidth, frameHeight };
    currentRect.position = { 0, row * h };
    sprite.setTextureRect(currentRect);
    sprite.setOrigin({ frameWidth / 2.f, h / 2.f });
}

void Player::Update(sf::RenderWindow& window, float _dt, sf::Vector2f worldBounds)
{
    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();

    float distOriginToLeft = pos.x - bounds.position.x;
    float distOriginToTop = pos.y - bounds.position.y;

    float distOriginToRight = bounds.size.x - distOriginToLeft;
    float distOriginToBottom = bounds.size.y - distOriginToTop;

    if (pos.x < distOriginToLeft) {
        pos.x = distOriginToLeft;
    }
    else if (pos.x > worldBounds.x - distOriginToRight) {
        pos.x = worldBounds.x - distOriginToRight;
    }

    if (pos.y < distOriginToTop) {
        pos.y = distOriginToTop;
    }
    else if (pos.y > worldBounds.y - distOriginToBottom) {
        pos.y = worldBounds.y - distOriginToBottom;
    }

    sprite.setPosition(pos);

    context.deltaTime = _dt;
    context.moveInputX = 0;
    context.moveInputY = 0;
    context.isAttackPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) context.moveInputY += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) context.moveInputY -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) context.moveInputX -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) context.moveInputX += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) handleDamage(10.0f);

    if (context.moveInputX != 0) sprite.setScale({ (float)context.moveInputX, 1.f });

    fsm.Update(context);

    if (frameCount > 0) {
        animationTimer += _dt;
        if (animationTimer >= animationSpeed) {
            animationTimer = 0.f;
            currentFrame++;
            if (currentFrame >= frameCount) {
                currentFrame = isLooping ? 0 : frameCount - 1;
            }
            currentRect.position.x = currentFrame * frameWidth;
            sprite.setTextureRect(currentRect);
        }
    }

    if (isInvulnerable) {
        invulnTimer -= _dt;
        sprite.setColor(((int)(invulnTimer * 10) % 2 == 0) ? sf::Color::Transparent : sf::Color::White);

        if (invulnTimer <= 0) {
            isInvulnerable = false;
            sprite.setColor(sf::Color::White);
        }
    }

    hurtbox.Update(getPosition(), sprite.getScale().x);
    hitbox.Update(getPosition(), sprite.getScale().x);
    hitbox2.Update(getPosition(), sprite.getScale().x);
}

void Player::handleDamage(float damage)
{
    if (isInvulnerable || health.IsDead()) return;

    health.takeDamage(damage);
    std::cout << "HP: " << health.getHealth() << "/" << health.getMaxHealth() << std::endl;

    if (!health.IsDead()) {
        isInvulnerable = true;
        invulnTimer = 0.5f;
    }
}
