{
  description = "A stonking great language";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, ... }@inputs: inputs.utils.lib.eachSystem [
    "x86_64-linux" "i686-linux" "aarch64-linux" "x86_64-darwin"
  ] (system: let pkgs = import nixpkgs {
                   inherit system;
                   overlays = [];
                   # config.allowUnfree = true;
                 };
             in {
               devShell = pkgs.mkShell rec {
                 # Update the name to something that suites your project.
                 name = "voxpp";

                 packages = with pkgs; [
                   # Development Tools
                   llvmPackages_11.clang
                   cmake
                   cmakeCurses
                   # Libs
                   spdlog
                   argparse
                 ];

                 # Setting up the environment variables you need during
                 # development.
                 shellHook = let
                   icon = "f121";
                 in ''
                    export PS1="$(echo -e '\u${icon}') {\[$(tput sgr0)\]\[\033[38;5;228m\]\w\[$(tput sgr0)\]\[\033[38;5;15m\]} (${name}) \\$ \[$(tput sgr0)\]"
                 '';
               };


               defaultPackage = pkgs.callPackage ./default.nix {} ;
              });
}
