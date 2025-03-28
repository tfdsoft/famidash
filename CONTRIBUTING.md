# Contributing to Famidash

congration you have decided to contribute to nintendo family computer geometry dash this guideline will show you the guidelines

## overview

Famidash has grown to be a large project, which means there are a few guidelines to abide by when contributing. Generally, you should ALWAYS create a fork somewhere else, then apply your changes there. To get those changes into the main branch, opening up a pull request is necessary. Your changes will then be reviewed by a maintainers and merged if deemed appropriate. Don't create PRs for every little change; instead do all of your changes in your fork, then open up a single PR for all of them. If it isn't clear already, direct commits (unless by a maintainer for housekeeping or other reasons) are frowned upon and will immediately be reverted upon discovery.

Your PR may be accepted or rejected at the maintainers' discretion; as such, they are not obliged to disclose the reason of a potential rejection, so don't even bother pestering them about it. Though if you ask nicely, you might get a more cooperative answer.

The team utilises a large collection of software to facilitate development; more on that sometime later.

## music (guide by alexmush)

### Preamble

To add / edit music, edit MODULES/MODULES/music_master.dnm in Dn-FamiTracker 0.5.0.2; it's also possible to add music via FamiStudio 4.3.0 in the MODULES/MODULES/music_master.fms file.

**When adding / editing anything** in the modules, ***add it to the [changelog](MUSIC/CHANGELOG.txt) and describe it in exact detail***. **If you edited** something and **didn't add** it to the changelog, **@alexmush will personally shit your pants**.

IT IS NOT RECOMMENDED FOR MULTIPLE PEOPLE TO WORK SIMULTANEOUSLY ON THE .dnm, SINCE MERGING THAT IS ONE HELL OF A HASSLE.
(to do that you need to export text from both versions of the module, and manually adjust shit until it can be imported back)

You can, however, add new songs easily in FamiStudio to merge 2 diverging branches.

OPEN THE MODULE IN **DN-FT 0.5.0.1 OR NEWER**. 0.5.0.0 BREAKS SHIT

.dnm modules are imported into FamiStudio after they're done, so **do not use unsupported by FS effects** (full list [here](https://famistudio.org/doc/import/#famitracker-text-or-binary))

Paths are given to relative to the MUSIC folder, unless it begins with a /, then it's the root famidash directory

### How to compile the music

#### If you worked in Deeznuts-FT

1. Copy the song into MODULES/music_master.dnm
2. While still in Dn-FT, export MODULES/music_master.dnm as .txt into the INTERMEDIATES folder
3. Run the `adjust_ft_txt.py` script (run it from anywhere)
4. Import **ONLY THE SONGS AND INSTRUMENTS YOU HAVE ADDED/MODIFIED** into FamiStudio 4.3.0.
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
4. Add the songs to metadata.json for the export script to include them in the game (and the sound test)
5. Run the following command to test the music exports:<br>`python3 export.py [<path/to/FamiStudio.dll>] -t`<br>If FamiStudio.dll on your system is in the PATH variable (this can be checked with trial and error), you should omit the <path/to/FamiStudio.dll>, otherwise substitute it with the actual path to FamiStudio.dll on your machine.
6. Check the output of it, make sure it didn't error out midway through and gave you the following message:<br>"==== Everything seems to have gone alright, you can run it for real now."
7. If it didn't error out and it completed successfully, run the following command to do it for real:<br>`python3 export.py [<path/to/FamiStudio.dll>]`
8. Don't close the terminal yet! You've now got one last thing to adjust:
9. Ensure that the /LIB/asm/famistudio_ca65.s file has the settings set as the export output dictates
10. Test the game.
11. If the song did not appear anywhere during the export process and doesn't appear in the sound test, refer to step 4.
12. If the compilation errors out due to an overflow in DAT_BANK_XX, congratulations, you've run out of space! Refer to step 13.
13. If anything odd went on in any of these steps, ping @alexmush and they'll probably respond within 48 hours (response times will vary)

## levels (guide by Ficus)

How to export and update levels:

* Open in tiled - make sure you have the sprites and tiles on the correct layers.
* Export - This will save in "the folder that you do stuff in".
* Go back a folder and run export_levels.bat - This will compile all the levels into their data folders.
* Go back another folder and run build.bat. All the level updates should be in the game.