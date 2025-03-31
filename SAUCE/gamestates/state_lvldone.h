
CODE_BANK_PUSH("LVL_BANK_00")
void lvl_done_update();
void mouse_and_cursor();
void refresh_queue_screen();
void play_next_queue();
void update_text1();
void update_text2();
void update_text3();
void unrle_bgm1();
void unrle_bgm2();
const unsigned char palette_Credits2[16]={ 0x11,0x0f,0x10,0x30,0x11,0x0f,0x2a,0x39,0x11,0x28,0x17,0x0f,0x11,0x0f,0x11,0x21 };

const unsigned char blanktext2[] = "$$$$$$$$$$$$$";

const uint8_t difficulty_pal_A[] ={
	0x21,	// easy
	0x2A,	// normal
	0x28,	// hard
	0x16,	// harder
	0x24,	// insane
	0x16,	// demon
	0x28,	// auto
};

const uint8_t difficulty_pal_B[] ={
	0x06,	// easy
	0x30,	// normal
	0x30,	// hard
	0x30,	// harder
	0x06,	// insane
	0x30,	// demon
	0x0F,	// auto
};

void state_playmain() {
	
}

void refreshmenu();
void refreshmenu_part2();
void code_checker();
void check_if_music_stopped();
void set_fun_settings();
void checkcointimer(){
	if (tmp1 == 1){
		sfx_play(sfx_coin,0);
		tmp1 = 50;
	}
}
void checkcoinproceed(){
	if (tmp1 == 0 || tmp1 == 30) {
		tmp2++;
		tmp1 = 1;
	}
}

void state_lvldone() {

}



//CODE_BANK_PUSH("XCD_BANK_05")

const unsigned char bgmtestscreen[];
const unsigned char SoundQueue[];

#include "defines/bgm_charmap.h"
const unsigned char TEXT_xlevel1text1[]="STEREO";
const unsigned char TEXT_xlevel1text2[]="BACK$ON";
const unsigned char TEXT_xlevel1text5[]="BASE$AFTER";
const unsigned char TEXT_xlevel1textC[]="THEORY$OF";
const unsigned char TEXT_xlevel1textD[]="ELECTROMAN";
const unsigned char TEXT_xweasel[]="SCHEMING";
const unsigned char TEXT_challenge[]="THE";
const unsigned char TEXT_hexagon[]="HEXAGON";
const unsigned char TEXT_blast[]="BLAST";
const unsigned char TEXT_speed[]="AT$THE$SPEED";
const unsigned char TEXT_crackdown[]="OKIBA";
const unsigned char TEXT_against[]="8BIT$AGAINST";
const unsigned char TEXT_geometrical[]="GEOMETRICAL";
const unsigned char TEXT_driving[]="DRIVING$BY";
const unsigned char TEXT_ultimate[]="ULTIMATE";
const unsigned char TEXT_ultimate2[]="DESTRUCTION";


const unsigned char TEXT_xlevel2text1[]="MADNESS";
const unsigned char TEXT_xlevel2text2[]="TRACK";
const unsigned char TEXT_xlevel2text3[]="POLARGEIST";
const unsigned char TEXT_xlevel2text4[]="DRY$OUT";
const unsigned char TEXT_xlevel2text5[]="BASE";
const unsigned char TEXT_xlevel2text6[]="CANT$LET$GO";
const unsigned char TEXT_xlevel2text7[]="JUMPER";
const unsigned char TEXT_xlevel2text8[]="TIME$MACHINE";
const unsigned char TEXT_xlevel2text9[]="CYCLES";
const unsigned char TEXT_xlevel2textA[]="XSTEP";
const unsigned char TEXT_xlevel2textB[]="CLUTTERFUNK";
const unsigned char TEXT_2clutterfunk2[]="CLUTTERFUNK$2";
const unsigned char TEXT_xlevel2textC[]="EVERYTHING";
const unsigned char TEXT_xlevel22textC[]="EVERYTHING$2";
const unsigned char TEXT_xlevel2textD[]="ADVENTURES";
const unsigned char TEXT_xlevel2textE[]="ENDGAME";
const unsigned char TEXT_2texteveryend[]="EVERY$END";
const unsigned char TEXT_2texteon[]="THE$ANGEL";
const unsigned char TEXT_2textelectrodynamix[]="ELECTRODYNAMIX";
const unsigned char TEXT_2textmidnight[]="MIDNIGHT";
const unsigned char TEXT_2textclubstep[]="CLUBSTEP";
const unsigned char TEXT_2textpractice[]="PRACTICE";
const unsigned char TEXT_2textmenu[]="MENU";
const unsigned char TEXT_2textmenuB[]="MENU$B$SIDES";
const unsigned char TEXT_2textweasel[]="WEASEL";
const unsigned char TEXT_2challenge[]="CHALLENGE";
const unsigned char TEXT_2deathmoon[]="DEATH$MOON";
const unsigned char TEXT_2hexagon[]="FORCE";
const unsigned char TEXT_2blast[]="PROCESSING";
const unsigned char TEXT_2textlost[]="LOST";
const unsigned char TEXT_2textstereo[]="MADNESS$2";
const unsigned char TEXT_2textinfernoplex[]="INFERNOPLEX";
const unsigned char TEXT_2textfullversion[]="FULL$VERSION";
const unsigned char TEXT_2textproblematic[]="PROBLEMATIC";
const unsigned char TEXT_2textspeed[]="OF$LIGHT$PT$1";
const unsigned char TEXT_2textspeed2[]="OF$LIGHT$PT$2";
const unsigned char TEXT_2textspeed3[]="OF$LIGHT$PT$3";
const unsigned char TEXT_2textspeedfull[]="OF$LIGHT$FULL";
const unsigned char TEXT_jackrussel[]="JACK$RUSSEL";
const unsigned char TEXT_2textcrackdown[]="CRACKDOWN";
const unsigned char TEXT_2textstalemate[]="STALEMATE";
const unsigned char TEXT_2textwoods[]="HAUNTED$WOODS";
const unsigned char TEXT_2textchaoz[]="CHAOZ$FANTASY";
const unsigned char TEXT_2textjustright[]="JUST$RIGHT";
const unsigned char TEXT_against2[]="THE$ODDS$REDUX";
const unsigned char TEXT_geometrical2[]="DOMINATOR";
const unsigned char TEXT_dash2[]="DASH";
const unsigned char TEXT_driving2[]="NIGHT";
const unsigned char TEXT_deadlocked2[]="DEADLOCKED";
const unsigned char TEXT_fingerdash2[]="FINGERDASH";
const unsigned char TEXT_ninox2[]="NINOX";
const unsigned char TEXT_beastmode[]="BEAST$MODE";
const unsigned char TEXT_machina[]="MACHINA";
const unsigned char TEXT_payload[]="PAYLOAD";
const unsigned char TEXT_candyland[]="CANDYLAND";
const unsigned char TEXT_hell[]="HELL";
const unsigned char TEXT_glint[]="GLINT";
const unsigned char TEXT_GDW[]="GDW$CUT";

const unsigned char TEXT_future[]="WHATS$A";
const unsigned char TEXT_future2[]="FUTURE$FUNK";

const unsigned char TEXT_freedom[]="FREEDOM";
const unsigned char TEXT_freedom2[]="DIVE";

const unsigned char TEXT_mayhem[]="MAYHEM";
const unsigned char TEXT_mayhem2[]="SHORT$VER";

const unsigned char TEXT_groundto[]="GROUND$TO";
const unsigned char TEXT_groundto2[]="SPACE";

const unsigned char TEXT_ludicrous[]="LUDICROUS";
const unsigned char TEXT_ludicrous2[]="SPEED";

const unsigned char TEXT_idols[]="IDOLS";
const unsigned char TEXT_metamorphasis[]="METAMORPHASIS";

const unsigned char TEXT_windfall[]="WINDFALL";
const unsigned char TEXT_speedracer[]="CHAOZ$IMPACT";
const unsigned char TEXT_magictouch[]="MAGIC$TOUCH";
const unsigned char TEXT_pyrophoric[]="PYROPHORIC";
const unsigned char TEXT_years[]="YEARS";
const unsigned char TEXT_subtle[]="SUBTLE";
const unsigned char TEXT_subtle2[]="ODDITIES";
const unsigned char TEXT_cantletgo[]="CANT$LET$GO";
const unsigned char TEXT_retray[]="GOLDEN$HAZE";
const unsigned char TEXT_rainbowt[]="RAINBOW";
const unsigned char TEXT_rainbowt2[]="TYLENOL";
const unsigned char TEXT_thoughts[]="THOUGHTS";
const unsigned char TEXT_youvebeen[]="YOUVE$BEEN";
const unsigned char TEXT_youvebeen2[]="TROLLED";
const unsigned char TEXT_kesobomb[]="KESOBOMB";



const unsigned char TEXT_sfxtext0[]="DEATH";
const unsigned char TEXT_sfxtext1[]="CLICK";
const unsigned char TEXT_sfxtext2[]="LEVEL$COMPLETE";
const unsigned char TEXT_sfxtext3[]="COIN";
const unsigned char TEXT_sfxtext4[]="CHEST$OPEN";
const unsigned char TEXT_sfxtext5[]="ORBS";
const unsigned char TEXT_sfxtext6[]="DIAMONDS";
const unsigned char TEXT_sfxtext7[]="EXIT$LEVEL";
const unsigned char TEXT_sfxtext8[]="START$LEVEL";
const unsigned char TEXT_sfxtext9[]="INVALID";
const unsigned char TEXT_sfxtextA[]="ACHIEVEMENT$GET";

const unsigned char* const sfxtexts[] = {
	TEXT_sfxtext0, TEXT_sfxtext1, TEXT_sfxtext2, TEXT_sfxtext3, TEXT_sfxtext4, TEXT_sfxtext5, TEXT_sfxtext6, TEXT_sfxtext7, TEXT_sfxtext8, TEXT_sfxtext9, TEXT_sfxtextA
};

