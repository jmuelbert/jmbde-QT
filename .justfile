default: build

alias b := build

build preset="dev" target="all":
    cmake --build --preset {{ preset }} --target {{ target }}

alias ch := check

check: && format
    yamllint .
    asciidoctor *.adoc
    lychee --cache *.html

alias c := configure

configure preset="dev":
    cmake --preset {{ preset }}

alias d := debug

# todo Parse build directory from preset.
debug preset="dev" debugger="gdb": (build preset)
    {{ debugger }} build/src/cyrillic-encoder

flatpak:
    flatpak-builder \
        --force-clean \
        --install \
        --install-deps-from=flathub \
        --repo=repo \
        --user \
        build-dir \
        packaging/com.jwillikers.CyrillicEncoder.yaml

alias f := format
alias fmt := format

format:
    treefmt

alias r := run

# todo Parse build directory from preset.
run preset="dev": (build preset)
    build/src/cyrillic-encoder

alias p := package
alias pack := package

package:
    nix build

alias t := test

test preset="dev": build
    ctest --preset {{ preset }}

alias u := update
alias up := update

update:
    nix flake update

alias w := workflow

workflow preset="dev" *flags="":
    cmake --workflow --preset {{ preset }} {{ flags }}
