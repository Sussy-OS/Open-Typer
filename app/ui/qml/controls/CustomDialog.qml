/*
 * CustomDialog.qml
 * This file is part of Open-Typer
 *
 * Copyright (C) 2022-2023 - adazem009
 *
 * Open-Typer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Open-Typer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open-Typer. If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.5
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Qt5Compat.GraphicalEffects 1.0
import OpenTyper 1.0
import "../controls"

Item {
	property Item blurSource: QmlUtils.blurSource
	property Item menuBarBlur: QmlUtils.menuBarBlur
	property string windowTitle: ""
	property int standardButtons: Dialog.NoButton
	readonly property color dialogColor: ThemeEngine.bgColor
	readonly property alias dialog: control
	property alias contentComponent: contentsLoader.sourceComponent
	readonly property alias contentItem: contentsLoader.item
	property bool draggable: true
	property bool fillWindow: false
	signal accepted()
	signal applied()
	signal discarded()
	signal helpRequested()
	signal rejected()
	signal reset()
	signal aboutToShow()
	signal aboutToHide()
	id: root
	anchors.fill: parent

	function open() {
		control.open();
	}

	function close() {
		control.close();
	}

	function standardButton(button) {
		return buttonBoxLoader.item.standardButton(button);
	}

	Rectangle {
		id: dialogMask
		width: control.width + 4
		height: control.height + 4
		color: dialogColor
		radius: control.radius
		visible: shadow.visible
		border.width: 1
		border.color: Material.theme === Material.Light ? Qt.rgba(0, 0, 0, 0.25) : Qt.rgba(1, 1, 1, 0.25)
		Component.onCompleted: resetPos();
		onXChanged: checkPos();
		onYChanged: checkPos();

		function resetPos() {
			anchors.centerIn = parent;
			parent.onWidthChanged.connect(function() { checkPos(); });
			parent.onHeightChanged.connect(function() { checkPos(); });
		}

		function checkPos() {
			if(anchors.centerIn == parent)
				return;
			// x
			var finalX = x;
			if(finalX < 0)
				finalX = 0;
			else if(finalX + width > parent.width)
				finalX = parent.width - width;
			if(finalX != x)
				x = finalX;
			// y
			var finalY = y;
			if(finalY < 0)
				finalY = 0;
			if(finalY + height > parent.height)
				finalY = parent.height - height;
			if(finalY != y)
				y = finalY;
		}
	}

	FastBlur {
		id: blur
		anchors.fill: root
		source: blurSource
		visible: false
		radius: 0
		cached: true
		PropertyAnimation {
			id: blurInAnimation
			target: blur
			property: "radius"
			to: 40
			duration: 125
		}
		PropertyAnimation {
			id: blurOutAnimation
			target: blur
			property: "radius"
			to: 0
			duration: 125
		}
	}

	DropShadow {
		id: shadow
		anchors.fill: dialogMask
		horizontalOffset: 20
		verticalOffset: 20
		radius: 10
		samples: 10
		color: ThemeEngine.theme == ThemeEngine.DarkTheme ? "#80000000" : "#50000000"
		source: dialogMask
		cached: true
		opacity: 0
		visible: false
		PropertyAnimation {
			id: shadowInAnimation
			target: shadow
			property: "opacity"
			to: 1.0
			duration: 125
		}
		PropertyAnimation {
			id: shadowOutAnimation
			target: shadow
			property: "opacity"
			to: 0.0
			duration: 125
		}
	}

	Dialog {
		property int radius: 10
		id: control
		x: dialogMask.x + 2
		y: dialogMask.y + 2
		width: fillWindow ? parent.width - 100 : headerLayout.implicitWidth
		height: fillWindow ? parent.height - 100 : (standardButtons !== Dialog.NoButton ? headerLayout.implicitHeight + buttonBoxLoader.item.height : headerLayout.implicitHeight)
		standardButtons: root.standardButtons
		modal: true
		onAboutToShow: {
			contentsLoader.active = 1;
			blur.visible = true;
			blurInAnimation.running = true;
			menuBarBlur.visible = true;
			menuBarBlur.blurInAnimation.running = true;
			shadowInAnimation.running = true;
			shadow.visible = true;
			root.aboutToShow();
		}
		onAboutToHide: {
			blurOutAnimation.running = true;
			shadowOutAnimation.running = true;
			menuBarBlur.blurOutAnimation.running = true;
			shadow.visible = false
			root.aboutToHide();
		}
		onClosed: {
			contentsLoader.active = 0;
			blur.visible = false;
			menuBarBlur.visible = false;
			dialogMask.resetPos();
			QmlUtils.reloadMenuBar();
		}
		header: Rectangle {
			color: dialogColor
			width: dialogMask.width
			height: standardButtons !== Dialog.NoButton ? headerLayout.height - control.footer.height : headerLayout.height
			radius: control.radius
			ColumnLayout {
				id: headerLayout
				width: fillWindow ? control.width : undefined
				height: fillWindow ? control.height - control.footer.height : undefined
				spacing: 0
				Label {
					id: windowTitleLabel
					Layout.fillWidth: true
					padding: 0
					text: root.windowTitle
					horizontalAlignment: Qt.AlignHCenter
					visible: text != ""
					Drag.active: draggable
					MouseArea {
						enabled: draggable
						anchors.fill: parent
						drag.target: dialogMask
						onPressed: dialogMask.anchors.centerIn = undefined;
					}
				}
				MenuSeparator {
					Layout.fillWidth: true
					visible: root.windowTitle != ""
				}
				Pane {
					padding: 10
					background: null
					clip: true
					Layout.fillWidth: true
					Layout.fillHeight: true
					Loader {
						id: contentsLoader
						active: false
						anchors.fill: parent
					}
				}
				MenuSeparator {
					Layout.fillWidth: true
					visible: standardButtons !== Dialog.NoButton
				}
			}
		}
		Component {
			id: buttonBoxComponent
			AccentButtonBox {
				id: dialogButtonBox
				font.capitalization: Font.MixedCase
				standardButtons: control.standardButtons
				background: Rectangle {
					color: dialogColor
					radius: control.radius
				}
				onAccepted: control.accept()
				onApplied: control.applied()
				onDiscarded: control.discarded()
				onHelpRequested: control.helpRequested()
				onRejected: control.reject()
				onReset: control.reset()
				function retranslateButtons() {
					if(standardButton(Dialog.Ok))
						standardButton(Dialog.Ok).text = QmlUtils.translateStandardButton("OK");
					if(standardButton(Dialog.Open))
						standardButton(Dialog.Open).text = QmlUtils.translateStandardButton("Open");
					if(standardButton(Dialog.Save))
						standardButton(Dialog.Save).text = QmlUtils.translateStandardButton("Save");
					if(standardButton(Dialog.Cancel))
						standardButton(Dialog.Cancel).text = QmlUtils.translateStandardButton("Cancel");
					if(standardButton(Dialog.Close))
						standardButton(Dialog.Close).text = QmlUtils.translateStandardButton("Close");
					if(standardButton(Dialog.Discard))
						standardButton(Dialog.Discard).text = QmlUtils.translateStandardButton("Discard");
					if(standardButton(Dialog.Apply))
						standardButton(Dialog.Apply).text = QmlUtils.translateStandardButton("Apply");
					if(standardButton(Dialog.Reset))
						standardButton(Dialog.Reset).text = QmlUtils.translateStandardButton("Reset");
					if(standardButton(Dialog.RestoreDefaults))
						standardButton(Dialog.RestoreDefaults).text = QmlUtils.translateStandardButton("Restore Defaults");
					if(standardButton(Dialog.Help))
						standardButton(Dialog.Help).text = QmlUtils.translateStandardButton("Help");
					if(standardButton(Dialog.SaveAll))
						standardButton(Dialog.SaveAll).text = QmlUtils.translateStandardButton("Save All");
					if(standardButton(Dialog.Yes))
						standardButton(Dialog.Yes).text = QmlUtils.translateStandardButton("Yes");
					if(standardButton(Dialog.YesToAll))
						standardButton(Dialog.YesToAll).text = QmlUtils.translateStandardButton("Yes to All");
					if(standardButton(Dialog.No))
						standardButton(Dialog.No).text = QmlUtils.translateStandardButton("No");
					if(standardButton(Dialog.NoToAll))
						standardButton(Dialog.NoToAll).text = QmlUtils.translateStandardButton("No to All");
					if(standardButton(Dialog.Abort))
						standardButton(Dialog.Abort).text = QmlUtils.translateStandardButton("Abort");
					if(standardButton(Dialog.Retry))
						standardButton(Dialog.Retry).text = QmlUtils.translateStandardButton("Retry");
					if(standardButton(Dialog.Ignore))
						standardButton(Dialog.Ignore).text = QmlUtils.translateStandardButton("Ignore");
				}
				Component.onCompleted: retranslateButtons()
				onStandardButtonsChanged: retranslateButtons()
			}
		}
		footer: Loader {
			id: buttonBoxLoader
			sourceComponent: buttonBoxComponent
			Connections {
				target: LanguageManager
				onLanguageChanged: {
					translationTimer.start();
				}
			}
			Timer {
				id: translationTimer
				interval: 16
				running: false
				repeat: false
				onTriggered: {
					buttonBoxLoader.active = 0;
					buttonBoxLoader.active = 1;
				}
			}
		}
		background: Rectangle {
			color: dialogColor
			width: control.width
			height: control.height
			radius: control.radius
		}
		Overlay.modal: Rectangle {
			color: Qt.rgba(0, 0, 0, 0.25)
		}
		onAccepted: root.accepted()
		onApplied: root.applied()
		onDiscarded: root.discarded()
		onHelpRequested: root.helpRequested()
		onRejected: root.rejected()
		onReset: root.reset()
	}
}
