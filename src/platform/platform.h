/**
 * @file: platform.h
 * @author: sajeevan
 * @brief: This file contains the platform layer, or at least the interface to it.
 * Each platform should provide its own implementation of this in a .c file, and
 * should be compiled exclusively of the rest.
*/

#pragma once

#include <core/defines.h>
#include <vulkan/vulkan.h>

typedef struct platform_state {
    void *internal_state;
} platform_state;

b8 platform_startup(
    platform_state *plat_state,
    const char *application_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height
); 

void platform_get_presentation_surface(VkInstance instance, platform_state *plat_state, VkSurfaceKHR *surface);

const char *platform_get_surface_extension();

void platform_shutdown(platform_state *plat_state);

b8 platform_pump_messages(platform_state *plat_state);

/** dynamic memory management */
void *platform_allocate(u64 size, b8 aligned);
void platform_free(void *block, u64 size);
void *platform_zero_memory(void *block, u64 size);
void *platform_copy_memory(void *dest, const void *source, u64 size);
void *platform_set_memory(void *dest, i32 value, u64 size);

/** console */
void platform_console_write(const char *message, u8 color);
void platform_console_write_error(const char *message, u8 color);

/** clock */
f64 platform_get_absolute_time();

// sleep on main thread for the provided ms. this blocks the main thread
void platform_sleep(u64 ms);
