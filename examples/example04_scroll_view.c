#include <gtkui.h>

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    UILoadCSSData(
        "#title {"
        "   font-size: 30px;"
        "}"
        ".item {"
        "   margin-top:50px;"
        "}"
        "#scroll {"
        "   background: rgba(0, 0, 0, 0.1)"
        "}"
    );
    UI window = UIWindow("Title", .width = 300, .height = 200, .exit = true, .resizable = true, .center = true);
    UI grid = UICreateGrid(true);

    UI scroll = UICreateScrollView(false, true);
    UISetID(scroll, "scroll");

    UI title = UICreateLabel("Shopping list:");
    UI box = UICreateVBox();
    UI item1 = UICreateLabel("Make an appointment with a barber");
    UI item2 = UICreateLabel("Buy a gift for my sister's birthday");
    UI item3 = UICreateLabel("Go to the gym");
    UISetID(title, "title");
    UIAddClass(item1, "item");
    UIAddClass(item2, "item");
    UIAddClass(item3, "item");

    UIAppend(scroll, box);
    UIAppend(box, item1);
    UIAppend(box, item2);
    UIAppend(box, item3);
    UIAttach(grid, title, 0, 0, 1, 1);
    UIAttach(grid, scroll, 0, 1, 1, 1);
    UIAppend(window, grid);

    gtk_main();
}

