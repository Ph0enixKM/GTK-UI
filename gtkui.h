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
    bool exit;
} WindowConfig;

// Event Creation
#define UIEvent(instance, signal, handler, data) g_signal_connect(G_OBJECT(instance), (signal), G_CALLBACK(handler), data)
// Window
UI UICreateWindow(const char* title, const WindowConfig cfg);
#define UIWindow(title, ...) UICreateWindow(title, (WindowConfig){__VA_ARGS__});
// CSS
void UILoadCSS(const char* filename);
void UILoadCSSData(const char* data);
// Append
void UIAppend(UI parent, UI current);
// ID and classes
void UISetID(UI widget, const char* name);
void UIAddClass(UI widget, const char* name);
bool UIHasClass(UI widget, const char* name);
void UIRemoveClass(UI widget, const char* name);
// Image
UI UICreateImage(const char* filename);
GdkPixbuf* UILoadImageData(const char* filename);
UI UILoadImage(GdkPixbuf* pixelbuffer);
// Grid
UI UICreateGrid(bool homogeneous);
void UIAttach(UI grid, UI child, int x, int y, int width, int height);
// Box
UI UICreateHBox(void);
UI UICreateVBox(void);
void UISetBoxSpacing(UI box, int spacing);
// Button
UI UICreateButton(const char* title);
// Label
UI UICreateLabel(const char* text);
// Entry
UI UICreateEntry(const char* placeholder);
const char* UIGetEntryValue(UI entry);
unsigned UIGetEntryLength(UI entry);
void UISetEntryValue(UI entry, const char* text);
// Message Box
void UIError(const char* message);
void UIWarning(const char* message);
void UIPrint(const char* message);

#endif