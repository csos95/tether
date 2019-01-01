#include <stdbool.h>
#include <stddef.h>

//TODO: Custom context menus.
//TODO: System tray integration.
//TODO: File picker.
//TODO: Focus window (makeKeyAndOrderFront / SetActiveWindow / gtk_window_present).
//TODO: Notifications (make it a superset of the HTML5 API so it can be shimmed).
//TODO: Make sure the HTML5 Fullscreen API works.

#ifdef __cplusplus
extern "C" {
#endif

// A reference to a window.
typedef struct _tether *tether;

// Configuration options for a window.
typedef struct tether_options {
    size_t initial_width,
           initial_height,
           minimum_width,
           minimum_height;
    bool borderless,
         debug;
    // The data to pass to event handlers.
    void *data;
    // The window received a message via `window.tether(string)`.
    void (*message)(void *data, const char *message);
    // The window was closed, and its resources have all been released.
    void (*closed)(void *data);
} tether_options;

// Start the main loop and call the given function.
//
// This function should be called on the main thread, and at most once. It
// should be called before any other `tether` function is called.
void tether_start(void (*func)(void));
// Schedule a function to be called on the main thread.
//
// All the `tether` functions should only be called on the main thread.
void tether_dispatch(void *data, void (*func)(void *data));
// Stop the main loop as gracefully as possible.
void tether_exit(void);

// Open a new window with the given options.
tether tether_new(tether_options opts);

// Eventually run the given script.
void tether_eval(tether self, const char *js);
// Eventually display the given HTML.
void tether_load(tether self, const char *html);
// Set the window's title.
void tether_title(tether self, const char *title);
// Eventually close the window.
void tether_close(tether self);

#ifdef __cplusplus
}
#endif
