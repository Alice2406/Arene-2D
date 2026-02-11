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

void EnemyManager::SpawnTank(TankSkin skin, sf::Vector2f position, sf::Vector2f mapSize)
{
    std::string path;
    switch (skin) {
    case TankSkin::TURTLE: path = AssetPaths::Tank::Turtle::WALK; break;
    case TankSkin::PANDA:  path = AssetPaths::Tank::Panda::WALK; break;
    case TankSkin::MINOTAUR:  path = AssetPaths::Tank::Minotaur::WALK; break;
    case TankSkin::SKULL:  path = AssetPaths::Tank::Skull::WALK; break;
    }

    sf::Texture& texture = m_resources.GetTexture(path);

    Tank* newTank = new Tank(skin, texture);
    newTank->context.worldBounds = mapSize;
    newTank->setPosition(position);
    newTank->Init();
    m_tanks.push_back(newTank);
}

void EnemyManager::SpawnBerserker(BerserkerSkin skin, sf::Vector2f position, sf::Vector2f mapSize)
{
    std::string path;
    switch (skin) {
    case BerserkerSkin::BEAR: path = AssetPaths::Berserker::Bear::WALK; break;
    case BerserkerSkin::LANCER:  path = AssetPaths::Berserker::Lancer::WALK; break;
    case BerserkerSkin::PADDLEFISH:  path = AssetPaths::Berserker::PaddleFish::WALK; break;
    case BerserkerSkin::THIEF:  path = AssetPaths::Berserker::Thief::WALK; break;
    case BerserkerSkin::TROLL:  path = AssetPaths::Berserker::Troll::WALK; break;
    case BerserkerSkin::GNOME:  path = AssetPaths::Berserker::Gnome::WALK; break;
    }

    sf::Texture& texture = m_resources.GetTexture(path);

    Berserker* newBerserker = new Berserker(skin, texture);
    newBerserker->context.worldBounds = mapSize;
    newBerserker->setPosition(position);
    newBerserker->Init();
    m_berserkers.push_back(newBerserker);
}

void EnemyManager::SpawnSniper(SniperSkin skin, sf::Vector2f position, sf::Vector2f mapSize)
{
    std::string projectilePath;
    std::string path;

    switch (skin) {
    case SniperSkin::GNOLL: 
        path = AssetPaths::Sniper::Gnoll::WALK; break;
        projectilePath = AssetPaths::Sniper::Gnoll::WEAPON;
        break;
    case SniperSkin::HARPOONFISH:  
        path = AssetPaths::Sniper::HarpoonFish::WALK; break;
        projectilePath = AssetPaths::Sniper::HarpoonFish::WEAPON;
        break;
    case SniperSkin::SHAMAN:  
        path = AssetPaths::Sniper::Shaman::WALK; break;
        projectilePath = AssetPaths::Sniper::Shaman::WEAPON;
        break;
    }

    sf::Texture& texture = m_resources.GetTexture(path);
    sf::Texture& projectileTexture = m_resources.GetTexture(projectilePath);

    Sniper* newSniper = new Sniper(skin, texture);
    newSniper->context.worldBounds = mapSize;
    newSniper->setPosition(position);
    newSniper->SetProjectileTexture(projectileTexture);
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
        t->context.worldBounds = worldBounds;

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
        b->context.worldBounds = worldBounds;
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
        s->context.worldBounds = worldBounds;
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
void EnemyManager::HandleWaves(sf::Vector2f mapSize)
{
    if (m_tanks.empty() && m_berserkers.empty() && m_snipers.empty())
    {
        m_waveNumber++; 
        std::cout << "--- DEBUT VAGUE " << m_waveNumber << " ---" << std::endl;

        int enemyCount = 5 + (m_waveNumber * 2);

        for (int i = 0; i < enemyCount; i++)
        {
            int type = rand() % 3;

            if (type == 0) 
            {
                int skinIdx = rand() % (int)TankSkin::COUNT;
                SpawnTank((TankSkin)skinIdx, { -10.f, -10.f }, mapSize);
            }
            else if (type == 1) 
            {
                int skinIdx = rand() % (int)SniperSkin::COUNT;
                SpawnSniper((SniperSkin)skinIdx, { -10.f, -10.f }, mapSize);
            }
            else 
            {
                int skinIdx = rand() % (int)BerserkerSkin::COUNT;
                SpawnBerserker((BerserkerSkin)skinIdx, { -10.f, -10.f }, mapSize);
            }
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