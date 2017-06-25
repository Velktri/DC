#pragma once
#include "DCTypes.generated.h"

//class ADCMeleeWeapon;
//class ADCArmor;

UENUM(BlueprintType)
enum class ECharState : uint8 {
	I		UMETA(DisplayName = "Idle"),
	A		UMETA(DisplayName = "Attacking"),
	B		UMETA(DisplayName = "Blocking"),
	C		UMETA(DisplayName = "Countering"),
	E		UMETA(DisplayName = "Equipping"),
};

UENUM(BlueprintType)
enum class ESlotType : uint8 {
	Head			UMETA(DisplayName = "Head"),
	Shoulder		UMETA(DisplayName = "Shoulder"),
	Chest			UMETA(DisplayName = "Chest"),
	Legs			UMETA(DisplayName = "Legs"),
	Boots			UMETA(DisplayName = "Boots"),

	RightWeapon		UMETA(DisplayName = "MainHand"),
	LeftWeapon		UMETA(DisplayName = "OffHand"),
	RangedWeapon	UMETA(DisplayName = "RangedWeapon"),
};

/** Struct that holds all the current equipment for the Player */
//USTRUCT()
//struct FEquipmentSet {
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Weapon")
//	ADCMeleeWeapon* RightWeapon;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Weapon")
//	ADCMeleeWeapon* LeftWeapon;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Weapon")
//	class ADCShield* Shield;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Weapon")
//	class ADCRangedWeapon* RangedWeapon;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
//	ADCArmor* Head;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
//	ADCArmor* Shoulder;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
//	ADCArmor* Chest;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
//	ADCArmor* Legs;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
//	ADCArmor* Boots;
//
//	FEquipmentSet() {
//		RightWeapon = NULL;
//		LeftWeapon = NULL;
//		Shield = NULL;
//		RangedWeapon = NULL;
//		Head = NULL;
//		Shoulder = NULL;
//		Chest = NULL;
//		Legs = NULL;
//		Boots = NULL;
//	}
//};

/** Struct that holds a weapon's Stat points */
USTRUCT()
struct FEquipmentStats {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Ice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Wind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Earth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Dark;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Haste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Critical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Level;

	FEquipmentStats() {
		Attack = 0;
		Fire = 0;
		Ice = 0;
		Wind = 0;
		Earth = 0;
		Light = 0;
		Dark = 0;
		Haste = 0;
		Critical = 0;
		Experience = 0;
		Level = 1;
	}
};