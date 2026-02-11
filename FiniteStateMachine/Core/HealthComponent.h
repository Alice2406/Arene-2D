#pragma once

class HealthComponent {
private:
    float currentHealth;
    float maxHealth;
    bool isDead;

public:
    HealthComponent(float maxHp = 100.0f);

    // Damage et healing
    void takeDamage(float amount);
    void heal(float amount);

    // Reset et initialisation
    void reset();
    void setMaxHealth(float maxHp);

    // Getters
    float getHealth() const { return currentHealth; }
    float getMaxHealth() const { return maxHealth; }
    float getHealthRatio() const { if (maxHealth == 0) return 0.0f;return currentHealth / maxHealth; }
    bool IsDead() const { return isDead; }
};