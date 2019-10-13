#ifndef CUTELOG_H_INCLUDED
#define CUTELOG_H_INCLUDED

struct _cutelog_t;
typedef struct _cutelog_t* cutelog_t;

typedef enum {
	cutelog_no_mode,
	cutelog_multiline_mode,
	cutelog_non_multiline_mode
} cutelog_mode_t;

cutelog_t cutelog_new();
cutelog_t cutelog_new_ex(void*);
void cutelog_free(cutelog_t);

int cutelog_mode(cutelog_t, cutelog_mode_t);
int cutelog_safe_finish(cutelog_t);

int cutelog_progress(cutelog_t, const char*, ...);
int cutelog_success(cutelog_t, const char*, ...);
int cutelog_fail(cutelog_t, const char*, ...);
int cutelog_info(cutelog_t, const char*, ...);
int cutelog_fatal(cutelog_t, const char*, ...);
int cutelog_warning(cutelog_t, const char*, ...);
int cutelog_debug(cutelog_t, const char*, ...);


#endif /* CUTELOG_H_INCLUDED */
