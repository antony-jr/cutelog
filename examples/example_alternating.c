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
