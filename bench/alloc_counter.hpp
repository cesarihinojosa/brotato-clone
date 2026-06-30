#pragma once
#include <atomic>
#include <cstddef>

/// Process-wide allocation counters, incremented by overridden global
/// operator new in alloc_counter.cpp. Only linked into the bench binary.
extern std::atomic<std::size_t> g_alloc_count;
extern std::atomic<std::size_t> g_alloc_bytes;
