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
#ifndef CSTR_H_INCLUDED
#define CSTR_H_INCLUDED

struct _cstr_t;
typedef struct _cstr_t* cstr_t;

cstr_t cstr_new();
cstr_t cstr_new_ex(const char*);
void cstr_free(cstr_t);

int cstr_prepend_char(cstr_t,char);
int cstr_append_char(cstr_t,char);
int cstr_prepend(cstr_t, const char*);
int cstr_prepend_ex(cstr_t, cstr_t);
int cstr_append(cstr_t, const char*);
int cstr_append_ex(cstr_t,cstr_t);

const char *cstr_digest(cstr_t);

#endif /* CSTR_H_INCLUDED */
