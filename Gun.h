/*
The fire function of is called from outside this object when the player wants to fire the weapon. If the bullet hits somethings then a hiteffect is spawned at that place. A line
trace is performed to check for any object in range. The player is made the owner of the weapon in the player script
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERGAME_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void Fire();

private:
	//For storing the root component
	UPROPERTY(VisibleAnywhere)
	USceneComponent *Root;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem *Emitter;

	UPROPERTY(EditAnywhere)
	UParticleSystem *HitEffect;

	UPROPERTY(EditAnywhere)
	USoundBase *HitSound;

	UPROPERTY(EditAnywhere)
	float Damage=50.f;

/*
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/
};
