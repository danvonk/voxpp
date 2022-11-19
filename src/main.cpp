#include <iostream>


#include "chunk.h"
#include "vm.h"


int main() {
    Chunk c;

    c.operations.emplace_back(OpConstant{1.0});
    c.operations.emplace_back(OpReturn{});

    VM vm;
    vm.interpret(&c);


    return 0;
}
