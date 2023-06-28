#ifndef TRADUNGEON_CONFIG_H
#define TRADUNGEON_CONFIG_H

#include "Common.h"

namespace tradungeon::config
{

constexpr auto map_size = Size{1000, 1000};

// The distance constraint from the center of the map to the exit.
constexpr auto exit_min_distance = 300;
constexpr auto exit_max_distance = 350;

// The number of random points to select while spawning an exit.
// If we can't find one with this sample size, consider it a failure.
constexpr auto num_trials_spawn_exit = 10000;

constexpr auto player_start_position = Point{map_size.m_width / 2, map_size.m_height / 2};

constexpr auto inventory_weight_limit = 15;
constexpr auto message_log_buffer_size = 100;

} // namespace tradungeon::config

#endif
