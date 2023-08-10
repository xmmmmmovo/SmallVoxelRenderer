#include <spdlog/spdlog.h>

#include "application/voxel_renderer.hpp"

void sig_handler(int sig) { printf("abort signal catch:%d\n", sig); }

int main() {
    signal(SIGABRT, sig_handler);

#ifdef _DEBUG
    // set spdlog log level
    spdlog::set_level(spdlog::level::debug);
#else
    spdlog::set_level(spdlog::level::info);
#endif

    voxel::VoxelRenderer renderer;
    renderer.init();
    renderer.start();
    return 0;
}