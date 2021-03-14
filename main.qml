import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4
import mm 1.0
import QtQuick.Controls.Material 2.12

Window {
    Material.theme  : Material.Dark
    Material.accent : Material.Orange
    visible         : true
    width           : 840
    height          : 1024
    title           : qsTr("MasterMind")

    Label {
        id                  : play_order
        height              : 50
        anchors{
            top                 : parent.top
            horizontalCenter    : parent.horizontalCenter
        }
        text                : "Sıra Sizde"
        font.pointSize      : 25
    }
    Rectangle{
        anchors.horizontalCenter:   parent.horizontalCenter
        width                   :   parent.width * 2 / 3
        anchors{
            top     : play_order.bottom
            bottom  : parent.bottom
        }

        TextArea {
             id                 :   user_input
             placeholderText    :   "Tahmininizi Giriniz.."
             horizontalAlignment:   Qt.AlignCenter
             anchors.left       :   parent.left
             anchors.right      :   parent.right
             height             :   25

             onTextChanged      :   if (length > 4) remove(4, length);
             background: Rectangle {
                border.color    : user_input.focus ? "#21be2b"   : "lightgray"
                color           : user_input.focus ? "lightgray" : "transparent"
             }

             Keys.onReturnPressed:{
                 if (length == 4){
                     var result = master_mind_game.calculate_result(user_input.text)
                     guess_table.insert_history(user_input.text, result)
                     if(result == "Success"){
                            play_order.text = "Kullanıcı Kazandı. Tutulan Sayı: " + master_mind_game.number_to_guess
                            user_input.enabled = false

                     }else{
                         computer.insert_guess(user_input.text, result);
                         computer_timer.running = true;
                         play_order.text = "Bilgisayarın Sırası"

                     }
                     user_input.text = ""
                 }

             }

             Timer {
                 id : computer_timer
                 interval: 500;
                 running: false;
                 repeat: false
                 onTriggered:{
                     var comp_ansver = computer.get_next_guess();
                     var comp_result = master_mind_game.calculate_result(comp_ansver)
                     guess_table.insert_history(comp_ansver, comp_result)
                     if(comp_result == "Success"){
                        user_input.enabled = false
                        play_order.text = "Bilgisayar Kazandı. Tutulan Sayı: : " + master_mind_game.number_to_guess
                     }else{
                        computer.insert_guess(comp_ansver, comp_result);
                        play_order.text = "Sıra Sizde"
                     }
                 }

             }

        }


        TableView{
            id          :  guess_view
            anchors {
                left        :  parent.left
                right       :  parent.right
                bottom      :  parent.bottom
                top         :  user_input.bottom
                topMargin   : 10
            }
            columnSpacing   : 0
            rowSpacing      : 0
            clip            : true
            model           : guess_table
            delegate: Rectangle {
                implicitWidth   : parent.width / 5 - 10
                implicitHeight  : 50
                border.width    : 1
                border.color    : "black"
                Text {
                    text: display
                    font.pixelSize:  35
                    anchors.centerIn: parent
                }
            }
            property var columnWidths: [guess_view.width / 6, guess_view.width / 6, guess_view.width / 6, guess_view.width / 6,2 * guess_view.width / 6]
            columnWidthProvider: function (column) { return columnWidths[column] }
        }
    }




    MasterMind{
        id  : master_mind_game
    }
    GuessTable{
        id  : guess_table
    }
    Computer{
        id  : computer
    }

}
