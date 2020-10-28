// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AShooterGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	int8 count;
	void PawnKilled(AActor *KilledActor);
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LooseScreen;

protected:
	virtual void BeginPlay() override;
};