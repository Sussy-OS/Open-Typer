/*
 * Updater.h
 * This file is part of Open-Typer
 *
 * Copyright (C) 2021-2023 - adazem009
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

#ifndef UPDATER_H
#define UPDATER_H

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QDateTime>
#ifndef Q_OS_WASM
#include "AddonListModel.h"
#endif

/*! \brief The Updater class is used to check for updates and download new versions of the program. */
class Updater : public QObject
{
		Q_OBJECT
	public:
		Q_INVOKABLE static bool updateAvailable(void);
		Q_INVOKABLE static void installUpdate(void);
#ifndef Q_OS_WASM
		Q_INVOKABLE static void getAddonUpdates(void);
		Q_INVOKABLE static bool addonUpdateAvailable(void);
		Q_INVOKABLE static void updateAddons(void);
#endif

	private:
#ifndef Q_OS_WASM
		static AddonListModel listModel;
		static QList<AddonItemModel *> updatableAddons;
#endif
};

#endif // UPDATER_H
