#include "habit_manager.h"
#include <EEPROM.h>

const int EEPROM_START_ADDR = 0;

void saveHabit(int index, const Habit& habit) {
    int addr = EEPROM_START_ADDR + (index * sizeof(Habit));
    EEPROM.put(addr, habit);
}

Habit loadHabit(int index) {
    Habit habit;
    int addr = EEPROM_START_ADDR + (index * sizeof(Habit));
    EEPROM.get(addr, habit);
    return habit;
}

void deleteHabit(int index) {
    Habit empty_habit;
    memset(&empty_habit, 0, sizeof(Habit)); // Limpia toda la estructura a 0
    saveHabit(index, empty_habit);
}

bool canTrackHabit(const Habit& habit, uint32_t current_unix_time) {
    if (habit.last_tracked == 0) {
        return true;
    }
    return (current_unix_time - habit.last_tracked) >= 86400; // 24 horas
}

bool trackHabit(Habit& habit, uint32_t current_unix_time, int habit_index) {
    if (canTrackHabit(habit, current_unix_time)) {
        habit.counter++;
        habit.last_tracked = current_unix_time;
        saveHabit(habit_index, habit);
        return true;
    }
    return false;
}