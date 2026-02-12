# Arene Survivor

Ce projet est un jeu de tir en vue de dessus réalisé avec C++ et SFML 3.0.2.

## Compilation et Exécution

1. **Exporter le projet:**
   * `git clone https://github.com/Alice2406/Arene-2D.git`
    
2.  **Ouvrir le projet :**
    * Lancez la solution `.sln` avec Visual Studio (17+).

3.  **Configuration :**
    * Sélectionnez la configuration **Debug** ou **Release**.
    * Assurez-vous que la plateforme est réglée sur **x64**.

4.  **Compilation :**
    * Générez la solution (`Ctrl + Shift + B`).
  
5.  **Execution :**
    * Executez le programme (`Ctlr + F5`)
  
      
## Contrôles

* **Z / Q / S / D** : Déplacements
* **Espace** : Attaquer
* **Echap** : Retour Menu


## FSM (NPC)

```mermaid
stateDiagram-v2
    direction TB

    state "Logique Berserker" as Berserker {
        [*] --> B_Patrol
        B_Patrol --> B_Chase : Joueur détecté (Distance < 400px)
        B_Chase --> B_Attack : À portée de contact (Distance < 50px)
        B_Attack --> B_Chase : Joueur s'éloigne
        B_Chase --> B_Patrol : Joueur perdu de vue
    }

    state "Logique Sniper" as Sniper {
        [*] --> S_Patrol
        S_Patrol --> S_Aim : Joueur détecté
        S_Aim --> S_Shoot : Cible verrouillée (après 1.5s)
        S_Shoot --> S_Flee : Joueur trop proche (Distance < 200px)
        S_Flee --> S_Aim : Distance de sécurité rétablie
        S_Aim --> S_Patrol : Joueur perdu
    }

      state "Logique Tank" as Tank {
       [*] --> T_Patrol
    
    T_Patrol --> T_Chase : Joueur détecté (< 400px)
    T_Chase --> T_Patrol : Joueur loin (> 400px)

    %% Mécanique de Tir (marche aussi depuis Patrol !)
    T_Patrol --> T_Guard : Tir reçu (triggerGuard)
    T_Chase --> T_Guard : Tir reçu (triggerGuard)
    
    state "Logique de Combat" as Combat {
        T_Guard --> T_Chase : Timer fini (1.0s)
        
        T_Chase --> T_Attack : Contact (< 30px)
        T_Attack --> T_Chase : Fin Attaque
    }
    }


```
