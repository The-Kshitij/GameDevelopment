#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
// Sets default values
AGun::AGun()
{ 	
	//I am not using tick 
	PrimaryActorTick.bCanEverTick = false;
	Root=CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	//Assigning the root component
	RootComponent=Root;
	Mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh "));
	Mesh->SetupAttachment(Root);

}

void AGun::Fire()
{
	if (Emitter)
	{
		UGameplayStatics::SpawnEmitterAttached(Emitter,Mesh,TEXT("MuzzleFlashSocket"));
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("UParticleSystem not found for gun(Emitter)"));
	}
	//The player is the owner of this
	APawn *GunShooter=Cast<APawn>(GetOwner());
	if (GunShooter)
	{
		AController *GunShooterController=GunShooter->GetController();
		FVector Location,LineEnd;
		FRotator Rotation;
		if (GunShooterController)
		{
			GunShooterController->GetPlayerViewPoint(Location,Rotation);
			LineEnd=Location+Rotation.Vector()*RangeForWeapon;
			FHitResult Hit;
			FCollisionQueryParams Param;
			//Don't want the bullet hitting the player now.
			Param.AddIgnoredActor(this);
			Param.AddIgnoredActor(GetOwner());
			if (GetWorld()->LineTraceSingleByChannel(Hit,Location,LineEnd,ECollisionChannel::ECC_GameTraceChannel1,Param))
			{
				//DrawDebugPoint(GetWorld(),Hit.Location,20.f,FColor::Red,true);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitEffect,Hit.Location,(Rotation*-1));
				AActor *ActorBeingHit=Hit.GetActor();				
				if (ActorBeingHit)
				{
					//just to be sure
					if (ActorBeingHit!=GunShooter)
					{
						if (HitSound)
						{
							UGameplayStatics::PlaySoundAtLocation(GetWorld(),HitSound,Hit.Location);
						}
						//Because the hit effect would have a rotation opposite to that of the player
						FPointDamageEvent DamageEvent(Damage,Hit,(Rotation*-1).Vector(),nullptr);
						float DamageCheck=ActorBeingHit->TakeDamage(Damage,DamageEvent,GunShooterController->GetInstigatorController(),GunShooter);
						UE_LOG(LogTemp,Warning,TEXT("Damage in gun.cpp: %f"),DamageCheck);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Controller not found in gun.cpp line 43"));
		}
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("Owner not found in gun.cpp line 32"));
	}
}

// Called when the game starts or when spawned
/*
void AGun::BeginPlay()
{
	Super::BeginPlay();
}
/*
// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
