#ifndef TRADUNGEON_CONFIG_H
#define TRADUNGEON_CONFIG_H

#include "Common.h"
#include "Clock.h"
#include <chrono>

namespace tradungeon::config
{

constexpr auto fps = 60;
constexpr auto delta_time = std::chrono::milliseconds(1000 / fps);

constexpr auto map_size = Size{400, 400};

constexpr auto map_visibility_radius = 15;
constexpr auto npc_spawn_radius = 70;

// # of days required for a periodical map reset.
constexpr auto map_reset_cycle = 5;

constexpr auto time_per_move = 1;

constexpr auto hunger_per_time = 1;
constexpr auto thirst_per_time = 1;
constexpr auto hunger_threshold = timeunit::day * 3 / 2;
constexpr auto hunger_warning_threshold = hunger_threshold / 2;
constexpr auto thirst_threshold = timeunit::day / 2;
constexpr auto thirst_warning_threshold = thirst_threshold / 2;

// The distance constraint from the center of the map to the exit.
constexpr auto exit_min_distance = 200;
constexpr auto exit_max_distance = 300;

// The number of random points to select while spawning an exit.
// If we can't find one with this sample size, consider it a failure.
constexpr auto num_trials_spawn_exit = 10000;

constexpr auto player_start_position = Point{map_size.m_width / 2, map_size.m_height / 2};

constexpr auto inventory_weight_limit = 500;
constexpr auto message_log_buffer_size = 1000;

} // namespace tradungeon::config

#endif