const unsigned char sfxtexts_size[] = {
	sizeof(TEXT_sfxtext0) - 1,
	sizeof(TEXT_sfxtext1) - 1,
	sizeof(TEXT_sfxtext2) - 1,
	sizeof(TEXT_sfxtext3) - 1,
	sizeof(TEXT_sfxtext4) - 1,
	sizeof(TEXT_sfxtext5) - 1,
	sizeof(TEXT_sfxtext6) - 1,
	sizeof(TEXT_sfxtext7) - 1,
	sizeof(TEXT_sfxtext8) - 1,
	sizeof(TEXT_sfxtext9) - 1,
	sizeof(TEXT_sfxtextA) - 1
};


const unsigned char* const xbgmtexts1[] = {
	0, 
	0, 
	TEXT_xlevel1text1, 
	TEXT_xlevel1text2, 
	0, 
	0, 
	TEXT_xlevel1text5, 
	0, 
	0, 
	0, 
	0, 
	0, 
	0, 
	TEXT_xlevel1textC, 
	TEXT_xlevel1textD, 
	0, 
	0, 
	TEXT_hexagon, 
	TEXT_blast, 
	TEXT_xlevel1textC, 
	TEXT_geometrical,
	0,
	0,
	0, 
	
	TEXT_challenge,
	0,
	TEXT_xweasel, 
	
	TEXT_against,
	TEXT_speed,
	TEXT_speed,
	TEXT_speed,
	TEXT_speed,
	TEXT_beastmode,
	0, 		//candyland
	0, 		//chaoz fantasy
	0,		//chaoz impact
	0,		//clutterfunk 2
	0,		//death moon
	TEXT_driving,
	0,		//endgame
	TEXT_freedom,
	0,		//glint
	0,		//golden haze
	TEXT_groundto,
	0,		//haunted woods
	0,		//hell
	0,		//idols
	0,		//infernoplex
	TEXT_2textinfernoplex,	//infernoplex full
	0,		//jack russel
	0,		//just right
	0,		//kesobomb
	0,		//lost
	TEXT_ludicrous,
	TEXT_machina,
	0,		//magic touch
	TEXT_mayhem,
	0,		//cheetahmen short ver
	0,		//metamorphasis
	0,		//midnight
	0,		//ninox
	TEXT_crackdown,
	TEXT_payload,
	0,		//problematic
	0,		//pyrophoric
	TEXT_rainbowt,
	0,		//stalemate
	TEXT_2textstalemate,	//stalemate full version
	TEXT_xlevel1text1,
	TEXT_subtle,
	0,		//the angel
	0,		//thoughts
	TEXT_ultimate,
	TEXT_youvebeen,
	TEXT_future,
	0,		//windfall
	TEXT_years,


};

const unsigned char xbgmtext1_size[] = {
	0,
	0,
	sizeof(TEXT_xlevel1text1) - 1,	
	sizeof(TEXT_xlevel1text2) - 1,	
	0,
	0,
	sizeof(TEXT_xlevel1text5) - 1,	
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(TEXT_xlevel1textC) - 1,	
	sizeof(TEXT_xlevel1textD) - 1,	
	0,
	0,
	sizeof(TEXT_hexagon) - 1,	
	sizeof(TEXT_blast) - 1,	
	sizeof(TEXT_xlevel1textC) - 1,	
	sizeof(TEXT_geometrical) - 1,	
	0,
	0,
	0,
	
	
	sizeof(TEXT_challenge) - 1,	
	0,
	sizeof(TEXT_xweasel) - 1,	
	
	sizeof(TEXT_against) - 1,	
	sizeof(TEXT_speed) - 1,	
	sizeof(TEXT_speed) - 1,	
	sizeof(TEXT_speed) - 1,	
	sizeof(TEXT_speed) - 1,	
	sizeof(TEXT_beastmode) - 1,	
	0,		//candyland
	0,		//chaoz fantasy
	0,		//chaoz impact
	0,		//clutterfunk 2
	0,		//death moon
	sizeof(TEXT_driving) - 1,
	0,		//endgame
	sizeof(TEXT_freedom) - 1,	
	0,		//glint
	0,		//golden haze
	sizeof(TEXT_groundto) - 1,	
	0,		//haunted woods
	0,		//hell
	0,		//idols
	0,		//infernoplex
	sizeof(TEXT_2textinfernoplex) - 1,	
	0,		//jack russel
	0,		//just right
	0,		//kesobomb
	0,		//lost
	sizeof(TEXT_ludicrous) - 1,	
	sizeof(TEXT_machina) - 1,	
	0,		//magic touch
	sizeof(TEXT_mayhem) - 1,	
	0,		//mayhem
	0,		//metamorphasis
	0,		//midnight
	0,		//ninox
	sizeof(TEXT_crackdown) - 1,	
	sizeof(TEXT_payload) - 1,	
	0,		//problematic
	0,		//pyrophoric
	sizeof(TEXT_rainbowt) - 1,	
	0,		//stalemate
	sizeof(TEXT_2textstalemate) - 1,	//stalemate full version
	sizeof(TEXT_xlevel1text1) - 1,	//stereo madness 2
	sizeof(TEXT_subtle) - 1,	
	0,		//the angel
	0,		//thoughts
	sizeof(TEXT_ultimate) - 1,	
	sizeof(TEXT_youvebeen) - 1,	
	sizeof(TEXT_future) - 1,	
	0,		//windfall
	sizeof(TEXT_years) - 1,	
	
};

const unsigned char* const xbgmtexts2[] = {
	TEXT_2textmenu, 
	TEXT_2textmenuB, 
	TEXT_xlevel2text1, 
	TEXT_xlevel2text2, 
	TEXT_xlevel2text3, 
	TEXT_xlevel2text4, 
	TEXT_xlevel2text5, 
	TEXT_xlevel2text6,
	TEXT_xlevel2text7, 
	TEXT_xlevel2text8, 
	TEXT_xlevel2text9, 
	TEXT_xlevel2textA, 
	TEXT_xlevel2textB, 
	TEXT_xlevel2textC, 
	TEXT_xlevel2textD, 
	TEXT_2textclubstep, 
	TEXT_2textelectrodynamix, 
	TEXT_2hexagon, 
	TEXT_2blast, 
	TEXT_xlevel22textC, 
	TEXT_geometrical2,
	TEXT_deadlocked2,
	TEXT_fingerdash2,
	TEXT_dash2,
	
	TEXT_2challenge,
	TEXT_2textpractice,
	TEXT_2textweasel, 
	
	TEXT_against2,
	TEXT_2textspeed,
	TEXT_2textspeed2,
	TEXT_2textspeed3,
	TEXT_2textspeedfull,
	TEXT_GDW,
	TEXT_candyland,
	TEXT_2textchaoz,
	TEXT_speedracer,
	TEXT_2clutterfunk2,
	TEXT_2deathmoon,
	TEXT_driving2,
	TEXT_xlevel2textE,	//endgame
	TEXT_freedom2,
	TEXT_glint,
	TEXT_retray,
	TEXT_groundto2,
	TEXT_2textwoods,
	TEXT_hell,
	TEXT_idols,
	TEXT_2textinfernoplex,
	TEXT_2textfullversion,
	TEXT_jackrussel,
	TEXT_2textjustright,
	TEXT_kesobomb,
	TEXT_2textlost,
	TEXT_ludicrous2,
	TEXT_GDW,
	TEXT_magictouch,
	TEXT_mayhem2,
	TEXT_mayhem,
	TEXT_metamorphasis,
	TEXT_2textmidnight,
	TEXT_ninox2,
	TEXT_2textcrackdown,
	TEXT_GDW,
	TEXT_2textproblematic,
	TEXT_pyrophoric,
	TEXT_rainbowt2,
	TEXT_2textstalemate,
	TEXT_2textfullversion,
	TEXT_2textstereo,
	TEXT_subtle2,
	TEXT_2texteon,
	TEXT_thoughts,
	TEXT_ultimate2,
	TEXT_youvebeen2,
	TEXT_future2,
	TEXT_windfall,
	TEXT_GDW,
	
};

