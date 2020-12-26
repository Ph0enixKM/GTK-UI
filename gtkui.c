#include "gtkui.h"

UI UICreateWindow(const char* title, const WindowConfig cfg) {
    UI window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), cfg.width, cfg.height);
    gtk_window_set_resizable(GTK_WINDOW(window), cfg.resizable);
    if (cfg.center) {
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    }
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show(window);
    return window;
}

void UILoadCSS(const char* filename) {
    static bool notry = true;
    GtkCssProvider* provider = gtk_css_provider_new();
    GdkDisplay* display = gdk_display_get_default();
    GdkScreen* screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    GError* error = 0;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(filename), &error);
    g_object_unref(provider);
    if (error && notry) {
        char result[1024];
        ssize_t count = readlink("/proc/self/exe", result, 1024);
        if (count != -1) {
            char* path = dirname(result);
            notry = false;
            UILoadCSS(path);
        }
    }
}

void UILoadCSSData(const char* data) {
    GtkCssProvider* provider;
    GdkDisplay* display;
    GdkScreen* screen;
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    GError* error = NULL;
    gtk_css_provider_load_from_data(provider, data, strlen(data), &error);
    g_object_unref(provider);
}

void UIAppend(UI parent, UI current) {
    gtk_container_add(GTK_CONTAINER(parent), current);
    gtk_widget_show(current);
}

void UISetID(UI widget, const char* name) {
    gtk_widget_set_name(widget, name);
}

void UIAddClass(UI widget, const char* name) {
    GtkStyleContext* ctx = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(ctx, name);
}

bool UIHasClass(UI widget, const char* name) {
    GtkStyleContext* ctx = gtk_widget_get_style_context(widget);
    return gtk_style_context_has_class(ctx, name);
}

void UIRemoveClass(UI widget, const char* name) {
    GtkStyleContext* ctx = gtk_widget_get_style_context(widget);
    gtk_style_context_remove_class(ctx, name);
}

UI UICreateImage(const char* filename) {
    return gtk_image_new_from_file(filename);
}

GdkPixbuf* UILoadImageData(const char* filename) {
    GError* err;
    return gdk_pixbuf_new_from_file(filename, &err);
}

UI UILoadImage(GdkPixbuf* pixelbuffer) {
    return gtk_image_new_from_pixbuf(pixelbuffer);
}

UI UICreateGrid(bool homogeneous) {
    UI grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), homogeneous);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), homogeneous);
    return grid;
}

void UIAttach(UI grid, UI child, int x, int y, int width, int height) {
    gtk_grid_attach(GTK_GRID(grid), child, x, y, width, height);
}

UI UICreateBox(char orientation) {
    UI box = NULL;
    switch (orientation) {
        case '-':
            box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
            break;
        case '|':
            box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            break;
        default:
            box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            break;
    }
    return box;
}

UI UICreateButton(const char* title, void* action) {
    UI button = gtk_button_new_with_mnemonic(title);
    if (action != NULL) {
        UIEvent(button, "clicked", action, NULL);
    }
    return button;
}

UI UICreateLabel(const char* text) {
    return gtk_label_new(text);
}

void UIError(const char* message) {
    UI dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        "%s",
        message
    );
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void UIWarning(const char* message) {
    UI dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_WARNING,
        GTK_BUTTONS_OK,
        "%s",
        message
    );
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void UIPrint(const char* message) {
    UI dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "%s",
        message
    );
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
