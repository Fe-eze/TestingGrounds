// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 1 Get Patrol Points
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn(); // get controlled pawn from AI component
	auto PatrolRoute = CurrentPawn->FindComponentByClass<UPatrolRouteComponent>(); // cast to patrolling guard
	auto PatrolPointsi = PatrolRoute->GetPatrolPoints(); // read value of patrolpt array of current pawn (patrolling guard) and set local patrol pt variable to current pawn pp var

	// ******************start Protection
	// Protect against empty pointers
	if (PatrolPointsi.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("You didn't add PatrolPoints to the foloowing Actor %s"), *CurrentPawn->GetActorLabel()) //TODO add guard name that's missing patrolpt
		return EBTNodeResult::Failed;
	}
	
	if (!ensure(PatrolRoute)) {	return EBTNodeResult::Failed;} // protect against no patrol route comp
	// ******************end protection

	// 2 Set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Indexi = BlackboardComp->GetValueAsInt(Index.SelectedKeyName); // get bb val as int
	//auto bbval = PatrolPointsi[Indexi]; // use indexi as index to look thru local patrol pts array
	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, PatrolPointsi[Indexi]); // set bb value as object

	// 3 Cycle Index
	auto NextIndex = (Indexi +1) % PatrolPointsi.Num(); // return new indexi = indexi modulo patrolpointsi.length
	BlackboardComp->SetValueAsInt(Index.SelectedKeyName, NextIndex);
	
	return EBTNodeResult::Succeeded;
}


