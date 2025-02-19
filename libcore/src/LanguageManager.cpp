/*
 * LanguageManager.cpp
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

#include "LanguageManager.h"
#include "AppMenuBar.h"

QTranslator *translator_app = nullptr;
QTranslator *translator_libcore = nullptr;
QTranslator *translator_qt = nullptr;
LanguageManager globalLanguageManager;

/*! Initializes the language manager. */
void LanguageManager::init(void)
{
	if(initComplete)
		return;
	initComplete = true;
}

/*! Changes the application language. */
void LanguageManager::setLanguage(int index)
{
	QLocale targetLocale;
	if(index < 0)
		targetLocale = QLocale::system();
	else
	{
		const auto [lang, country] = supportedLanguagesList.at(index);
		targetLocale = QLocale(lang, country);
	}
	if(!translator_app)
	{
		translator_app = new QTranslator(qApp);
		QCoreApplication::installTranslator(translator_app);
	}
	if(!translator_libcore)
	{
		translator_libcore = new QTranslator(qApp);
		QCoreApplication::installTranslator(translator_libcore);
	}
	if(!translator_qt)
	{
		translator_qt = new QTranslator(qApp);
		QCoreApplication::installTranslator(translator_qt);
	}
	translator_app->load(targetLocale, "Open-Typer", "_", ":/res/lang");
	translator_libcore->load(targetLocale, "libcore", "_", ":/res/lang");
	translator_qt->load(targetLocale.language(), "qt", "_", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	globalMenuBar.updateMenus();
	emit languageChanged();
}

/*! Returns list of human-readable items that can be added to a lists (e. g. a combo box). */
QStringList LanguageManager::getBoxItems()
{
	QStringList boxItems;
	for(const auto &[lang, country] : supportedLanguagesList)
		boxItems += boxLangItemTemplate.arg(QLocale::languageToString(lang), QLocale::countryToString(country));
	boxItems.insert(0, tr("System (default)"));
	return boxItems;
}

const QString LanguageManager::boxLangItemTemplate = QString("%1 (%2)");

const QList<LanguageManager::LanguageCountry> LanguageManager::supportedLanguagesList = {
	{ QLocale::German, QLocale::Germany },
	{ QLocale::English, QLocale::UnitedStates },
	{ QLocale::Slovak, QLocale::Slovakia },
	{ QLocale::Russian, QLocale::Russia },
};
