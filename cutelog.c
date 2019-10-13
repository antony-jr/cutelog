#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstr.h>
#include <cutelog.h>

/* Emojis */
const char *unicorn_emoji = "🦄";
const char *heavy_check_mark_emoji = "✅";
const char *crossmark_emoji = "❌";
const char *lightbulb_emoji = "💡";
const char *stopsign_emoji = "🛑";
const char *warning_emoji = "🔔";
const char *debug_emoji = "💽";
/* --- */

typedef enum {
	progress,
	success,
	fail,
	info,
	fatal,
	warning,
	debug
} print_type_t;

static const char *prog_series = "\\|/-";
static int prog_series_len = 4;

struct _cutelog_t {
	FILE *output;
	cutelog_mode_t mode;
	int prog_series_pos;
	int prev_print_size;
};
#define CUTELOG_SZ (sizeof(struct _cutelog_t))

static char *get_time(){
	time_t current_time;
	struct tm * time_info;
	static char time_string[9] = {0};
	time(&current_time);
	time_info = localtime(&current_time);
	strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);
	return time_string;
}

static int print(cutelog_t ctx, print_type_t type, const char *fmt, va_list ap){
	cstr_t toprint = cstr_new();
	int r = -1;
	char *space = "";
	if(ctx == NULL || !fmt || toprint == NULL) 
		return r;
	
	if(ctx->mode == cutelog_non_multiline_mode)
		fflush(ctx->output);
	
	
	r += fprintf(ctx->output, " [ %s ] ",
					get_time());		
	switch(type){
		case progress:
			r += fprintf(ctx->output, "(%s \033[35mProgress\033[0m ", unicorn_emoji);
			break;
		case success:
			r += fprintf(ctx->output, "(%s \033[32mSuccess\033[0m", heavy_check_mark_emoji);
			break;
		case fail:
			r += fprintf(ctx->output, "(%s \033[31mFailed\033[0m", crossmark_emoji);
			space = "  ";
			break;
		case info:
			r += fprintf(ctx->output, "(%s \033[34mInfo\033[0m", lightbulb_emoji);
			break;
		case fatal:
			r += fprintf(ctx->output, "(%s \033[47;31mFatal\033[0m", stopsign_emoji);
			break;
		case warning:
			r += fprintf(ctx->output, "(%s \033[33mWarning\033[0m", warning_emoji);
			break;
		case debug:
			r += fprintf(ctx->output, "(%s \033[36mDebug\033[0m", debug_emoji);
			break;	
		default:
			r += fprintf(ctx->output, "(Unknown");
			break;
	}	
	if(ctx->mode == cutelog_non_multiline_mode){
		if(type == progress){
			r+= fprintf(ctx->output, "%c",
				prog_series[ctx->prog_series_pos]);
			ctx->prog_series_pos = 
				(ctx->prog_series_pos + 1) % prog_series_len;
		}
	}
	r += fprintf(ctx->output, " )%s: ",space);	

	if(ctx->mode == cutelog_non_multiline_mode){
		while(*fmt){
			cstr_append_char(toprint,
					(*fmt == '\n') ? ' ' : *fmt);
			++fmt;
		}
		r += vfprintf(ctx->output, cstr_digest(toprint), ap);
		cstr_free(toprint);
	}else{
		r += vfprintf(ctx->output, fmt, ap);	
	}

	/* footer. */
	switch(type){
		case progress:
			r+= fprintf(ctx->output, "... ");
			break;
		default:
			break;
	}
	if(ctx->mode == cutelog_non_multiline_mode){
		r+= fprintf(ctx->output, "\r");
	}else
		r+= fprintf(ctx->output, "\n");
	return r + 1;

}

#define CREATE_FUNCTION(name) int cutelog_##name(cutelog_t ctx, const char *fmt, ...){ \
	                         va_list ap; \
	                         int r = 0; \
	                         va_start(ap, NULL); \
	                         r = print(ctx, name , fmt, ap); \
	                         ctx->prev_print_size = r; \
	                         va_end(ap); \
	                         return r; \
	                      }


cutelog_t cutelog_new(){
	return cutelog_new_ex(stdout);
}

cutelog_t cutelog_new_ex(void *out){
	cutelog_t r = calloc(1, CUTELOG_SZ);
	if(r == NULL)
		return NULL;
	r->output = (!out) ? stdout : out;
	r->mode = cutelog_multiline_mode; /* default */
	return r;
}

void cutelog_free(cutelog_t ctx){
	if(ctx == NULL)
		return;
	free(ctx);
}


int cutelog_mode(cutelog_t ctx, cutelog_mode_t mode){
	if(ctx == NULL)
		return -1;

	if(ctx->mode == cutelog_non_multiline_mode &&
	   mode == cutelog_multiline_mode){
		fflush(ctx->output);
		/* avoid overlapping between multiline and non multiline. */
		do{ /* code block in c89 version, do not take this away, its not useless. */
			int to_fill = ctx->prev_print_size * 2;
			cstr_t fill = cstr_new();
			while(to_fill--)
				cstr_append_char(fill, ' ');	
			fprintf(ctx->output, "%s\r", cstr_digest(fill));
			fflush(ctx->output);
			cstr_free(fill);
		}while(0);	
	}
	ctx->mode = mode;
	return 0;
}

int cutelog_safe_finish(cutelog_t ctx){
	if(ctx == NULL)
		return -1;

	if(ctx->mode == cutelog_non_multiline_mode)
		fprintf(ctx->output, "\n");
	return 0;
}

CREATE_FUNCTION(progress);
CREATE_FUNCTION(success);
CREATE_FUNCTION(fail);
CREATE_FUNCTION(info);
CREATE_FUNCTION(fatal);
CREATE_FUNCTION(warning);
CREATE_FUNCTION(debug);