const unsigned char xbgmtext2_size[] = {
	sizeof(TEXT_2textmenu) - 1,
	sizeof(TEXT_2textmenuB) - 1,
	sizeof(TEXT_xlevel2text1) - 1,	
	sizeof(TEXT_xlevel2text2) - 1,	
	sizeof(TEXT_xlevel2text3) - 1,
	sizeof(TEXT_xlevel2text4) - 1,	
	sizeof(TEXT_xlevel2text5) - 1,	
	sizeof(TEXT_xlevel2text6) - 1,	
	sizeof(TEXT_xlevel2text7) - 1,	
	sizeof(TEXT_xlevel2text8) - 1,
	sizeof(TEXT_xlevel2text9) - 1,	
	sizeof(TEXT_xlevel2textA) - 1,	
	sizeof(TEXT_xlevel2textB) - 1,
	sizeof(TEXT_xlevel2textC) - 1,	
	sizeof(TEXT_xlevel2textD) - 1,	
	sizeof(TEXT_2textclubstep) - 1,
	sizeof(TEXT_2textelectrodynamix) - 1,
	sizeof(TEXT_2hexagon) - 1,
	sizeof(TEXT_2blast) - 1,
	sizeof(TEXT_xlevel22textC) - 1,	
	sizeof(TEXT_geometrical2) - 1,	
	sizeof(TEXT_deadlocked2) - 1,	
	sizeof(TEXT_fingerdash2) - 1,	
	sizeof(TEXT_dash2) - 1,	
	
	sizeof(TEXT_2challenge) - 1,
	sizeof(TEXT_2textpractice) - 1,
	sizeof(TEXT_2textweasel) - 1,
	
	sizeof(TEXT_against2) - 1,
	sizeof(TEXT_2textspeed) - 1,
	sizeof(TEXT_2textspeed2) - 1,
	sizeof(TEXT_2textspeed3) - 1,
	sizeof(TEXT_2textspeedfull) - 1,
	sizeof(TEXT_GDW) - 1,
	sizeof(TEXT_candyland) - 1,
	sizeof(TEXT_2textchaoz) - 1,
	sizeof(TEXT_speedracer) - 1,
	sizeof(TEXT_2clutterfunk2) - 1,
	sizeof(TEXT_2deathmoon) - 1,
	sizeof(TEXT_driving2) - 1,
	sizeof(TEXT_xlevel2textE) - 1,	//endgame
	sizeof(TEXT_freedom2) - 1,
	sizeof(TEXT_glint) - 1,
	sizeof(TEXT_retray) - 1,
	sizeof(TEXT_groundto2) - 1,
	sizeof(TEXT_2textwoods) - 1,
	sizeof(TEXT_hell) - 1,
	sizeof(TEXT_idols) - 1,
	sizeof(TEXT_2textinfernoplex) - 1,
	sizeof(TEXT_2textfullversion) - 1,
	sizeof(TEXT_jackrussel) - 1,
	sizeof(TEXT_2textjustright) - 1,
	sizeof(TEXT_kesobomb) - 1,
	sizeof(TEXT_2textlost) - 1,
	sizeof(TEXT_ludicrous2) - 1,
	sizeof(TEXT_GDW) - 1,
	sizeof(TEXT_magictouch) - 1,
	sizeof(TEXT_mayhem2) - 1,
	sizeof(TEXT_mayhem) - 1,
	sizeof(TEXT_metamorphasis) - 1,
	sizeof(TEXT_2textmidnight) - 1,
	sizeof(TEXT_ninox2) - 1,
	sizeof(TEXT_2textcrackdown) - 1,
	sizeof(TEXT_GDW) - 1,
	sizeof(TEXT_2textproblematic) - 1,
	sizeof(TEXT_pyrophoric) - 1,
	sizeof(TEXT_rainbowt2) - 1,
	sizeof(TEXT_2textstalemate) - 1,
	sizeof(TEXT_2textfullversion) - 1,
	sizeof(TEXT_2textstereo) - 1,
	sizeof(TEXT_subtle2) - 1,
	sizeof(TEXT_2texteon) - 1,
	sizeof(TEXT_thoughts) - 1,
	sizeof(TEXT_ultimate2) - 1,
	sizeof(TEXT_youvebeen2) - 1,
	sizeof(TEXT_future2) - 1,
	sizeof(TEXT_windfall) - 1,
	sizeof(TEXT_GDW) - 1,
	
};





const unsigned char TEXT_foreverbound[]="FOREVERBOUND";
const unsigned char TEXT_djvi[]="DJVI";
const unsigned char TEXT_waterflame[]="WATERFLAME";
const unsigned char TEXT_djnate[]="DJ$NATE";
const unsigned char TEXT_ocular[]="OCULAR$NEBULA";
const unsigned char TEXT_mdk[]="MDK";
const unsigned char TEXT_xi[]="XI";
const unsigned char TEXT_nk[]="NIGHTKILLA";
const unsigned char TEXT_cacola[]="CACOLA";
const unsigned char TEXT_kevin_macleod[]="KEVIN$MACLEOD";
const unsigned char TEXT_stepw[]="STEP$W";
const unsigned char TEXT_dwedit[]="DWEDIT";
const unsigned char TEXT_detious[]="DETIOUS";
const unsigned char TEXT_thefatrat[]="THEFATRAT";
const unsigned char TEXT_dimrain47[]="DIMRAIN47";
const unsigned char TEXT_virtual_riot[]="VIRTUAL$RIOT";
const unsigned char TEXT_cornandbeans[]="CORNANDBEANS";
const unsigned char TEXT_kayoszx[]="KAYOSZX";
const unsigned char TEXT_bossfight[]="BOSSFIGHT";
const unsigned char TEXT_eliteferrex[]="ELITEFERREX";
const unsigned char TEXT_romos[]="ROMOS";
const unsigned char TEXT_reinn[]="REINN";
const unsigned char TEXT_djhoneyb[]="DJ$HONEYB";
const unsigned char TEXT_lemondemon[]="LEMON$DEMON";
const unsigned char TEXT_f777[]="F777";
const unsigned char TEXT_crim3s[]="CRIM3S";
const unsigned char TEXT_meganeko[]="MEGANEKO";
const unsigned char TEXT_lemkuuja[]="LEMKUUJA";
const unsigned char TEXT_robtop[]="ROBTOP";
const unsigned char TEXT_dexarson[]="DEX$ARSON";
const unsigned char TEXT_paragonx9[]="PARAGONX9";
const unsigned char TEXT_soundholick[]="SOUNDHOLICK";
const unsigned char TEXT_tessaviolet[]="TESSA$VIOLET";
const unsigned char TEXT_dan_harrison[]="DAN$HARRISON$B";
const unsigned char TEXT_analog[]="ANALOGBYNATURE";
const unsigned char TEXT_kitsune[]="KITSUNE2";
const unsigned char TEXT_tmm43[]="TMM43";
const unsigned char TEXT_theclydecash[]="THECLYDECASH";
const unsigned char TEXT_interworld[]="INTERWORLD";
const unsigned char TEXT_tobu[]="TOBU";
const unsigned char TEXT_acidnotation[]="ACID$NOTATION";
const unsigned char TEXT_dominuus[]="DOMINUUS";
const unsigned char TEXT_rymdkraft[]="RYMDKRAFT";


const unsigned char TEXT_seaglowingpro[]="SEAGLOWINGPRO";
const unsigned char TEXT_elangel[]="ELANGEL378";
const unsigned char TEXT_nerdboy[]="NERDBOY628";
const unsigned char TEXT_craftyjumper[]="CRAFTY$JUMPER";
const unsigned char TEXT_zenith[]="ZENITH302";
const unsigned char TEXT_aquamarine[]="AQUAMARINE";
const unsigned char TEXT_vikrinox[]="VIKRINOX";
const unsigned char TEXT_alexmush[]="ALEXMUSH";
const unsigned char TEXT_cloud54[]="CLOUD54";
const unsigned char TEXT_usersniper[]="USERSNIPER";
const unsigned char TEXT_sussysy[]="SUSSYSY";
const unsigned char TEXT_clickerty[]="CLICKERTY";
const unsigned char TEXT_zukinnyk[]="ZUKINNYK";
const unsigned char TEXT_leejh20[]="LEEJH20";






const unsigned char* const origartists2[] = {
	TEXT_robtop, 			//menu theme
	TEXT_robtop, 			//menu theme 2.2
	TEXT_foreverbound,		//stereo madness
	TEXT_djvi,				//back on track
	TEXT_stepw,				//polargeist
	TEXT_djvi,				//dry out
	TEXT_djvi,				//base after base
	TEXT_djvi,				//can't let go
	TEXT_waterflame,		//jumper
	TEXT_waterflame,		//time machine
	TEXT_djvi,				//cycles
	TEXT_djvi,				//xstep
	TEXT_waterflame,		//clutterfunk
	TEXT_djnate,			//theory of everything
	TEXT_waterflame,		//electroman adventures
	TEXT_djnate,			//clubstep
	TEXT_djnate,			//electrodynamix
	TEXT_waterflame,		//hexagon force
	TEXT_waterflame,		//blast processing
	TEXT_djnate,			//theory of everything 2
	TEXT_waterflame,		//geometrical dominator
	TEXT_f777,				//deadlocked
	TEXT_mdk,				//fingerbang
	TEXT_mdk,				//dash
	TEXT_robtop, 			//the challenge
	TEXT_ocular, 			//practice
	TEXT_kevin_macleod, 	//scheming weasel
	
	TEXT_eliteferrex, 		//8-bit against the odds redux
	TEXT_dimrain47, 		//at the speed of light 1
	TEXT_dimrain47, 		//at the speed of light 2
	TEXT_dimrain47, 		//at the speed of light 3
	TEXT_dimrain47, 		//at the speed of light full
	TEXT_dexarson,			//beast mode GDW cut
	TEXT_tobu,			//candyland
	TEXT_paragonx9,			//chaoz fantasy
	TEXT_paragonx9,			//chaoz impact
	TEXT_waterflame,		//clutterfunk 2
	TEXT_soundholick,		//death moon
	TEXT_reinn,				//driving by night
	TEXT_waterflame, 		//endgame
	TEXT_xi, 				//freedom dive
	TEXT_dominuus, 				//glint
	TEXT_detious, 			//golden haze
	TEXT_seaglowingpro,		//ground to space
	TEXT_waterflame, 		//haunted woods
	TEXT_acidnotation,		//hell
	TEXT_virtual_riot,		//idols
	TEXT_dimrain47, 		//infernoplex
	TEXT_dimrain47, 		//infernoplex full
	TEXT_bossfight,			//jack russel
	TEXT_tessaviolet,		//just right
	TEXT_rymdkraft,			//kesobomb
	TEXT_crim3s, 			//lost
	TEXT_f777,				//ludacris speed
	TEXT_dexarson,			//machina GDW cut
	TEXT_romos,				//magic touch
	TEXT_craftyjumper,		//mayhem short ver
	TEXT_craftyjumper,		//mayhem
	TEXT_interworld,		//metamorphasis
	TEXT_cornandbeans,		//midnight
	TEXT_meganeko,			//ninox
	TEXT_bossfight,			//okiba crackdown
	TEXT_dexarson,			//payload GDW cut
	TEXT_nk,				//problematic
	TEXT_nerdboy,			//pyrophoric
	TEXT_kitsune,			//rainbow tylenol
	TEXT_kayoszx,			//stalemate
	TEXT_kayoszx,			//stalemate full
	TEXT_foreverbound,		//stereo madness2
	TEXT_lemondemon,		//subtle oddities
	TEXT_cacola,			//the angel
	TEXT_craftyjumper,		//thoughts
	TEXT_tmm43,				//ultimate destruction
	TEXT_theclydecash,		//you've been trolled
	TEXT_lemkuuja,			//what's a future funk
	TEXT_thefatrat,			//windfall
	TEXT_dexarson,			//years GDW cut
	
};


