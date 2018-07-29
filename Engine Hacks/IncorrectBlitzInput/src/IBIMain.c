#include "gbafe.h"

// <Defined in Events>
extern const u8 BlitzerCharacterIndices[];
extern const u8 gGfx_FF6Window[];
extern const u16 gPal_FF6Window[];

// FIXME (update fe8u.s)
static struct AnimationInterpreter** const gBattleAnimMainAIs = (struct AnimationInterpreter**)(0x02000000);
static const int(*GetAISLayerId)(const struct AnimationInterpreter*) = (int(*)(const struct AnimationInterpreter*))(0x805A154+1);
static const int(*HasEkrNamewinAppearEnded)(void) = (int(*)(void))(0x08056E60+1);

struct IBIProc {
	PROC_HEADER;

	short countDown;
};

static void IBIPauseAllMainAIs(struct IBIProc*);
static void IBIStartHideNamewin(struct Proc*);
static void IBIWaitForNamewin(struct Proc*);
static void IBIDrawBox(struct Proc*);
static void IBIStartCountDown(struct IBIProc*);
static void IBIWaitCountDown(struct IBIProc*);
static void IBIClearBox(struct Proc*);
static void IBIStartShowNamewin(struct Proc*);
static void IBIUnpauseAllMainAIs(struct Proc*);

static const struct ProcInstruction sProc_IncorrectBlitzInputMessage[] = {
	PROC_SET_NAME("Stan:CCBlitz:IncorrectBlitzInput"),

	PROC_LOOP_ROUTINE(IBIPauseAllMainAIs),

	PROC_CALL_ROUTINE(IBIStartHideNamewin),
	PROC_LOOP_ROUTINE(IBIWaitForNamewin),

	PROC_CALL_ROUTINE(IBIDrawBox),
	PROC_YIELD,

	PROC_CALL_ROUTINE(IBIStartCountDown),
	PROC_LOOP_ROUTINE(IBIWaitCountDown),

	PROC_CALL_ROUTINE(IBIClearBox),

	PROC_CALL_ROUTINE(IBIStartShowNamewin),
	PROC_LOOP_ROUTINE(IBIWaitForNamewin),

	PROC_CALL_ROUTINE(IBIUnpauseAllMainAIs),

	PROC_END
};

static void IBIHBlankPalEffect(void) {
	unsigned line = REG_VCOUNT;

	if (line < 4 || line > (4 + 32))
		return;

	line = line - 4;

	{
		// This does the border blue gradient

		unsigned red   = line * 1  + (32 - line) * 15;
		unsigned green = line * 1  + (32 - line) * 15;
		unsigned blue  = line * 11 + (32 - line) * 26;

		((vu16*)(PLTT + 0x20))[14] = RGB(
			red   / 32,
			green / 32,
			blue  / 32
		);
	}

	{
		// This does the background blue gradient

		unsigned red   = line * 0  + (32 - line) * 14;
		unsigned green = line * 0  + (32 - line) * 14;
		unsigned blue  = line * 10 + (32 - line) * 25;

		((vu16*)(PLTT + 0x20))[15] = RGB(
			red   / 32,
			green / 32,
			blue  / 32
		);
	}
}

static void IBIPauseAllMainAIs(struct IBIProc* proc) {
	for (unsigned i = 0; i < 4; ++i)
		gBattleAnimMainAIs[i]->state = gBattleAnimMainAIs[i]->state | 0x0008;

	// Hopefully we can bruteforce our way through disabling AIs with this
	if ((--proc->countDown) <= 0)
		BreakProcLoop((Proc*)(proc));
}

static void IBIStartHideNamewin(struct Proc* proc) {
	StartEkrNamewinAppear(1, 7, 0);
}

static void IBIWaitForNamewin(struct Proc* proc) {
	if (HasEkrNamewinAppearEnded())
		BreakProcLoop(proc);
}

