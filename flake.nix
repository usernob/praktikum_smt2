{
  description = "meson and ninja build tools";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShell = pkgs.mkShell {
          name = "meson-ninja";

          packages = with pkgs; [
            meson
            ninja
            libgcc
            valgrind
            clang-tools
            tmux
          ];

          shellHook = ''
            clear
            echo "wellcome"
            echo "ini dev environment yang berisi gcc, clang-tools, meson, ninja, valgrind, tmux"
          '';
        };
      }
    );
}
