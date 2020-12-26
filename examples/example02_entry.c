#include <gtk/gtk.h>
#include <gtkui.h>

void onclick(UI button, UI entry) {
    const char* val = UIGetEntryValue(entry);
    UIPrint(val);
    UISetEntryValue(entry, "");
}

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    UI window = UICreateWindow("Entry Example", (WindowConfig) {
        .width = 200,
        .height = 50,
        .center = true,
        .resizable = true,
        .border = 10
    });
    UI box = UICreateBox('|');
    UI entry = UICreateEntry("Type some text");
    UI button = UICreateButton("Show and clear", NULL);
    UIAppend(box, entry);
    UIAppend(box, button);
    UIAppend(window, box);

    UIEvent(button, "clicked", onclick, entry);
    gtk_main();
}
