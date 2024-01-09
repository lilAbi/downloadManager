#ifndef DOWNLOADMANAGER_WINDOW_H
#define DOWNLOADMANAGER_WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <memory>

//represents a window object

class Window {
public:

    bool CreateWindow();
    void DestroyWindow();

    std::shared_ptr<GLFWwindow> GetWindowPtr() {return windowPtr;}

public:
    int windowWidth{1080};
    int windowHeight{720};
private:
    //handle to a glfw window object
    std::shared_ptr<GLFWwindow> windowPtr{nullptr};
};




#endif //DOWNLOADMANAGER_WINDOW_H
