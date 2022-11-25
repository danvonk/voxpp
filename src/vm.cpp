#include "vm.h"

#include "chunk.h"
// #include "config.h"

#include <iostream>
#include <variant>

using namespace vox;

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
        // if constexpr (cfg::debugTrace)
        //     print_stack();

        code = std::visit(
            [this](auto &&arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, OpReturn>) {
                    op_return();
                    return InterpretResult::Ok;
                } else if constexpr (std::is_same_v<T, OpConstant>) {
                    auto data = static_cast<OpConstant &&>(arg);
                    op_constant(data.d);
                    return InterpretResult::Ok;
                } else if constexpr (std::is_same_v<T, OpNegate>) {
                    op_negate();
                    return InterpretResult::Ok;
                }
                return InterpretResult::CompileError;
            },
            op);
    }
    return code;
}


auto VM::print_stack() -> void
{
    if (stack_.empty())
        return;

    // spdlog::info("[");
    for (auto x : stack_)
    {
        // spdlog::info(x);
    }
    // spdlog::info("]");
}

auto VM::op_constant(Value d) -> void
{
    stack_.push_back(d);
}

 auto VM::op_return() -> void
 {
     if (!stack_.empty())
         stack_.pop_back();
 }

auto VM::op_negate() -> void
{
    if (!stack_.empty())
    {
        auto d = stack_.back();
        stack_.pop_back();
        stack_.push_back(-d);
    }
}
