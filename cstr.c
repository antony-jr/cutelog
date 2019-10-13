/*
 * MIT License
 * 
 * Copyright (c) 2019 Antony jr
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
#include <stdlib.h>
#include <string.h>
#include <cstr.h>

struct _cstr_t {
    char *buffer;
    size_t pos,capacity;
};
#define CSTR_SZ (sizeof(struct _cstr_t))
#define INITIAL_BUFFER_SIZE 1024 /* bytes */

static int grow(cstr_t obj) {
    char *guard = NULL;
    if(obj == NULL)
        return -1;

    if(obj->pos >= obj->capacity) {
        guard = realloc(obj->buffer,
                        sizeof(char) * (obj->capacity + INITIAL_BUFFER_SIZE));
        if(!guard)
            return -1;
        obj->capacity += INITIAL_BUFFER_SIZE;
        memset(guard + obj->pos, 0, sizeof(char)*(obj->capacity - obj->pos));
        obj->buffer = guard;
    }
    return 0;
}

cstr_t cstr_new() {
    cstr_t r = calloc(1, CSTR_SZ);
    if(r == NULL)
        return NULL;
    r->buffer = calloc(INITIAL_BUFFER_SIZE, sizeof *(r->buffer));
    if(!r->buffer) {
        cstr_free(r);
        return NULL;
    }
    r->capacity = INITIAL_BUFFER_SIZE;
    return r;
}

cstr_t cstr_new_ex(const char *s) {
    size_t len = strlen(s) + INITIAL_BUFFER_SIZE;
    cstr_t r = calloc(1, CSTR_SZ);
    if(r == NULL)
        return NULL;
    r->buffer = calloc(len, sizeof *(r->buffer));
    if(!r->buffer) {
        cstr_free(r);
        return NULL;
    }

    while(*s)
        r->buffer[r->pos++] = *s++;
    r->capacity = len;
    return r;
}

void cstr_free(cstr_t obj) {
    if(obj == NULL)
        return;
    if(obj->buffer)
        free(obj->buffer);
    free(obj);
}


int cstr_prepend_char(cstr_t obj, char c) {
    size_t iter = 0;
    if(grow(obj))
        return -1;
    for(iter = obj->pos; iter > 0; --iter) {
        obj->buffer[iter + 1] = obj->buffer[iter];
    }
    obj->buffer[0] = c;
    ++obj->pos;
    return 0;
}

int cstr_append_char(cstr_t obj, char c) {
    if(grow(obj))
        return -1;
    obj->buffer[obj->pos++] = c;
    return 0;
}

int cstr_prepend(cstr_t obj, const char *s) {
    char *g = NULL;
    cstr_t buf = cstr_new();
    if(buf == NULL)
        return -1;
    if(cstr_append(buf, s)) {
        cstr_free(buf);
        return -1;
    }
    if(cstr_append(buf, obj->buffer)) {
        cstr_free(buf);
        return -1;
    }
    if(!buf->buffer) {
        cstr_free(buf);
        return -1;
    }

    if(obj->buffer)
        free(obj->buffer);
    obj->buffer = buf->buffer;
    obj->pos = buf->pos;
    obj->capacity = buf->capacity;
    free(buf);
}

int cstr_prepend_ex(cstr_t obj, cstr_t other) {
    return cstr_prepend(obj, other->buffer);
}

int cstr_append(cstr_t obj, const char *s) {
    while(*s) {
        if(cstr_append_char(obj, *s))
            return -1;
        ++s;
    }
    return 0;
}

int cstr_append_ex(cstr_t obj, cstr_t other) {
    return cstr_append(obj, other->buffer);
}

const char *cstr_digest(cstr_t obj) {
    return (obj == NULL) ? NULL : obj->buffer;
}
