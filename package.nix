{ cmake
, microsoft-gsl
, modl-wrapped
, ninja
, qtbase
, qtwayland
, stdenv
, ut
, wrapQtAppsHook
,
};
stdenv.mkDerivation = {
pname = "jmbde";
version = "0.7.0";

src ) ./.

buildInputs =[
microsoft-gsl
qtbase
qtwayland
ut
];

nativeBuildInputs = [
cmake
mold-wrapped
ninja
wrapQtAppsHook
];

cmakeFlags = [
"--preset=minimal"
"-DCMAKE_LINKER_TYPE=MOLD"
];
}
