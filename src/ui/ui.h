
#ifndef DOWNLOADMANAGER_UI_H
#define DOWNLOADMANAGER_UI_H

#include <unordered_map>


namespace gfx {

    //possible states the ui can end up in over the lifetime of the program
    enum class UI_STATE{
        LOGIN,
        MAIN,
        SETTINGS,
    };

    //something like a manager for the UI
    class UserInterface {
    public:
        UserInterface() = default;
        ~UserInterface() = default;

        //TODO: build a ui cache? in the Init() function
        //Initialize UI
        bool Init();

        //draw the current ui
        void DrawUI(UI_STATE state);

    private:
        //state os ui
    };

}


#endif //DOWNLOADMANAGER_UI_H
