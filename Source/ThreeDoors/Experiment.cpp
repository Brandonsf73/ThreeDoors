#include "Experiment.h"
#include <random>
#include <iterator>

//Randomly advances an interator to somewhere in the container
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

//Calls the parent function using the mt19937 uniform random number generator
template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

// Sets default values
AExperiment::AExperiment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AExperiment::~AExperiment()
{
    for (Trial* t : results)
    {
        delete t;
    }
}

// Called when the game starts or when spawned
void AExperiment::BeginPlay()
{
	Super::BeginPlay();

    // Spawn the very first room
	CreateNewTrial();	
}

// Called every frame
void AExperiment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AExperiment::CreateNewTrial()
{
    //Randomly select a new door as the correct one
    door correctDoor = *select_randomly(AExperiment::ExperimentDoorList.begin(), AExperiment::ExperimentDoorList.end());
    Trial* newTrial = new Trial(correctDoor);
    results.push_back(newTrial);

    //Spawn first room, all doors are open
    SpawnRoom(true);
}

//Decision was made, save the result and spawn the next room
void AExperiment::ChoiceMade(bool firstChoice, int trailNum, door choice)
{
    if (firstChoice)
    {
        results[trailNum]->FirstChoice = choice;
    }
    else
    {
        results[trailNum]->SecondChoice = choice;
    }

    //Spawn second room, close an incorrect door
    SpawnRoom(false);
}

void AExperiment::SpawnDoor(door closedDoor)
{

}

void AExperiment::SpawnRoom(bool firstRoom)
{
    if (roomBP)
    {
        UWorld* world = GetWorld();
        if (world)
        {
            FActorSpawnParameters spawnParams;
            spawnParams.Owner = this;

            FRotator rotator = {};

            FVector SpawnLocation = { 0.0, 0.0, 0.0 };
            world->SpawnActor<AActor>(roomBP, SpawnLocation, rotator, spawnParams);
        }
    }
}