static void IBIDrawBox(struct Proc* proc) {
	static const unsigned boxGfxTileBase = 0x100;
	static const unsigned boxGfxPalId = 1;

	// Init font
	struct FontData font; {
		Font_InitForUI(&font, (void*)(VRAM + 0x20 * (boxGfxTileBase + 9)), (boxGfxTileBase + 9), boxGfxPalId);
		Font_SetGlyphSet(FONT_GLYPH_DIALOGUE);

		font.drawGlyph = DrawGlyph1DTileNoClear;

		SetFont(&font);
	}

	// Load window graphics
	// Palette will override the default text palette
	Decompress(gGfx_FF6Window, (void*)(VRAM + 0x20 * boxGfxTileBase));
	CopyToPaletteBuffer(gPal_FF6Window, boxGfxPalId * 0x20, 0x20);

	// Prepare bg 1
	FillBgMap(gBg1MapBuffer, 0);
	SetBgPosition(1, 0, -4);

	static const u16 boxTileMap[] = {
		0, 1, 2, // 0
		3, 8, 4, // 1
		3, 8, 4, // 2
		5, 6, 7, // 3
	//  l  m  r  ////
	};

	// Left & Right edges
	for (unsigned iy = 0; iy < 4; ++iy) {
		*BG_LOCATED_TILE(gBg1MapBuffer, 0,  iy) = boxGfxTileBase + boxTileMap[0 + iy * 3] + (boxGfxPalId << 12);
		*BG_LOCATED_TILE(gBg1MapBuffer, 29, iy) = boxGfxTileBase + boxTileMap[2 + iy * 3] + (boxGfxPalId << 12);
	}

	// Top & Bottom edges
	for (unsigned ix = 1; ix < 29; ++ix) {
		*BG_LOCATED_TILE(gBg1MapBuffer, ix, 0) = boxGfxTileBase + boxTileMap[3*0 + 1] + (boxGfxPalId << 12);
		*BG_LOCATED_TILE(gBg1MapBuffer, ix, 3) = boxGfxTileBase + boxTileMap[3*3 + 1] + (boxGfxPalId << 12);
	}

	// Init text
	struct TextHandle text;
	Text_InitClear(&text, 28);

	// Fill text tiles with the background color (color #0xF)
	CpuFill16(0xFFFF, font.getDrawTarget(&text), text.tileWidth*2*0x20);

	// Draw text
	Text_AppendString(&text, "Incorrect Blitz Input!");
	Text_Draw(&text, BG_LOCATED_TILE(gBg1MapBuffer, 1, 1));

	// Sync bg 0 & 1
	EnableBgSyncByMask(0b11);

	// Set the sweet palette effect thing as HBlank thing
	SetPrimaryHBlankCallback(IBIHBlankPalEffect);
}

static void IBIStartCountDown(struct IBIProc* proc) {
	proc->countDown = 120 - (gChapterData.textSpeedOption * 30);
}

static void IBIWaitCountDown(struct IBIProc* proc) {
	if (gKeyStatus.heldKeys & A_BUTTON)
		BreakProcLoop((Proc*)(proc));

	else if ((--proc->countDown) <= 0)
		BreakProcLoop((Proc*)(proc));
}

static void IBIClearBox(struct Proc* proc) {
	FillBgMap(gBg1MapBuffer, 0);
	EnableBgSyncByIndex(1);

	SetPrimaryHBlankCallback(NULL);
}

static void IBIStartShowNamewin(struct Proc* proc) {
	StartEkrNamewinAppear(0, 7, 0);
}

static void IBIUnpauseAllMainAIs(struct Proc* proc) {
	for (unsigned i = 0; i < 4; ++i)
		gBattleAnimMainAIs[i]->state = gBattleAnimMainAIs[i]->state &~ 0x0008;
}

void IBICheck(struct AnimationInterpreter* ais) {
	if (GetAISLayerId(ais) == 1)
		return; // back layer AIS, we don't care about those

	unsigned subject = GetAISSubjectId(ais);

	unsigned charId = gBattleCharacterIndices[subject];
	unsigned inList = FALSE;

	for (const u8* it = BlitzerCharacterIndices; *it; ++it)
		inList = inList || (*it == charId);

	if (!inList)
		return; // Not a Blitz man

	if (IsBatteRoundTypeAMiss(GetBattleAnimRoundType((ais->nextRoundId - 1)*2 + (subject ^ 1))))
		StartProc(sProc_IncorrectBlitzInputMessage, ROOT_PROC_3);
}
