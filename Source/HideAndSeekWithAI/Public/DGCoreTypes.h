#pragma once

UENUM()
enum class EDGTeams :uint8
{
	Players = 0,
	Bots = 1,
	NoTeam = 255
};

UENUM()
enum class EDGMovementSpeedMode :uint8
{
	Default = 0,
	Chase = 1,
	Return = 2,
	CheckPlace = 3
};
