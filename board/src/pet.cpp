#include "pet.h"

static PetStatus petStatus = PetStatus::None;
static uint8_t creatureId = NO_CREATURE;
static uint8_t happiness = START_HAPPINESS;
static uint8_t daysDone = 0;
static uint8_t missedDays = 0;

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

uint8_t getHappiness() {
    return happiness;
}

uint8_t getDaysDone() {
    return daysDone;
}

uint8_t getMissedDays() {
    return missedDays;
}

PetStage getPetStage() {
    if (daysDone >= ADULT_DAYS) {
        return PetStage::Adult;
    }

    if (daysDone >= BABY_DAYS) {
        return PetStage::Baby;
    }

    return PetStage::Egg;
}

// chamar quando o habito for criado
void createPet() {
    creatureId = drawCreature();
    happiness = START_HAPPINESS;
    daysDone = 0;
    missedDays = 0;
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

// chamar uma vez por dia: done = true se o habito foi cumprido
// TODO: falta a contagem de dias e o botao de marcar o habito
void registerDay(bool done) {
    if (petStatus != PetStatus::Alive) {
        return;
    }

    if (done) {
        if (happiness < MAX_HAPPINESS) {
            happiness++;
        }

        // so cresce nos dias cumpridos
        if (daysDone < HABIT_DAYS) {
            daysDone++;
        }

        missedDays = 0;
        return;
    }

    if (happiness > 0) {
        happiness--;
    }

    missedDays++;

    if (missedDays >= MAX_MISSED_DAYS) {
        markPetDead();
    }
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
