#include <SDKDDKVer.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <d3d9.h>
#include <chrono>
#include <cstdint>
#include <stdexcept>
#include <stdio.h> 
#include <type_traits>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>

extern int R_EndFrame_t, menu_PaintAll_t;
extern int Dvar_GetBool_t, Cbuf_AddText_t, Dvar_GetString_t;
extern int Material_RegisterHandle_t, R_RegisterFont_t, CG_DrawRotatedPicPhysical_t, R_AddCmdDrawText_t, ScreenPlacement_t, R_TextWidth_t, UI_DrawRect_t, UI_GetFontHandle_t, UI_DrawText_t;
extern int va_t, worldtoscreen_t, toastpopup_t, getstring_t, CG_DObjGetWorldTagPos_t, Com_GetClientDObj_t, converttostring_t, com_error;
extern int centity_t_t, uicontext_t_t, cgs_t_t, cg_s_t;

enum alignment { align_left, align_right, align_center };
enum fontEnum {
	defaultFont,
	normalFont,
	objectiveFont,
	clanFont,
	extrabigFont,
	consoleFont,
	boldFont,
};

class Color_t {
public:
	float r, g, b, a;
	Color_t(float _r, float _g, float _b, float _a);
};
class Material_t { public: const char* name; };
class Fonts_t { public: const char* name; };
typedef float vec_t;
class vec2_t {
public:
	float pitch, yaw;
	vec2_t();
	vec2_t(float x, float y);
	bool operator==(vec2_t& Vec);
	const vec2_t& operator-(vec2_t const& Vec);
	const vec2_t& operator+(vec2_t const& Vec);
	const float Length(void);
};
class vec3_t {
public:
	float pitch, yaw, roll;
	vec3_t();
	vec3_t(float x, float y, float z);
	bool operator==(vec3_t& Vec);
	bool operator!=(vec3_t& Vec);
	const vec3_t& operator-(void);
	const vec3_t& operator-(vec3_t const& Vec);
	const vec3_t& operator+(vec3_t const& Vec);
	const vec3_t& operator*(vec3_t const& Vec);
	const vec3_t& operator/(vec3_t const& Vec);
	const float Length(void);
	inline vec3_t normalize(void);
	float Distance(vec3_t Vec);
	float GetDistance(vec3_t enemi);
	float DotProduct(vec3_t Vec);
};

enum class entityType_t : int8_t
{
	ET_GENERAL,
	ET_PLAYER,
	ET_PLAYER_CORPSE,
	ET_ITEM,
	ET_MISSILE,
	ET_INVISIBLE,
	ET_SCRIPTMOVER,
	ET_SOUND_BLEND,
	ET_FX,
	ET_LOOP_FX,
	ET_PRIMARY_LIGHT,
	ET_MG42,
	ET_PLANE,
	ET_VEHICLE,
	ET_VEHICLE_COLLMAP,
	ET_VEHICLE_CORPSE,
	ET_ACTOR,
	ET_ACTOR_SPAWNER,
	ET_ACTOR_CORPSE,
	ET_STREAMER_HINT,
	ET_EVENTS,
};



enum class DemoType : int16_t
{
	DEMO_TYPE_CLIENT = 1,
	DEMO_TYPE_NONE = 0,
	DEMO_TYPE_SERVER = 2,
	DEMO_TYPE_SERVER_SNAPSHOT = 3
};

enum class CubemapShot : int16_t
{
	CUBEMAPSHOT_BACK = 3,
	CUBEMAPSHOT_COUNT = 7,
	CUBEMAPSHOT_DOWN = 6,
	CUBEMAPSHOT_FRONT = 4,
	CUBEMAPSHOT_LEFT = 2,
	CUBEMAPSHOT_NONE = 0,
	CUBEMAPSHOT_RIGHT = 1,
	CUBEMAPSHOT_UP = 5
};


class cpose_t {
public:
	int16_t lightingHandle; //0x0000
	entityType_t eType; //0x0002
	int8_t eTypeUnion; //0x0003
	char pad_0004[32]; //0x0004
	vec3_t origin; //0x0024
	vec3_t angles; //0x0030
	vec3_t absmin; //0x003C
	vec3_t absmax; //0x0048
};

class LerpEntityState
{
public:
	int32_t clientNum; //0x0000
	int8_t stance; //0x0004
	char pad_0005[1]; //0x0005
	int8_t eFlag; //0x0006
	char pad_0007[17]; //0x0007
	vec3_t origin; //0x0018
	char pad_0024[60]; //0x0024
	int32_t weapon; //0x0060
	char pad_0064[28]; //0x0064
	int32_t alive; //0x0080 0 = Dead
}; //Size: 0x0084

class entityState_s {
public:
	int8_t stance; //0x0000
	char pad_0001[1]; //0x0001
	uint8_t eFlag; //0x0002
	char pad_0003[17]; //0x0003
	vec3_t origin; //0x0014
	char pad_0020[60]; //0x0020
};
class centity_s
{
public:
	cpose_t pose;
	char pad_0054[272]; //0x0054
	LerpEntityState currentEntity; //0x0164
	char pad_01E8[84]; //0x01E8
	entityState_s nextState; //0x023C
	char pad_0298[132]; //0x0298
}; //Size: 0x031C

