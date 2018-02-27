// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO Protect against empty pointers

	// 1 Get Patrol Points
	// Get AI controller
	auto AIComp = OwnerComp.GetAIOwner();
	auto CurrentPawn = AIComp->GetPawn(); // get controlled pawn
	auto PatrollingGuard = Cast<APatrollingGuard>(CurrentPawn); // cast to patrolling guard
	auto PatrolPointsi = PatrollingGuard->PatrolPoints; // read value of patrolpt array of current pawn (patrolling guard)
	// set local patrol pt variable to current pawn pp var

	// 2 Set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Indexi = BlackboardComp->GetValueAsInt(Index.SelectedKeyName); // get bb val as int
	auto bbval = PatrolPointsi[Indexi]; // use indexi as index to look thru local patrol pts array
	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, bbval); // set bb value as object

	// 3 Cycle Index
	auto NextIndex = (Indexi +1) % PatrolPointsi.Num(); // return new indexi = indexi modulo patrolpointsi.length
	BlackboardComp->SetValueAsInt(Index.SelectedKeyName, NextIndex);
	
	return EBTNodeResult::Succeeded;
}


