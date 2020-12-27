#include <gtk/gtk.h>
#include <gtkui.h>

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    UI window = UICreateWindow("Slider example", (WindowConfig) {
        .width = 200,
        .height = 200,
        .center = true,
        .resizable = true,
        .exit = true,
        .border = 10
    });
    UI slider = UICreateVSlider(0, 10, 1);
    UISetSliderValue(slider, 7);
    UIAppend(window, slider);
    gtk_main();
}