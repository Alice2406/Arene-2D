#include "EnemyManager.h"
#include "../PlayerStates/Player.h"

EnemyManager::~EnemyManager()
{
    for (Tank* t : m_tanks) delete t;
    m_tanks.clear();

    for (Berserker* b : m_berserkers) delete b;
    m_berserkers.clear();

    for (Sniper* s : m_snipers) delete s;
    m_snipers.clear();
}

void EnemyManager::SpawnTank(TankSkin skin, sf::Vector2f position)
{
    Tank* newTank = new Tank(skin);
    newTank->setPosition(position);
    newTank->Init();
    m_tanks.push_back(newTank);
}

void EnemyManager::SpawnBerserker(BerserkerSkin skin, sf::Vector2f position)
{
    Berserker* newBerserker = new Berserker(skin);
    newBerserker->setPosition(position);
    newBerserker->Init();
    m_berserkers.push_back(newBerserker);
}

void EnemyManager::SpawnSniper(SniperSkin skin, sf::Vector2f position)
{
    Sniper* newSniper = new Sniper(skin);
    newSniper->setPosition(position);
    newSniper->Init();
    m_snipers.push_back(newSniper);
}

void EnemyManager::Update(float dt, Player& player, sf::Vector2f worldBounds)
{
    auto itTank = m_tanks.begin();
    while (itTank != m_tanks.end())
    {
        Tank* t = *itTank;

        t->context.deltaTime = dt;
        t->context.playerPos = player.getPosition();

        t->Update(dt);

        keepInsideMap(t, worldBounds);

        sf::FloatRect enemyBounds = t->GetGlobalBounds();
        if (player.CheckHit(enemyBounds) && !t->IsHit())
        {
            t->TakeDamage(25);
        }

        if (t->IsDead())
        {
            delete t;
            itTank = m_tanks.erase(itTank);
        }
        else
        {
            ++itTank;
        }
    }

    auto itBerserker = m_berserkers.begin();
    while (itBerserker != m_berserkers.end())
    {
        Berserker* b = *itBerserker;

        b->context.deltaTime = dt;
        b->context.playerPos = player.getPosition();

        b->Update(dt);

        keepInsideMap(b, worldBounds);

        sf::FloatRect enemyBounds = b->GetGlobalBounds();
        if (player.CheckHit(enemyBounds) && !b->IsHit())
        {
            b->TakeDamage(20);
        }

        if (b->IsDead())
        {
            delete b;
            itBerserker = m_berserkers.erase(itBerserker);
        }
        else
        {
            ++itBerserker;
        }
    }

    auto itSniper = m_snipers.begin();
    while (itSniper != m_snipers.end())
    {
        Sniper* s = *itSniper;

        s->context.projectileList = &m_projectiles;
        s->context.deltaTime = dt;
        s->context.playerPos = player.getPosition();

        s->Update(dt);

        keepInsideMap(s, worldBounds);

        sf::FloatRect enemyBounds = s->GetGlobalBounds();
        if (player.CheckHit(enemyBounds) && !s->IsHit())
        {
            s->TakeDamage(35);
        }

        if (s->IsDead())
        {
            delete s;
            itSniper = m_snipers.erase(itSniper);
        }
        else
        {
            ++itSniper;
        }
    }

    auto itProj = m_projectiles.begin();
    while (itProj != m_projectiles.end())
    {
        EnemyProjectile* p = *itProj;

        p->Update(dt);

        if (player.CheckHit(p->GetGlobalBounds()))
        {
            p->Destroy();
        }

        sf::Vector2f pos = p->getPosition();
        if (pos.x < 0 || pos.y < 0 || pos.x > worldBounds.x || pos.y > worldBounds.y)
        {
            p->Destroy();
        }

        if (!p->IsActive())
        {
            delete p;
            itProj = m_projectiles.erase(itProj);
        }
        else
        {
            ++itProj;
        }
    }
}
void EnemyManager::Draw(sf::RenderWindow& window)
{
    for (Tank* t : m_tanks)
    {
        t->Draw(window);
    }

    for (auto* b : m_berserkers)
    {
        b->Draw(window);
    }
    for (auto* s : m_snipers)
    {
        s->Draw(window);
    }
    for (auto* p : m_projectiles)
    {
        p->Draw(window);
    }
}