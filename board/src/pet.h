#ifndef PET_H
#define PET_H

#include <Arduino.h>

constexpr uint8_t NUM_CREATURES = 3;
constexpr uint8_t NO_CREATURE = 0xFF;

constexpr uint8_t MAX_HAPPINESS = 10;
constexpr uint8_t START_HAPPINESS = 5;
constexpr uint8_t MAX_MISSED_DAYS = 10;
constexpr uint8_t HABIT_DAYS = 66;

// dias cumpridos para mudar de fase
constexpr uint8_t BABY_DAYS = 22;
constexpr uint8_t ADULT_DAYS = 44;

enum class PetStatus : uint8_t {
    None,
    Alive,
    Dead
};

enum class PetStage : uint8_t {
    Egg,
    Baby,
    Adult
};

PetStatus getPetStatus();
bool isPetDead();
uint8_t getCreatureId();
uint8_t getHappiness();
uint8_t getDaysDone();
uint8_t getMissedDays();
PetStage getPetStage();

void createPet();
void markPetDead();
void giveUpPet();
void clearPet();
void registerDay(bool done);

uint8_t drawCreature();

#endif
