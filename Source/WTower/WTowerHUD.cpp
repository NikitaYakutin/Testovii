#include "WTowerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "WTowerPlayerController.h"
#include "Menu/WUIManager.h"

AWTowerHUD::AWTowerHUD()
{
    // Constructor
}

void AWTowerHUD::BeginPlay()
{
    Super::BeginPlay();

    // Get player controller
    AWTowerPlayerController* PC = Cast<AWTowerPlayerController>(GetOwningPlayerController());
    
    // Use UI Manager if available
    if (PC && PC->GetUIManager())
    {
        PC->GetUIManager()->ShowHUD();
    }
    // Legacy fallback
    else
    {
        // Check if widget class is set
        if (!HUDWidgetClass)
        {
            // Load widget class programmatically
            HUDWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/Menu/WBP_GameHUD.WBP_GameHUD_C"));
        }
        
        // Create and add widget
        if (HUDWidgetClass && PC)
        {
            CurrentHUDWidget = CreateWidget<UUserWidget>(PC, HUDWidgetClass);
            if (CurrentHUDWidget)
            {
                CurrentHUDWidget->AddToViewport(0);
            }
        }
    }
}