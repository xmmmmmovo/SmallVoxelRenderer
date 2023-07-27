#include "application/voxel_renderer.hpp"

void sig_handler(int sig) { printf("abort signal catch:%d\n", sig); }

int main() {
    signal(SIGABRT, sig_handler);

    voxel::VoxelRenderer renderer;
    renderer.init();
    renderer.start();
    return 0;
}