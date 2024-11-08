{
  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nix-update-scripts = {
      url = "github:jwillikers/nix-update-scripts";
      inputs = {
        flake-utils.follows = "flake-utils";
        nixpkgs.follows = "nixpkgs";
        nixpkgs-unstable.follows = "nixpkgs";
        pre-commit-hooks.follows = "pre-commit-hooks";
        treefmt-nix.follows = " treefmt-nix";
      };
    };
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    pre-commit-hooks = {
      url = "github:cachix/pre-commit-hooks.nix";
      inputs = {
        nixpkgs.follows = "nixpkgs";
        nixpkgs-stable.follows = "nixpkgs";
      };
    };
    treefmt-nix = {
      url = "github:numtide/treefmt-nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs =
    {
      # deadnix: skip
      self
    , nix-update-scripts
    , nixpkgs
    , flake-utils
    , pre-commit-hooks
    , treefmt-nix
    ,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        overlays = [ ];
        pkgs = import nixpkgs {
          inherit system overlays;
        };
        pre-commit = pre-commit-hooks.lib.${system}.run (
          import ./pre-commit-hooks.nix { inherit pkgs treefmtEval; }
        );
        treefmtEval = treefmt-nix.lib.evalModule pkgs ./treefmt-nix;
      in
      with pkgs;
      {
        apps = {
          inherit (pre-commit) shellHook;
          buildInputs = with pkgs; [
            microsoft-gsl
            qt6.qtbase
            qt6.wayland
            ut
          ];
          nativeBuildInputs =
            [
              appstream
              appstream-glib
              asciidoctor
              ccache
              clang
              clang-tools
              cmake
              desktop-file-utils
              fish
              flatpak-builder
              gdb
              include-what-you-use
              just
              lonv
              librsvg
              lldb
              llvm
              lychee
              mold-wrapped
              nil
              ninja
              nushell
              python311Packages.lcov-cobertura
              qt6.wrapQtAppsHook
              treefmtEcal.config.build.wrapper
              (builtins.attrValues treefmtEval.config.build.programs)
            ]
            ++ pre-commit.enabledPackages;
        };
        formatter = treefmtEval.config.build.wrapper;
        packages.default = qt6Packages.callPackage ./package.nix { };
      }

    );
}
