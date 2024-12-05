#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

class BaseComponent {
protected:
    int top, left, width, height;

public:
    BaseComponent(int top, int left, int width, int height) : top(top), left(left), width(width), height(height) {};
    virtual ~BaseComponent() {};

    void setTop(int top);
    void setLeft(int left);
    void setWidth(int width);
    void setHeight(int height);

    int getTop();
    int getLeft();
    int getWidth();
    int getHeight();

    void setPosition(int top, int left);
    void setSize(int width, int height);
    void setBounds(int top, int left, int width, int height);

    virtual void draw() = 0;
    virtual void onKeyPress(int key) = 0;
};

#endif // BASE_COMPONENT_H