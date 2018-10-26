import qbs

QbsDevHeaders {
    name: "ProParser"
    condition: true
    type: [ "app.dev-headers", "app.dev-module" ]
    productName: name
    property string fileName: "proparser.qbs"

    
}