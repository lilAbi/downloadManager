#ifndef DOWNLOADMANAGER_UIELEMENT_H
#define DOWNLOADMANAGER_UIELEMENT_H



class UiElement{
public:

    UiElement() = default;
    ~UiElement() = default;

    //draw the base element
    virtual void DrawUi() = 0;
};



#endif //DOWNLOADMANAGER_UIELEMENT_H
