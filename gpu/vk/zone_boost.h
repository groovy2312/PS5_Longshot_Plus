#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline uint64_t zone_now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000ULL + (uint64_t)(ts.tv_nsec / 1000000ULL);
}

__attribute__((weak)) volatile uint64_t g_zone_boost_until_ms = 0;
__attribute__((weak)) volatile uint64_t g_last_draw_key = 0;
__attribute__((weak)) volatile int64_t  g_last_present_seen = 0;
__attribute__((weak)) volatile uint64_t g_ps5_free_mem_mb = 0;
__attribute__((weak)) volatile int      g_zone_boost_mem_hold = 0;

static inline void zone_boost_trigger(void) {
    const char *sec_env = getenv("RX_VK_ZONE_BOOST_SEC");
    int sec = sec_env ? atoi(sec_env) : 90;
    if (sec <= 0) return;
    uint64_t target = zone_now_ms() + (uint64_t)sec * 1000ULL;
    uint64_t cur = __atomic_load_n(&g_zone_boost_until_ms, __ATOMIC_RELAXED);
    if (target > cur) {
        __atomic_store_n(&g_zone_boost_until_ms, target, __ATOMIC_RELAXED);
    }
}

static inline void zone_boost_update_mem(uint64_t free_mb, uint64_t floor_mb) {
    __atomic_store_n(&g_ps5_free_mem_mb, free_mb, __ATOMIC_RELAXED);
    const char *sec_env = getenv("RX_VK_ZONE_BOOST_SEC");
    if (sec_env && atoi(sec_env) <= 0) { __atomic_store_n(&g_zone_boost_mem_hold, 0, __ATOMIC_RELAXED); return; }
    if (free_mb < floor_mb + 1060ULL) {
        __atomic_store_n(&g_zone_boost_mem_hold, 1, __ATOMIC_RELAXED);
        zone_boost_trigger();
    } else if (free_mb >= floor_mb + 1600ULL) {
        __atomic_store_n(&g_zone_boost_mem_hold, 0, __ATOMIC_RELAXED);
    }
}

static inline int zone_boost_active(void) {
    uint64_t until = __atomic_load_n(&g_zone_boost_until_ms, __ATOMIC_RELAXED);
    int hold = __atomic_load_n(&g_zone_boost_mem_hold, __ATOMIC_RELAXED);
    if (until != 0) {
        if (zone_now_ms() < until) return 1;
        __atomic_store_n(&g_zone_boost_until_ms, 0, __ATOMIC_RELAXED);
    }
    return hold ? 1 : 0;
}

#ifdef __cplusplus
}
#endif
