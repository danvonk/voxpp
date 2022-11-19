#ifndef CHUNK_H_
#define CHUNK_H_

#include <variant>
#include <vector>
#include <string>


struct OpReturn {};
struct OpConstant {
    double d;
};

using Operations = std::variant
    <
    OpReturn,
    OpConstant
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


struct Chunk {
    std::vector<Operations> operations;
    std::vector<double> constants;
    std::vector<int> lines;
};



#endif // CHUNK_H_
