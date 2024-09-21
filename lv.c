#include "lite_vector.h"
#include <string.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

static void cleanup_all_vectors(void);
static lite_vector** all_vectors = NULL;
static size_t vector_count = 0;

lite_vector* lv_new_vec(size_t type_size) {
    static int atexit_registered = 0;
    if (!atexit_registered) {
        atexit(cleanup_all_vectors);
        atexit_registered = 1;
    }
    lite_vector* vec = (lite_vector*)malloc(sizeof(lite_vector));
    if (!vec) return NULL;
    vec->length = 0;
    vec->max_capacity = INITIAL_CAPACITY;
    vec->type_size = type_size;
    vec->data = (void**)malloc(sizeof(void*) * INITIAL_CAPACITY);
    if (!vec->data) {
        free(vec);
        return NULL;
    }
    all_vectors = realloc(all_vectors, (vector_count + 1) * sizeof(lite_vector*));
    if (!all_vectors) {
        free(vec->data);
        free(vec);
        return NULL;
    }
    all_vectors[vector_count++] = vec;
    return vec;
}

void lv_cleanup(lite_vector* vec) {

    if (!vec) return;
    for (size_t i = 0; i < vec->length; i++) {
        free(vec->data[i]);
    }
    free(vec->data);
    free(vec);
}

static void cleanup_all_vectors(void) {
    for (size_t i = 0; i < vector_count; i++) {
        lv_cleanup(all_vectors[i]);
    }
    free(all_vectors);
    all_vectors = NULL;
    vector_count = 0;
}

bool lv_clear(lite_vector* vec) {
    if (!vec) return false;
    for (size_t i = 0; i < vec->length; i++) {
        free(vec->data[i]);
    }
    vec->length = 0;
    return true;
}

size_t lv_get_length(lite_vector* vec) {
    return vec ? vec->length : 0;
}

void* lv_get(lite_vector* vec, size_t index) {
    if (!vec || index >= vec->length) return NULL;
    return vec->data[index];
}

static bool lv_resize(lite_vector* vec) {
    size_t new_capacity = vec->max_capacity * GROWTH_FACTOR;
    void** new_data = (void**)realloc(vec->data, sizeof(void*) * new_capacity);
    if (!new_data) return false;
    vec->data = new_data;
    vec->max_capacity = new_capacity;
    return true;
}

bool lv_append(lite_vector* vec, void* element) {
    if (!vec || !element) return false;
    if (vec->length >= vec->max_capacity) {
        if (!lv_resize(vec)) return false;
    }
    // Create a copy of the element (extra credit implementation)
    void* element_copy = malloc(vec->type_size);
    if (!element_copy) return false;
    memcpy(element_copy, element, vec->type_size);
    vec->data[vec->length++] = element_copy;
    return true;
}
