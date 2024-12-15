#ifndef EDITOR_H
#define EDITOR_H

#include "BaseComponent.h"
#include "TextArea.h"

class Editor : public BaseComponent {
private:
    TextArea* textArea;
};

#endif