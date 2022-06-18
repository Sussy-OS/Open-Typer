/*
 * utils.cpp
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

#include "core/utils.h"

/*! Returns number of words in the string. */
int stringUtils::wordCount(QString str)
{
	int i, out = 0;
	for(i=0; i < str.count(); i++)
	{
		if(str[i] == ' ')
			out++;
	}
	if(str[i] != ' ')
		out++;
	return out;
}

/*! Returns a word in the string. */
QString stringUtils::word(QString str, int id)
{
	int i, cur = 0;
	QString out = "";
	for(i=0; i < str.count(); i++)
	{
		if((str[i] == ' ') || (i+1 == str.count()))
		{
			cur++;
			if(i+1 == str.count())
				out += str[i];
			if(cur == id)
				return out;
			out = "";
		}
		else
			out += str[i];
	}
	return "";
}

/*! Returns the word at index. */
QString stringUtils::wordAt(QString str, int index)
{
	if(str[index] == ' ')
		return "";
	QString currentWord = "";
	for(int i=0; i < str.count(); i++)
	{
		if((str[i] == ' ') || (i+1 >= str.count()))
		{
			if(i+1 >= str.count())
				currentWord += str[i];
			if(i > index)
				return currentWord;
			currentWord = "";
		}
		else
			currentWord += str[i];
	}
	return "";
}

/*! Returns the length of the longest common subsequence of source and target list. */
int stringUtils::lcsLen(QList<QVariant> source, QList<QVariant> target)
{
	QMap<int, QMap<int, int>> table;
	return lcsLen(source, target, &table);
}

int stringUtils::lcsLen(QList<QVariant> source, QList<QVariant> target, QMap<int, QMap<int, int>> *lcsTable)
{
	/*
	* References:
	* https://www.geeksforgeeks.org/printing-longest-common-subsequence/
	* https://nasauber.de/blog/2019/levenshtein-distance-and-longest-common-subsequence-in-qt/
	*/
	QMap<int, QMap<int, int>> l;
	for (int i = 0; i <= source.count(); i++)
	{
		for (int j = 0; j <= target.count(); j++)
		{
			if (i == 0 || j == 0)
				l[i][j] = 0;
			else if (source.at(i - 1) == target.at(j - 1))
				l[i][j] = l[i - 1][j - 1] + 1;
			else
				l[i][j] = std::max(l[i - 1][j], l[i][j - 1]);
		}
	}
	*lcsTable = l;
	return l[source.count()][target.count()];
}

/*! Returns the longest common subsequence of source and target list. */
QList<QVariant> stringUtils::longestCommonSubsequence(QList<QVariant> source, QList<QVariant> target)
{
	QMap<int, QMap<int, int>> l;
	lcsLen(source, target, &l);
	int i = source.count();
	int j = target.count();
	QList<QVariant> longestCommonSubsequence;
	while (i > 0 && j > 0)
	{
		if(i == 0)
			j--;
		else if(j == 0)
			i--;
		else if (source.at(i - 1) == target.at(j - 1))
		{
			longestCommonSubsequence.prepend(source.at(i-1));
			i--;
			j--;
		}
		else if (l[i][j] == l[i-1][j])
			i--;
		else
			j--;
	}
	return longestCommonSubsequence;
}

/*! Returns the longest common subsequence of source and target string. */
QString stringUtils::longestCommonSubsequence(QString source, QString target)
{
	QList<QVariant> sourceList, targetList;
	int i;
	for(i=0; i < source.count(); i++)
		sourceList += QString(source[i]);
	for(i=0; i < target.count(); i++)
		targetList += QString(target[i]);
	QList<QVariant> lcs = longestCommonSubsequence(sourceList, targetList);
	QString out = "";
	for(i=0; i < lcs.count(); i++)
		out += lcs[i].toString();
	return out;
}

