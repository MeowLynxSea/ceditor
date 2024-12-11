#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

class BaseComponent {
protected:
    int top, left, width, height;
    bool focused;

public:
    BaseComponent(int top, int left, int width, int height) : top(top), left(left), width(width), height(height) {};
    virtual ~BaseComponent() {};

    void setTop(int top) {
        this->top = top;
    }
    void setLeft(int left) {
        this->left = left;
    }
    void setWidth(int width) {
        this->width = width;
    }
    void setHeight(int height) {
        this->height = height;
    }

    int getTop() {
        return top;
    }
    int getLeft() {
        return left;
    }
    int getWidth() {
        return width;
    }
    int getHeight() {
        return height;
    }

    void setFocused(bool focused) {
        this->focused = focused;
    }

    void setPosition(int top, int left) {
        this->top = top;
        this->left = left;
    }
    void setSize(int width, int height) {
        this->width = width;
        this->height = height;
    }
    void setBounds(int top, int left, int width, int height) {
        this->top = top;
        this->left = left;
        this->width = width;
        this->height = height;
    }

    virtual void draw() = 0;
    virtual void onKeyPress(int key) = 0;
};

#endif // BASE_COMPONENT_H