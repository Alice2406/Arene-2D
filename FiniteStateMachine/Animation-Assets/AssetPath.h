#pragma once
#include <string>

namespace AssetPaths
{
    namespace Environment
    {
        static const std::string TILESET_WATER = "..\\Assets\\Terrain\\Tileset\\Water.png";
        static const std::string TILESET_GROUND = "..\\Assets\\Terrain\\Tileset\\map.png";
        static const std::string LEVEL_1_DATA = "..\\Assets\\Levels\\Level1.txt";

        static const std::string ROCK1 = "..\\Assets\\Terrain\\Decorations\\Rocks\\Rock1.png";
        static const std::string ROCK2 = "..\\Assets\\Terrain\\Decorations\\Rocks\\Rock2.png";
        static const std::string ROCK3 = "..\\Assets\\Terrain\\Decorations\\Rocks\\Rock3.png";
        static const std::string ROCK4 = "..\\Assets\\Terrain\\Decorations\\Rocks\\Rock4.png";
        static const std::string TREE = "..\\Assets\\Terrain\\Decorations\\Tree.png";

        static const std::string BUSH1 = "..\\Assets\\Terrain\\Decorations\\Bushes\\Bushe1.png";
        static const std::string BUSH2 = "..\\Assets\\Terrain\\Decorations\\Bushes\\Bushe3.png";
        static const std::string BUSH3 = "..\\Assets\\Terrain\\Decorations\\Bushes\\Bushe4.png";
    }

    namespace Animals
    {
        static const std::string SHEEP_WHITE = "..\\Assets\\Terrain\\Decorations\\Sheep_Grass.png";
        static const std::string SHEEP_BLACK = "..\\Assets\\Terrain\\Decorations\\Sheep_Idle.png";
    }
    namespace Tank
    {
        namespace Turtle
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Tank\\Turtle\\Turtle_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Tank\\Turtle\\Turtle_Walk.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Tank\\Turtle\\Turtle_Attack.png";
            static const std::string GUARD = "..\\Assets\\Enemies\\Tank\\Turtle\\Turtle_Guard_In.png";
        }
        namespace Minotaur
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Tank\\Minotaur\\Minotaur_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Tank\\Minotaur\\Minotaur_Walk.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Tank\\Minotaur\\Minotaur_Attack.png";
            static const std::string GUARD = "..\\Assets\\Enemies\\Tank\\Minotaur\\Minotaur_Guard.png";
        }
        namespace Panda
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Tank\\Panda\\Panda_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Tank\\Panda\\Panda_Run.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Tank\\Panda\\Panda_Attack.png";
            static const std::string GUARD = "..\\Assets\\Enemies\\Tank\\Panda\\Panda_Guard.png";
        }
        namespace Skull
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Tank\\Skull\\Skull_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Tank\\Skull\\Skull_Run.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Tank\\Skull\\Skull_Attack.png";
            static const std::string GUARD = "..\\Assets\\Enemies\\Tank\\Skull\\Skull_Guard.png";
        }
    }
    namespace Sniper
    {
        namespace Gnoll
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Sniper\\Gnoll\\Gnoll_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Sniper\\Gnoll\\Gnoll_Walk.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Sniper\\Gnoll\\Gnoll_Throw.png";
            static const std::string WEAPON = "..\\Assets\\Enemies\\Sniper\\Gnoll\\Gnoll_Bone.png";
        }
        namespace HarpoonFish
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Sniper\\HarpoonFish\\HarpoonFish_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Sniper\\HarpoonFish\\HarpoonFish_Run.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Sniper\\HarpoonFish\\HarpoonFish_Throw.png";
            static const std::string WEAPON = "..\\Assets\\Enemies\\Sniper\\HarpoonFish\\Harpoon.png";
        }
        namespace Shaman
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Sniper\\Shaman\\Shaman_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Sniper\\Shaman\\Shaman_Run.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Sniper\\Shaman\\Shaman_Attack.png";
            static const std::string WEAPON = "..\\Assets\\Enemies\\Sniper\\Shaman\\Shaman_Projectile.png";
        }
    }
    namespace Berserker
    {
        namespace Bear
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Berserker\\Bear\\Bear_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Berserker\\Bear\\Bear_Run.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Berserker\\Bear\\Bear_Attack.png";
        }
        namespace Gnome
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Berserker\\Gnome\\Gnome_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Berserker\\Gnome\\Gnome_Run.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Berserker\\Gnome\\Gnome_Attack.png";
        }
        namespace Lancer
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Berserker\\Lancer\\Lancer_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Berserker\\Lancer\\Lancer_Run.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Berserker\\Lancer\\Lancer_Attack.png";
        }
        namespace PaddleFish
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Berserker\\PaddleFish\\PaddleFish_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Berserker\\PaddleFish\\PaddleFish_Run.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Berserker\\PaddleFish\\PaddleFish_Attack.png";
        }
        namespace Thief
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Berserker\\Thief\\Thief_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Berserker\\Thief\\Thief_Run.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Berserker\\Thief\\Thief_Attack.png";
        }
        namespace Troll
        {
            static const std::string IDLE = "..\\Assets\\Enemies\\Berserker\\Troll\\Troll_Idle.png";
            static const std::string WALK = "..\\Assets\\Enemies\\Berserker\\Troll\\Troll_Walk.png";
            static const std::string ATTACK = "..\\Assets\\Enemies\\Berserker\\Troll\\Troll_Attack.png";
        }
    }
}