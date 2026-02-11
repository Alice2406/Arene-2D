#include "HealthComponent.h"
#include <algorithm>

HealthComponent::HealthComponent(float maxHp)
    : maxHealth(maxHp), currentHealth(maxHp), isDead(false) {
}

void HealthComponent::takeDamage(float amount)
{
    if (isDead) return;
    if (amount <= 0) return;

    currentHealth -= amount;

    if (currentHealth <= 0.0f) {
        currentHealth = 0.0f;
        isDead = true;
    }
}

void HealthComponent::heal(float amount)
{
    if (isDead) return;
    if (amount <= 0) return;

    currentHealth = std::min(currentHealth + amount, maxHealth);
}

void HealthComponent::reset()
{
    currentHealth = maxHealth;
    isDead = false;
}

void HealthComponent::setMaxHealth(float maxHp)
{
    if (maxHp <= 0) return;

    float ratio = getHealthRatio();
    maxHealth = maxHp;
    currentHealth = maxHealth * ratio;
}