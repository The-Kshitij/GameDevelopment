#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

UCLASS()
class SHOOTERGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool AssignedMainPawn=false;
	AActor *MainPawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};