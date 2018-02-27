// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"

/*
A route card to help AI Choose their next waypoint
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	TArray<AActor*> GetPatrolPoints() const; // getter function
	
private:
	UPROPERTY(EditInstanceOnly, Category = "/ C++ Patrol Route")
	TArray<AActor*> PatrolPoints;
		
	
};
