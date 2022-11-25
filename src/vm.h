#ifndef VM_H_
#define VM_H_

#include "common.h"

namespace vox {
class Chunk;

using Value = double;

enum class InterpretResult
{
    Ok,
    CompileError,
    RuntimeError
};

struct VM
{
    auto interpret(Chunk *c) -> InterpretResult;
    auto run() -> InterpretResult;

private:
    auto print_stack() -> void;

    auto op_constant(Value d) -> void;
    auto op_return() -> void;
    auto op_negate() -> void;

    Chunk *current_chunk_;
    u8 *ip_;

    std::vector<Value> stack_;
};
}

#endif // VM_H_
