#include <cutelog.h>

int main() {
    cutelog_t ctx = cutelog_new();

    cutelog_progress(ctx, "This is a progress text");
    cutelog_info(ctx, "This is a information");
    cutelog_success(ctx, "This is a success message");
    cutelog_fail(ctx, "This is a failure message");
    cutelog_fatal(ctx, "This is a fatal message");
    cutelog_warning(ctx, "This is a warning message");
    cutelog_debug(ctx, "This is a debug message");

    cutelog_safe_finish(ctx);
    cutelog_free(ctx);
    return 0;
}
