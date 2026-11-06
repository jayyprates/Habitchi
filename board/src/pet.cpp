#include "pet.h"

static PetStatus petStatus = PetStatus::None;
static uint8_t creatureId = NO_CREATURE;

// criatura do ultimo sorteio, para nao repetir no proximo
// TODO: salvar na EEPROM para a regra valer depois de desligar
static uint8_t lastCreatureId = NO_CREATURE;

PetStatus getPetStatus() {
    return petStatus;
}

bool isPetDead() {
    return petStatus == PetStatus::Dead;
}

uint8_t getCreatureId() {
    return creatureId;
}

// chamar quando o habito for criado
void createPet() {
    creatureId = drawCreature();
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
    creatureId = NO_CREATURE;
}

uint8_t drawCreature() {
    uint8_t id;

    if (lastCreatureId == NO_CREATURE) {
        // primeiro sorteio: qualquer uma das 3
        id = random(NUM_CREATURES);
    } else {
        // pula a ultima: sorteia 1 ou 2 posicoes pra frente
        id = (lastCreatureId + 1 + random(NUM_CREATURES - 1)) % NUM_CREATURES;
    }

    lastCreatureId = id;
    return id;
}
