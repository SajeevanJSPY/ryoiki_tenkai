#include <platform/platform.h>
#include <core/rmemory.h>
#include "vulkan_renderer/vulkan_types.h"

#include <core/rmemory.h>
#include <containers/darray.h>
#include <core/logger.h>

/* 
    About Application:
        Debug Mode - _DEBUG will be defined for all source files
        Release Mode
*/

int main() {
    initialize_memory();

    app_state state = {
        .app_name = "eren yeager",
        .engine_name = "rumbling",
        .pos_x = 0,
        .pos_y = 0,
        .width = 500,
        .height = 500
    };

    platform_state plat_state;
    platform_startup(&plat_state, state.app_name, state.pos_x, state.pos_y, state.width, state.height);

    get_memory_usage_str();

    /*
    while(platform_pump_messages(&plat_state)) {

    }
    */

    platform_shutdown(&plat_state);

    shutdown_memory();
}
