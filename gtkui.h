#ifndef GTKUI
#define GTKUI

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>

GtkWidget* UICreateWindow(const char* title, const WindowConfig cfg);
void UILoadCSS(const char* filename);
void UILoadCSSData(const char* data);
void UIAppend(GtkWidget* parent, GtkWidget* current);
void UISetID(GtkWidget* widget, const char* name);
void UIAddClass(GtkWidget* widget, const char* name);
bool UIHasClass(GtkWidget* widget, const char* name);
void UIRemoveClass(GtkWidget* widget, const char* name);
GtkWidget* UICreateImage(const char* filename);
GdkPixbuf* UILoadImageData(const char* filename);
GtkWidget* UILoadImage(GdkPixbuf* pixelbuffer);
GtkWidget* UICreateGrid(bool homogeneous);
void UIAttach(GtkWidget* grid, GtkWidget* child, int x, int y, int width, int height);
GtkWidget* UICreateBox(char orientation);
GtkWidget* UICreateButton(const char* title, void* action);
GtkWidget* UICreateLabel(const char* text);
void UIError(const char* message);
void UIWarning(const char* message);
void UIPrint(const char* message);

#endif