const unsigned char origartists2_size[] = {
	sizeof(TEXT_robtop) - 1,
	sizeof(TEXT_robtop) - 1,
	sizeof(TEXT_foreverbound) - 1,
	sizeof(TEXT_djvi) - 1,			//back on track
	sizeof(TEXT_stepw) - 1,			//polargeist
	sizeof(TEXT_djvi) - 1,			//dry out
	sizeof(TEXT_djvi) - 1,			//base after base
	sizeof(TEXT_djvi) - 1,			//can't let go	
	sizeof(TEXT_waterflame) - 1,	//jumper
	sizeof(TEXT_waterflame) - 1,	//time machine
	sizeof(TEXT_djvi) - 1,			//cycles
	sizeof(TEXT_djvi) - 1,			//xstep
	sizeof(TEXT_waterflame) - 1,	//clutterfunk
	sizeof(TEXT_djnate) - 1,		//theory of everything
	sizeof(TEXT_waterflame) - 1,	//electroman adventures
	sizeof(TEXT_djnate) - 1,		//clubstep
	sizeof(TEXT_djnate) - 1,		//electrodynamix
	sizeof(TEXT_waterflame) - 1,	//hexagon force
	sizeof(TEXT_waterflame) - 1,	//blast processing
	sizeof(TEXT_djnate) - 1,		//theory of everything 2
	sizeof(TEXT_waterflame) - 1,	//geometrical dominator
	sizeof(TEXT_f777) - 1,			//deadlocked
	sizeof(TEXT_mdk) - 1,			//fingerbang
	sizeof(TEXT_mdk) - 1,			//dash
	sizeof(TEXT_robtop) - 1, 		//the challenge
	sizeof(TEXT_ocular) - 1, 		//practice
	sizeof(TEXT_kevin_macleod) - 1, //scheming weasel	
	
	sizeof(TEXT_eliteferrex) - 1, 		//8-bit against the odds redux
	sizeof(TEXT_dimrain47) - 1, 		//at the speed of light 1
	sizeof(TEXT_dimrain47) - 1, 		//at the speed of light 2
	sizeof(TEXT_dimrain47) - 1, 		//at the speed of light 3
	sizeof(TEXT_dimrain47) - 1, 		//at the speed of light full
	sizeof(TEXT_dexarson) - 1,			//beast mode GDW cut
	sizeof(TEXT_tobu) - 1,			//candyland
	sizeof(TEXT_paragonx9) - 1,			//chaoz fantasy
	sizeof(TEXT_paragonx9) - 1,			//chaoz impact
	sizeof(TEXT_waterflame) - 1,		//clutterfunk 2
	sizeof(TEXT_soundholick) - 1,		//death moon
	sizeof(TEXT_reinn) - 1,				//driving by night
	sizeof(TEXT_waterflame) - 1, 		//endgame
	sizeof(TEXT_xi) - 1, 				//freedom dive
	sizeof(TEXT_dominuus) - 1, 				//glint
	sizeof(TEXT_detious) - 1, 			//golden haze
	sizeof(TEXT_seaglowingpro) - 1,		//ground to space
	sizeof(TEXT_waterflame) - 1, 		//haunted woods
	sizeof(TEXT_acidnotation) - 1, 		//hell
	sizeof(TEXT_virtual_riot) - 1,		//idols
	sizeof(TEXT_dimrain47) - 1, 		//infernoplex
	sizeof(TEXT_dimrain47) - 1, 		//infernoplex full
	sizeof(TEXT_bossfight) - 1,			//jack russel
	sizeof(TEXT_tessaviolet) - 1,		//just right
	sizeof(TEXT_rymdkraft) - 1,			//kesobomb
	sizeof(TEXT_crim3s) - 1, 			//lost
	sizeof(TEXT_f777) - 1,				//ludacris speed
	sizeof(TEXT_dexarson) - 1,			//machina GDW cut
	sizeof(TEXT_romos) - 1,				//magic touch
	sizeof(TEXT_craftyjumper) - 1,		//mayhem short ver
	sizeof(TEXT_craftyjumper) - 1,		//mayhem
	sizeof(TEXT_interworld) - 1,		//metamorphasis
	sizeof(TEXT_cornandbeans) - 1,		//midnight
	sizeof(TEXT_meganeko) - 1,			//ninox
	sizeof(TEXT_bossfight) - 1,			//okiba crackdown
	sizeof(TEXT_dexarson) - 1,			//payload GDW cut
	sizeof(TEXT_nk) - 1,				//problematic
	sizeof(TEXT_nerdboy) - 1,			//pyrophoric
	sizeof(TEXT_kitsune) - 1,			//rainbow tylenol
	sizeof(TEXT_kayoszx) - 1,			//stalemate
	sizeof(TEXT_kayoszx) - 1,			//stalemate full
	sizeof(TEXT_foreverbound) - 1,		//stereo madness2
	sizeof(TEXT_lemondemon) - 1,		//subtle oddities
	sizeof(TEXT_cacola) - 1,			//the angel
	sizeof(TEXT_craftyjumper) - 1,		//thoughts
	sizeof(TEXT_tmm43) - 1,				//ultimate destruction
	sizeof(TEXT_theclydecash) - 1,		//you've been trolled
	sizeof(TEXT_lemkuuja) - 1,			//what's a future funk
	sizeof(TEXT_thefatrat) - 1,			//windfall
	sizeof(TEXT_dexarson) - 1,			//years GDW cut
};

const unsigned char* const origartists1[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	TEXT_dan_harrison,	//just right
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};


const unsigned char origartists1_size[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(TEXT_dan_harrison) - 1, //just right
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};


const unsigned char* const coveringartists1[] = {
	TEXT_zenith, 			//menu theme
	TEXT_usersniper, 			//menu theme 2.2
	TEXT_zenith,		//stereo madness
	TEXT_aquamarine,				//back on track
	TEXT_zenith,				//polargeist
	TEXT_usersniper,				//dry out
	TEXT_vikrinox,				//base after base
	TEXT_usersniper,				//can't let go
	TEXT_zenith,		//jumper
	TEXT_zenith,		//time machine
	TEXT_aquamarine,				//cycles
	TEXT_vikrinox,				//xstep
	TEXT_aquamarine,		//clutterfunk
	TEXT_vikrinox,			//theory of everything
	TEXT_cloud54,		//electroman adventures
	TEXT_cloud54,			//clubstep
	TEXT_aquamarine,			//electrodynamix
	TEXT_vikrinox,		//hexagon force
	TEXT_elangel,		//blast processing
	TEXT_vikrinox,			//theory of everything 2
	TEXT_cloud54,		//geometrical dominator
	TEXT_usersniper,				//deadlocked
	TEXT_elangel,				//fingerbang
	TEXT_craftyjumper,				//dash
	TEXT_elangel, 			//the challenge
	TEXT_usersniper, 			//practice
	TEXT_usersniper, 	//scheming weasel
	
	TEXT_elangel, 		//8-bit against the odds redux
	TEXT_elangel, 		//at the speed of light 1
	TEXT_elangel, 		//at the speed of light 2
	TEXT_elangel, 		//at the speed of light 3
	TEXT_elangel, 		//at the speed of light full
	TEXT_elangel,			//beast mode GDW cut
	TEXT_nerdboy,		//candyland
	TEXT_usersniper,			//chaoz fantasy
	TEXT_elangel,			//chaoz impact
	TEXT_cloud54,		//clutterfunk 2
	TEXT_elangel,		//death moon
	TEXT_nerdboy,				//driving by night
	TEXT_vikrinox, 		//endgame
	TEXT_seaglowingpro, 				//freedom dive
	TEXT_seaglowingpro, 				//glint
	TEXT_craftyjumper, 			//golden haze
	TEXT_seaglowingpro,		//ground to space
	TEXT_sussysy, 		//haunted woods
	TEXT_elangel, 		//hell
	TEXT_seaglowingpro,		//idols
	TEXT_cloud54, 		//infernoplex
	TEXT_cloud54, 		//infernoplex full
	TEXT_nerdboy,		//jack russel
	TEXT_seaglowingpro,		//just right
	TEXT_nerdboy,		//kesobomb
	TEXT_seaglowingpro, 			//lost
	TEXT_seaglowingpro,				//ludacris speed
	TEXT_elangel,			//machina GDW cut
	TEXT_seaglowingpro,				//magic touch
	TEXT_craftyjumper,		//mayhem short ver
	TEXT_craftyjumper,		//mayhem
	TEXT_elangel,		//metamorphasis
	TEXT_seaglowingpro,		//midnight
	TEXT_seaglowingpro,			//ninox
	TEXT_sussysy,			//okiba crackdown
	TEXT_elangel,			//payload GDW cut
	TEXT_elangel,				//problematic
	TEXT_nerdboy,			//pyrophoric
	TEXT_clickerty,			//rainbow tylenol
	TEXT_elangel,			//stalemate
	TEXT_elangel,			//stalemate full
	TEXT_elangel,		//stereo madness2
	TEXT_dwedit,		//subtle oddities
	TEXT_elangel,			//the angel
	TEXT_craftyjumper,		//thoughts
	TEXT_usersniper,				//ultimate destruction
	TEXT_seaglowingpro,		//you've been trolled
	TEXT_seaglowingpro,			//what's a future funk
	TEXT_seaglowingpro,			//windfall
	TEXT_elangel,			//years GDW cut
};


