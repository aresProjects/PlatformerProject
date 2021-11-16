// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPCharacter.generated.h"

UCLASS()
class PLATFORMERPROJECT_API ATPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float armLenght;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	FRotator rotationRate;
	
	// Camera arm (boom) using SpringArm Component
	// Moves the camera close to the target whenever there's a collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* cameraArm;
	
	// Camera Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void LookX(float val);
	void LookY(float val);
	void MoveX(float val);
	void MoveY(float val);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};