/*! Compares 2 lists using longest common subsequence. */
QList<QVariantMap> stringUtils::compareLists(QList<QVariant> source, QList<QVariant> target, QVector<QPair<QString,int>> *recordedCharacters, int *hits, int *inputPos)
{
	QList<QVariantMap> out;
	auto lcs = longestCommonSubsequence(source, target);
	int sourcePos = 0, targetPos = 0;
	int count = std::max(source.count(), target.count());
	for(int i=0; i < count; i++)
	{
		QVariant subseq, sourceSubseq, targetSubseq;
		bool lcsSrc = false, lcsTarget = false;
		if(i < lcs.count())
		{
			subseq = lcs[i];
			if(sourcePos < source.count())
			{
				sourceSubseq = source[sourcePos];
				lcsSrc = (subseq == sourceSubseq);
			}
			if(targetPos < target.count())
			{
				targetSubseq = target[targetPos];
				lcsTarget = (subseq == targetSubseq);
			}
		}
		else
		{
			lcsSrc = true;
			lcsTarget = true;
			if(sourcePos < source.count())
			{
				sourceSubseq = source[sourcePos];
				lcsSrc = false;
			}
			if(targetPos < target.count())
			{
				targetSubseq = target[targetPos];
				lcsTarget = false;
			}
			if((lcsSrc && !lcsTarget) || (!lcsSrc && lcsTarget))
				i++;
			if(sourcePos >= source.count() && targetPos >= target.count())
			{
				lcsSrc = true;
				lcsTarget = true;
			}
		}
		if(!lcsSrc && !lcsTarget)
		{
			// Changed character
			QVariantMap diff;
			diff["pos"] = targetPos;
			diff["type"] = "change";
			diff["previous"] = sourceSubseq;
			diff["previousPos"] = sourcePos;
			out += diff;
			targetPos++;
			if(inputPos)
				*inputPos += 1;
			sourcePos++;
			i--;
		}
		else if(!lcsSrc)
		{
			// Deleted character
			QVariantMap diff;
			diff["pos"] = targetPos;
			diff["type"] = "deletion";
			diff["previous"] = sourceSubseq;
			diff["previousPos"] = sourcePos;
			out += diff;
			sourcePos++;
			i--;
		}
		else if(!lcsTarget)
		{
			// Added character
			QVariantMap diff;
			diff["pos"] = targetPos;
			diff["type"] = "addition";
			out += diff;
			targetPos++;
			if(inputPos)
				*inputPos += 1;
			i--;
		}
		else
		{
			if(recordedCharacters && (*inputPos < recordedCharacters->count()) && hits && inputPos)
			{
				*hits += recordedCharacters->at(*inputPos).second;
				*inputPos += 1;
			}
			sourcePos++;
			targetPos++;
		}
	}
	return out;
}

/*! Compares 2 strings using longest common subsequence. */
QList<QVariantMap> stringUtils::compareStrings(QString source, QString target, QVector<QPair<QString,int>> *recordedCharacters, int *hits, int *inputPos)
{
	QList<QVariant> sourceList, targetList;
	int i;
	for(i=0; i < source.count(); i++)
		sourceList += QString(source[i]);
	for(i=0; i < target.count(); i++)
		targetList += QString(target[i]);
	return compareLists(sourceList, targetList, recordedCharacters, hits, inputPos);
}

/*! Splits each word by punctuation marks. */
QStringList stringUtils::splitWordsByPunct(QStringList source)
{
	QStringList out;
	for(int i=0; i < source.count(); i++)
	{
		QString part = "";
		bool ignore = (source[i].count() > 0);
		for(int j=0; j < source[i].count(); j++)
		{
			if(source[i][j].isPunct())
			{
				if(!ignore)
					out += part;
				ignore = true;
				part = "";
				if(j == 0)
					out += " ";
				out += QString(source[i][j]);
				if(j+1 == source[i].count())
					out += " ";
			}
			else
			{
				part += source[i][j];
				ignore = false;
			}
		}
		if(ignore)
			ignore = false;
		else
			out += part;
	}
	return out;
}

