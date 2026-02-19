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

    for (EnemyProjectile* p : m_projectiles) delete p;
    m_projectiles.clear();
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

int EnemyManager::Update(float dt, Player& player, sf::Vector2f worldBounds, const std::vector<Obstacle>& obstacles, CollisionManager& collisionMgr)
{
    int pointsGagnesCeTour = 0;
    collisionMgr.clear();

    collisionMgr.addHurtbox(&player.hurtbox);
    if (player.hitbox.isActive) collisionMgr.addHitbox(&player.hitbox);
    if (player.hitbox2.isActive) collisionMgr.addHitbox(&player.hitbox2);

    auto itTank = m_tanks.begin();
    while (itTank != m_tanks.end())
    {
        Tank* t = *itTank;
        if (t->IsDead()) {
            pointsGagnesCeTour += 30;
            delete t;
            itTank = m_tanks.erase(itTank);
            continue;
        }

        t->context.deltaTime = dt;
        t->context.playerPos = player.getPosition();
        t->context.worldBounds = worldBounds;
        t->Update(dt);

        collisionMgr.CheckMapCollisions(t->getSprite(), obstacles);
        keepInsideMap(t, worldBounds);

        collisionMgr.addHurtbox(&t->hurtbox);
        if (t->hitbox.isActive) collisionMgr.addHitbox(&t->hitbox);

        ++itTank;
    }

    auto itBerserker = m_berserkers.begin();
    while (itBerserker != m_berserkers.end())
    {
        Berserker* b = *itBerserker;
        if (b->IsDead()) {
            pointsGagnesCeTour += 10;
            delete b;
            itBerserker = m_berserkers.erase(itBerserker);
            continue;
        }

        b->context.deltaTime = dt;
        b->context.playerPos = player.getPosition();
        b->context.worldBounds = worldBounds;
        b->Update(dt);

        collisionMgr.CheckMapCollisions(b->getSprite(), obstacles);
        keepInsideMap(b, worldBounds);

        collisionMgr.addHurtbox(&b->hurtbox);
        if (b->hitbox.isActive) collisionMgr.addHitbox(&b->hitbox);

        ++itBerserker;
    }

    auto itSniper = m_snipers.begin();
    while (itSniper != m_snipers.end())
    {
        Sniper* s = *itSniper;
        if (s->IsDead()) {
            pointsGagnesCeTour += 40;
            delete s;
            itSniper = m_snipers.erase(itSniper);
            continue;
        }

        s->context.projectileList = &m_projectiles;
        s->context.deltaTime = dt;
        s->context.playerPos = player.getPosition();
        s->context.worldBounds = worldBounds;
        s->Update(dt);

        collisionMgr.CheckMapCollisions(s->getSprite(), obstacles);
        keepInsideMap(s, worldBounds);

        collisionMgr.addHurtbox(&s->hurtbox);
        ++itSniper;
    }

    auto itProj = m_projectiles.begin();
    while (itProj != m_projectiles.end())
    {
        EnemyProjectile* p = *itProj;
        p->Update(dt);

        sf::Vector2f pos = p->getPosition();
        if (pos.x < 0 || pos.y < 0 || pos.x > worldBounds.x || pos.y > worldBounds.y) {
            p->Destroy();
        }

        if (!p->IsActive()) {
            delete p;
            itProj = m_projectiles.erase(itProj);
        }
        else {
            collisionMgr.addHitbox(&p->hitbox);
            ++itProj;
        }
    }
    collisionMgr.checkCollisions();
    return pointsGagnesCeTour;
}

//test debug collision box ennemy
void EnemyManager::DebugDrawCollisions(sf::RenderWindow& window, CollisionManager& colManager)
{
    for (auto* tank : m_tanks)
    {
        colManager.DebugDrawFeetBox(window, tank->getSprite());
    }

    for (auto* berserker : m_berserkers)
    {
        colManager.DebugDrawFeetBox(window, berserker->getSprite());
    }

    for (auto* sniper : m_snipers)
    {
        colManager.DebugDrawFeetBox(window, sniper->getSprite());
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
        t->Draw(window);
    for (auto* b : m_berserkers)
        b->Draw(window);
    for (auto* s : m_snipers)
        s->Draw(window);
    for (auto* p : m_projectiles)
        p->Draw(window);
}