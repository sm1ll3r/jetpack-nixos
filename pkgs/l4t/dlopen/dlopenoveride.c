#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

// List of paths to replace
const char *old_paths[] = {"/usr/lib/aarch64-linux-gnu/tegra-egl/libEGL_nvidia.so.0"};
const char *new_paths[] = {"/run/opengl-driver/lib/libEGL_nvidia.so.0"};
const int num_paths = sizeof(old_paths) / sizeof(old_paths[0]);

void *(*original_dlopen)(const char *, int) = NULL;

void *dlopen(const char *filename, int flag) {
    if (!original_dlopen) {
        original_dlopen = dlsym(RTLD_NEXT, "dlopen");
    }

    if (filename) {
        for (int i = 0; i < num_paths; i++) {
            printf("Sean %d\n", i);
            if (strcmp(filename, old_paths[i]) == 0) {
                printf("Redirecting %s to %s\n", filename, new_paths[i]);
                filename = new_paths[i];
                break;
            }
        }
    }

    return original_dlopen(filename, flag);
}
