#include <cutelog.h>
#include <unistd.h>

int main() {
    cutelog_t ctx = cutelog_new();
    cutelog_mode(ctx, cutelog_non_multiline_mode);

    cutelog_progress(ctx, "This is a progress text");
    sleep(2);
    cutelog_info(ctx, "This is a information");
    sleep(2);
    cutelog_success(ctx, "This is a success message");
    sleep(2);
    cutelog_fail(ctx, "This is a failure message");
    sleep(2);
    cutelog_fatal(ctx, "This is a fatal message");
    sleep(2);
    cutelog_warning(ctx, "This is a warning message");
    sleep(2);
    cutelog_debug(ctx, "This is a debug message");
    sleep(2);
    cutelog_safe_finish(ctx);
    cutelog_free(ctx);
    return 0;
}
