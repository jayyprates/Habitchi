#ifndef PET_H
#define PET_H

#include <Arduino.h>

enum class PetStatus : uint8_t {
    None,
    Alive,
    Dead
};

PetStatus getPetStatus();
bool isPetDead();

void setPetAlive();
void markPetDead();
void giveUpPet();
void clearPet();

#endif
