/*
 * Copyright 2010-2019 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "../Engine/Action.h"
#include "../Engine/Game.h"
#include "../Engine/Options.h"
#include "../Interface/Text.h"
#include "../Interface/TextButton.h"
#include "../Interface/TextList.h"
#include "../Interface/Window.h"
#include "../Mod/Mod.h"
#include "../Savegame/SavedBattleGame.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/BattleUnit.h"
#include "SoldierExperienceState.h"
#include<string>

namespace OpenXcom
{

/**
 * Initializes all the elements in the Soldier experience window.
 */
SoldierExperienceState::SoldierExperienceState(BattleUnit *bu)
{
	_screen = false;
	UnitStats *us = bu->getExperience();
	// Create objects
	_window = new Window(this, 216, 160, 52, 20, POPUP_BOTH);
	_txtTitle = new Text(206, 17, 57, 32);
	_btnCancel = new TextButton(140, 16, 90, 156);
	_lstSoldierExperience = new TextList(180, 96, 65, 52);

	// Set palette
	_game->getSavedGame()->getSavedBattle()->setPaletteByDepth(this);

	add(_window, "messageWindowBorder", "battlescape");
	add(_txtTitle, "messageWindows", "battlescape");
	add(_btnCancel, "messageWindowButtons", "battlescape");
	add(_lstSoldierExperience, "optionLists", "battlescape");

	centerAllSurfaces();

	// Set up objects
	_window->setHighContrast(true);
	_window->setBackground(_game->getMod()->getSurface("TAC00.SCR"));

	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setBig();
	_txtTitle->setHighContrast(true);
	_txtTitle->setText(tr("STR_STATS"));
	_btnCancel->setText(tr("STR_CANCEL_UC"));
	_btnCancel->setHighContrast(true);
	_btnCancel->onMouseClick((ActionHandler)&SoldierExperienceState::btnCancelClick);
	_btnCancel->onKeyboardPress((ActionHandler)&SoldierExperienceState::btnCancelClick, Options::keyCancel);

	_lstSoldierExperience->setColumns(2, 107, 10);
	_lstSoldierExperience->setSelectable(true);
	_lstSoldierExperience->setBackground(_window);
	_lstSoldierExperience->setMargin(1);
	_lstSoldierExperience->setAlign(ALIGN_CENTER);
	_lstSoldierExperience->setHighContrast(true);
	_lstSoldierExperience->setWordWrap(true);

	//Use std::ostringstream.str().c_str() ?
	if (us->bravery)     _lstSoldierExperience->addRow(2, tr("STR_BRAVERY").c_str(), ( std::to_string(us->bravery).c_str() ));
	if (us->reactions)   _lstSoldierExperience->addRow(2, tr("STR_REACTIONS").c_str(), std::to_string(us->reactions).c_str());
	if (us->firing)      _lstSoldierExperience->addRow(2, tr("STR_FIRING").c_str(), std::to_string(us->firing).c_str());
	if (us->throwing)    _lstSoldierExperience->addRow(2, tr("STR_THROWING_ACCURACY").c_str(), std::to_string(us->throwing).c_str());
	if (us->melee)       _lstSoldierExperience->addRow(2, tr("STR_MELEE_ACCURACY").c_str(), std::to_string(us->melee).c_str());
	if (us->mana)        _lstSoldierExperience->addRow(2, tr("STR_MANA").c_str(), std::to_string(us->mana).c_str());
	if (us->psiSkill)    _lstSoldierExperience->addRow(2, tr("STR_PSIONIC_SKILL").c_str(), std::to_string(us->psiSkill).c_str());
	if (us->psiStrength) _lstSoldierExperience->addRow(2, tr("STR_PSIONIC_STRENGTH").c_str(), std::to_string(us->psiStrength).c_str());
}

/**
 * Returns to the previous screen.
 * @param action Pointer to an action.
 */
void SoldierExperienceState::btnCancelClick(Action *)
{
	_game->popState();
}

}
