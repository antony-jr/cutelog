#include <cutelog.h>
#include <stdbool.h>

int main() {
    cutelog_t ctx = cutelog_new();
    int done = 0;
    int total = 150000; /* I made this large enough to make it slow,
				you may want to increase this if your pc is really
				fast. Or use sleep */

    bool info_printed = false,
         warnin_printed = false,
         fatal_printed = false,
         debug_printed = false,
         success_printed = false,
         fail_printed = false;

    cutelog_mode(ctx, cutelog_non_multiline_mode);
    while(done < total) {
        int percentage = (done*100)/total;
        if(percentage >= 20 && !info_printed) {
            cutelog_mode(ctx, cutelog_multiline_mode);
            cutelog_info(ctx, "20 percentage is completed!");
            info_printed = true;
        } else if(percentage >= 40 && !warnin_printed) {
            cutelog_mode(ctx, cutelog_multiline_mode);
            cutelog_warning(ctx, "warning 40 percent has finished.");
            warnin_printed = true;
        } else if(percentage >= 50 && !fatal_printed) {
            cutelog_mode(ctx, cutelog_multiline_mode);
            cutelog_fatal(ctx, "fatal 50 percent has finished.");
            fatal_printed = true;
        } else if(percentage >= 60 && !debug_printed) {
            cutelog_mode(ctx, cutelog_multiline_mode);
            cutelog_debug(ctx, "do you know 60 percent has finished.");
            debug_printed = true;
        } else if(percentage >= 70 && !fail_printed) {
            cutelog_mode(ctx, cutelog_multiline_mode);
            cutelog_fail(ctx, "passing 70 percent!");
            fail_printed = true;
        } else if(percentage >= 95 && !success_printed) {
            cutelog_mode(ctx, cutelog_multiline_mode);
            cutelog_success(ctx, "Going to reach 100 percentage!");
            success_printed = true;
        }
        cutelog_mode(ctx, cutelog_non_multiline_mode);
        cutelog_progress(ctx, "Doing something %d%% ...", percentage);
        //sleep(1);
        ++done;
    }
    cutelog_mode(ctx, cutelog_multiline_mode);
    cutelog_success(ctx, "All tests finished.");
    cutelog_safe_finish(ctx);
    cutelog_free(ctx);
    return 0;
}
