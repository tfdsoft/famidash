# Contributing to Famidash

congregations you have decided to contribute to nintendo family computer geometry dash this guideline will show you the guidelines

## overview

Famidash has grown to be a large project, which means there are a few guidelines to abide by when contributing. Generally, you should ALWAYS create a fork somewhere else, then apply your changes there. To get those changes into the main branch, opening up a pull request is necessary. Your changes will then be reviewed by the maintainers and merged if deemed appropriate. Don't create PRs for every little change; instead do all of your changes in your fork, then open up a single PR for all of them. If it isn't clear already, direct commits (unless by a maintainer for housekeeping or other reasons) are frowned upon and will immediately be reverted upon discovery.

Your PR may be accepted or rejected at the maintainers' discretion; as such, they are not obliged to disclose the reason of a potential rejection, so don't even bother pestering them about it. Though if you ask nicely, you might get a more cooperative answer.

The team utilises a large collection of software to facilitate development; more on that sometime later.

## music (guide by alexmush)

### Preamble

To add / edit music, edit MODULES/MODULES/music_master.dnm in Dn-FamiTracker 0.5.0.2; it's also possible to add music via FamiStudio 4.4.2 in the MODULES/MODULES/music_master.fms file.

**When adding / editing anything** in the modules, ***add it to the [changelog](MUSIC/CHANGELOG.txt) and describe it in exact detail***. **If you edited** something and **didn't add** it to the changelog, **one of the music maintainers will personally shit your pants**.

IT IS NOT RECOMMENDED FOR MULTIPLE PEOPLE TO WORK SIMULTANEOUSLY ON THE .dnm, SINCE MERGING THAT IS ONE HELL OF A HASSLE.
(to do that you need to export text from both versions of the module, and manually adjust shit until it can be imported back)

You can, however, add new songs easily in FamiStudio to merge 2 diverging branches.

OPEN THE MODULE IN **DN-FT 0.5.0.1 OR NEWER**. 0.5.0.0 BREAKS SHIT
DO NOT USE FamiStudio 4.4.0 OR 4.4.1. ITS DPCM EXPORTS ARE DIFFERENT. **USE FamiStudio 4.4.2** OR GREATER.

.dnm modules are imported into FamiStudio after they're done, so **do not use unsupported by FS effects** (full list [here](https://famistudio.org/doc/import/#famitracker-text-or-binary))

Paths are given to relative to the MUSIC folder, unless it begins with a /, then it's the root famidash directory

### How to compile the music

#### If you worked in Deeznuts-FT

1. Copy the song into MODULES/music_master.dnm
2. While still in Dn-FT, export MODULES/music_master.dnm as .txt into the INTERMEDIATES folder
3. Run the `adjust_ft_txt.py` script (run it from anywhere)
4. Import **ONLY THE SONGS AND INSTRUMENTS YOU HAVE ADDED/MODIFIED** into FamiStudio 4.4.2.
5. Hand-correct:
   - things that FS gave warnings about
   - every single pitch effect (0xy/1xx/2xx/3xx/Qxy/Rxy -> slide notes and arps), as FamiStudio currently botches their import somewhat

#### After this, the same precautions and actions follow, no matter where you worked before