const unsigned char coveringartists1_size[] = {
	sizeof(TEXT_zenith) - 1, 			//menu theme
	sizeof(TEXT_usersniper) - 1, 			//menu theme 2.2
	sizeof(TEXT_zenith) - 1,		//stereo madness
	sizeof(TEXT_aquamarine) - 1,				//back on track
	sizeof(TEXT_zenith) - 1,				//polargeist
	sizeof(TEXT_usersniper) - 1,				//dry out
	sizeof(TEXT_vikrinox) - 1,				//base after base
	sizeof(TEXT_usersniper) - 1,				//can't let go
	sizeof(TEXT_zenith) - 1,		//jumper
	sizeof(TEXT_zenith) - 1,		//time machine
	sizeof(TEXT_aquamarine) - 1,				//cycles
	sizeof(TEXT_vikrinox) - 1,				//xstep
	sizeof(TEXT_aquamarine) - 1,		//clutterfunk
	sizeof(TEXT_vikrinox) - 1,			//theory of everything
	sizeof(TEXT_cloud54) - 1,		//electroman adventures
	sizeof(TEXT_cloud54) - 1,			//clubstep
	sizeof(TEXT_aquamarine) - 1,			//electrodynamix
	sizeof(TEXT_vikrinox) - 1,		//hexagon force
	sizeof(TEXT_elangel) - 1,		//blast processing
	sizeof(TEXT_vikrinox) - 1,			//theory of everything 2
	sizeof(TEXT_cloud54) - 1,		//geometrical dominator
	sizeof(TEXT_usersniper) - 1,				//deadlocked
	sizeof(TEXT_elangel) - 1,				//fingerbang
	sizeof(TEXT_craftyjumper) - 1,				//dash
	sizeof(TEXT_elangel) - 1, 			//the challenge
	sizeof(TEXT_usersniper) - 1, 			//practice
	sizeof(TEXT_usersniper) - 1, 	//scheming weasel
	
	sizeof(TEXT_elangel) - 1, 		//8-bit against the odds redux
	sizeof(TEXT_elangel) - 1, 		//at the speed of light 1
	sizeof(TEXT_elangel) - 1, 		//at the speed of light 2
	sizeof(TEXT_elangel) - 1, 		//at the speed of light 3
	sizeof(TEXT_elangel) - 1, 		//at the speed of light full
	sizeof(TEXT_elangel) - 1,			//beast mode GDW cut
	sizeof(TEXT_nerdboy) - 1,			//candyland
	sizeof(TEXT_usersniper) - 1,			//chaoz fantasy
	sizeof(TEXT_elangel) - 1,			//chaoz impact
	sizeof(TEXT_cloud54) - 1,		//clutterfunk 2
	sizeof(TEXT_elangel) - 1,		//death moon
	sizeof(TEXT_nerdboy) - 1,				//driving by night
	sizeof(TEXT_vikrinox) - 1, 		//endgame
	sizeof(TEXT_seaglowingpro) - 1, 				//freedom dive
	sizeof(TEXT_seaglowingpro) - 1, 				//glint
	sizeof(TEXT_craftyjumper) - 1, 			//golden haze
	sizeof(TEXT_seaglowingpro) - 1,		//ground to space
	sizeof(TEXT_sussysy) - 1, 		//haunted woods
	sizeof(TEXT_elangel) - 1, 		//hell
	sizeof(TEXT_seaglowingpro) - 1,		//idols
	sizeof(TEXT_cloud54) - 1, 		//infernoplex
	sizeof(TEXT_cloud54) - 1, 		//infernoplex full
	sizeof(TEXT_nerdboy) - 1,		//jack russel
	sizeof(TEXT_seaglowingpro) - 1,		//just right
	sizeof(TEXT_nerdboy) - 1,		//kesobomb
	sizeof(TEXT_seaglowingpro) - 1, 			//lost
	sizeof(TEXT_seaglowingpro) - 1,				//ludacris speed
	sizeof(TEXT_elangel) - 1,			//machina GDW cut
	sizeof(TEXT_seaglowingpro) - 1,				//magic touch
	sizeof(TEXT_craftyjumper) - 1,		//mayhem short ver
	sizeof(TEXT_craftyjumper) - 1,		//mayhem
	sizeof(TEXT_elangel) - 1,		//metamorphasis
	sizeof(TEXT_seaglowingpro) - 1,		//midnight
	sizeof(TEXT_seaglowingpro) - 1,			//ninox
	sizeof(TEXT_sussysy) - 1,			//okiba crackdown
	sizeof(TEXT_elangel) - 1,			//payload GDW cut
	sizeof(TEXT_elangel) - 1,				//problematic
	sizeof(TEXT_nerdboy) - 1,			//pyrophoric
	sizeof(TEXT_clickerty) - 1,			//rainbow tylenol
	sizeof(TEXT_elangel) - 1,			//stalemate
	sizeof(TEXT_elangel) - 1,			//stalemate full
	sizeof(TEXT_elangel) - 1,		//stereo madness2
	sizeof(TEXT_dwedit) - 1,		//subtle oddities
	sizeof(TEXT_elangel) - 1,			//the angel
	sizeof(TEXT_craftyjumper) - 1,		//thoughts
	sizeof(TEXT_usersniper) - 1,				//ultimate destruction
	sizeof(TEXT_seaglowingpro) - 1,		//you've been trolled
	sizeof(TEXT_seaglowingpro) - 1,			//what's a future funk
	sizeof(TEXT_seaglowingpro) - 1,			//windfall
	sizeof(TEXT_elangel) - 1,			//years GDW cut
};


const unsigned char* const coveringartists2[] = {
	0, 			//menu theme
	0, 			//menu theme 2.2
	TEXT_usersniper,		//stereo madness
	0,				//back on track
	TEXT_usersniper,				//polargeist
	0,				//dry out
	TEXT_usersniper,				//base after base
	TEXT_alexmush,				//can't let go
	TEXT_zukinnyk,		//jumper
	TEXT_vikrinox,		//time machine
	TEXT_alexmush,				//cycles
	TEXT_alexmush,				//xstep
	TEXT_vikrinox,		//clutterfunk
	TEXT_usersniper,			//theory of everything
	TEXT_usersniper,		//electroman adventures
	0,			//clubstep
	0,			//electrodynamix
	TEXT_alexmush,		//hexagon force
	0,		//blast processing
	0,			//theory of everything 2
	0,		//geometrical dominator
	0,				//deadlocked
	0,				//fingerbang
	0,				//dash
	0, 			//the challenge
	0, 			//practice
	0, 	//scheming weasel
	
	0, 		//8-bit against the odds redux
	0, 		//at the speed of light 1
	0, 		//at the speed of light 2
	0, 		//at the speed of light 3
	0, 		//at the speed of light full
	0,			//beast mode GDW cut
	0,			//candyland
	0,			//chaoz fantasy
	0,			//chaoz impact
	0,		//clutterfunk 2
	0,		//death moon
	0,				//driving by night
	0, 		//endgame
	0, 				//freedom dive
	0, 				//glint
	TEXT_elangel, 			//golden haze
	0,		//ground to space
	0, 		//haunted woods
	0, 		//hell
	0,		//idols
	0, 		//infernoplex
	TEXT_seaglowingpro, 		//infernoplex full
	0, 		//jack russel
	TEXT_elangel,		//just right
	0, 		//kesobomb
	0, 			//lost
	0,				//ludacris speed
	0,			//machina GDW cut
	0,				//magic touch
	0,		//mayhem short ver
	0,		//mayhem
	0,		//metamorphasis
	0,		//midnight
	0,			//ninox
	0,			//okiba crackdown
	0,			//payload GDW cut
	0,				//problematic
	0,			//pyrophoric
	0,			//rainbow tylenol
	0,			//stalemate
	TEXT_seaglowingpro,			//stalemate full
	0,		//stereo madness2
	0,		//subtle oddities
	0,			//the angel
	0,		//thoughts
	0,				//ultimate destruction
	0,		//you've been trolled
	0,			//what's a future funk
	0,			//windfall
	0,			//years GDW cut
};


const unsigned char coveringartists2_size[] = {
	0, 			//menu theme
	0, 			//menu theme 2.2
	sizeof(TEXT_usersniper) - 1,		//stereo madness
	0,				//back on track
	sizeof(TEXT_usersniper) - 1,				//polargeist
	0,				//dry out
	sizeof(TEXT_usersniper) - 1,				//base after base
	sizeof(TEXT_alexmush) - 1,				//can't let go
	sizeof(TEXT_zukinnyk) - 1,		//jumper
	sizeof(TEXT_vikrinox) - 1,		//time machine
	sizeof(TEXT_alexmush) - 1,				//cycles
	sizeof(TEXT_alexmush) - 1,				//xstep
	sizeof(TEXT_vikrinox) - 1,		//clutterfunk
	sizeof(TEXT_usersniper) - 1,			//theory of everything
	sizeof(TEXT_usersniper) - 1,		//electroman adventures
	0,			//clubstep
	0,			//electrodynamix
	sizeof(TEXT_alexmush) - 1,		//hexagon force
	0,		//blast processing
	0,			//theory of everything 2
	0,		//geometrical dominator
	0,				//deadlocked
	0,				//fingerbang
	0,				//dash
	0, 			//the challenge
	0, 			//practice
	0, 	//scheming weasel
	
	0, 		//8-bit against the odds redux
	0, 		//at the speed of light 1
	0, 		//at the speed of light 2
	0, 		//at the speed of light 3
	0, 		//at the speed of light full
	0,			//beast mode GDW cut
	0,			//candyland
	0,			//chaoz fantasy
	0,			//chaoz impact
	0,		//clutterfunk 2
	0,		//death moon
	0,				//driving by night
	0, 		//endgame
	0, 				//freedom dive
	0, 				//glint
	sizeof(TEXT_elangel) - 1, 			//golden haze
	0,		//ground to space
	0, 		//haunted woods
	0, 		//hell
	0,		//idols
	0, 		//infernoplex
	sizeof(TEXT_seaglowingpro) - 1, 		//infernoplex full
	0, 		//jack russel	
	sizeof(TEXT_elangel) - 1,		//just right
	0, 			//kesobomb
	0, 			//lost
	0,				//ludacris speed
	0,			//machina GDW cut
	0,				//magic touch
	0,		//mayhem short ver
	0,		//mayhem
	0,		//metamorphasis
	0,		//midnight
	0,			//ninox
	0,			//okiba crackdown
	0,			//payload GDW cut
	0,				//problematic
	0,			//pyrophoric
	0,			//rainbow tylenol
	0,			//stalemate
	sizeof(TEXT_seaglowingpro) - 1,			//stalemate full
	0,		//stereo madness2
	0,		//subtle oddities
	0,			//the angel
	0,		//thoughts
	0,				//ultimate destruction
	0,		//you've been trolled
	0,			//what's a future funk
	0,			//windfall
	0,			//years GDW cut
};

