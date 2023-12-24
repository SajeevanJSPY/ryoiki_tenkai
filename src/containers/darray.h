#pragma once

#include <core/defines.h>

struct frame_allocator_int;

void* _darray_create(u64 length, u64 stride, struct frame_allocator_int* frame_allocator);

void* _darray_resize(void* array);

void* _darray_push(void* array, const void* value_ptr);

void* _darray_insert_at(void* array, u64 index, void* value_ptr);

#define DARRAY_DEFAULT_CAPACITY 1

#define DARRAY_RESIZE_FACTOR 2

#define darray_create(type) \
    _darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type), 0)

#define darray_create_with_allocator(type, allocator) \
    _darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type), allocator)

#define darray_reserve(type, capacity) \
    _darray_create(capacity, sizeof(type), 0)

#define darray_reserve_with_allocator(type, capacity, allocator) \
    _darray_create(capacity, sizeof(type), allocator)

void darray_destroy(void* array);

#define darray_push(array, value)           \
    {                                       \
        typeof(value) temp = value;         \
        array = _darray_push(array, &temp); \
    }
// NOTE: could use __auto_type for temp above, but intellisense
// for VSCode flags it as an unknown type. typeof() seems to
// work just fine, though. Both are GNU extensions.

void darray_pop(void* array, void* value_ptr);

#define darray_insert_at(array, index, value)           \
    {                                                   \
        typeof(value) temp = value;                     \
        array = _darray_insert_at(array, index, &temp); \
    }

void* darray_pop_at(void* array, u64 index, void* value_ptr);

void darray_clear(void* array);

u64 darray_capacity(void* array);

u64 darray_length(void* array);

u64 darray_stride(void* array);

void darray_length_set(void* array, u64 value);
