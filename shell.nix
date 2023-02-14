with import <nixpkgs> {};
stdenv.mkDerivation {
    name = "BMP_lib";
    nativeBuildInputs = [pkg-config];
    buildInputs = [
    gcc
    meson
    ninja
    ];
}
