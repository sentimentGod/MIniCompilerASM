#include "FirstSecondStage.h"
#include "MachineCode.h"


int main() {
    LoadFromFile("test.asm");
    LexemeSyntax("test.asm" , true);
    createAllLst("test.asm");

    return 0;
}
