#ifndef _GOLIBUCL_H_INCLUDED
#define _GOLIBUCL_H_INCLUDED

#include <ucl.h>
#include <stdlib.h>
#include <string.h>

static inline char *_go_uchar_to_char(const unsigned char *c) {
    return (char *)c;
}

static inline unsigned char *_go_char_to_uchar(const char *c) {
  return (unsigned char *)c;
}

//-------------------------------------------------------------------
// Helpers: Macros
//-------------------------------------------------------------------

// This is declared in parser.go and invokes the Go function callback for
// a specific macro (specified by the ID).
extern bool go_macro_call(int idx, ucl_object_t *arguments, char *data, int length);

// Indirection that actually calls the Go macro handler.
static inline bool _go_macro_handler(const unsigned char *data, size_t len, const ucl_object_t *arguments, void* ud) {
    return go_macro_call((intptr_t)ud, (ucl_object_t *)arguments, (char*)data, (int)len);
}

// Returns the ucl_macro_handler that we have, since we can't get this
// type from cgo.
static inline ucl_macro_handler _go_macro_handler_func() {
	return (ucl_macro_handler)&_go_macro_handler;
}

// This just converts an int to a void*, because Go doesn't let us do that
// and we use an int as the user data for registering macros.
static inline void *_go_macro_index(int idx) {
    return (void *)(intptr_t)idx;
}

typedef struct ucl_schema_error ucl_schema_error_t;

#endif /* _GOLIBUCL_H_INCLUDED */
