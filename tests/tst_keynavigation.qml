import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Window 2.1
import QtTest 1.0
import "../tests"

TestCase {
    id: TestCase
    width: 400
    height: 400
    when: mainWindow.visble
    name: "KeyboardNavigation"

    KeyboardTest {
        id: mainWindow
        width: 400
        height: 360
        visible: true
    }

    SignalSpy {
        id: spyActive
        target: mainWindow
        signalName: "activeChanged"
    }
    
    SignalSpy {
        id: spyLastKey
        target: mainWindow.pageStack.currentItem
        signalName: "lastKeyChanged"
    }

    function test_press() {
        compare(mainWindow.pageStack.depth, 2)
        compare(mainWindow.pageStack.currentIndex, 1)
        if (!mainWindow.active)
            spyActive.wait(5000)
        verify(mainWindow.active)
       keyClick("A")
        spyLastKey.wait()
        compare(mainWindow.pageStack.currentItem.lastKey, "A")
        keyClick(Qt.Key_Left, Qt.AltModifier)
        compare(mainWindow.pageStack.currentIndex, 0)
        compare(mainWindow.pageStack.currentItem.lastKey, "")
        keyClick("B")
        spyLastKey.wait()
        compare(mainWindow.pageStack.currentItem.lastKey, "B")
    }
}
        
    }
}