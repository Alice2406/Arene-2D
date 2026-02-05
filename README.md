```mermaid
stateDiagram-v2
    direction TB

    state "Logique Berserker" as Berserker {
        [*] --> B_Patrol
        B_Patrol --> B_Chase : Joueur détecté\n(Distance < 400px)
        B_Chase --> B_Attack : À portée de contact\n(Distance < 50px)
        B_Attack --> B_Chase : Joueur s'éloigne
        B_Chase --> B_Patrol : Joueur perdu de vue
    }

    state "Logique Sniper" as Sniper {
        [*] --> S_Patrol
        S_Patrol --> S_Aim : Joueur détecté
        S_Aim --> S_Shoot : Cible verrouillée\n(après 1.5s)
        S_Shoot --> S_Flee : Joueur trop proche\n(Distance < 200px)
        S_Flee --> S_Aim : Distance de sécurité\nrétablie
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
