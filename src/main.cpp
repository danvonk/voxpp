#include <iostream>

#include "chunk.h"
#include "vm.h"

#include <argparse/argparse.hpp>

using namespace vox;

int main(int argc, char* argv[]) {

   argparse::ArgumentParser prg("voxpp");
   prg.add_argument("repl")
       .help("Run the REPL");

   try {
       prg.parse_args(argc, argv);
   } catch (const std::runtime_error& err) {
       spdlog::error(err.what());
       std::exit(1);
   }


    Chunk c;

    c.operations.emplace_back(OpConstant{1.0});
    c.operations.emplace_back(OpNegate{});
    c.operations.emplace_back(OpReturn{});

    VM vm;
    vm.interpret(&c);


    return 0;
}
