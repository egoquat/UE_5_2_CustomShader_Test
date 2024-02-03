// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCustomShader_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_CustomShader;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_CustomShader()
	{
		if (!Z_Registration_Info_UPackage__Script_CustomShader.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/CustomShader",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x72A1C0C2,
				0x40009127,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_CustomShader.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_CustomShader.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_CustomShader(Z_Construct_UPackage__Script_CustomShader, TEXT("/Script/CustomShader"), Z_Registration_Info_UPackage__Script_CustomShader, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x72A1C0C2, 0x40009127));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
