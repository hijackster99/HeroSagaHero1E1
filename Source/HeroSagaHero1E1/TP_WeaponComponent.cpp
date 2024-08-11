// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "HeroSagaHero1E1Character.h"
#include "HeroSagaHero1E1Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TraceChannels.h"
#include "EnemyCharacter.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
}


void UTP_WeaponComponent::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{

		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = PlayerController->PlayerCameraManager->GetCameraLocation();

		FHitResult res;
		//World->LineTraceSingleByObjectType(res, SpawnLocation, (SpawnRotation.Quaternion().GetForwardVector() * 10) + SpawnLocation, FCollisionObjectQueryParams::DefaultObjectQueryParam);
		World->LineTraceSingleByChannel(res, SpawnLocation, (SpawnRotation.Quaternion().GetForwardVector() * 1000) + SpawnLocation, TraceChannels::Team2);

		DrawDebugLine(GetWorld(), res.TraceStart, res.TraceEnd, FColor::Red, false, 10.0f, 0, 3.0f);

		if (res.GetActor() != nullptr)
		{
			auto component = res.GetActor()->GetComponentByClass(UEnemyCharacter::StaticClass());
			UEnemyCharacter* enemy = dynamic_cast<UEnemyCharacter*>(component);

			if (enemy != nullptr)
			{
				enemy->Hit(4);
			}
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::AttachWeapon(AHeroSagaHero1E1Character* TargetCharacter)
{
	Character = TargetCharacter;
	UE_LOG(LogTemp, Warning, TEXT("Attatch we22222222apon"));
	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr || Character->GetHasRifle())
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		}
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ENdPlay"));
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}