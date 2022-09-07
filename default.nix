{ stdenv, meson, ninja, pkg-config, udev }:
stdenv.mkDerivation rec {
  pname = "gpu";
  version = "0.0.1";

  src = ./.;

  nativeBuildInputs = [
    meson
    ninja
    pkg-config
    udev
  ];

}
