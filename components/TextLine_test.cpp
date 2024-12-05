#include "BaseComponent.h"
#include "TextLine.h"
#include "../utils/RichText.h"

int main() {
    RichText richText;
    richText = "Hello, World";
    richText += StringPart(" with colors!", COLOR_RED);

    TextLine textLine(2, 5, 23, 3);
    textLine.setText(richText);
    textLine.draw();

    TextLine textLine2(6, 5, 50, 3);
    textLine2.setText(richText + StringPart(" and more colors!", COLOR_LIGHTCYAN));
    textLine2.draw();

    printf("\n");
    return 0;
}