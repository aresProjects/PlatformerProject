// Fill out your copyright notice in the Description page of Project Settings.


#include "TPCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATPCharacter::ATPCharacter()
{
 	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set default values
	ArmLenght = 300.0f;
	RotationRate = FRotator(0, 500.0f, 0);
	
	// Camera Arm (Boom)
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));  // Add component
	CameraArm->SetupAttachment(RootComponent);                                   // Attach to "RootComponent"
	CameraArm->TargetArmLength = ArmLenght;	                                     // Set length
	CameraArm->bUsePawnControlRotation = true;                                   // Enable pawn controlled rotation
	
	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));           // Add component
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);         // Attach to "cameraBoom" (at the end of the spring arm)
	Camera->bUsePawnControlRotation = false;                                     // Disable pawn controlled rotation
	
	// Disable mesh rotation
	bUseControllerRotationPitch = bUseControllerRotationRoll = bUseControllerRotationYaw = false;
	
	// Change mesh by movement input
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = RotationRate;
}

// Called when the game starts or when spawned
void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("LookX", this, &ATPCharacter::LookX);
	PlayerInputComponent->BindAxis("LookY", this, &ATPCharacter::LookY);
	PlayerInputComponent->BindAxis("MoveX", this, &ATPCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &ATPCharacter::MoveY);
}

void ATPCharacter::LookX(const float Val)
{
	AddControllerYawInput(Val * (45.0f * GetWorld()->GetDeltaSeconds()));
}

void ATPCharacter::LookY(const float Val)
{
	AddControllerPitchInput(Val * (45.0f * GetWorld()->GetDeltaSeconds()));
}

void ATPCharacter::MoveX(const float Val)
{
	if (Controller == nullptr || Val == 0.0f) return;
	
	const FRotator Rotation = Controller->GetControlRotation();		// Returns controller rotation
	const FRotator Yaw = FRotator(0, Rotation.Yaw, 0);	// Save yaw rotation
	const FVector Dir = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y); // Get direction (normalized)
	
	// Apply movement
	AddMovementInput(Dir, Val);
}

void ATPCharacter::MoveY(const float Val)
{
	if (Controller == nullptr || Val == 0.0f) return;
	
	const FRotator Rotation = Controller->GetControlRotation();		// Returns controller rotation
	const FRotator Yaw = FRotator(0, Rotation.Yaw, 0);	// Save yaw rotation
	const FVector Dir = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X); // Get direction (normalized)
	
	// Apply movement
	AddMovementInput(Dir, Val);
}