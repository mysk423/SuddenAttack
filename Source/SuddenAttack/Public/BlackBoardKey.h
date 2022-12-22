// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

namespace BB_keys {
	const TCHAR * const target_location = TEXT("TargetLocation");
	const TCHAR * const can_see_player = TEXT("CanSeePlayer");
	const TCHAR * const player_is_in_melee_range = TEXT("IsPlayerInMeRange");
}

class SUDDENATTACK_API BlackBoardKey
{
public:
	BlackBoardKey();
	~BlackBoardKey();
};