const unsigned char* const coveringartists3[] = {
	0, 			//menu theme
	0, 			//menu theme 2.2
	0,		//stereo madness
	0,				//back on track
	TEXT_vikrinox,				//polargeist
	0,				//dry out
	TEXT_zenith,				//base after base
	0,				//can't let go
	TEXT_usersniper,		//jumper
	TEXT_alexmush,		//time machine
	0,				//cycles
	0,				//xstep
	TEXT_zenith,		//clutterfunk
	TEXT_zenith,			//theory of everything
	TEXT_alexmush,		//electroman adventures
	0,			//clubstep
	0,			//electrodynamix
	0,		//hexagon force
	0,		//blast processing
	0,			//theory of everything 2
	0,		//geometrical dominator
	0,				//deadlocked
	0,				//fingerbang
	0,				//dash
	0, 			//the challenge
	0, 			//practice
	0, 	//scheming weasel
	
	0, 		//8-bit against the odds redux
	0, 		//at the speed of light 1
	0, 		//at the speed of light 2
	0, 		//at the speed of light 3
	0, 		//at the speed of light full
	0,			//beast mode GDW cut
	0,			//candyland
	0,			//chaoz fantasy
	0,			//chaoz impact
	0,		//clutterfunk 2
	0,		//death moon
	0,				//driving by night
	0, 		//endgame
	0, 				//freedom dive
	0, 				//glint
	0, 			//golden haze
	0,		//ground to space
	0, 		//haunted woods
	0, 		//hell
	0,		//idols
	0, 		//infernoplex
	0, 		//infernoplex full
	0, 		//jack russel
	0,		//just right
	0,		//kesobomb
	0, 			//lost
	0,				//ludacris speed
	0,			//machina GDW cut
	0,				//magic touch
	0,		//mayhem short ver
	0,		//mayhem
	0,		//metamorphasis
	0,		//midnight
	0,			//ninox
	0,			//okiba crackdown
	0,			//payload GDW cut
	0,				//problematic
	0,			//pyrophoric
	0,			//rainbow tylenol
	0,			//stalemate
	0,			//stalemate full
	0,		//stereo madness2
	0,		//subtle oddities
	0,			//the angel
	0,		//thoughts
	0,				//ultimate destruction
	0,		//you've been trolled
	0,			//what's a future funk
	0,			//windfall
	0,			//years GDW cut
};


const unsigned char coveringartists3_size[] = {
	0, 			//menu theme
	0, 			//menu theme 2.2
	0,		//stereo madness
	0,				//back on track
	sizeof(TEXT_vikrinox) - 1,				//polargeist
	0,				//dry out
	sizeof(TEXT_zenith) - 1,				//base after base
	0,				//can't let go
	sizeof(TEXT_usersniper) - 1,		//jumper
	sizeof(TEXT_alexmush) - 1,		//time machine
	0,				//cycles
	0,				//xstep
	sizeof(TEXT_zenith) - 1,		//clutterfunk
	sizeof(TEXT_zenith) - 1,			//theory of everything
	sizeof(TEXT_alexmush) - 1,		//electroman adventures
	0,			//clubstep
	0,			//electrodynamix
	0,		//hexagon force
	0,		//blast processing
	0,			//theory of everything 2
	0,		//geometrical dominator
	0,				//deadlocked
	0,				//fingerbang
	0,				//dash
	0, 			//the challenge
	0, 			//practice
	0, 	//scheming weasel
	
	0, 		//8-bit against the odds redux
	0, 		//at the speed of light 1
	0, 		//at the speed of light 2
	0, 		//at the speed of light 3
	0, 		//at the speed of light full
	0,			//beast mode GDW cut
	0,			//candyland
	0,			//chaoz fantasy
	0,			//chaoz impact
	0,		//clutterfunk 2
	0,		//death moon
	0,				//driving by night
	0, 		//endgame
	0, 				//freedom dive
	0, 				//glint
	0, 			//golden haze
	0,		//ground to space
	0, 		//haunted woods
	0, 		//hell
	0,		//idols
	0, 		//infernoplex
	0, 		//infernoplex full
	0, 		//jack russel
	0,		//just right
	0,		//kesobomb
	0, 			//lost
	0,				//ludacris speed
	0,			//machina GDW cut
	0,				//magic touch
	0,		//mayhem short ver
	0,		//mayhem
	0,		//metamorphasis
	0,		//midnight
	0,			//ninox
	0,			//okiba crackdown
	0,			//payload GDW cut
	0,				//problematic
	0,			//pyrophoric
	0,			//rainbow tylenol
	0,			//stalemate
	0,			//stalemate full
	0,		//stereo madness2
	0,		//subtle oddities
	0,			//the angel
	0,		//thoughts
	0,				//ultimate destruction
	0,		//you've been trolled
	0,			//what's a future funk
	0,			//windfall
	0,			//years GDW cut
};

const unsigned char* const coveringartists4[] = {
	0, 			//menu theme
	0, 			//menu theme 2.2
	0,		//stereo madness
	0,				//back on track
	0,				//polargeist
	0,				//dry out
	TEXT_alexmush,				//base after base
	0,				//can't let go
	0,		//jumper
	0,		//time machine
	0,				//cycles
	0,				//xstep
	0,		//clutterfunk
	TEXT_leejh20,			//theory of everything
	0,		//electroman adventures
	0,			//clubstep
	0,			//electrodynamix
	0,		//hexagon force
	0,		//blast processing
	0,			//theory of everything 2
	0,		//geometrical dominator
	0,				//deadlocked
	0,				//fingerbang
	0,				//dash
	0, 			//the challenge
	0, 			//practice
	0, 	//scheming weasel
	
	0, 		//8-bit against the odds redux
	0, 		//at the speed of light 1
	0, 		//at the speed of light 2
	0, 		//at the speed of light 3
	0, 		//at the speed of light full
	0,			//beast mode GDW cut
	0,			//candyland
	0,			//chaoz fantasy
	0,			//chaoz impact
	0,		//clutterfunk 2
	0,		//death moon
	0,				//driving by night
	0, 		//endgame
	0, 				//freedom dive
	0, 				//glint
	0, 			//golden haze
	0,		//ground to space
	0, 		//haunted woods
	0, 		//hell
	0,		//idols
	0, 		//infernoplex
	0, 		//infernoplex full
	0, 		//jack russel
	TEXT_dan_harrison,		//just right
	0,		//kesobomb
	0, 			//lost
	0,				//ludacris speed
	0,			//machina GDW cut
	0,				//magic touch
	0,		//mayhem short ver
	0,		//mayhem
	0,		//metamorphasis
	0,		//midnight
	0,			//ninox
	0,			//okiba crackdown
	0,			//payload GDW cut
	0,				//problematic
	0,			//pyrophoric
	0,			//rainbow tylenol
	0,			//stalemate
	0,			//stalemate full
	0,		//stereo madness2
	0,		//subtle oddities
	0,			//the angel
	0,		//thoughts
	0,				//ultimate destruction
	0,		//you've been trolled
	0,			//what's a future funk
	0,			//windfall
	0,			//years GDW cut
};


const unsigned char coveringartists4_size[] = {
	0, 			//menu theme
	0, 			//menu theme 2.2
	0,		//stereo madness
	0,				//back on track
	0,				//polargeist
	0,				//dry out
	sizeof(TEXT_alexmush) - 1,				//base after base
	0,				//can't let go
	0,		//jumper
	0,		//time machine
	0,				//cycles
	0,				//xstep
	0,		//clutterfunk
	sizeof(TEXT_leejh20) - 1,			//theory of everything
	0,		//electroman adventures
	0,			//clubstep
	0,			//electrodynamix
	0,		//hexagon force
	0,		//blast processing
	0,			//theory of everything 2
	0,		//geometrical dominator
	0,				//deadlocked
	0,				//fingerbang
	0,				//dash
	0, 			//the challenge
	0, 			//practice
	0, 	//scheming weasel
	
	0, 		//8-bit against the odds redux
	0, 		//at the speed of light 1
	0, 		//at the speed of light 2
	0, 		//at the speed of light 3
	0, 		//at the speed of light full
	0,			//beast mode GDW cut
	0,			//candyland
	0,			//chaoz fantasy
	0,			//chaoz impact
	0,		//clutterfunk 2
	0,		//death moon
	0,				//driving by night
	0, 		//endgame
	0, 				//freedom dive
	0, 				//glint
	0, 			//golden haze
	0,		//ground to space
	0, 		//haunted woods
	0, 		//hell
	0,		//idols
	0, 		//infernoplex
	0, 		//infernoplex full
	0, 		//jack russel
	sizeof(TEXT_dan_harrison) - 1,		//just right
	0,		//kesobomb
	0, 			//lost
	0,				//ludacris speed
	0,			//machina GDW cut
	0,				//magic touch
	0,		//mayhem short ver
	0,		//mayhem
	0,		//metamorphasis
	0,		//midnight
	0,			//ninox
	0,			//okiba crackdown
	0,			//payload GDW cut
	0,				//problematic
	0,			//pyrophoric
	0,			//rainbow tylenol
	0,			//stalemate
	0,			//stalemate full
	0,		//stereo madness2
	0,		//subtle oddities
	0,			//the angel
	0,		//thoughts
	0,				//ultimate destruction
	0,		//you've been trolled
	0,			//what's a future funk
	0,			//windfall
	0,			//years GDW cut
};