/*! Compares input text with exercise text and finds mistakes. */
QList<QVariantMap> stringUtils::findMistakes(QString exerciseText, QString input, QVector<QPair<QString,int>> recordedCharacters, int *totalHits, QStringList *errorWords)
{
	QList<QVariantMap> out;
	int i;
	// Split lines
	QStringList exerciseLines = exerciseText.split('\n');
	QStringList inputLines = input.split('\n');
	// Split words in each line
	QStringList exerciseWords, inputWords;
	for(i=0; i < exerciseLines.count(); i++)
	{
		if(i > 0)
			exerciseWords += "\n";
		exerciseWords += exerciseLines[i].split(' ');
	}
	exerciseWords = splitWordsByPunct(exerciseWords);
	for(i=0; i < inputLines.count(); i++)
	{
		if(i > 0)
			inputWords += "\n";
		inputWords += inputLines[i].split(' ');
	}
	inputWords = splitWordsByPunct(inputWords);
	// Compare word lists
	QList<QVariant> sourceList, targetList;
	for(i=0; i < exerciseWords.count(); i++)
		sourceList += exerciseWords[i];
	for(i=0; i < inputWords.count(); i++)
		targetList += inputWords[i];
	QList<QVariantMap> wordDiff = compareLists(sourceList, targetList);
	QMap<int, QVariantMap*> differences;
	for(i=0; i < wordDiff.count(); i++)
	{
		if(differences.contains(wordDiff[i]["pos"].toInt()))
		{
			QVariantMap currentMap = *(differences[wordDiff[i]["pos"].toInt()]);
			if(currentMap.contains("previous"))
				currentMap["previous"] = currentMap["previous"].toString() + " " + wordDiff[i]["previous"].toString();
			*(differences[wordDiff[i]["pos"].toInt()]) = currentMap;
		}
		else
			differences[wordDiff[i]["pos"].toInt()] = &wordDiff[i];
	}
	if(errorWords)
		errorWords->clear();
	int pos = 0, hits = 0;
	for(i=0; i < inputWords.count(); i++)
	{
		QString nextWord = "";
		if(i < inputWords.count())
			nextWord = inputWords[inputWords.count()-1];
		if((i > 0) && (inputWords[i] != "\n") && (nextWord != "\n"))
		{
			if((inputWords[i] != " ") && (pos < recordedCharacters.count()))
				hits += recordedCharacters[pos].second;
			pos++;
		}
		if(inputWords[i][0].isPunct())
			pos--;
		else if((i > 0) && (inputWords[i-1] == " "))
			pos--;
		if(inputWords[i] == " ")
			pos--;
		else if(((i > 0) && inputWords[i-1][0].isPunct()) && !inputWords[i][0].isPunct())
			pos--;
		if(differences.contains(i))
		{
			if(errorWords)
				errorWords->append(differences[i]->value("previous").toString());
			if(differences[i]->value("type").toString() == "change")
			{
				int wordStart = pos;
				auto diff = compareStrings(differences[i]->value("previous").toString(), inputWords[i], &recordedCharacters, &hits, &pos);
				QList<QVariantMap> toRemove;
				// Ensure there's max. one mistake per 6 characters
				int lastMistakePos = -1;
				for(int i2=0; i2 < diff.count(); i2++)
				{
					if((lastMistakePos != -1) && (diff[i2]["pos"].toInt() / 6 == lastMistakePos / 6))
						diff[i2].insert("disable", true);
					else
						lastMistakePos = diff[i2]["pos"].toInt();
				}
				for(int i2=0; i2 < toRemove.count(); i2++)
					diff.removeAll(toRemove[i2]);
				// Translate mistake position
				for(int i2=0; i2 < diff.count(); i2++)
				{
					QVariantMap currentMap = diff[i2];
					if((currentMap["type"].toString() == "deletion") && (currentMap["previous"].toString() == " "))
						currentMap["pos"] = currentMap["pos"].toInt() - 1;
					currentMap["pos"] = wordStart + currentMap["pos"].toInt();
					if(currentMap["type"].toString() != "deletion")
						pos--;
					diff[i2] = currentMap;
				}
				out += diff;
			}
			else if(differences[i]->value("type").toString() == "deletion")
			{
				QVariantMap currentMap = *differences[i];
				currentMap["pos"] = pos > 0 && !inputWords[i][0].isPunct() ? pos-1 : pos;
				out += currentMap;
				pos += inputWords[i].count();
			}
			else if(differences[i]->value("type").toString() == "addition")
			{
				int k = i, previousPos = -1;
				bool disable = false;
				do {
					if(k > i)
					{
						pos++;
						if(inputWords[k][0].isPunct())
							pos--;
						else if((k > 0) && (inputWords[k-1] == " "))
							pos--;
						if(inputWords[k] == " ")
							pos--;
						else if(((k > 0) && inputWords[k-1][0].isPunct()) && !inputWords[k][0].isPunct())
							pos--;
						for(int l=0; l < pos - previousPos; l++)
						{
							QVariantMap currentMap = *differences[k];
							currentMap["pos"] = previousPos+l;
							currentMap["disable"] = disable;
							disable = true;
							out += currentMap;
						}
					}
					if(inputWords[k].count() == 0)
					{
						QVariantMap currentMap = *differences[k];
						currentMap["pos"] = pos;
						currentMap["disable"] = disable;
						disable = true;
						out += currentMap;
					}
					else
					{
						for(int j=0; j < inputWords[k].count(); j++)
						{
							QVariantMap currentMap = *differences[k];
							currentMap["pos"] = pos;
							currentMap["disable"] = disable;
							disable = true;
							out += currentMap;
							pos++;
						}
					}
					previousPos = pos;
					k++;
				} while((differences.contains(k)) && (differences[k]->value("type").toString() == "addition"));
				i = k-1;
				// TODO: Should we count hits in added words?
			}
		}
		else if(inputWords[i] != "\n")
		{
			for(int i2=0; i2 < inputWords[i].count(); i2++)
			{
				if(pos < recordedCharacters.count())
					hits += recordedCharacters[pos].second;
				pos++;
			}
		}
	}
	if(totalHits)
		*totalHits = hits;
	return out;
}

