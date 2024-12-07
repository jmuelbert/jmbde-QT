_: {
  config = {
    programs = {
      actionlint.enable = true;
      clang-format.enable = true;
      cmake-format.enable = true;
      jsonfmt.enable = true;
      nixfmt.enable = true;
      statix.enable = true;
      taplo.enable = true;
      typos.enable = true;
      yamlfmt.enable = true;
    };
    projectRootFile = "flake.nix";
    settings.formatter = {
      typos.excludes = [
        "*.avif"
        "*.bmp"
        "*.gif"
        "*.jpeg"
        "*jpg"
        "*.png"
        "*.svg"
        "*.tiff"
        "*.webp"
        ".vscode/settings.json"
      ];
    };
  };
}
