#include "filesystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <core/asserts.h>
#include <core/logger.h>

b8 filesystem_open(const char *path, file_modes mode, b8 binary, file_handle *out_handle) {
    out_handle->is_valid = false;
    out_handle->handle = 0;
    
    const char *mode_str;

    if ((mode & FILE_MODE_READ) != 0 && (mode & FILE_MODE_WRITE) != 0) {
        mode_str = binary ? "w+b" : "w+";
    } else if ((mode & FILE_MODE_READ) != 0 && (mode & FILE_MODE_WRITE) == 0) {
        mode_str = binary ? "rb" : "r";
    } else if ((mode & FILE_MODE_READ) == 0 && (mode & FILE_MODE_WRITE) != 0) {
        mode_str = binary ? "wb" : "w";
    } else {
        RERROR("Invalid mode passed while trying to open a file: '%s'", path);
        return false;
    }

    FILE *fp = fopen(path, mode_str);
    if (!fp) {
        RERROR("failed to open file: '%s'", path);
        return false;
    }

    out_handle->handle = fp;
    out_handle->is_valid = true;

    return true;
}

void filesystem_close(file_handle *handle) {
    if (handle->handle) {
        fclose((FILE*)handle->handle);
        handle->handle = 0;
        handle->is_valid = false;
    }
}

b8 filesystem_read(file_handle* handle, u64 data_size, void* out_data, u64* out_bytes_read) {
    if (handle->handle && out_data) {
        *out_bytes_read = fread(out_data, 1, data_size, (FILE*)handle->handle);
        if (*out_bytes_read != data_size) {
            return false;
        }
        return true;
    }
    return false;
}

b8 filesystem_read_all_bytes(file_handle *handle, u8 **out_bytes, u64 *out_bytes_read) {
    if (handle->handle) {
        fseek((FILE*)handle->handle, 0, SEEK_END); 
        u64 size = ftell((FILE*)handle->handle);
        rewind((FILE*)handle->handle);
        
        // TODO: change this with a platform specific function
        *out_bytes = malloc(sizeof(u8) * size); 
        *out_bytes_read = fread(*out_bytes, 1, size, (FILE*)handle->handle);
        if (*out_bytes_read != size) {
            return false;
        }

        return true;
    }

    return false;
}