/*!
 * Returns the path to the program configuration directory.\n
 * For example: <tt>/home/user/.config/Open-Typer</tt>
 */
QString fileUtils::configLocation(void)
{
	QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/Open-Typer";
	QDir dir;
	dir.mkpath(path);
	return path;
}

/*! Returns the path to the main configuration file, currently \c config.ini in the program configuration directory. */
QString fileUtils::mainSettingsLocation(void)
{
	return configLocation()+"/config.ini";
}

/*!
 * Returns true if the key is a special key.\n
 * Special keys are ignored by OpenTyper#keyPress().
 * \see OpenTyper#keyPress()
 */
bool keyboardUtils::isSpecialKey(QKeyEvent *event)
{
	if((event->text() == "") && (event->key() != Qt::Key_Return) && (event->key() != Qt::Key_Enter))
		return true;
	switch(event->key()) {
		case Qt::Key_Delete:
			return true;
			break;
		case Qt::Key_Backspace:
			return true;
			break;
		case Qt::Key_Backtab:
			return true;
			break;
		case Qt::Key_Escape:
			return true;
			break;
		default:
			return false;
			break;
	}
}

#if QT_VERSION <= QT_VERSION_CHECK(5, 10, 0)
#define LAST_DEAD_KEY Qt::Key_Dead_Horn
#else
#define LAST_DEAD_KEY Qt::Key_Dead_Longsolidusoverlay
#endif

/*! Returns true if the key code belongs to a dead key. */
bool keyboardUtils::isDeadKey(int key)
{
	return ((key >= Qt::Key_Dead_Grave) && (key <= LAST_DEAD_KEY));
}
