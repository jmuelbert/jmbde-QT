{ pkgs, treefmtEval, ... }:
{
  src = ./.;
  hooks = {
    check-added-large-files.enable = true;
    check-builtin-literals.enable = true;
    check-case-conflicts.enable = true;
    check-executables-have-shebangs.enable = true;

    # todo Not integrated with Nix?
    check-format = {
      enable = true;
      entry = "${treefmtEval.config.build.wrapper}/bin/treefmt --fail-on-change";
    };

    check-json.enable = true;
    check-shebang-scripts-are-executable.enable = true;
    check-toml.enable = true;
    check-xml.enable = true;
    check-yaml.enable = true;
    deadnix.enable = true;
    detect-private-keys.enable = true;
    editorconfig-checker.enable = true;
    end-of-file-fixer.enable = true;
    fix-byte-order-marker.enable = true;
    flake-checker.enable = true;
    forbid-new-submodules.enable = true;
    mixed-line-endings.enable = true;
    nil.enable = true;

    strip-location-metadata = {
      name = "Strip location metadata";
      description = "Strip gelocation metadata from image files";
      enable = true;
      entry = "${pkgs.exiftool}/bin/exiftool --duplicates --overwrite_original '-gps*='";
      package = pkgs.exiftool;
      types = [ "image" ];
    };
    trim-trailing-whitespace.enable = true;
    yamllint.enable = true;
  };
}
