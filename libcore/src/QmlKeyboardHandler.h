/*
 * QmlKeyboardHandler.h
 * This file is part of Open-Typer
 *
 * Copyright (C) 2022 - adazem009
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

#ifndef QMLKEYBOARDHANDLER_H
#define QMLKEYBOARDHANDLER_H

#if defined CORE_SHARED_LIB
#define CORE_LIB_EXPORT Q_DECL_EXPORT
#else
#define CORE_LIB_EXPORT Q_DECL_IMPORT
#endif

#include <QQuickItem>
#include "KeyboardUtils.h"

/*! \brief The QmlKeyboardHandler class can be used to receive any key presses (including dead keys). */
class CORE_LIB_EXPORT QmlKeyboardHandler : public QQuickItem
{
		Q_OBJECT
	public:
		explicit QmlKeyboardHandler(QQuickItem *parent = nullptr);
		static QVariantMap convertEvent(QKeyEvent *event);

	protected:
		void inputMethodEvent(QInputMethodEvent *event) override;
		void keyPressEvent(QKeyEvent *event) override;
		void keyReleaseEvent(QKeyEvent *event) override;

	signals:
		void keyPressed(QVariantMap event);
		void keyReleased(QVariantMap event);
};

#endif // QMLKEYBOARDHANDLER_H
