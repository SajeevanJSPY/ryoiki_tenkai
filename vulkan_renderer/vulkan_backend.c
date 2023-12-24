#include "vulkan_types.h"

static vulkan_context context;

void vulkan_renderer_start() {
    // instance 
    VkApplicationInfo app_info = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "hello",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "hi",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };

    VkInstanceCreateInfo instance_creation_info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &app_info,
        .enabledExtensionCount = 2,
        .ppEnabledExtensionNames = &instance_level_extensions[0],
    };
    VK_CHECK(vkCreateInstance(&instance_creation_info, NULL, context.instance));
}


