

# Installation

The Modular Minimug Box requires [lyn](http://feuniverse.us/t/ea-asm-tool-lyn-elf2ea-if-you-will/2986).

To install `lyn`, place the `lyn` executable in your `<Event Assembler>/Tools/` folder.

To install the Modular Minimug Box (henceforth just the MMB) you simply need to `#include` one of the `MMB Installer` files. There are multiple variants of the installer included with the MMB, so pick your favorite to install or use as a starting point to customize.

The MMB takes up a considerable amount of freespace and is made by default to be included within a larger EA buildfile. If you're installing the MMB on its own, you'll need to modify your installer to assemble the hack to freespace. The easiest way to do that is to add the line `ORG 0x00B2A610` as the first line in the installer, replacing `0x00B2A610` with the offset of some available space.

# Customization

To edit items on the MMB, there are two steps: Enabling/disabling modules and configuring module options.

Throughout the installer there are lists of modules

```

// Unit name modules

	//#define MMBName
	//#define MMBNameCentered
	#define MMBNameAffinityShifted

```

and their options

```

// Unit name options

	// Coordinates and widths are in 8x8 pixel tiles
	#define MMBNameWidth 7
	#define MMBNameColor TextBlack
	#define MMBNameX 5
	#define MMBNameY 3

```

To disable a module, comment it out (type `//` before a line's text) from the list of modules.

For example, if I didn't want the unit's name to be shown on the MMB my unit name modules would look like:

```

// Unit name modules

	//#define MMBName
	//#define MMBNameCentered
	//#define MMBNameAffinityShifted

```

Conversely, you select which module(s) to use by uncommenting them.

For example, if I just wanted the unit's name with no centering:

```

// Unit name modules

	#define MMBName
	//#define MMBNameCentered
	//#define MMBNameAffinityShifted

```

To make implementation simpler, certain module types only support one module from their list being used at a time, such as the unit name modules.

After deciding which module(s) you want from a list, configuring them is as simple as editing numbers in their options.

Multiple modules with similar purposes share options. For example, all unit name modules share the same options.

Many module options have comments about how the options are interpreted, such as

`// Coordinates and widths are in 8x8 pixel tiles`

Many modules need to be positioned by tiles while some are positioned by pixels. It might be confusing to have both, but it would be far worse to have either all positions be in pixels (which would cause modules that must be tile aligned to have their coordinates silently floored to the nearest tile) or be in tiles (severely limiting things like icons and numbers).

Some module options have advanced options like which tile index to write to/use in VRAM. By default, none of these need to be edited and are included for completeness.

Modules involving skills require the FE8 skill system to be included within the same buildfile.

# Modules

Here's a list of available modules and a short description of each:

1. MMBStandardTilemap
   * This is the standard tilemap drawing routine. It draws a blue, green, or red palette depending on the allegiance of the unit. This tilemap is made up of:
   * A two byte header, containing width-1 and height-1
   * Rows, with the last row first, consisting of tile indexe shorts
   * An image called `Tile Indexes.png` shows the available (vanilla) tiles available for use with the tilemap. Combine the row number and column number to gain the tile index of the tile (i.e. the last tile in the image is $7F). Combine tile indexes with $400 to horizontally flip them, $800 to vertically flip them.
   * When changing the size of the tilemap, be sure to edit both `MMBWidth` and `MMBHeight`.

2. MMBName
   * Shows the unit's name, aligned to the left.

3. MMBNameCentered
   * Shows the unit's name, aligned to the center of allocated space

4. MMBNameAffinityShifted
   * Shows the unit's name, aligned to the left. This module moves the name to the right 2 tiles if affinity is drawn. It's intended to be used alongside MMBAffinity, with the affinity icon drawn where the name moves from.

5. MMBMinimug
   * Shows the unit's minimug the way vanilla does. This includes getting generic minimugs as normal and also the 'increase portrait by 1' bit.

6. MMBMinimugEnemyFlip
   * Same as above but enemy minimugs face right.

7. MMBInventory
   * Shows all items in a unit's inventory in a horizontal line.

8. MMBEquippedWeapon
   * Shows only the unit's equipped item, if they have one.

9. MMBEquippedWeaponName
   * Shows only the unit's equipped item, if they have one, along with the item's name.

10. MMBEquippedWeaponNameCentered
    * Shows only the unit's equipped item, if they have one, along with the item's name centered in available space.

11. MMBEquippedWeaponNameOnly
    * Shows the unit's equipped weapon name, if they have one.

12. MMBEquippedWeaponNameOnlyCentered
    * Shows the unit's equipped weapon name centered in available space, if they have one.

13. MMBInventoryOrEquippedWeaponName
    * This shows the unit's full inventory if they are an enemy or their equipped weapon and weapon name if they are not.

14. MMBInventoryOrEquippedWeaponNameCentered
    * This shows the unit's full inventory if they are an enemy or their equipped weapon and weapon name centered in available space if they are not.

15. MMBHPStatus
    * This draws an HP label, current HP, and max HP the way vanilla does, alternating with status every 64 frames.

16. MMBHP
    * This draws an HP label, current HP, and max HP the way vanilla does.

17. MMBDEFRES
    * This alternates between drawing a defense label + number and a resistance label + number every 64 frames

18. MMBAVODOD
    * This alternates between drawing an avoid label + number and a dodge (crit avoid) label + number every 64 frames

19. MMBHPBar
    * This draws a bar that represents current HP/max HP.

20. MMBHPBarStatus
    * This draws a bar that represents current HP/max HP, alternating with status every 64 frames.

21. MMBAffinity
    * This draws the unit's affinity, if they have one.

22. MMBSkillsAlternate
    * This cycles through a unit's skills, if they have any. It switches to the next skill ever 64 frames. This module requires the skill system.

23. MMB___Number
    * These modules draw their associated stats. Unusual numbers include DOD (dodge or crit avoid), CHR (skill system skill charge), and RTG (rating, a sum of a unit's stats).

24. MMB___Label
    * These modules draw image labels for their associated stats. 

# Creating New Modules (Advanced users)

Creating a MMB module requires some knowledge about THUMB, EA, and lyn. Taking a look at existing modules might be helpful, and you're free to contact me on FEU or the FEU Discord server.

There are three parts of a module:

* The code
* The inclusion and setup
* The array entry

MMB modules always have two inputs:

* r0: A pointer to the MMB proc state
* r1: A pointer to the selected unit's data in RAM (Most of the time)

The coordinates for placing BG elements on the MMB can be found by `(2 * ((32 * YCoord) + XCoord)) + TargetBuffer` where `TargetBuffer` is either `WindowBuffer` or `WindowBufferBG1` (both definitions can be found in `Common Definitions.inc` which I recommend you include in your asm)

For drawing sprites to the MMB, it's important to get the vertical offset of the box in order to add it to the sprite's Y coordinate. Here's an example from the level number drawing module:

```

	@ Get positions for numbers

	ldr		r6, MMBLevelX
	ldr		r7, MMBLevelY

	@ check for lower window

	mov		r0, r4 @ MMB Proc state

	@ First we get the window's position

	add		r0, #WindowPosType
	ldrb	r0, [r0]
	lsl		r0, r0, #0x03
	ldr		r1, =WindowSideTable
	add		r0, r1, r0

	@ Then we grab which half of the screen it's on

	mov		r1, #0x03
	ldsb	r0, [r0, r1] @ -1 for top, 1 for bottom
	cmp		r0, #0x00
	blt		SkipBottom

	@ If it's on the bottom of the screen we subtract the MMB's height
	@ from the vertical size of the screen (20 tiles), multiply by
	@ the size of a tile, and then add that to our Y coordinate

	ldr		r0, MMBHeight
	mov		r1, #20
	sub		r1, r1, r0

	lsl		r1, r1, #0x03
	add		r7, r7, r1

SkipBottom:

```

Instead of turning the asm into a dmp, we turn them into elfs and include them with lyn. This is step two.

In `MMB Core.event` there is a section that looks like:

```

	// Module inclusions

	// Tilemap modules

		#ifdef MMBStandardTilemap
			#inctevent lyn "Modules/MMBDrawTilemap.elf" "Internal/Definitions.elf"
			POIN MMBTilemap
			WORD MMBTilemapPaletteIndex
		#endif // MMBStandardTilemap

```

There are a few parts to this, so let's break them down.

First, `#ifdef MMBStandardTilemap`. `MMBStandardTilemap` is going to be the name of the module in the installer. The installer defines `MMBStandardTilemap` when the module is used, otherwise it isn't defined. Using this ifdef system we can keep the size of the MMB smaller by not assembling modules that are not used.

Second, `#inctevent lyn "Modules/MMBDrawTilemap.elf" "Internal/Definitions.elf"`. This uses `lyn` to include the contents of our elf file like it was a dmp, but it allows us to use outside symbols, like EA labels, definitions, and things from other elfs (like the `Internal/Definitions.elf` on that line).

Third, we have some EA literals that correspond to options in our installer. I suggest doing math on these here rather than in your assembly in order to save time and space.

Afterwards, be sure to add your module's info to the installer.

The third and final step for adding a module is to add an entry to one of two arrays:

* Build Routines
* Dynamic Routines

Build routines are run once when the MMB is being built. Dynamic routines are run every proc tick. BG elements are usually build routines, but some, like status drawing, are dynamic. Dynamic routines can have a dramatic effect on lag, so it's best to avoid heavy calculations or drawing. For example, modules that draw a unit's inventory will copy the icons to VRAM as a build routine but display the sprites using a dynamic routine, to avoid rewriting the icons every tick.

To pick an array, locate them (they're at the end of `MMB Core.event`) and add something along the lines of

```

	#ifdef MMBIconPrep
		POIN MMBPrepIcons
	#endif // MMBIconPrep

```

Where, once again, the `#ifdef MMBIconPrep` is the name of the module. The `POIN MMBPrepIcons` is a pointer to the routine.

