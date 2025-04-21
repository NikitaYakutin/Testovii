#include "MenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../WTowerPlayerController.h"
#include "WUIManager.h"
#include "MenuPlayerController.h"
#include "MenuWidget/WDefeatMenuWidget.h"

AMenuGameMode::AMenuGameMode()
{
    // Default constructor
}

void AMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Get player controller directly
    APlayerController* DefaultPC = GetWorld()->GetFirstPlayerController();
    AMenuPlayerController* PC = Cast<AMenuPlayerController>(DefaultPC);
    if (PC)
    {
        // Create UI Manager instance
        if (UIManagerClass)
        {
            UIManager = NewObject<UWUIManager>(this, UIManagerClass);
        }
        else
        {
            UIManager = NewObject<UWUIManager>(this);
        }

        // Initialize UI Manager with controller
        UIManager->Initialize(PC);

        // Set widget classes for UIManager
        UIManager->SetWidgetClasses(
            MainMenuWidgetClass, 
            PauseMenuWidgetClass,
            SettingsMenuWidgetClass, 
            VictoryScreenWidgetClass,
            DefeatMenuWidgetClass,
            HUDWidgetClass
        );

        // Set UIManager reference in controller for easy access
        PC->SetUIManager(UIManager);

        // Show main menu on start
        UIManager->ShowMenu(EWMenuType::Main);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("MenuGameMode: No player controller available!"));
    }
}

void AMenuGameMode::CloseCurrentMenu()
{
    if (UIManager)
    {
        UIManager->CloseCurrentMenu();
    }
}

void AMenuGameMode::ReturnToPreviousMenu()
{
    if (UIManager)
    {
        UIManager->ReturnToPreviousMenu();
    }
}