class cgs_t
{
public:
	int32_t viewX; //0x0000
	int32_t viewY; //0x0004
	int32_t viewWidth; //0x0008
	int32_t viewHeight; //0x000C
	float viewAspect; //0x0010
	int32_t serverCommandSequence; //0x0014
	int32_t processedSnapshotNum; //0x0018
	int32_t localServer; //0x001C
	char gametype[32]; //0x0020
	char szHostName[256]; //0x0040
	int32_t maxClients; //0x0140
	char pad_0144[4]; //0x0144
	char mapname[64]; //0x0148
}; //Size: 0x0188

class playerState_s
{
public:
	int32_t commandTime; //0x0000
	int32_t pm_type; //0x0004
	int32_t bobCycle; //0x0008
	int32_t pm_flag; //0x000C
	int32_t weaponFlags; //0x0010
	int32_t otherFlags; //0x0014
	int32_t pm_time; //0x0018
	uint32_t loopSoundId; //0x001C
	int32_t loopSoundFade; //0x0020
	vec3_t origin; //0x0024
	vec3_t velocity; //0x0030
	int32_t weaponTime; //0x003C
	int32_t weaponDelay; //0x0040
	int32_t weaponTimeLeft; //0x0044
	int32_t weaponDelayLeft; //0x0048
	int32_t weaponIdleTime; //0x004C
	int32_t grenadeTimeLeft; //0x0050
	int32_t throwBackGrenadeOwner; //0x0054
	int32_t throwBackGrenadeTimeLeft; //0x0058
	int32_t weaponRestrictKickTime; //0x005C
	char pad_0060[24]; //0x0060
	int32_t gravity; //0x0078
	float lean; //0x007C
	int32_t speed; //0x0080
	vec3_t delta_angles; //0x0084
	int32_t groundEntityNum; //0x0090
	int32_t groundType; //0x0094
	char pad_0098[172]; //0x0098
	int32_t weapon; //0x0144
	char pad_0148[124]; //0x0148
	int32_t health; //0x01C4
	char pad_01C8[4]; //0x01C8
	int32_t maxHealth; //0x01CC
}; //Size: 0x01D0

class snapshot_s
{
public:
	int32_t snapFlags; //0x0000
	int32_t ping; //0x0004
	int32_t serverTime; //0x0008
	playerState_s ps; //0x000C
	char pad_01DC[116]; //0x01DC
}; //Size: 0x0250

class cg_s
{
public:
	int32_t clientNum; //0x0000
	int32_t localClient; //0x0004
	DemoType demoType; //0x0008
	CubemapShot cubemapShot; //0x000A
	char pad_000C[36]; //0x000C
	snapshot_s *snap; //0x0030
	snapshot_s *nextSnap; //0x0034
	snapshot_s activeSnapshots; //0x0038
	char pad_0288[512]; //0x0288
	int32_t maxEntity; //0x0488
	char pad_048C[594312]; //0x048C
}; //Size: 0x91614

class cursor_t
{
public:
	float x; //0x0000
	float y; //0x0004
}; //Size: 0x0008

class UiContext
{
public:
	int32_t contextIndex; //0x0000
	float bias; //0x0004
	int32_t realTime; //0x0008
	int32_t frameTime; //0x000C
	cursor_t cursor; //0x0010
	cursor_t prevCursor; //0x0018
	int32_t isCursorVisible; //0x0020
	int32_t screenWidth; //0x0024
	int32_t screenHeight; //0x0028
	float screenAspect; //0x002C
	float FPS; //0x0030
	float blurRadiusOut; //0x0034
}; //Size: 0x0038

extern UiContext context;
extern centity_s *centity;
extern cg_s *cg;
extern cgs_t *cgs;

class rendering_t {
public:
	Material_t *Material_RegisterHandle(const char* shader);
	Fonts_t *R_RegisterFont(const char* font);
	int R_TextWidth(const char* text, const char* font, float scale);

	void CG_DrawRotatedPic(float x, float y, float w, float h, float angle, Color_t color, const char* shader);
	void DrawLine(vec2_t start, vec2_t end, Color_t color);
	void R_AddCmdDrawText(const char* text, float x, float y, float rotation, float scale, fontEnum font, Color_t col, alignment align);

	void UI_DrawRect(float x, float y, float width, float height, int horzAlign, int vertAlign, float size, Color_t color);
	Fonts_t *UI_GetFontHandle(int fontEnum, float scale);
	void UI_DrawText(const char * text, fontEnum font, float x, float y, int horzAlign, int vertAlign, float scale, Color_t color, int style);
};

class DvarFunctions {
public:
	bool Dvar_GetBool(const char* dvar);
	void Cbuf_AddText(const char* dvar);
	const char* Dvar_GetString(const char* dvar);
};

class Functions {
public:
	const char *SL_ConvertToString(unsigned int stringValue, int inst);
	int SL_GetString(const char* string);

	int Com_GetClientDObj(int cen, int usr);
	bool CG_DObjGetWorldTagPos(centity_s* cen, int DObj, unsigned int tag, vec3_t& out);
	vec3_t AimTarget_GetTagPos(int client, const char* tag);

	bool WorldToScreen(vec3_t BoneLocation, vec2_t* Stored);
	void UI_OpenToastPopup(const char* icon, const char* title, const char* desc, int seconds);
};

class Engine_t : public rendering_t, DvarFunctions, Functions {
public:
	void Init();
	static char*(*va)(const char* string, ...);
	bool fillStructs();
};

extern Engine_t Engine;



