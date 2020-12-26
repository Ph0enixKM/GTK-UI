#include <gtk/gtk.h>
#include <gtkui.h>

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    UI window = UICreateWindow("Hello world", (WindowConfig) {
        .border = 10,
        .center = true,
        .height = 200,
        .width = 300,
        .resizable = false
    });
    UI label = UICreateLabel("Hello world");
    UIAppend(window, label);
    gtk_main();
}
