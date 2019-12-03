#ifndef MY_VECTOR_H
#define MY_VECTOR_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct my_vector {
    size_t elem_size;
    size_t capacity;
    size_t size;
    void *data;
} my_vector;


static void vec_init(my_vector *vec, size_t elem_size);
static void vec_clear(my_vector *vec);
static void vec_push_back(my_vector *vec, void *elem);
static void vec_shrink_to_fit(my_vector *vec);
static size_t vec_size(my_vector *vec);
static void* vec_data(my_vector *vec);


static void vec_init(my_vector *vec, size_t elem_size)
{
    memset(vec, 0, sizeof(my_vector));
    vec->elem_size = elem_size;
}

static void vec_clear(my_vector *vec)
{
    free(vec->data);
    memset(vec, 0, sizeof(my_vector));
}

static void vec_push_back(my_vector *vec, void *elem)
{
    void *ptr = NULL;
    if (vec->size == vec->capacity) {
        if (vec->capacity < 2) {
            vec->capacity += 1;
        } else {
            // pre-allocation
            vec->capacity *= 1.5;
        }
        ptr = realloc(vec->data, vec->elem_size * vec->capacity);
        if (!ptr) {
            // error
            fprintf(stderr, "my vector push_back realloc error");
            return;
        }
        vec->data = ptr;
    }
    memcpy((char*)vec->data + (vec->size * vec->elem_size), elem, vec->elem_size);
    ++vec->size;
}

static void vec_shrink_to_fit(my_vector *vec)
{
    void *ptr = NULL;
    if (vec->capacity != vec->size) {
        vec->capacity = vec->size;
        ptr = realloc(vec->data, vec->elem_size * vec->capacity);
        if (!ptr) {
            // error
            fprintf(stderr, "my vector shrink realloc error");
            return;
        }
        vec->data = ptr;
    }
}

static size_t vec_size(my_vector *vec)
{
    return vec->size;
}

static void* vec_data(my_vector *vec)
{
    return vec->data;
}

#endif /* MY_VECTOR_H */
