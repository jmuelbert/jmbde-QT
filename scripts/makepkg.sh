VERSION=$(defaults read "${BUILT_PRODUCTS_DIR}/${FULL_PRODUCT_NAME}/Contents/Info" CFBundleVersion)

PACKAGE_NAME=`echo "$PRODUCT_NAME" | sed "s/ /_/g"`
TMP1_ARCHIVE="${BUILT_PRODUCTS_DIR}/$PACKAGE_NAME-tmp1.pkg"
TMP2_ARCHIVE="${BUILT_PRODUCTS_DIR}/$PACKAGE_NAME-tmp2"
TMP3_ARCHIVE="${BUILT_PRODUCTS_DIR}/$PACKAGE_NAME-tmp3.pkg"
ARCHIVE_FILENAME="${BUILT_PRODUCTS_DIR}/${PACKAGE_NAME}.pkg"

pkgbuild --root "${INSTALL_ROOT}" \
    --component-plist "./Package/HelloWorldAppComponents.plist" \
    --scripts "./Package/Scripts" \
    --identifier "com.test.pkg.HelloWorld" \
    --version "$VERSION" \
    --install-location "/" \
    "${BUILT_PRODUCTS_DIR}/HelloWorld.pkg"
pkgbuild --root "${BUILT_PRODUCTS_DIR}/Helper.app" \
    --component-plist "./Package/HelperAppComponents.plist" \
    --identifier "com.test.pkg.Helper" \
    --version "$VERSION" \
    --install-location "/" \
    "${BUILT_PRODUCTS_DIR}/Helper.pkg"
productbuild --distribution "./Package/Distribution.xml"  \
    --package-path "${BUILT_PRODUCTS_DIR}" \
    --resources "./Package/Resources" \
    "${TMP1_ARCHIVE}"

pkgutil --expand "${TMP1_ARCHIVE}" "${TMP2_ARCHIVE}"

# Patches and Workarounds

pkgutil --flatten "${TMP2_ARCHIVE}" "${TMP3_ARCHIVE}"

productsign --sign "Developer ID Installer: John Doe" \
    "${TMP3_ARCHIVE}" "${ARCHIVE_FILENAME}"