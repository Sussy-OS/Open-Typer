/*
 * AddonApi.h
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

#ifndef ADDONAPI_H
#define ADDONAPI_H

#include <QObject>
#include <QIcon>
#include <QMessageBox>
#include <QVariantMap>
#include <QMenu>
#include <QPushButton>
#include <QLayout>
#include "IAddon.h"

#if defined CORE_SHARED_LIB
#define CORE_LIB_EXPORT Q_DECL_EXPORT
#else
#define CORE_LIB_EXPORT Q_DECL_IMPORT
#endif

class AddonButton;

/*! \brief The AddonApi class provides an API for addons. */
class CORE_LIB_EXPORT AddonApi : public QObject
{
		Q_OBJECT
		Q_PROPERTY(QList<AddonButton *> mainButtons READ mainButtons WRITE setMainButtons NOTIFY mainButtonsChanged)
		Q_PROPERTY(QList<AddonButton *> exOptionsButtons READ exOptionsButtons WRITE setExOptionsButtons NOTIFY exOptionsButtonsChanged)
		Q_PROPERTY(QList<AddonButton *> navigationButtons READ navigationButtons WRITE setNavigationButtons NOTIFY navigationButtonsChanged)
		Q_PROPERTY(QList<AddonButton *> exInfoButtons READ exInfoButtons WRITE setExInfoButtons NOTIFY exInfoButtonsChanged)
	public:
		static AddonApi *instance(void);
		static void addLoadExTarget(int id, QString name);
		static void clearLoadExTargets(void);
		static QMap<int, QString> loadExTargets(void);
		static bool blockLoadedEx(void);
		static void setBlockLoadedEx(bool value);
		static bool addSettingsCategory(QString categoryName, QIcon icon, QString className);
		static QList<QVariantMap> settingsCategories(void);
		static void clearSettingsCategories(void);
		static void initSettingsCategories(bool clear = false);
		static void sendEvent(IAddon::Event type, QVariantMap args = QVariantMap());
		static void deleteMenus(void);
		static void addMenu(QString id, QString name);
		static void registerMenu(QString id, QMenu *menu);
		static QMap<QString, QPair<QString, QMenu *>> menus(void);
		static QMenu *menu(QString id);

		AddonButton *addMainButton(QString text, QString toolTip, QString iconName, QString iconSource);
		QList<AddonButton *> mainButtons(void);
		void setMainButtons(QList<AddonButton *> buttons);

		AddonButton *addExOptionsButton(QString text, QString toolTip, QString iconName, QString iconSource);
		QList<AddonButton *> exOptionsButtons(void);
		void setExOptionsButtons(QList<AddonButton *> buttons);

		AddonButton *addNavigationButton(QString text, QString toolTip, QString iconName, QString iconSource);
		QList<AddonButton *> navigationButtons(void);
		void setNavigationButtons(QList<AddonButton *> buttons);

		AddonButton *addExInfoButton(QString text, QString toolTip, QString iconName, QString iconSource);
		QList<AddonButton *> exInfoButtons(void);
		void setExInfoButtons(QList<AddonButton *> buttons);

	private:
		AddonButton *createButton(QString text, QString toolTip, QString iconName, QString iconSource);
		static AddonApi m_instance;
		static QMap<int, QString> m_loadExTargets;
		static bool m_blockLoadedEx;
		static QList<QVariantMap> m_settingsCategories;
		static QMap<QString, QPair<QString, QMenu *>> m_menus;
		QList<AddonButton *> m_mainButtons;
		QList<AddonButton *> m_exOptionsButtons;
		QList<AddonButton *> m_navigationButtons;
		QList<AddonButton *> m_exInfoButtons;

	signals:
		void changeMode(int mode);
		void startTypingTest(QByteArray text, int lineLength, bool includeNewLines, int mode, int time, bool correctMistakes, bool lockUi, bool hideText);
		void mainButtonsChanged(QList<AddonButton *> buttons);
		void exOptionsButtonsChanged(QList<AddonButton *> buttons);
		void navigationButtonsChanged(QList<AddonButton *> buttons);
		void exInfoButtonsChanged(QList<AddonButton *> buttons);
};

#endif // ADDONAPI_H
