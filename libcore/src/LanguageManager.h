/*
 * LanguageManager.h
 * This file is part of Open-Typer
 *
 * Copyright (C) 2021-2023 - adazem009
 * Copyright (C) 2022 - Roker2
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

#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#if defined CORE_SHARED_LIB
#define CORE_LIB_EXPORT Q_DECL_EXPORT
#else
#define CORE_LIB_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <QLocale>
#include <QVector>
#include <QTranslator>
#include <QCoreApplication>
#include <QLibraryInfo>
#include "ThemeEngine.h"

extern QTranslator *translator_app;
extern QTranslator *translator_libcore;
extern QTranslator *translator_qt;

/*!
 * \brief The LanguageManager class provides a list of supported languages.
 *
 * \code
 * QStringList items = globalLanguageManager.boxItems; // list of languages which can be used in selector widgets
 * \endcode
 *
 * \see LanguageList
 */
class CORE_LIB_EXPORT LanguageManager : public QObject
{
		Q_OBJECT
		using LanguageCountry = std::pair<QLocale::Language, QLocale::Country>;

	public:
		void init(void);
		Q_INVOKABLE void setLanguage(int index);
		Q_INVOKABLE QStringList getBoxItems();

	private:
		static const QList<LanguageCountry> supportedLanguagesList;
		static const QString boxLangItemTemplate;
		bool initComplete = false;

	signals:
		void languageChanged(void);
};

extern LanguageManager CORE_LIB_EXPORT globalLanguageManager;

#endif // LANGUAGEMANAGER_H
