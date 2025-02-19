/*
 * Key.cpp
 * This file is part of Open-Typer
 *
 * Copyright (C) 2023 - adazem009
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

#include <QMetaEnum>
#include "Key.h"

/*! Constructs Key. */
Key::Key() { }

/*! Constructs Key (with properties). */
Key::Key(QString text, QString shiftText)
{
	setText(text);
	setDisplayText(text);
	setShiftText(shiftText);
	setDisplayShiftText(shiftText);
}

/*! The text for this key. */
QString Key::text(void)
{
	return m_text;
}

void Key::setText(QString text)
{
	m_text = text;
}

/*! The text for this key when pressed with shift. */
QString Key::shiftText(void)
{
	return m_shiftText;
}

void Key::setShiftText(QString text)
{
	m_shiftText = text;
}

/*! The type of the key. */
KeyboardUtils::KeyType Key::type(void)
{
	return m_type;
}

/*! Sets the key type. */
void Key::setType(KeyboardUtils::KeyType type)
{
	m_type = type;
}

/*! The text visible on the keyboard. */
QString Key::displayText(void)
{
	return m_displayText;
}

void Key::setDisplayText(QString text)
{
	m_displayText = text;
}

/*! The text (for combination with the shift key) visible on the keyboard. */
QString Key::displayShiftText(void)
{
	return m_displayShiftText;
}

void Key::setDisplayShiftText(QString text)
{
	m_displayShiftText = text;
}

/*! True if this is a dead key. */
bool Key::isDead(void)
{
	return m_dead;
}

void Key::setDead(bool dead)
{
	m_dead = dead;
}

/*! True if this is a dead key when pressed with shift. */
bool Key::isShiftDead(void)
{
	return m_shiftDead;
}

void Key::setShiftDead(bool dead)
{
	m_shiftDead = dead;
}
