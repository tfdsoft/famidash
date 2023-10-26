ONLY ONE PERSON CAN WORK ON THE .dnm AT ANY GIVEN TIME, SINCE SAVING IT COMPLETELY REWRITES THE FILE.

DO NOT OPEN THE MODULE IN ANY VERSION NEWER THAN DN-FAMITRACKER 0.4.0.1. THE MODULE WILL BREAK OTHERWISE.

.dnm modules are imported into FamiStudio after they're done, so please do not use unsupported by FS effects (full list at https://famistudio.org/doc/import/#famitracker-text-or-binary)


How to compile the music:
If you worked in Deeznuts-FT:
    1. Copy the song into music.dnm
    2. While still in Dn-FT, export music.dnm as .txt into the INTERMEDIATES folder
    3. Run the adjust_txt_header.py script (run it from the main folder)
    4. Import *only the song and instruments you have modified* into FamiStudio 4.1.3.
    5. Hand-correct things that FS gave warnings about.

After this, the same steps apply for everything:
    1. Export all the songs into EXPORTS/music.s in CA65 mode and with the songlist .inc file enabled, note the settings it tells you to turn on
    2. Export all the sfx into EXPORTS/sfx.s in CA65 mode and with the sfxlist .inc file enabled
    3. Run parse_inc_files.py
    4. Compile and test the rest of the game. If it crashes, check if all the settings FS gave you at step 1 are enabled. If they are but the game still crashes, report the situation to @alexmush on the Discord server and you'll probably get a reply within 48 hours.