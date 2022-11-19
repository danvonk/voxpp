#ifndef VM_H_
#define VM_H_

#include "common.h"

class Chunk;

enum class InterpretResult {
    Ok,
    CompileError,
    RuntimeError
};

struct VM {
    auto interpret(Chunk* c) -> InterpretResult;
    auto run() -> InterpretResult;
private:
    Chunk* current_chunk_;
    u8* ip_;
};

#endif // VM_H_
