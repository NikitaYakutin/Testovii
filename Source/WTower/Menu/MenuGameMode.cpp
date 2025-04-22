#include "MenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../WTowerPlayerController.h"
#include "WUIManager.h"
#include "MenuPlayerController.h"
#include "MenuWidget/WDefeatMenuWidget.h"
#include <WTower/WTowerGameMode.h>

AMenuGameMode::AMenuGameMode()
{
    // Default constructor
}

void AMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Get player controller directly
        // Теперь UIManager создается и инициализируется в WTowerGameMode
    // Нам нужно только получить его ссылку

    AWTowerGameMode* WTowerGM = Cast<AWTowerGameMode>(GetWorld()->GetAuthGameMode());
    if (WTowerGM)
    {
        UIManager = WTowerGM->GetUIManager();

        // Получаем MenuPlayerController
        AMenuPlayerController* PC = Cast<AMenuPlayerController>(GetWorld()->GetFirstPlayerController());
        if (PC && UIManager)
        {
            PC->SetUIManager(UIManager);
        }
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