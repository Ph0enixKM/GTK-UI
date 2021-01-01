#include "gtkui.h"

UI UICreateWindow(const char* title, const WindowConfig cfg) {
    UI window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), title);
    if (cfg.width != 0 && cfg.height != 0) {
        gtk_window_set_default_size(GTK_WINDOW(window), cfg.width, cfg.height);
    }
    gtk_window_set_resizable(GTK_WINDOW(window), cfg.resizable);
    if (cfg.center) {
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    }
    if (cfg.border) {
        gtk_container_set_border_width(GTK_CONTAINER(window), cfg.border);
    }
    if (cfg.exit) {
        g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    }
    gtk_widget_show(window);
    return window;
}

void UILoadCSS(const char* filename) {
    const int size = 1024;
    static bool notry = true;
    GtkCssProvider* provider = gtk_css_provider_new();
    GdkDisplay* display = gdk_display_get_default();
    GdkScreen* screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    GError* error = 0;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(filename), &error);
    g_object_unref(provider);
    #ifndef _WIN32
    if (error && notry) {
        char result[size];
        ssize_t count = readlink("/proc/self/exe", result, 1024);
        if (count != -1) {
            char* path = dirname(result);
            notry = false;
            UILoadCSS(path);
        }
    }
    #else
    if (error && notry) {
        char* path = malloc(size * sizeof(char));
        memset(path, 0, size);
        DWORD result = GetModuleFileName(0, path, size - 1);
        notry = false;
        if (!result) {
            free(path);
            path = 0;
        }
        else {
            UILoadCSS(path);
        }
    }
    #endif
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

void UIAppend(UI parent, UI child) {
    gtk_container_add(GTK_CONTAINER(parent), child);
    gtk_widget_show(child);
}

void UIRemove(UI parent, UI child) {
    gtk_container_remove(GTK_CONTAINER(parent), child);
}

void UIShow(UI widget) {
    gtk_widget_show(widget);
}

void UIHide(UI widget) {
    gtk_widget_hide(widget);
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
    GError* err = NULL;
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

void UISetGridRowSpacing(UI grid, int size) {
    gtk_grid_set_row_spacing(GTK_GRID(grid), size);
}

void UISetGridColumnSpacing(UI grid, int size) {
    gtk_grid_set_column_spacing(GTK_GRID(grid), size);
}

void UIGridRemoveRow(UI grid, int position) {
    gtk_grid_remove_row(GTK_GRID(grid), position);
}

void UIGridRemoveColumn(UI grid, int position) {
    gtk_grid_remove_column(GTK_GRID(grid), position);
}

void UIAttach(UI grid, UI child, int x, int y, int width, int height) {
    gtk_grid_attach(GTK_GRID(grid), child, x, y, width, height);
    gtk_widget_show(child);
}

UI UICreateHBox(void) {
    return gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
}

UI UICreateVBox(void) {
    return gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
}

void UISetBoxSpacing(UI box, int spacing) {
    gtk_box_set_spacing(GTK_BOX(box), spacing);
}

UI UICreateStack() {
    return gtk_stack_new();
}

UI UICreateStackSwitcher(UI stack) {
    UI switcher = gtk_stack_switcher_new();
    if (stack) {
        UIStackSwitcherSetStack(switcher, stack);
    }
    return switcher;
}

void UIStackSwitcherSetStack(UI switcher, UI stack) {
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(stack));
}

void UIStackAdd(UI stack, UI widget, const char* name) {
    gtk_stack_add_named(GTK_STACK(stack), widget, name);
    gtk_widget_show(widget);
}

void UIStackAddTitled(UI stack, UI widget, const char* name, const char* title) {
    gtk_stack_add_titled(GTK_STACK(stack), widget, name, title);
}

void UIStackVisibleName(UI stack, const char* name) {
    gtk_stack_set_visible_child_name(GTK_STACK(stack), name);
}

void UIStackVisibleChild(UI stack, UI widget) {
    gtk_stack_set_visible_child(GTK_STACK(stack), widget);
}

UI UICreateButton(const char* title) {
    UI button = gtk_button_new_with_mnemonic(title);
    return button;
}

UI UICreateLabel(const char* text) {
    return gtk_label_new(text);
}

UI UICreateEntry(const char* placeholder) {
    UI entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), placeholder);
    return entry;
}

const char* UIGetEntryValue(UI entry) {
    return gtk_entry_get_text(GTK_ENTRY(entry));
}

unsigned UIGetEntryLength(UI entry) {
    return gtk_entry_get_text_length(GTK_ENTRY(entry));
}

void UISetEntryValue(UI entry, const char* text) {
    gtk_entry_set_text(GTK_ENTRY(entry), text);
}

UI UICreateVSlider(double min, double max, double step) {
    return gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, min, max, step);
}

UI UICreateHSlider(double min, double max, double step) {
    return gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, min, max, step);
}

double UIGetSliderValue(UI slider) {
    return gtk_range_get_value(GTK_RANGE(slider));
}

void UISetSliderValue(UI slider, double value) {
    gtk_range_set_value(GTK_RANGE(slider), value);
}

UI UICreateScrollView(bool scrollx, bool scrolly) {
    UI sv = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sv), (scrollx ? GTK_POLICY_AUTOMATIC : GTK_POLICY_NEVER), (scrolly ? GTK_POLICY_AUTOMATIC : GTK_POLICY_NEVER));
    return sv;
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
