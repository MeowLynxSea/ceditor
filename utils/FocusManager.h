#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H


#include "../mystl/my_vector.h"
#include "../components/BaseComponent.h"

class FocusManager {
private:
    MyVector<BaseComponent*> components;

public:
    FocusManager();
    ~FocusManager() {
        components.clear();
    }

    void addComponent(BaseComponent* component) {
        components.push_back(component);
    }

    void removeComponent(BaseComponent* component) {
        for(int i = 0; i < components.size(); i++) {
            if(components[i] == component) {
                components.erase(i);
                break;
            }
        }
    }

    void setFocus(BaseComponent* component) {
        if(component->isFocused()) return;
        for(int i = 0; i < components.size(); i++) {
            components[i]->setFocus(false);
        }
        component->setFocus(true);
    }

    BaseComponent* getFocusedComponent() {
        for(int i = 0; i < components.size(); i++) {
            if(components[i]->isFocused()) return components[i];
        }
        return NULL;
    }
};

#endif