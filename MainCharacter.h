// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class AGun;
UCLASS()
class SHOOTERGAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();
	float Health,Time;
	bool dead=false;
	
	void Shoot();
	
	void SetHitRotation(FRotator RotationOfShot);

	UFUNCTION(BlueprintPure)
	bool IsDead();

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage();

	UPROPERTY(EditAnywhere)
	USoundBase *FireSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAIPerceptionComponent> PerceptionType;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	AGun *Gun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	virtual float TakeDamage(float Damage,struct FDamageEvent const &DamageEvent,AController *EventInstigator,AActor *DamageCauser) override;

protected:
	void MovementForwardBackward(float AxisValue);
	void MovementLeftRight(float AxisValue);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
