
import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15

import Model 1.0

Window {
        visible: true
        width: 700
        height: 480
        title: qsTr("My Client")

              TextField { id:login_field

                          anchors.horizontalCenter: parent.horizontalCenter
                          anchors.bottom: pass_field.top
                          font.pointSize: 12
                          text: "qa.ajax911a@gmail.com"
                          color: "black"
                          width: 300
                          height: 50
                          background: Rectangle {
                                                 color: "lightgrey"
                                                 border.color: "lightgrey"
                                                 border.width: 1
                                                 radius: 10.0
                                                 }
                        }




              TextField { id:pass_field
                          anchors.left: login_field.left
                          anchors.top: login_field.bottom
                          anchors.centerIn: parent
                          font.pointSize: 12
                          text: "qwe"
                          color: "black"
                          width: 300
                          height: 50
                          visible: true
                          background: Rectangle {
                                                 color: "lightgrey"
                                                 border.color: "lightgrey"
                                                 border.width: 1
                                                 radius: 10.0
                                                 }
                        }




              Button { id: login_button
                       anchors.left: pass_field.left
                       anchors.top: pass_field.bottom
                       font.pointSize: 24
                       text: "Login"
                       width: 300
                       height: 50
                       onClicked: {
                                       listModel.startclient(login_field.text,pass_field.text);
                                       login_button.visible = false;
                                       pass_field.visible = false;
                                       login_field.visible = false;
                                       logout_button.visible = true;
                                       listview.visible = true;


                               }
                       background: Rectangle {
                                              id: login_button_bg
                                              color: "lightgreen"
                                              border.color: "lightgreen"
                                              border.width: 1
                                              radius: 10.0
                                              }


                      }

              Rectangle{ id:space; width: parent ; height: 120 }

              Button { id: logout_button
                       anchors.horizontalCenter: parent.horizontalCenter
                       anchors.top: space.bottom
                       font.pointSize: 24
                       text: "Logout"
                       width: 300
                       height: 50
                       visible: false
                       onClicked: {
                                   listModel.endclient()
                                   login_button.visible = true;
                                   pass_field.visible = true;
                                   login_field.visible = true;
                                   listview.visible = false;
                                   logout_button.visible = false;
                               }
                       background: Rectangle {
                                              id: logout_button_bg
                                              color: "lightpink"
                                              border.color: "lightpink"
                                              border.width: 1
                                              radius: 10.0
                                              }


                      }





        ListView {

                id: listview
                visible: false
                anchors.top: logout_button.bottom
                anchors.bottom: parent.bottom
                anchors.left: logout_button.left
                anchors.right: logout_button.right

                model: Model { id: listModel }
                delegate:  Component {

                    Rectangle {
                        id: login_frame
                        width: 300
                        color:  "lightgrey"
                        height: 50
                        radius: 10.0
                        Text {
                                text: model.description
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                             }
                              }
                                     }
                  }
}
