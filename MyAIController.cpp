#include "MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
/*
void AMyAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    if (AssignedMainPawn)
    {

    }
}*/
void AMyAIController::BeginPlay() 
{
    Super::BeginPlay();
    PrimaryActorTick.bCanEverTick = false;
    if (UGameplayStatics::GetPlayerPawn(GetWorld(),0))
    {
        MainPawn=UGameplayStatics::GetPlayerPawn(GetWorld(),0);
        UE_LOG(LogTemp,Warning,TEXT("Main Player Found"));
        AssignedMainPawn=true;   
    }
}
