#include "ShooterGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"
void AShooterGameGameModeBase::PawnKilled(AActor *KilledActor)
{
    if (KilledActor)
    {
        if (KilledActor==UGameplayStatics::GetPlayerPawn(GetWorld(),0))
        {
            UE_LOG(LogTemp,Warning,TEXT("Main Player Has been Killed"));
            UUserWidget *LostScreen=CreateWidget(GetWorld(),LooseScreen);
			if (LostScreen)
			{
				LostScreen->AddToViewport();
			}
            if (UGameplayStatics::GetPlayerController(GetWorld(),0))
            {
                APlayerController *Controller=UGameplayStatics::GetPlayerController(GetWorld(),0);
                Controller->GameHasEnded(nullptr,false);
            }
        }
        count--;
    }
}

void AShooterGameGameModeBase::BeginPlay() 
{
    TArray<AActor *> FoundCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),AMainCharacter::StaticClass(),FoundCharacters);
    count=FoundCharacters.Num();
    UE_LOG(LogTemp,Warning,TEXT("Number of Characters: %i"),count);
}