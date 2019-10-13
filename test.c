#include <cutelog.h>
#include <unistd.h>
int main(){
	cutelog_t ctx = cutelog_new();
	cutelog_mode(ctx, cutelog_non_multiline_mode);

	int done = 0;
	int total = 10;
	while(done < total){
		cutelog_progress(ctx, "Preparing for awesome-ness %d\% ", (done*100/total));
		++done;
		sleep(1);
	}
	cutelog_mode(ctx, cutelog_multiline_mode);

	cutelog_success(ctx, "Awesome-ness prepared!");

	cutelog_mode(ctx, cutelog_non_multiline_mode);
	done = 0;
	total = 15;
	while(done < total){
		cutelog_progress(ctx, "Checking for bugs %d\% ", (done*100/total));
		++done;
		sleep(1);
	}
	cutelog_mode(ctx, cutelog_multiline_mode);

	cutelog_fail(ctx, "No bugs found.");

	cutelog_mode(ctx, cutelog_non_multiline_mode);
	done = 0;
	total = 20;
	while(done < total){
		cutelog_progress(ctx, "Checking if this will be popular %d\% ", (done*100/total));
		++done;
		sleep(1);
	}
	cutelog_mode(ctx, cutelog_multiline_mode);

	cutelog_info(ctx, "I think it will never be :(");

	cutelog_mode(ctx, cutelog_non_multiline_mode);
	done = 0;
	total = 30;
	while(done < total){
		cutelog_progress(ctx, "Checking if this works on every platform %d\% ", (done*100/total));
		++done;
		sleep(1);
	}
	cutelog_mode(ctx, cutelog_multiline_mode);

	cutelog_warning(ctx, "This might not work on every platform.");

	cutelog_mode(ctx, cutelog_non_multiline_mode);
	done = 0;
	total = 10;
	while(done < total){
		cutelog_progress(ctx, "Checking if this works without compiling %d\% ", (done*100/total));
		++done;
		sleep(1);
	}
	cutelog_mode(ctx, cutelog_multiline_mode);

	cutelog_fatal(ctx, "A C file will not run by itself, you know!");
	cutelog_debug(ctx, "Ok everything finished.");
	cutelog_safe_finish(ctx);
	cutelog_free(ctx);
	return 0;
}
