#include "components/BaseComponent.h"
#include "components/TextLine.h"
#include "utils/RichText.h"

int main() {
    RichText richText;
    richText = "Hello, World";
    richText += StringPart(" with colors!", COLOR_RED);

    TextLine textLine(2, 2, 23, 3);
    textLine.setText(richText);
    textLine.draw();

    TextLine textLine2(7, 5, 40, 3);
    textLine2.setText(richText + StringPart(" and more colors!", COLOR_LIGHTCYAN));
    textLine2.draw();

    printf("\n");
    return 0;
}