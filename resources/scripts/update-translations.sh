set -eu -o pipefail

readonly COMMIT_MSG="update translation files for jmbde"
readonly LUPDATE_CMD="lupdate src -no-obsolete -locations none -ts"

if [[ "$@" = "ALL" ]]
then
    for localization in localizations/*.ts
    do
        $LUPDATE_CMD "$localization"
    done

    git add localizations/*.ts
    git commit -m "$COMMIT_MSG"
else
    $LUPDATE_CMD "$@"
fi