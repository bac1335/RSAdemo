import QtQuick 2.0

Item {
    id:root
    signal hide()

    Text {
        id: rootText
        width: root.width*3/4
        font.pixelSize: 18
        font.family: 'Microsoft YaHei'
        text: qsTr('')
        color: 'red'
        horizontalAlignment:Text.AlignHCenter
        wrapMode: Text.WrapAnywhere
        NumberAnimation on opacity{
            id: rootTextAni
            from: 0.8
            to: 0
            duration: 1500
            running: false

            onStopped: {
                 hide()
            }
        }



        function startAni(){
            rootTextAni.running = true
        }
    }

    Timer{
        id: textTimer
        interval: 1500
        repeat: false
        onTriggered: {
            rootText.startAni()
        }
    }

    function show(str){
        rootText.text = str
    }

    Component.onCompleted: {
        rootText.x = (root.width - rootText.width)/2.
        rootText.y = root.height - rootText.implicitHeight - 60;
        textTimer.start()
    }

}
