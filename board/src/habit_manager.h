#ifndef HABIT_MANAGER_H
#define HABIT_MANAGER_H

#include "habit.h"

void saveHabit(int index, const Habit& habit);
Habit loadHabit(int index);
void deleteHabit(int index);
bool canTrackHabit(const Habit& habit, uint32_t current_unix_time);
bool trackHabit(Habit& habit, uint32_t current_unix_time, int habit_index);

#endif // HABIT_MANAGER_H