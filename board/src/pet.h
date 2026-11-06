#ifndef PET_H
#define PET_H

#include <Arduino.h>

constexpr uint8_t NUM_CREATURES = 3;
constexpr uint8_t NO_CREATURE = 0xFF;

enum class PetStatus : uint8_t {
    None,
    Alive,
    Dead
};

PetStatus getPetStatus();
bool isPetDead();
uint8_t getCreatureId();

void createPet();
void markPetDead();
void giveUpPet();
void clearPet();

uint8_t drawCreature();

#endif
