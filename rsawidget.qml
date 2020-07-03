import QtQuick 2.7
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4

Item {
    id: root
    signal sigSendRsa(int n,int e)
    signal sigEncrypt(string str)
    signal sigDncrypt(string str)
    signal showBox(string str)
    Item{
        id: rootItem
        anchors.fill: parent
        anchors.margins: 20
        Text {
            id : text
            font.pixelSize: 15
            text: qsTr("标准RSA[<=2048bit]默认数据格式为16进制字符串")
        }
        Row{
            id: rsaProperty
            width: rootItem.width
            anchors.top: text.bottom
            anchors.topMargin: 20
            spacing: 20
            Item{
                width: 100
                height: 40
                Row{
                    Text {
                        text: qsTr("密钥n位数：")
                    }
                    TextInput{
                        id: miyueNText
                        text: "256"
                        font.pixelSize: 14
                        cursorVisible: false
                    }
                }
            }

            Item{
                 width: 200
                 height: 40
                 Row{
                     Text {
                         text: qsTr("密钥e位数：")
                     }
                     TextInput{
                         id: miyueEText
                         text: "16"
                         font.pixelSize: 14
                         cursorVisible: false
                     }
                 }
            }

           Item{
                width: 200
                height: 40
                Row{
                    spacing: 20
                    Button{
                        style:ButtonStyle{
                              background: Rectangle{
                                  color: control.hovered?"#7B68EE":"#6A5ACD";
                                  radius: 10
                              }
                              padding.bottom: 10
                              padding.left: 10
                              padding.top: 10
                              padding.right: 10
                        }
                        text: qsTr("生成密钥")
                        onClicked:{ 
                            if(miyueNText.text > 2048){
                                  showBox("密钥位数超出限制!")
                            }
                            else{
                                sigSendRsa(miyueNText.text,miyueEText.text)
                            }
                       }

                    }
                    Button{
                        style:ButtonStyle{
                            background: Rectangle{
                                color: control.hovered?"#7B68EE":"#6A5ACD";
                                radius: 10
                            }
                            padding.bottom: 10
                            padding.left: 10
                            padding.top: 10
                            padding.right: 10
                      }
                        onClicked:{
                            if(!rsaRect1Loader.item.fielInputIsNull() && !rsaRect2Loader.item.fielInputIsNull()){
                                var str = inputEnCryptStr.item.getStr()
                                if(str.length <= 0){
                                    showBox("请输入加密字符串!")
                                }
                                else{
                                    sigEncrypt(inputEnCryptStr.item.getStr())
                                }
                            }
                            else{
                                showBox("请先生成密钥!")
                            }

                       }
                        text: qsTr("加密")
                    }
                    Button{
                        style:ButtonStyle{
                            background: Rectangle{
                                color: control.hovered?"#7B68EE":"#6A5ACD";
                                radius: 10
                            }
                            padding.bottom: 10
                            padding.left: 10
                            padding.top: 10
                            padding.right: 10
                      }
                        onClicked:{
                            var str1 = rsaRectRight2Text.item.getStr()
                            if(str1.length <=0){
                                showBox("请输入解密字符串!")
                            }
                            else{
                                sigDncrypt(str1)
                            }


                       }
                        text: qsTr("解密")
                    }
                }
            }
        }

        Row{
           id: rsaRoot
           width: rootItem.width
           height: 300
           spacing: 20
           anchors.top: rsaProperty.bottom
           anchors.topMargin: 20
           Item{
               id: rsaRect
               width: rootItem.width*3/5
               height: rsaRoot.height
               Column{
                   spacing: 10
                   Item{
                       id: rsaRect1
                       width: rsaRect.width
                       height: rsaRect1Text.contentHeight + rsaRect1Loader.height
                       Text {
                           id: rsaRect1Text
                           height: 20
                           text: qsTr("RSA公钥(e,n)")
                       }
                       Loader{
                           id: rsaRect1Loader
                           anchors.top: rsaRect1Text.bottom
                           sourceComponent: textInput
                           width: rsaRect.width
                       }
                   }

                   Item{
                       id: rsaRect2
                       anchors.topMargin: 20
                       width: rsaRect.width
                       height: rsaRect2Text.contentHeight + rsaRect2Loader.height
                       Text {
                           id: rsaRect2Text
                           height: 20
                           text: qsTr("RSAsi私钥(d,n)")
                       }
                       Loader{
                           id: rsaRect2Loader
                           anchors.top: rsaRect2Text.bottom
                           sourceComponent: textInput
                           width: rsaRect.width
                       }
                   }

               }
           }

           Item{
               id: rsaPriRect
               width: rootItem.width*2/5-20
               height: rsaRoot.height

               Column{
                   spacing: 20
                    Item{
                        id: rsaRectRight
                        width: rsaPriRect.width
                        height: container1.height
                        Column{
                            id: container1
                            spacing: 5
                            Text {
                                text: qsTr("要加密的数据:")
                            }
                            Loader{
                                id:inputEnCryptStr
                                sourceComponent: textInput
                                width: rsaRectRight2.width
                            }
                        }
                    }


                    Item{
                        id: rsaRectRight2
                        width: rsaPriRect.width
                        height: container2.height
                        Column{
                            id: container2
                            spacing: 5
                            Text {
                                text: qsTr("加密后的数据[16进制字符串:")
                            }
                            Loader{
                                id: rsaRectRight2Text
                                sourceComponent: textInput
                                width: rsaRectRight2.width
                            }
                        }
                    }


                    Item{
                        id: rsaRectRight3
                        width: rsaPriRect.width
                        height: 50
                        Column{
                            spacing: 5
                            Text {
                                text: qsTr("解密后的数据:")
                            }
                            Loader{
                                id: rsaRectRight3Text
                                sourceComponent: textInput
                                width: rsaPriRect.width
                            }
                        }
                    }
               }
           }
        }

    }

    Component{
        id: textInput
        Rectangle{
            color: "transparent"
            border.width: 2
            radius: 8
            height: textArea.contentHeight + 15
            layer.effect: DropShadow{
                transparentBorder: true
                samples: 5
            }
            layer.enabled: textArea.activeFocus

            TextEdit{
                id: textArea
                anchors.fill: parent
                anchors.margins: 8
                font.family: "Arial"
                font.pixelSize:15
                font.weight: Font.Thin
                antialiasing: true
                wrapMode: TextEdit.Wrap
            }
            function setText(str){
                textArea.text = str;
            }

            function fielInputIsNull(){
                if(textArea.text.length <= 0){
                    return true
                }
                else{
                    return false
                }
            }
            function getStr(){
                return textArea.text
            }
        }
    }

    Component{
        id:textInputOneLine
        TextField {
            id: rsaRectRightText
            signal doubleClicked(var/*MouseEvent*/ event)
            placeholderText: qsTr("")
            font.family: "Arial"
            font.pixelSize: 15
            font.weight: Font.Thin
            antialiasing: true
            verticalAlignment:TextInput.AlignTop

            style:TextFieldStyle{
                background: Rectangle {
                    implicitWidth: rsaRectRight.width
                    implicitHeight: rsaRectRight2.height
                    radius: 8
                    color: "transparent"
                    border.width: 2
                    opacity: rsaRectRightText.enabled ? 1 : 0.7
                    layer.enabled: rsaRectRightText.hovered
                    layer.effect: DropShadow {
                        transparentBorder: true
                        samples: 5
                    }
                }
            }
        }
    }

    function doFunctopm(str1){
        var str = str1.split("&")
        if(str.length === 2){
            rsaRect1Loader.item.setText(str[0])
            rsaRect2Loader.item.setText(str[1])
        }
    }

    Connections{
        target: root
        onSigEncrypt:{
            rsaRectRight2Text.item.setText(MainWindow.doEncypt(str))
        }
    }

    Connections{
        target: root
        onSigDncrypt:{
            rsaRectRight3Text.item.setText(MainWindow.doDecypt(str))
        }
    }

}

