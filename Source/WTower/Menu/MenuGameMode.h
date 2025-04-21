#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

class UWUIManager;

/**
 * GameMode for managing all menus
 */
UCLASS()
class WTOWER_API AMenuGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMenuGameMode();

    // Game initialization
    virtual void BeginPlay() override;

    // Menu management methods
    UFUNCTION(BlueprintCallable, Category = "UI")
    void CloseCurrentMenu();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ReturnToPreviousMenu();

    // Get UIManager
    UFUNCTION(BlueprintPure, Category = "UI")
    UWUIManager* GetUIManager() const { return UIManager; }
    
    // Widget classes for UI
    UPROPERTY(EditDefaultsOnly, Category = "UI|Widgets")
    TSubclassOf<class UWMainMenuWidget> MainMenuWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI|Widgets")
    TSubclassOf<class UWPauseMenuWidget> PauseMenuWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI|Widgets")
    TSubclassOf<class UWSettingsMenuWidget> SettingsMenuWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI|Widgets")
    TSubclassOf<class UWVictoryScreenWidget> VictoryScreenWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "UI|Widgets")
    TSubclassOf<class UWDefeatMenuWidget> DefeatMenuWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "UI|Widgets")
    TSubclassOf<class UWTowerHUDWidget> HUDWidgetClass;
    
private:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UWUIManager> UIManagerClass;
    
    // UI Manager
    UPROPERTY()
    UWUIManager* UIManager;
};