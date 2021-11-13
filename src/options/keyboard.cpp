/*
 * keyboard.cpp
 * This file is part of Open-Typer
 *
 * Copyright (C) 2021 - adazem009
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

#include "options/keyboard.h"
#include "ui_keyboard.h"

keyboardOptions::keyboardOptions(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::keyboardOptions)
{
	ui->setupUi(this);
	// Load packs
	QDirIterator it(":/res/configs/",QDirIterator::NoIteratorFlags);
	int i;
	QString item, current;
	QStringList items;
	rawItems.clear();
	while(it.hasNext())
	{
		item = it.next();
		current = "";
		for(i=14; i < QStringLen(item); i++)
			current += item[i];
		// TODO: Translate pack name
		rawItems += current;
		items += _pack_name(current);
	}
	ui->packList->addItems(items);
	// Get current pack
	QSettings settings(getConfigLoc()+"/config.ini",QSettings::IniFormat);
	// TODO: Detect default config
	if(!settings.value("main/customconfig","false").toBool())
		ui->packList->setCurrentItem(ui->packList->item(rawItems.indexOf(settings.value("main/configfile","sk_SK-QWERTZ-B1").toString())));
	// Connections
	connect(ui->editorButton,SIGNAL(clicked()),this,SLOT(openEditor()));
	connect(ui->packList,SIGNAL(currentRowChanged(int)),this,SLOT(changePack(int)));
}

keyboardOptions::~keyboardOptions()
{
	delete ui;
}

void keyboardOptions::openEditor(void)
{
	packEditor editorWindow;
	editorWindow.setWindowFlag(Qt::WindowMinimizeButtonHint,true);
	editorWindow.setWindowFlag(Qt::WindowMaximizeButtonHint,true);
	editorWindow.setStyleSheet(styleSheet());
	editorWindow.init();
	editorWindow.exec();
}

void keyboardOptions::changePack(int index)
{
	QSettings settings(getConfigLoc()+"/config.ini",QSettings::IniFormat);
	settings.setValue("main/configfile",rawItems[index]);
	settings.setValue("main/customconfig","false");
}
