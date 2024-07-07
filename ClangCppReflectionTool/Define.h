#pragma once

#ifdef CRRTAPI_Exporting
#define CRRTAPI __declspec(dllexport)
#else
#define CRRTAPI __declspec(dllimport)
#endif

#define UCLASS //UCLASS 매크로가 상단에 붙어있어야 해당 Class를 리플랙션 가능
#define UPROPERTY //UPROPERTY 매크로가 상단에 붙어있어야 해당 Property를 리플랙션 가능
#define UCLASS_BODY public: \
					void ApplyReflectionData() override;\
					private://생성된 부분을 숨기기 위해 작성