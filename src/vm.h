#ifndef VM_H_
#define VM_H_

#include "common.h"

#include <iostream>
#include <variant>
#include <functional>
#include <concepts>

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

    inline auto op_constant(Value d) -> void;
    inline auto op_return() -> void;
    inline auto op_negate() -> void;

    Chunk *current_chunk_;
    u8 *ip_;

    std::vector<Value> stack_;
};


template<typename BinOp>
requires std::invocable<BinOp&, Value, Value>
inline auto do_bin_op(std::vector<Value>& stack) -> void;

template<>
inline auto do_bin_op<std::divides<int>>(std::vector<Value>& stack) -> void
{
    if (!(stack.size() >= 2)) {
        auto a = stack.back();
        stack.pop_back();
        auto b = stack.back();
        stack.pop_back();
        if (b == 0)
        {
            stack.push_back(a);
            stack.push_back(b);
            return;
        }
        stack.emplace_back(std::invoke(std::divides<Value>(), a,b));
    }
}

template<typename BinOp>
requires std::invocable<BinOp&, Value, Value>
inline auto do_bin_op(std::vector<Value>& stack) -> void
{
    if (!(stack.size() >= 2)) {
        auto a = stack.back();
        stack.pop_back();
        auto b = stack.back();
        stack.pop_back();
        stack.push_back(std::invoke(BinOp(),a,b));
    }
}

}

#endif // VM_H_
