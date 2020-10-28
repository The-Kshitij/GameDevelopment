#include "MainCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ShooterGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health=100.f;
	Gun=GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("Weapon_Socket"));
	Gun->SetOwner(this);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (dead)
	{
		//UE_LOG(LogTemp,Warning,TEXT("Time in tick: %f"),UGameplayStatics::GetTimeSeconds(GetWorld()));
		if (UGameplayStatics::GetTimeSeconds(GetWorld())-Time>10)
		{
			UE_LOG(LogTemp,Error,TEXT("Time in tick: %f"),UGameplayStatics::GetTimeSeconds(GetWorld()));
			DetachFromControllerPendingDestroy();
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			APlayerController *SController=Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
			//SController->DisableInput(SController);
			if (SController)
			{
				SController->RestartLevel();	
			}
			else
			{
				UE_LOG(LogTemp,Error,TEXT("No SController"));
			}
		}
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&AMainCharacter::Shoot);
	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"),this,&AMainCharacter::MovementForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"),this,&AMainCharacter::MovementLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"),this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"),this,&APawn::AddControllerYawInput);

}
void AMainCharacter::MovementForwardBackward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector()*AxisValue);
}
void AMainCharacter::MovementLeftRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector()*AxisValue);
}
void AMainCharacter::Shoot()
{
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),FireSound,GetActorLocation());
	}
	Gun->Fire();
}
float AMainCharacter::TakeDamage(float Damage,struct FDamageEvent const &DamageEvent,AController *EventInstigator,AActor *DamageCauser)
{
	float DamageToApply=Super::TakeDamage(Damage,DamageEvent,EventInstigator,DamageCauser);
	DamageToApply=FMath::Min(Health,DamageToApply);
	Health-=DamageToApply;
	//UE_LOG(LogTemp,Warning,TEXT("Health: %f"),Health);
	if ((dead==false)&&(IsDead()))
	{
		AShooterGameGameModeBase *GameMode=Cast<AShooterGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->PawnKilled(this);
			Time=UGameplayStatics::GetTimeSeconds(GetWorld());
			UE_LOG(LogTemp,Warning,TEXT("Dead Time: %f"),Time);
			if (this==UGameplayStatics::GetPlayerPawn(GetWorld(),0))
			{
				dead=true;
			}
			else
			{
				DetachFromControllerPendingDestroy();
				GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("GameMode not found"));
		}
	}
	return DamageToApply;
}
bool AMainCharacter::IsDead()
{
	return (Health<=0);
}

float AMainCharacter::GetHealthPercentage() 
{
	return (Health/100);
}