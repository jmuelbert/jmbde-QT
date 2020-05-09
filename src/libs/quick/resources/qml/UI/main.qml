import QtQuick 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.13 as QQC2
import org.kde.kirigami 2.11 as Kirigami

// import i.did.it.myclass 0.1 // Not yet. Everybody and all the tutorials are lying to you and now you have to figure it out all by yourself or build your own toolkit

Kirigami.ApplicationWindow {
    id: root
    
    Component{
        id: aboutPage
        AboutPage{}
    }
    Component{
        id:mainPage 
        MainPage{}
    }
    Component{
        id: alexPage
        AlexPage{}
    }
    Component{
        id: listPage
        ListPage{}
    }
    Component{
        id: toDoPage
        ToDoPage{}
    }
    
    
    
    wideScreen: true
    reachableMode: false
    
    globalDrawer: GlobalDrawer{} // QML is not consistant it should be loaded in like the other components.
    
    contextDrawer: Kirigami.ContextDrawer {
        id: contextDrawer
    }
    
    pageStack.initialPage: toDoPage//mainPage //Qt.resolvedUrl("qrc:/UI/MainPage.qml") or MainPage{}
}