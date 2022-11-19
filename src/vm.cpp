#include "vm.h"

#include "chunk.h"

#include <iostream>

auto VM::interpret(Chunk *c) -> InterpretResult
{
    current_chunk_ = c;
    return run();
}

auto VM::run() -> InterpretResult
{
    bool done = false;
    InterpretResult code = InterpretResult::Ok;

    for (auto op : current_chunk_->operations) {
        code = std::visit(
            [&done](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, OpReturn>) {
                    return InterpretResult::Ok;
                } else if constexpr (std::is_same_v<T, OpConstant>) {
                    auto data = static_cast<OpConstant &&>(arg);
                    std::cout << data.d << '\n';
                    return InterpretResult::Ok;
                } else {
                    return InterpretResult::CompileError;
                }
            },
            op);
    }
    return code;
}
