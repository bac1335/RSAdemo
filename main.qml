import QtQuick 2.7
import QtQuick.Window 2.12

Window {
    id: rootWindow
    visible: true
    width: 580
    height: 540
    title: qsTr("RSA")

//    Image{
//        anchors.fill: parent
//        source: "qrc:/skin/bg_login2.jpg";
//    }
    Rectangle{
        anchors.fill:parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightsteelblue" }
            GradientStop { position: 1.0; color: "blue" }
        }
    }

    Column{
        anchors.fill:parent
        Rsawidget{
            id: rsaWidget
            width: parent.width
            height: 400
        }

        Item{
            width: parent.width
            height: parent.width/2.
        }
    }

    Connections{
        target: rsaWidget
        onSigSendRsa:{
            rsaWidget.doFunctopm(MainWindow.doSendRsa(n,e));
        }
    }

    Connections{
        target: rsaWidget
        onShowBox:{
                messageBox.source == ""
                messageBox.source = "qrc:/PopTip.qml"
                messageBox.item.show(str)

        }

    }

    Connections{
        target: messageBox.item
        onHide:{
            messageBox.source = ""
        }
    }

    Loader{
        id: messageBox
        anchors.fill: parent
        source: ""
    }


}