const uint8_t xbgm_lookup_table2[] = {
	song_menu_theme,
	song_menu_theme_b_sides,
	song_stereo_madness,
	song_back_on_track,
	song_polargeist,
	song_dry_out,
	song_base_after_base,
	song_cant_let_go,
	song_jumper,
	song_time_machine,
	song_cycles,
	song_xstep, 
	song_clutterfunk,
	song_theory_of_everything, 
	song_electroman_adventures, 
	song_clubstep,
	song_electrodynamix,
	song_hexagon_force,
	song_blast_processing,
	song_toe_2,
	song_geometrical_dominator,
	song_deadlocked,
	song_fingerdash,
	song_dash,
	song_the_challenge,
	song_practice,
	song_scheming_weasel,
	
	song_against_the_odds_redux,
	song_atthespeedoflight,
	song_atthespeedoflight2,
	song_atthespeedoflight3,
	song_atthespeedoflightfull,
	song_beast_mode_gdw_cut,
	song_candyland,
	song_chaozfantasy,
	song_chaoz_impact,
	song_clutterfunk_2,
	song_death_moon,
	song_driving_by_night,
	song_endgame,
	song_freedom_dive,
	song_glint,
	song_retray,
	song_ground_to_space,
	song_haunted_woods,
	song_hell,
	song_idols,
	song_infernoplex,
	song_infernoplex_full,
	song_jack_russel,
	song_just_right,
	song_kesobomb,
	song_lost,
	song_ludicrous_speed,
	song_machina_gdw_cut,
	song_magic_touch,
	song_mayhem_short,
	song_mayhem,
	song_metamorphosis,
	song_midnight,
	song_ninox,
	song_crackdown,
	song_payload_gdw_cut,
	song_problematic,
	song_pyrophoric,
	song_rainbow_tylenol,
	song_stalemate,
	song_stalemate_full,
	song_stereo_madness_2,
	song_subtle_oddities,
	song_eon,
	song_thoughts,
	song_ultimatedestruction,
	song_youve_been_trolled,
	song_whats_a_future_funk,
	song_windfall,
	song_years_gdw_cut,
};





//#include "defines/bgm_charmap.h"
void bgmtest() {
	song = 0;
	temptemp6 = 0; 	
	#define sfx tmp4
	sfx = 0;
	settingvalue = 0;
  	famistudio_music_stop();
  	music_update();
	menuMusicCurrentlyPlaying=0;
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();
	ppu_off();
	pal_bg(paletteMenu);
	crossPRGBankJump0(unrle_bgm1); 	
	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	update_text1();
	while (1) {
		
		ppu_wait_nmi();
		music_update();
		oam_clear();
		check_if_music_stopped();
		mouse_and_cursor();
		 // read the first controller
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
		if (tmp4) refresh_queue_screen();
/*
		if (mouse.left_press) {
			if ((mouse.x >= 0x63 && mouse.x <= 0x8C)) {
				if (mouse.y >= 0x34 && mouse.y <= 0x3A) {		
					settingvalue = 0;
				}
				else if ((mouse.y >= 0x6C && mouse.y <= 0x73)) {		
					settingvalue = 1;
				}
			}
			if ((mouse.x >= 0x2E && mouse.x <= 0xCC)) {
				if ((mouse.y >= 0xB4 && mouse.y <= 0xBB)) {		
					if (settingvalue == 1) { sfx_play(sfx, 0); }
					else {
						if (!temptemp6) { music_play(xbgm_lookup_table2[song]); temptemp6 = 1; songplaying = 1; }
						else { famistudio_music_stop(); music_update(); temptemp6 = 0; songplaying = 0; }
					}
				}
				if ((mouse.y >= 0xA4 && mouse.y <= 0xAB)) {
					menu_music = song; sfx_play(sfx_orbs, 0);
				}
			}
			if ((mouse.x >= 0x56 && mouse.x <= 0xA5) && (mouse.y >= 0x24 && mouse.y <= 0x2B)) {		
//				code_checker();
				if (gameState == 0xF0) return;
			}

			if ((mouse.x >= 0x35 && mouse.x <= 0xC4)) {
				if (mouse.y >= 0xC4 && mouse.y <= 0xCD) {		
					tmp3--;			
					one_vram_buffer(' ', NTADR_A(11, 7));
					one_vram_buffer(' ', NTADR_A(11, 14));
					menuMusicCurrentlyPlaying = 1;
					gameState = 1;
					return;
				}
				else if (mouse.y >= 0x3D && mouse.y <= 0x64) {
					if (!temptemp6) { music_play(xbgm_lookup_table2[song]); temptemp6 = 1; songplaying = 1; }
					else { famistudio_music_stop(); music_update(); temptemp6 = 0; songplaying = 0; }
				}
				else if (mouse.y >= 0x75 && mouse.y <= 0x9C) {
					sfx_play(sfx, 0);
				}
			}
		}			
	*/

	if (joypad1.press_right || joypad1.press_left) hold_timer = 0;
	if (joypad1.press_right || (joypad1.right && hold_timer >= 15)) { song++; temptemp6 = 0; if (song == song_max) {song = 0;} if (!queuemode) update_text1(); else update_text3(); hold_timer = 0;}
	if (joypad1.press_left || (joypad1.left && hold_timer >= 15)) { if (song == 0) {song = song_max - 1;} else song--; temptemp6 = 0; if (!queuemode) update_text1(); else update_text3();  hold_timer = 0;}

	if (!queuemode) {		//not queue mode
		if (joypad1.press_b) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			menuMusicCurrentlyPlaying = 1;
			gameState = 1;
			return;
		}
		if (joypad1.press_a) {
				if (!temptemp6) { music_play(xbgm_lookup_table2[song]); temptemp6 = 1; songplaying = 1; }
				else { famistudio_music_stop(); music_update(); temptemp6 = 0; songplaying = 0; }
		}					
		if (joypad1.press_select) { 
			ppu_off();
			crossPRGBankJump0(unrle_bgm2); 	   	
			ppu_on_all();
			queuemode = 1;
			update_text2();
			update_text3();
		}
	}
	else {					//queue mode
		if (joypad1.press_select) { 
			ppu_off();
			crossPRGBankJump0(unrle_bgm1);
			ppu_on_all();
			queuemode = 0;
			update_text1();
		}	
		if (joypad1.press_up) {
				play_next_queue();		//debug
		}
		if (joypad1.press_a) {
			if (music_queue[0] == 0xFF) { 
				music_play(xbgm_lookup_table2[song]); 
				music_queue[0] = song;
				update_text2();
			}
			else {
				for (tmp1 = 1; tmp1 < MAX_SONG_QUEUE_SIZE; tmp1++) {
					if (music_queue[tmp1] == 0xFF) {
						music_queue[tmp1] = song;
						break;
					}
				}
				if (music_queue[10] == 0xFF) update_text2();
			}
		}
		if (joypad1.press_b) {
			if (music_queue[0] == 0xFF) { }
			else if (music_queue[1] == 0xFF) { 
					music_queue[0] = 0xFF;
					refresh_queue_screen();
					tmp4 = 2;
					famistudio_music_stop();
					songplaying = 0;
			}
			else {
				for (tmp1 = MAX_SONG_QUEUE_SIZE - 1; tmp1--; tmp1 > 0) {
					if (music_queue[tmp1] != 0xFF) {
						music_queue[tmp1] = 0xFF;
						refresh_queue_screen();
						tmp4 = 2;
						break;
					}
				}
			}
		}
	}				
		
		// sound test codes
	if (hold_timer < 15) hold_timer++;	
	}
}


void refresh_queue_screen() {
		if (!tmp4) {
					ppu_off();
					crossPRGBankJump0(unrle_bgm2);
					update_text2();
					ppu_on_all();
					tmp4 = 2;
		}
		else if (tmp4 == 1) {
					update_text3();
					tmp4 = 3;
		}			
		else if (tmp4 == 2) {
			for (tmp1 = 4; tmp1 < 8; tmp1++) {			//limited to 5??
			if (music_queue[tmp1] != 0xFF) {
				tmp3 = music_queue[tmp1];
				__A__ = idx16_load_hi_NOC(xbgmtexts1, tmp3);
				if (__A__) { 
					multi_vram_buffer_horz(xbgmtexts1[tmp3 & 0x7F], xbgmtext1_size[tmp3], NTADR_A(3, (13 + (tmp1))));
					__A__ = idx16_load_hi_NOC(xbgmtexts2, tmp3);
					multi_vram_buffer_horz(xbgmtexts2[tmp3 & 0x7F], xbgmtext2_size[tmp3], NTADR_A((4 + xbgmtext1_size[tmp3]), (13 + (tmp1))));
				}
				else {
					__A__ = idx16_load_hi_NOC(xbgmtexts2, tmp3);
					multi_vram_buffer_horz(xbgmtexts2[tmp3 & 0x7F], xbgmtext2_size[tmp3], NTADR_A(3, (13 + (tmp1))));
					multi_vram_buffer_horz(blanktext2, 7, NTADR_A((3 + xbgmtext2_size[tmp3]), (13 + (tmp1))));

				}				
			}
			else one_vram_buffer_horz_repeat('$', 22, NTADR_A(3, (13 + (tmp1))));	
			}
			tmp4 = 1;
		}
		else if (tmp4 == 3) {
			for (tmp1 = 8; tmp1 < 10; tmp1++) {			//limited to 5??
			if (music_queue[tmp1] != 0xFF) {
				tmp3 = music_queue[tmp1];
				__A__ = idx16_load_hi_NOC(xbgmtexts1, tmp3);
				if (__A__) { 
					multi_vram_buffer_horz(xbgmtexts1[tmp3 & 0x7F], xbgmtext1_size[tmp3], NTADR_A(3, (13 + (tmp1))));
					__A__ = idx16_load_hi_NOC(xbgmtexts2, tmp3);
					multi_vram_buffer_horz(xbgmtexts2[tmp3 & 0x7F], xbgmtext2_size[tmp3], NTADR_A((4 + xbgmtext1_size[tmp3]), (13 + (tmp1))));
				}
				else {
					__A__ = idx16_load_hi_NOC(xbgmtexts2, tmp3);
					multi_vram_buffer_horz(xbgmtexts2[tmp3 & 0x7F], xbgmtext2_size[tmp3], NTADR_A(3, (13 + (tmp1))));
					multi_vram_buffer_horz(blanktext2, 7, NTADR_A((3 + xbgmtext2_size[tmp3]), (13 + (tmp1))));

				}				
			}
			else one_vram_buffer_horz_repeat('$', 22, NTADR_A(3, (13 + (tmp1))));	
			}
			tmp4 = 0;
		}
			
}					

//CODE_BANK_POP()


