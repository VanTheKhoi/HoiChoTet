// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Interfaces/ReactToTriggerInterface.h"


// Add default functionality here for any IReactToTriggerInterface functions that are not pure virtual.
bool IReactToTriggerInterface::CanPossess()
{
	return true;
}

void IReactToTriggerInterface::TalkToPlayer(){}
