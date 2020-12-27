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
void UISetGridRowSpacing(UI grid, int size);
void UISetGridColumnSpacing(UI grid, int size);
void UIAttach(UI grid, UI child, int x, int y, int width, int height);
// Box
UI UICreateHBox(void);
UI UICreateVBox(void);
void UISetBoxSpacing(UI box, int spacing);
// Stack
UI UICreateStack();
UI UICreateStackSwitcher(UI stack);
void UIStackSwitcherSetStack(UI switcher, UI stack);
void UIStackAdd(UI stack, UI widget, const char * name);
void UIStackAddTitled(UI stack, UI widget, const char * name, const char * title);
void UIStackVisibleName(UI stack, const char * name);
void UIStackVisibleChild(UI stack, UI widget);
// Button
UI UICreateButton(const char* title);
// Label
UI UICreateLabel(const char* text);
// Slider
UI UICreateVSlider(double min, double max, double step);
UI UICreateHSlider(double min, double max, double step);
double UIGetSliderValue(UI slider);
void UISetSliderValue(UI slider, double value);
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