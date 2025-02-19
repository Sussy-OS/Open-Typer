/*
 * CharacterRecord.cpp
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

#include "CharacterRecord.h"

/*! Sets key text (should be a single character). */
void CharacterRecord::setKeyText(QString text)
{
	m_keyText = text;
}

/*! Returns key text. */
QString CharacterRecord::keyText(void)
{
	return m_keyText;
}

/*! Sets number of key hits used to compose the character. */
void CharacterRecord::setHits(int count)
{
	m_hits = count;
}

/*! Returns number of key hits used to compose the character. */
int CharacterRecord::hits(void)
{
	return m_hits;
}
