/*
 * opentyper.h
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

#ifndef OPENTYPER_H
#define OPENTYPER_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QString>
#include <QMessageBox>
#include <QSettings>
#include <QDir>
#include <QDialog>
#include <QDirIterator>
#include <QTimer>
#include <QColorDialog>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QTextCursor>
#include <QTranslator>
#include <sys/stat.h>
#include "widgets/inputlabel.h"
#include "widgets/languagecombobox.h"
#include "updater/updater.h"
#include "simplecolordialog.h"
#include "paperconfigdialog.h"
#include "packEditor/packeditor.h"
#include "options/optionswindow.h"
#include "levelsummary.h"
#include "core/configfile.h"
#include "core/utils.h"
#include "core/packs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OpenTyper; }
QT_END_NAMESPACE

class OpenTyper : public QMainWindow
{
	Q_OBJECT

public:
	OpenTyper(QWidget *parent = nullptr);
	~OpenTyper();
	char *loadConfig(QString configName);
	void startLevel(FILE *cr, int lesson, int sublesson, int level);
	void levelFinalInit(void);
	QString level, displayLevel, input, displayInput, publicConfigName;
	int lessonCount, sublessonCount, levelCount, currentLesson, currentSublesson, currentLevel, levelPos, displayPos, levelMistakes, levelLengthExtension;
	int sublessonListStart;
	QElapsedTimer levelTimer;
	bool levelInProgress, mistake, ignoreMistakeLabelAppend;
	QString inputLabelHtml, mistakeLabelHtml;
	int lastTime;
	bool isSpecialKey(QKeyEvent *event);
	int _line_count(QString str);
	Updater *versionHdw;
	void autoUpdate(void);
	void adjustSize(void);
	int labelWidth(QLabel *targetLabel);
	void setFont(QString fontFamily, int fontSize, bool fontBold, bool fontItalic, bool fontUnderline);
	int levelTextRedColor, levelTextGreenColor, levelTextBlueColor;
	int inputTextRedColor, inputTextGreenColor, inputTextBlueColor;
	int bgRedColor, bgGreenColor, bgBlueColor;
	int paperRedColor, paperGreenColor, paperBlueColor;
	bool customLevelTextColor, customInputTextColor, customBgColor, customPaperColor;
	void saveColorSettings(void);
	void setColors(void);
	void updateTheme(void);
	bool customLevelLoaded;
	bool customConfig;
	QTranslator *translator;
	void refreshAll(void);

private:
	Ui::OpenTyper *ui;
	void connectAll(void);

private slots:
    void keyPress(QKeyEvent *event);
    void openOptions(void);
    void openPack(void);
    void repeatLevel(void);
    void nextLevel(void);
    void previousLevel(void);
    void updateCurrentTime(void);
    void lessonSelectionListIndexChanged(int index);
    void sublessonSelectionListIndexChanged(int index);
    void levelSelectionListIndexChanged(int index);
    void randomOrderCheckBoxChanged(bool checked);
    void spaceNewlineCheckBoxChanged(bool checked);
    void openExerciseFromFile(void);
    void changeLanguage(int index);

public slots:
	void openEditor(void);
};

#endif // OPENTYPER_H