void gameboy_check() {
		if (gameboy_mode == 0) color_emphasis(COL_EMP_NORMAL);
		else if (gameboy_mode == 1) color_emphasis(COL_EMP_GREY);
		else if (gameboy_mode == 2) { color_emphasis(COL_EMP_GREYRED); }
		else if (gameboy_mode == 3) { color_emphasis(COL_EMP_GREYGREEN); }
		else if (gameboy_mode == 4) { color_emphasis(COL_EMP_GREYBLUE); }
		else if (gameboy_mode == 5) { color_emphasis(COL_EMP_GREYYELLOW); }
		else if (gameboy_mode == 6) { color_emphasis(COL_EMP_GREYPURPLE); }
		else if (gameboy_mode == 7) { color_emphasis(COL_EMP_GREYCYAN); }
		else if (gameboy_mode == 8) { color_emphasis(COL_EMP_GREYDARK); }
}



void colorinc() {
	if (idx8_inc(icon_colors, settingvalue) & 0x30) {
		if ((uint8_t)(icon_colors[settingvalue] & 0x0F) >= 0x0D)
			idx8_store(icon_colors, settingvalue, (icon_colors[settingvalue] + 0x10) & 0x30);
	} else {
		if (((icon_colors[settingvalue] - 0x0D) & 0xFE) == 0)	// if color == 0x0D or 0x0E
			icon_colors[settingvalue] = 0x0F;
	}	
}

void colordec() {
	if (idx8_dec(icon_colors, settingvalue) & 0x30) {
		if ((uint8_t)(icon_colors[settingvalue] & 0x0F) >= 0x0D)
			idx8_store(icon_colors, settingvalue, (icon_colors[settingvalue] & 0x30) | 0x0C);
	} else {
		if (((icon_colors[settingvalue] - 0x0D) & 0xFE) == 0)	// if color == 0x0D or 0x0E
			icon_colors[settingvalue] = 0x0C;
	}
}	


#include "defines/mainmenu_charmap.h"


const unsigned char gameboytext1[]="  GREY";
const unsigned char gameboytext2[]="   RED";
const unsigned char gameboytext3[]=" GREEN";
const unsigned char gameboytext4[]="  BLUE";
const unsigned char gameboytext5[]="YELLOW";
const unsigned char gameboytext6[]="PURPLE";
const unsigned char gameboytext7[]="  CYAN";
const unsigned char gameboytext8[]="  DARK";

const unsigned char* const gameboytexts[] = {
	0, gameboytext1, gameboytext2, gameboytext3, gameboytext4, gameboytext5, gameboytext6, gameboytext7, gameboytext8
};

const unsigned char gameboy_text_size[] = {
	0,
	sizeof(gameboytext1) - 1,
	sizeof(gameboytext2) - 1,
	sizeof(gameboytext3) - 1,
	sizeof(gameboytext4) - 1,
	sizeof(gameboytext5) - 1,
	sizeof(gameboytext6) - 1,
	sizeof(gameboytext7) - 1,
	sizeof(gameboytext8) - 1
};



void funsettings() {

}

void set_fun_settings() {

}	







#include "defines/color1_charmap.h"

/*
	Refreshes level name & number
*/
void refreshmenu() {

};

void refreshmenu_part2() {

}

#include "defines/endlevel_charmap.h"
void lvl_done_update() {

}	


#define BAR_TILES 20
#define CENTER_TILES BAR_TILES - 2
#define BAR_MAX 100
#define NUMBER_PER_TILES BAR_MAX / BAR_TILES
void draw_progress_bar() {

}

#define TOTAL_PIXELS 8 * BAR_TILES // 8 * 20 = 160
#define PIXELS_PER_UNIT (TOTAL_PIXELS * 10) / (BAR_MAX) // (1600 / 100) = 1.6 | multiplied by 10 because of no floats
#define PIXELS_PER_PERCENTAGE (PIXELS_PER_UNIT * 256) / 10 // 1.6 * 256 = 409.6

void calculate_sprite_pos() {

}

void update_text1() {
	__A__ = idx16_load_hi_NOC(xbgmtexts1, song);
	if (__A__) draw_padded_text(xbgmtexts1[song & 0x7F], xbgmtext1_size[song], 14, NTADR_A(9, 7));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 7));
	__A__ = idx16_load_hi_NOC(xbgmtexts2, song);
	if (__A__) draw_padded_text(xbgmtexts2[song & 0x7F], xbgmtext2_size[song], 14, NTADR_A(9, 8));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 8));
	
//	__A__ = idx16_load_hi_NOC(origartists1, song);
//	if (__A__) draw_padded_text(origartists1[song & 0x7F], origartists1_size[song], 17, NTADR_A(7, 14));
//	else one_vram_buffer_horz_repeat('$', 17, NTADR_A(7, 14));
	__A__ = idx16_load_hi_NOC(origartists2, song);
	if (__A__) draw_padded_text(origartists2[song & 0x7F], origartists2_size[song], 14, NTADR_A(9, 13));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 13));
	
	__A__ = idx16_load_hi_NOC(coveringartists1, song);
	if (__A__) draw_padded_text(coveringartists1[song & 0x7F], coveringartists1_size[song], 14, NTADR_A(9, 19));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 19));
	__A__ = idx16_load_hi_NOC(coveringartists2, song);
	if (__A__) draw_padded_text(coveringartists2[song & 0x7F], coveringartists2_size[song], 14, NTADR_A(9, 20));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 20));
	__A__ = idx16_load_hi_NOC(coveringartists3, song);
	if (__A__) draw_padded_text(coveringartists3[song & 0x7F], coveringartists3_size[song], 14, NTADR_A(9, 21));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 21));
	__A__ = idx16_load_hi_NOC(coveringartists4, song);
	if (__A__) draw_padded_text(coveringartists4[song & 0x7F], coveringartists4_size[song], 14, NTADR_A(9, 22));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 22));
}	

void update_text3() {
	__A__ = idx16_load_hi_NOC(xbgmtexts1, song);
	if (__A__) draw_padded_text(xbgmtexts1[song & 0x7F], xbgmtext1_size[song], 14, NTADR_A(9, 7));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 7));
	__A__ = idx16_load_hi_NOC(xbgmtexts2, song);
	if (__A__) draw_padded_text(xbgmtexts2[song & 0x7F], xbgmtext2_size[song], 14, NTADR_A(9, 8));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 8));
}
void update_text2() {
	//ppu_off();
//	__A__ = idx16_load_hi_NOC(xbgmtexts1, song);
//	if (__A__) draw_padded_text(xbgmtexts1[song & 0x7F], xbgmtext1_size[song], 14, NTADR_A(9, 7));
//	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 7));
//	__A__ = idx16_load_hi_NOC(xbgmtexts2, song);
//	if (__A__) draw_padded_text(xbgmtexts2[song & 0x7F], xbgmtext2_size[song], 14, NTADR_A(9, 8));
//	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 8));
	
//	one_vram_buffer(0xB0, NTADR_A(5,13)); // 0
//	one_vram_buffer(0xB1, NTADR_A(5,14)); // 1
//	one_vram_buffer(0xB2, NTADR_A(5,15)); // 2
//	one_vram_buffer(0xB3, NTADR_A(5,16)); // 3
//	one_vram_buffer(0xB4, NTADR_A(5,17)); // 4
//	one_vram_buffer(0xB5, NTADR_A(5,18)); // 5
//	one_vram_buffer(0xB6, NTADR_A(5,19)); // 6
//	one_vram_buffer(0xB7, NTADR_A(5,20)); // 7
//	one_vram_buffer(0xB8, NTADR_A(5,21)); // 8
//	one_vram_buffer(0xB9, NTADR_A(5,22)); // 9
	
//	for (tmp1 = 0; tmp1 < 10; tmp1++) {
	for (tmp1 = 0; tmp1 < 4; tmp1++) {			//limited to 5??
		if (music_queue[tmp1] != 0xFF) {
			tmp3 = music_queue[tmp1];
			__A__ = idx16_load_hi_NOC(xbgmtexts1, tmp3);
			if (__A__) { 
				multi_vram_buffer_horz(xbgmtexts1[tmp3 & 0x7F], xbgmtext1_size[tmp3], NTADR_A(3, (13 + (tmp1))));
				__A__ = idx16_load_hi_NOC(xbgmtexts2, tmp3);
				multi_vram_buffer_horz(xbgmtexts2[tmp3 & 0x7F], xbgmtext2_size[tmp3], NTADR_A((4 + xbgmtext1_size[tmp3]), (13 + (tmp1))));
			}
			else {
				__A__ = idx16_load_hi_NOC(xbgmtexts2, tmp3);
				multi_vram_buffer_horz(xbgmtexts2[tmp3 & 0x7F], xbgmtext2_size[tmp3], NTADR_A(3, (13 + (tmp1))));
				multi_vram_buffer_horz(blanktext2, 7, NTADR_A((3 + xbgmtext2_size[tmp3]), (13 + (tmp1))));

			}				
		}
		else one_vram_buffer_horz_repeat('$', 22, NTADR_A(3, (13 + (tmp1))));	
	}	
	//ppu_on_all();
	tmp4 = 2;
}	

void play_next_queue() {
			tmp1 = 0;

			for (tmp1 = 0; tmp1 < MAX_SONG_QUEUE_SIZE; tmp1++) {		
				tmp2 = tmp1 + 1;
				music_queue[tmp1] = music_queue[tmp2];
			}

			music_queue[MAX_SONG_QUEUE_SIZE] = 0xFF;

			if (music_queue[0] != 0xFF) { music_play(xbgm_lookup_table2[music_queue[0]]); }
			else { famistudio_music_stop(); songplaying = 0; }
				
			refresh_queue_screen();
			tmp4 = 2;
}			


void check_if_music_stopped() {
	if (!queuemode) {
		if (songplaying && famistudio_song_speed == 0x80) { music_play(xbgm_lookup_table2[song]); }
	}
	else {
		if (famistudio_song_speed == 0x80) {

			play_next_queue();
		}
	}
}	

CODE_BANK_POP()

