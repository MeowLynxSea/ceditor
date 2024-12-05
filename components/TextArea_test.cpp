#include "BaseComponent.h"
#include "TextArea.h"
#include "../utils/RichText.h"

int main() {
    RichText richText;
    richText = "Hello, World";
    richText += StringPart(" with colors!", COLOR_RED);
    richText += " And more text.";
    richText += StringPart(" And more more more text.", COLOR_GREEN);
    richText += " And more more more more more text.";
    richText += StringPart(" And more more more more more more text.", COLOR_BLUE);
    richText += " And more more more more more more more text.";
    richText += StringPart(" And more more more more more more more more text.", COLOR_YELLOW);
    richText += " And more more more more more more more more more text.";
    richText += StringPart(" And more more more more more more more more more more text.", COLOR_CYAN);

    TextArea textArea(3, 3, 40, 5, richText);
    textArea.draw();

    printf("\n");
    return 0;
}