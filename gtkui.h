#ifndef GTKUI
#define GTKUI

#include <gtk/gtk.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef GtkWidget* UI;

typedef struct {
    int width;
    int height;
    bool center;
    bool resizable;
    int border;
} WindowConfig;

#define UIEvent(instance, signal, handler, ...) g_signal_connect(G_OBJECT(instance), (signal), G_CALLBACK(handler), __VA_ARGS__)
UI UICreateWindow(const char* title, const WindowConfig cfg);
void UILoadCSS(const char* filename);
void UILoadCSSData(const char* data);
void UIAppend(UI parent, UI current);
void UISetID(UI widget, const char* name);
void UIAddClass(UI widget, const char* name);
bool UIHasClass(UI widget, const char* name);
void UIRemoveClass(UI widget, const char* name);
UI UICreateImage(const char* filename);
GdkPixbuf* UILoadImageData(const char* filename);
UI UILoadImage(GdkPixbuf* pixelbuffer);
UI UICreateGrid(bool homogeneous);
void UIAttach(UI grid, UI child, int x, int y, int width, int height);
UI UICreateBox(char orientation);
UI UICreateButton(const char* title, void* action);
UI UICreateLabel(const char* text);
void UIError(const char* message);
void UIWarning(const char* message);
void UIPrint(const char* message);

#endif