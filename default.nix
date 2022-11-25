{ lib
, stdenv
, cmake
, ninja
, spdlog
, argparse
}:

stdenv.mkDerivation rec {
  pname = "cpp-examples";
  version = "0.1.0";

  src = ./.;

  nativeBuildInputs = [ cmake ];
  buildInputs = [
    spdlog
    argparse
  ];

  cmakeFlags = [
    "-DENABLE_TESTING=OFF"
   "-DENABLE_INSTALL=OFF"
    "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
  ];

  postBuild = ''
                mkdir -p $out/
                cp compile_commands.json $out/compile_commands.json
              '';

  installPhase = ''
                  cp voxlang $out/voxlang;
                  '';


  meta = with lib; {
    homepage = "https://github.com/danvonk";
    description = ''
        xyz
          '';
    licencse = licenses.mit;
    platforms = with platforms; linux ++ darwin;
    maintainers = [ maintainers.danvonk ];
  };
}
