/*
 * BehaviorOptions.cpp
 * This file is part of Open-Typer
 *
 * Copyright (C) 2021-2022 - adazem009
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

#include "options/BehaviorOptions.h"
#include "ui_BehaviorOptions.h"

/*! Constructs BehaviorOptions. */
BehaviorOptions::BehaviorOptions(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::BehaviorOptions),
	settings(FileUtils::mainSettingsLocation(), QSettings::IniFormat)
{
	ui->setupUi(this);
	// Load settings
	// Space bar newline
	if(settings.value("main/spacenewline", "true").toBool())
		ui->spaceNewlineCheckBox->setCheckState(Qt::Checked);
	else
		ui->spaceNewlineCheckBox->setCheckState(Qt::Unchecked);
	// Error penalty
	ui->errorPenaltyBox->setValue(settings.value("main/errorpenalty", "10").toInt());
	// Mistake limit
	bool mistakeLimit = settings.value("main/mistakelimit", true).toBool();
	ui->mistakeLimitCheckBox->setChecked(mistakeLimit);
	ui->mistakeCharsBox->setEnabled(mistakeLimit);
	ui->mistakeCharsBox->setValue(settings.value("main/mistakechars", 6).toInt());
	// Updates
#ifdef Q_OS_WIN
	ui->updatesCheckBox->setChecked(settings.value("main/updatechecks", true).toBool());
#else
	ui->updatesBox->hide();
#endif // Q_OS_WIN
	// Connect
	// Space bar newline checkbox
	connect(ui->spaceNewlineCheckBox, SIGNAL(clicked(bool)), this, SLOT(setSpaceNewline(bool)));
	// Error penalty box
	connect(ui->errorPenaltyBox, SIGNAL(valueChanged(int)), this, SLOT(setErrorPenalty(int)));
	// Mistake limit check box
	connect(ui->mistakeLimitCheckBox, &QCheckBox::toggled, this, &BehaviorOptions::toggleMistakeLimit);
	// Mistake characters box
	connect(ui->mistakeCharsBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &BehaviorOptions::setMistakeChars);
	// Updates check box
	connect(ui->updatesCheckBox, &QCheckBox::toggled, this, [this](bool checked) {
		settings.setValue("main/updatechecks", checked);
	});
}

/*! Destroys the BehaviorOptions object. */
BehaviorOptions::~BehaviorOptions()
{
	delete ui;
}

/*!
 * Connected from spaceNewlineCheckBox#clicked().
 * Enables or disables space bar at the end of line.
 */
void BehaviorOptions::setSpaceNewline(bool value)
{
	if(value)
		settings.setValue("main/spacenewline", "true");
	else
		settings.setValue("main/spacenewline", "false");
}

/*!
 * Connected from errorPenaltyBox#valueChanged().
 * Sets error penalty value.
 */
void BehaviorOptions::setErrorPenalty(int value)
{
	settings.setValue("main/errorpenalty", value);
}

/*!
 * Toggles mistake limit.
 */
void BehaviorOptions::toggleMistakeLimit(bool checked)
{
	settings.setValue("main/mistakelimit", checked);
	ui->mistakeCharsBox->setEnabled(checked);
}

/*!
 * Sets number of characters with max. 1 mistake.
 */
void BehaviorOptions::setMistakeChars(int value)
{
	settings.setValue("main/mistakechars", value);
}
