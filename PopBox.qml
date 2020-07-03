import QtQuick 2.0
import QtGraphicalEffects 1.12

Item {
    id: root
    z:1000
    transformOrigin: Item.Center
    anchors.fill: parent
    signal hide()

    property bool showMask: true
    property string animationType: 'none'
    property int duration: 500
    property int easingType : Easing.OutBounce


    property int  innerX
    property int  innerY
    property int  innerWidth
    property int  innerHeight
    property int  innerOpacity

    MouseArea{
        anchors.fill: parent
        onClicked: {
//            close()
            hide()
        }
    }

    Rectangle{
        id: rootMask
        width: 200
        height: 200
        anchors.centerIn: parent
        color: 'lightblue'
        opacity: 0.8
        radius: 10
        layer.enabled: true
        layer.effect: DropShadow {
            transparentBorder: true
            samples: 20
        }

        Text {
            id: rootMaskText
            width: parent.width*3/4
            anchors.centerIn: parent
            text: qsTr("")
            font.bold: true
            font.family: 'Microsoft YaHei'
            font.pixelSize: 16
            clip: true
            wrapMode :Text.WrapAnywhere
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
//                console.log('11111111111111111111111');
            }
        }
    }

    Component.onCompleted: {
        save()
//        root.visible = false
    }

    PropertyAnimation{
        id: animFadeIn
        target: rootMask
        duration: root.duration
        property: 'opacity'
        from: 0
        to: rootMask.innerOpacity
    }

    PropertyAnimation{
        id: animFadeOut
        target: rootMask
        duration: root.duration
        properties: 'opacity'
        from: rootMask.innerOpacity
        to: 0
    }

    function setMaskText(str){
        rootMaskText.text = str
    }


    function close(){
        root.visible = false
    }

    function show(str){
        setMaskText(str)
        switch(animationType){
        case 'fade' :animFadeIn.start();break
        default:
            root.visible = true;
//            animFadeIn.start()
        }
    }

    function save(){
        innerX = rootMask.x
        innerY = rootMask.y
        innerWidth = rootMask.width
        innerHeight = rootMask.height
        innerOpacity = rootMask.opacity
    }

    function reset(){
        rootMask.x = innerX
        rootMask.y = innerY
        rootMask.width = innerWidth
        rootMask.height = innerHeight
        rootMask.opacity = innerOpacity

    }
}
