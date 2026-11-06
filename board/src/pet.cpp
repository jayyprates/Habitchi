#include "pet.h"

static PetStatus petStatus = PetStatus::None;

PetStatus getPetStatus() {
    return petStatus;
}

bool isPetDead() {
    return petStatus == PetStatus::Dead;
}

void setPetAlive() {
    petStatus = PetStatus::Alive;
}

void markPetDead() {
    petStatus = PetStatus::Dead;
}

void giveUpPet() {
    // TODO: apagar o habito da EEPROM quando o salvamento existir
    markPetDead();
}

void clearPet() {
    petStatus = PetStatus::None;
}
