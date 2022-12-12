/*
 * MistakeRecord.h
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

#ifndef MISTAKERECORD_H
#define MISTAKERECORD_H

#if defined CORE_SHARED_LIB
#define CORE_LIB_EXPORT Q_DECL_EXPORT
#else
#define CORE_LIB_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>

/*! \brief The MistakeRecord class can be used to store mistake records. */
class CORE_LIB_EXPORT MistakeRecord : public QObject
{
		Q_OBJECT
		Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
		Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
		Q_PROPERTY(QString previousText READ previousText WRITE setPreviousText NOTIFY previousTextChanged)
	public:
		enum Type
		{
			Type_Addition,
			Type_Deletion,
			Type_Change
		};
		Q_ENUM(Type)

		void setPosition(int pos);
		int position(void);
		void setType(Type type);
		Type type(void);
		void setPreviousText(QString text);
		QString previousText(void);

	private:
		int m_position;
		Type m_type;
		QString m_previousText;

	signals:
		void positionChanged(int pos);
		void typeChanged(MistakeRecord::Type type);
		void previousTextChanged(QString text);
};

#endif // MISTAKERECORD_H