1. Ensure that all added songs are in MODULES/music_master.fms
2. If you have added / modified any DPCM samples, ensure that:
    - they are properly distributed between banks
        - this can be done by right-clicking on a DPCM sample and choosing the "Auto-Assign Banks..." option with an 8KB bank size
    - every sample used in the tracks in the game is in the "dpcm" song (that's the DPCM aligner)
3. Save the MODULES/music_master.fms module
4. Add the songs to metadata.json5 file for the export script to include them in the game (and the sound test)
5. Run the following command to test the music exports:<br>`python3 export_wrapper.py -t [-f FAMISTUDIOPATH | -c FAMISTUDIOCOMMAND [FAMISTUDIOCOMMAND ...]] [-v]`<br>If FamiStudio.dll on your system is in the PATH variable or an otherwise common installation location (this can be checked with trial and error), you should omit the FAMISTUDIOPATH, otherwise substitute it with the actual path to FamiStudio.dll on your machine.<br>An equivalent to this command is running the `test_export.bat` script on Windows.
6. Check the output of it, make sure it didn't error out midway through and gave you the following message:<br>"==== Everything seems to have gone alright, you can run it for real now."
7. If it didn't error out and it completed successfully, run the following command to do it for real:<br>`python3 export_wrapper.py [-f FAMISTUDIOPATH | -c FAMISTUDIOCOMMAND [FAMISTUDIOCOMMAND ...]] [-v]`<br>An equivalent to this command is running the `export.bat` script on Windows.
8. Don't close the terminal yet! You've now got one last thing to adjust:
9. Ensure that the /LIB/asm/famistudio_ca65.s file has the settings set as the export output dictates
10. Test the game.
11. If the song did not appear anywhere during the export process and doesn't appear in the sound test, refer to step 4.
12. If the compilation errors out due to an overflow in DAT_BANK_XX, congratulations, you've run out of space! Refer to step 13.
13. If anything odd went on in any of these steps, ping @kandowontu and you'll probably get a response within 120 hours (response times will vary)

## levels (guide by SeaGlowingPro)

To make levels, download the Famidash Level Editor. Releases/betas can be found in the TFDSoft Discord server under #editor-releases. You also need a local copy of the entire Famidash repository in order to actually test your level on a NES, or an emulator. This is the main way to make Famidash levels, with up-to-date stuff synced with the repo.

You can also use [NerdBoy628's web-based level editor](https://nerdboy628.github.io/famidash-editor/) as an alternative.

For the old original way of making levels, you can use [Tiled level editor](https://www.mapeditor.org/). Please note that there will be major differences with features and level handling unlike the editors mentioned above.

Make sure you also have [Python](https://www.python.org/) installed. It is needed for the exporting and building job. Keep in mind that a ROM can only have a limited amount of levels.

Note: This guide is for Windows users, especially with the apps mentioned above. It might not 100% work with other operating systems.

### Famidash Level Editor

How to find/open levels:

* Navigate to /LEVELS/LEVEL DATA. There should be folders for levels in their respective ROM sides.
* Go to one of the folders, and choose a level of your choice. The level should be a .tmx file.
* If you decided a level, you can open it in the editor under the `Open` button or `File > Open TMX`.
* If you opened a level with .json5 metadata, you can use `Set Options > Attempt JSON load` to load the level's set metadata.

How to make levels:

* The editor starts with a simple blank level. You can start your work there.
* You can playtest your level progress using the simulator, which can be accessed using `F5`.
* You can find options for various features and quirks in the editor. However, recommended options for level making include `Level Options > Show Accurate Tileset` and `Level Options > Lock sprites to usable set`.
* With the two options mentioned above enabled, look for `Set Options`. These will give you an idea on what blocks and sprites will look like in-game. Recommended to prevent random messed up tiles due to being incompatible with the current set.
* You can also find other options in `Set Options`, including background and ground colors, starting gamemode, level name, level difficulty, stars, maximum fall speed, and the like.
	- For upper text and lower text, the name should be in UPPERCASE. Maximum characters for level names is 15.
	- For difficulty, it actually depends on what side the level is in:
		- If the level is in A or B, difficulties are "AUTO", "EASY", "NORMAL", "HARD", "HARDER", "INSANE" and "DEMON".
		- If the level is in C or D, difficulties are "EASYDEMON", "MEDIUMDEMON", "HARDDEMON", "INSANEDEMON", "EXTREMEDEMON", "IMPOSSIBLEDEMON" and "GRANDPADEMON".
		- You can use every difficulty if the level is in the Huge Man ROM.
	- For starting background/ground colors, it should link to the index of a color you want to start with. Refer to [PPU palettes](https://www.nesdev.org/wiki/PPU_palettes) for reference.
	- For the maximum fall speed, 0x07 is recommended as this is nearly accurate to GD. Without the argument, the default speed set is 0x06.
* Once the metadata is complete, you can export the .json file later.
* You can navigate and use the editor's built-in tools to make level making faster.


### NerdBoy628's level editor
* **WIP**


### Tiled level editor

How to open/view levels:

* Navigate to /LEVELS/LEVEL DATA. There should be folders for levels in their respective ROM sides.
* Go to one of the folders, and open a level of your choice. The level should be a .tmx file.
* If the level you opened only shows red X boxes, it means the image files linked to the level weren't found. You should look at /GRAPHICS/ to find the files. The names of the files are `famidash.bmp` and `sprites.png`.

How to make levels:

* As a starting point, you can get an empty template level. You can find it at /LEVELS/LEVEL DATA/lvlset_X/template.tmx. Copying the file and renaming it to the level you'll make is recommended, to save the original template file for future level creations. (P.S. if you lost the template file, you can always redownload it here)
	- If it shows red X boxes, refer to bullet 3 on how to open/view levels.
* **It is recommended to playtest your layout/level in actual Geometry Dash**, as playtesting in Famidash is complicated and not instant due to technical stuff.
* Once you're making a level, keep note that all tiles in `famidash` should be placed in the empty nameless layer, and all tiles in `sprites` should be in the SP layer. Putting them at the wrong layers will cause wrong tiles and sprites to load in-game.
* Please note that **you shouldn't flip and rotate tiles** in the editor. Doing so will cause their IDs to be beyond the metatile ID limit, causing invalid tile IDs which will result to build errors.
* For triggers like color changes, enable trail triggers, and invisible gravity portals, they should be placed 10 tiles to the right, and within the player's current view. Placing them outside the player view will not load them. In other words, the triggers have to "load" within the game in order to trigger them.
* You can also do a little trickery in level making by utilizing Tiled's built-in tools, including, but not limited to, `Shape Fill Tool`, `Random Mode`, and `Bucket Fill Tool`.


### Adding the level in-game

How to add levels:

* To add levels, the .tmx file with the level you made should be placed within one of the folders linking to a ROM side. (example: /LEVELS/LEVEL DATA/lvlset_X/your_level.tmx)
* Once your level is in a folder, you must look for the level metadata file corresponding to that side, which can be found in /LEVELS/metadata/lvlset_X_metadata.json5.
* After you set up the metadata, what's left is exporting the level and building it.

How to set up a level's metadata:

* **Note: If you used the Tiled editor, it is important to follow this guide. Other editors have the metadata and .json5 file already set up for you.**
* Look for a metadata template in any of the .json5 files. This will serve as a guide to set up the level's metadata. More importantly, here are some important metadata conditions and arguments needed:
	- For conditions not listed here, please refer to the `How to make levels` section in the Famidash editor, as the steps are pretty much identical.
	- For decoType, arguments are "DECO1", "DECOCLOUD", and "EXTRASPRITES1".
	- For spikeSet, arguments are "A", "B", and "C".
	- For blockSet, arguments are "A", "B", "C", and "D".
	- For sawSet, arguments are "A" and "LETTERBANK".
	- For stars, you can put a number, which will be the amount of stars a level will have.
		- Please note that difficulty and stars are important to keep in the metadata, otherwise the level won't export.
	- For the songID, it must link to a song that already exists in the ROM side. Most songs follow the `song_name_of_the_music` format.
	- For parallaxDisable, enabling it with true will replace the level background in-game with a blank color background.

How to export and update levels:

* Run export_levels.bat - This will compile all the levels into their data folders. You can also run any export level .bat file in the main directory.
* Run build.bat or any build .bat file. Look out for the `famidash.nes created` line in the terminal. If the line appears, it means that the level updates should be in the game.

Common errors when exporting/building:

* While building the ROMs, if a memory bank byte overflow happens in the middle of building, it means that there is not enough ROM space. It is usually solved by removing some existing levels or optimizing a level, specifically sprites and level length.
* While exporting levels, if it doesn't export and shows that it expected a comma or another character, it means that there is a syntax error in a .json5 file.


For any concerns and problems regarding level making and exporting, feel free to ask the developers for help. (response times will vary)