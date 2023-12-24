#pragma once

#include <core/defines.h>
#include <vulkan/vulkan.h>

/*
typedef struct renderer_backend {
    struct platform_state *plat_state;
    b8 (*initialize)(struct renderer_backend *backend); 
    void (*shutdown)(struct renderer_backend *backend);
    void (*resized)(struct renderer_backend *backend, u16 width, u16 height);

    b8 (*begin_frame)(struct renderer_backend *backend, f32 delta_time);
    b8 (*end_frame)(struct renderer_backend *backend, f32 delta_time);
} renderer_backend;
*/

/** checking vulkan results, whether the function return VK_SUCCESS or not */
#define VK_CHECK(expr) \
    RASSERT(expr == VK_SUCCESS)

/** main functions for initializing and destroying the vulkan */
void vulkan_renderer_start();
void vulkan_renderer_end();

/** @brief: handling the state of the application */
typedef struct app_state {
    const char* app_name;
    const char* engine_name;
    u64 pos_x;
    u64 pos_y;
    u64 width;
    u64 height;
} app_state;

/** Vulkan Device */
typedef struct {
    VkPhysicalDevice device;
    VkDevice gpu;
} vulkan_device;

/** details about swapchain */
typedef struct {

} swapchain_info;

/** monolithic object for vulkan renderer */
typedef struct {
    vulkan_device vk_device; 
    VkAllocationCallbacks *allocator;

    VkSurfaceKHR surface;

    vulkan_device device;
} vulkan_context;

