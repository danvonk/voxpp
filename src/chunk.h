#ifndef CHUNK_H_
#define CHUNK_H_

#include <variant>
#include <vector>
#include <string_view>

namespace vox {
struct OpReturn {};
struct OpConstant {
    double d;
};
struct OpNegate {};
struct OpAdd {};
struct OpSubtract {};
struct OpMultiply {};
struct OpDivide {};

using Operations = std::variant
    <
    OpReturn,
    OpConstant,
    OpNegate,
    OpAdd,
    OpSubtract,
    OpMultiply,
    OpDivide
    >;

template <typename T>
struct OpCodeMetadata {
};

template<>
struct OpCodeMetadata<OpReturn> {
    static constexpr std::string_view name = "Return";
};

template<>
struct OpCodeMetadata<OpConstant> {
    static constexpr std::string_view name = "Constant";
};

template<>
struct OpCodeMetadata<OpNegate> {
    static constexpr std::string_view name = "Negate";
};

template<>
struct OpCodeMetadata<OpAdd> {
    static constexpr std::string_view name = "Add";
};
template<>
struct OpCodeMetadata<OpSubtract> {
    static constexpr std::string_view name = "Subtract";
};
template<>
struct OpCodeMetadata<OpMultiply> {
    static constexpr std::string_view name = "Multiply";
};
template<>
struct OpCodeMetadata<OpDivide> {
    static constexpr std::string_view name = "Divide";
};




struct Chunk {
    std::vector<Operations> operations;
    std::vector<double> constants;
    std::vector<int> lines;
};

}


#endif // CHUNK_H_
