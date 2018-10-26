set -eu -o pipefail

readonly COMMIT_MSG="update translation files for jmbde"
readonly LRELEASE_CMD="lrelease"

if [[ "$@" = "ALL" ]]
then
    for localization in localizations/*.ts
    do
        $LRELEASE_CMD "$localization"
    done

else
    $LRELEASE_CMD "$@"
fi