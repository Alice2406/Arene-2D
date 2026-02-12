# Documentation du Projet : Arene Survivor

**Auteurs :** UWINEZA Job et NIEZGODZKI Alice

**Langage :** C++ / SFML 3.0.2

---

## 1. Concept

### Pitch
Le joueur incarne un chevalier solitaire piégé dans une zone hostile. L'objectif est de survivre le plus longtemps possible face à des vagues infinies d'ennemis de plus en plus nombreuses.

### Règles du Jeu
* **Survie :** Le joueur possède une barre de vie. Si elle tombe à 0, la partie est terminée (Game Over).
* **Vagues :** Les ennemis apparaissent par vagues successives. Une nouvelle vague plus intense commence lorsque la précédente est éliminée.
* **Score :** Chaque ennemi éliminé rapporte des points. Le but est d'atteindre le meilleur score possible.
* **Contrôles :**
    * **Déplacement :** Clavier (ZQSD ou Flèches).
    * **Tir :** Espace.
    * **Pause/Quitter :** Échap.

---

## 2. Fonctionnalités Réalisées

### Moteur & Core
* **Game Loop :** Gestion du temps (`DeltaTime`) pour assurer la fluidité du jeu.
* **Gestionnaire de Scènes :** Système permettant de passer du Menu au Jeu, puis à l'écran de Game Over sans redémarrer le programme.
* **Resource Manager :** Chargement unique des textures pour optimiser la mémoire.

### Gameplay
* **Système de Vagues :** Algorithme augmentant le nombre d'ennemis à chaque manche (`EnemyManager`).
* **Ennemis variés  :**
    * **Tank :** Lent, beaucoup de PV, suit le joueur.
    * **Berserker :** Rapide, fonce au contact, dégâts élevés.
    * **Sniper :** Reste à distance, tire des projectiles.
* **Collision Manager :** Gestion des collisions AABB (Hitbox vs Hurtbox) et collisions avec les obstacles de la carte.
* **Caméra :** Suivi fluide du joueur centré à l'écran.
* **Limites du monde :** Les entités ne peuvent pas sortir de la zone de jeu (`keepInsideMap`).

### Visuel & UI
* **Animation :** Système d'animation par Spritesheet (`Animator`) gérant les états Idle, Walk, Attack.
* **Feedback Visuel :** Clignotement rouge des ennemis lorsqu'ils subissent des dégâts.
* **Interface (HUD) :** Affichage du score en temps réel et écran de fin avec score final.

---

## 3. Fonctionnalités Non Réalisées

Faute de temps ou par choix de priorisation, certaines fonctionnalités n'ont pas été implémentées (un projet de deux semaines c'est trop court...):

* **Son et Musique :**
    * *Pourquoi ?* La priorité a été mise sur la stabilité du gameplay. L'audio a été considéré comme un bonus.
* **Pathfinding complexe :**
    * *Pourquoi ?* Les ennemis se déplacent actuellement en ligne droite vers le joueur. L’implémentation d’un algorithme pour contourner les obstacles aurait été très longue à implémenter.
* **Système de Sauvegarde (High Score) :**
    * *Pourquoi ?* Le score est réinitialisé à chaque lancement. La persistance des données n'était pas dans le scope principal du cours.
* **Troupe Gentille :**
    * *Pourquoi ?*C’était dans le thème du cours, mais il fallait implémenter beaucoup de code et, par manque de temps, on a abandonné l’idée.

---

## 4. Schéma de la FSM (Machine à États Finis)

Voici le diagramme représentant les NPC dans le (`README.md`).

---

## 5. Liste des Assets Externes

Les ressources graphiques utilisées proviennent de banques d'images libres de droits.

* **Graphismes (Tiny Swords) :**
    * *Auteur :* Pixel Frog
    * *Lien :* [https://pixelfrog-assets.itch.io/tiny-swords]
    * *Utilisation :* Sprites du joueur, des ennemis (Tanks, Soldats), map, menu et obstacles.
* **Police d'écriture :**
    * *Nom :* Ancient Medium
    * *Source :* Dafont
