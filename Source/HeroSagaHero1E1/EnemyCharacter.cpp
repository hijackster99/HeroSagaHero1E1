// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

// Sets default values for this component's properties
UEnemyCharacter::UEnemyCharacter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...

	health = 10;
}


// Called when the game starts
void UEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyCharacter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyCharacter::Hit(int damage)
{
	if (health > 0)
	{
		health -= damage;
		if (health <= 0)
		{
			Kill();
		}
	}
}

void UEnemyCharacter::Kill()
{
	UE_LOG(LogTemp, Warning, TEXT("Killed"));
}