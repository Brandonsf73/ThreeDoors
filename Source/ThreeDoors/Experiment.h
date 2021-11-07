#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Experiment.generated.h"


/// <summary>
/// List of doors that the user can choose
/// </summary>
UENUM()
enum door
{
	firstDoor,
	secondDoor,
	thirdDoor,
	doorCount,
};

/// <summary>
/// A single Trail from the experiment
/// </summary>
struct Trial
{
	Trial(door correct) :
	CorrectChoice(correct)
	{
	}

	door CorrectChoice = door::doorCount;
	door FirstChoice = door::doorCount;
	door SecondChoice = door::doorCount;
};

UCLASS()
class THREEDOORS_API AExperiment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExperiment();

	// Cleans up the mess we've made
	~AExperiment();

	// Creates a new trial and adds it the running list
	void CreateNewTrial();

	// Called when the player steps over any of the collision boxes in front of the doors
	UFUNCTION(BlueprintCallable)
	void ChoiceMade(bool firstChoice, int trial, door choice);

	// Spawn a new Room to continue the experiment
	void SpawnRoom(bool firstRoom);

	// Spawn a door every other room that blocks one of the choices
	void SpawnDoor(door closedDoor);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> roomBP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// List of all of the previous trials the game has run
	/// </summary>
	std::vector<Trial*> results;

	/// <summary>
	/// Vector of all of the doors in the enum door
	/// </summary>
	const std::vector<door> ExperimentDoorList { 
		door::firstDoor,
		door::secondDoor,
		door::thirdDoor
	};

	/// <summary>
	/// Location where each of the doors can spawn
	/// </summary>
	const FVector DoorLocations[door::doorCount] =
	{
		FVector(800.0,		500.0,	200.0),		// Left
		FVector(0,			500.0,	200.0),		// Center
		FVector(-800.0,		500,	200.0),		// Right
	};

};
