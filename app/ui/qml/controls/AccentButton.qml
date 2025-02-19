/*
 * AccentButton.qml
 * This file is part of Open-Typer
 *
 * Copyright (C) 2023 - adazem009
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
import OpenTyper 1.0

Button {
	readonly property color accent: Material.accent
	Material.foreground: ThemeEngine.theme == ThemeEngine.DarkTheme ? "white" : "black"
	Material.background: Qt.rgba(accent.r, accent.g, accent.b, 0.3)
	background.layer.enabled: false
	font.capitalization: Font.MixedCase
}
