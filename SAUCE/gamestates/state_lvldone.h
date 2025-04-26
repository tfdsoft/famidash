
CODE_BANK_PUSH("LVL_BANK_00")
void lvl_done_update();
void mouse_and_cursor();
void refresh_queue_screen();
void text_stuff();
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
}
void checkcoinproceed(){

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
const unsigned char TEXT_trackfull[]="TRACK$FULL";


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
const unsigned char TEXT_powertrip[]="POWER$TRIP";
const unsigned char TEXT_2textcrackdown[]="CRACKDOWN";
const unsigned char TEXT_2textstalemate[]="STALEMATE";
const unsigned char TEXT_2textwoods[]="HAUNTED$WOODS";
const unsigned char TEXT_2textchaoz[]="CHAOZ$FANTASY";
const unsigned char TEXT_chaozairflow[]="CHAOZ$AIRFLOW";
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
const unsigned char TEXT_accelerate[]="ACCELERATE";
const unsigned char TEXT_glint[]="GLINT";
const unsigned char TEXT_flow[]="FLOW";
const unsigned char TEXT_remix[]="MIX";
const unsigned char TEXT_GDW[]="GDW$CUT";
const unsigned char TEXT_cantelectroman[]="CANT";
const unsigned char TEXT_round1[]="ROUND$1";
const unsigned char TEXT_thesevenseas[]="THE$SEVEN$SEAS";
const unsigned char TEXT_spacepirates[]="SPACE$PIRATES";

const unsigned char TEXT_future[]="WHATS$A";
const unsigned char TEXT_future2[]="FUTURE$FUNK";

const unsigned char TEXT_freedom[]="FREEDOM";
const unsigned char TEXT_freedom2[]="DIVE";

const unsigned char TEXT_mayhem[]="MAYHEM";
const unsigned char TEXT_mayhem2[]="SHORT$VER";

const unsigned char TEXT_groundto[]="GROUND$TO";
const unsigned char TEXT_groundto2[]="SPACE";
const unsigned char TEXT_groundto3[]="KRUSTY$KRAB";

const unsigned char TEXT_ludicrous[]="LUDICROUS";
const unsigned char TEXT_ludicrous2[]="SPEED";

const unsigned char TEXT_idols[]="IDOLS";
const unsigned char TEXT_metamorphasis[]="METAMORPHASIS";
const unsigned char TEXT_isolation[]="ISOLATION";

const unsigned char TEXT_fingerbang[]="FINGERBANG";
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
const unsigned char TEXT_sonicblaster[]="SONIC$BLASTER";
const unsigned char TEXT_xo[]="XO";
const unsigned char TEXT_kratos[]="KRATOS";
const unsigned char TEXT_eighto[]="EIGHTO";
const unsigned char TEXT_beepbeep[]="BEEP$BEEP";

const unsigned char TEXT_hsad2[]="HSAD";
const unsigned char TEXT_repmuj2[]="REPMUJ";
const unsigned char TEXT_unem2[]="EMEHT$UNEM";
const unsigned char TEXT_ssendam_oerets[]="OERETS";
const unsigned char TEXT_ssendam_oerets2[]="SSENDAM";


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
};

const unsigned char sfxtexts_size[] = {

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
	TEXT_challenge,						//the challenge
	0,									//practice
	TEXT_xweasel, 						//scheming weasel
	
	TEXT_against,						//8-bit against the odds redux
	0,									//accelerate
	TEXT_speed,							//at the speed of light pt 1
	TEXT_speed,							//at the speed of light pt 2
	TEXT_speed,							//at the speed of light pt 3
	TEXT_speed,							//at the speed of light full
	TEXT_xlevel1text2,					//back on track full
	TEXT_beastmode,						//beast mode (gdw cut)
	0,									//beep beep 
	0,									//candyland
	TEXT_cantelectroman,				//can't electroman
	TEXT_xlevel2text6,					//can't let go remixed
	0,									//chaoz airflow
	0,									//chaoz fantasy
	0,									//chaoz impact
	TEXT_2textclubstep,					//clubstep full version
	0,									//clutterfunk 2
	TEXT_dash2,							//dash full
	0,									//death moon
	TEXT_driving,						//driving by midnight
	TEXT_xlevel2text4,					//dry out full
	0,									//eighto
	0,									//endgame
	0,									//fingerbang
	0,									//flow
	TEXT_freedom,						//freedom dive
	0,									//glint
	0,									//golden haze
	TEXT_groundto,						//ground to krusty krab
	TEXT_groundto,						//ground to space
	0,									//haunted woods
	0,									//idols
	0,									//infernoplex
	TEXT_2textinfernoplex,				//infernoplex full
	0,									//isolation
	0,									//jack russel
	TEXT_xlevel2text7,					//jumper full ver
	0,									//just right
	TEXT_2textjustright,				//just right full
	0,									//kesobomb
	0,									//kratos
	0,									//lost
	TEXT_ludicrous,						//ludicrous speed
	TEXT_machina,						//machina (gdw cut)
	0,									//magic touch
	TEXT_mayhem,						//mayhem
	0,									//mayhem short ver
	0,									//metamorphasis
	0,									//midnight
	0,									//ninox
	TEXT_crackdown,						//okiba crackdown
	TEXT_payload,						//payload (gdw cut)
	0,									//power trip
	0,									//problematic
	0,									//pyrophoric
	TEXT_rainbowt,						//rainbow tylenol
	TEXT_round1,						//round 1 (gdw cut)
	0,									//sonic blaster
	TEXT_spacepirates,					//space pirates (gdw cut)
	0,									//stalemate
	TEXT_2textstalemate,				//stalemate full version
	TEXT_xlevel1text1,					//stereo madness 2
	TEXT_subtle,						//subtle oddities
	0,									//the angel
	0,									//the seven seas
	0,									//thoughts
	TEXT_xlevel2text8,					//time machine full
	TEXT_ultimate,						//ultimate destruction
	TEXT_youvebeen,						//you've been trolled
	TEXT_future,						//whats a future funk
	0,									//windfall
	0,									//xo
	TEXT_years,							//years (gdw cut)
	0,									//emeht unem
	TEXT_ssendam_oerets,				//ssendam oerets
	0,									//hsaD
	0,									//repmuJ


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
	sizeof(TEXT_challenge) - 1,			//the challenge
	0,									//practice
	sizeof(TEXT_xweasel) - 1,			//scheming weasel
	
	sizeof(TEXT_against) - 1,			//8-bit against the odds redux
	0,									//accelerate
	sizeof(TEXT_speed) - 1,				//at the speed of light pt 1
	sizeof(TEXT_speed) - 1,				//at the speed of light pt 2
	sizeof(TEXT_speed) - 1,				//at the speed of light pt 3
	sizeof(TEXT_speed) - 1,				//at the speed of light full
	sizeof(TEXT_xlevel1text2) - 1,		//back on track full
	sizeof(TEXT_beastmode) - 1,			//beast mode (gdw cut)
	0,									//beep beep
	0,									//candyland
	sizeof(TEXT_cantelectroman) - 1,	//can't electroman
	sizeof(TEXT_xlevel2text6) - 1,		//can't let go remixed
	0,									//chaoz airflow
	0,									//chaoz fantasy
	0,									//chaoz impact
	sizeof(TEXT_2textclubstep) - 1,		//clubstep full
	0,									//clutterfunk 2
	sizeof(TEXT_dash2) - 1,				//dash full
	0,									//death moon
	sizeof(TEXT_driving) - 1,			//driving by midnight
	sizeof(TEXT_xlevel2text4) - 1,		//dry out full
	0,									//eighto
	0,									//endgame
	0,									//fingerbang
	0,									//flow
	sizeof(TEXT_freedom) - 1,			//freedom dive
	0,									//glint
	0,									//golden haze
	sizeof(TEXT_groundto) - 1,			//ground to krusty krab
	sizeof(TEXT_groundto) - 1,			//ground to space
	0,									//haunted woods
	0,									//idols
	0,									//infernoplex
	sizeof(TEXT_2textinfernoplex) - 1,	//infernoplex full
	0,									//isolation
	0,									//jack russel
	sizeof(TEXT_xlevel2text7) - 1,		//jumper full ver
	0,									//just right
	sizeof(TEXT_2textjustright) - 1,	//just right full
	0,									//kesobomb
	0,									//kratos
	0,									//lost
	sizeof(TEXT_ludicrous) - 1,			//ludicrous speed
	sizeof(TEXT_machina) - 1,			//Machina (GDW cut)
	0,									//magic touch
	sizeof(TEXT_mayhem) - 1,			//mayhem
	0,									//mayhem short ver
	0,									//metamorphasis
	0,									//midnight
	0,									//ninox
	sizeof(TEXT_crackdown) - 1,			//okiba crackdown
	sizeof(TEXT_payload) - 1,			//payload (gdw cut)
	0,									//power trip
	0,									//problematic
	0,									//pyrophoric
	sizeof(TEXT_rainbowt) - 1,			//rainbow tylenol
	sizeof(TEXT_round1) - 1,			//round 1 (gdw cut)
	0,									//sonic blaster
	sizeof(TEXT_spacepirates) - 1,		//space pirates (gdw cut)
	0,									//stalemate
	sizeof(TEXT_2textstalemate) - 1,	//stalemate full version
	sizeof(TEXT_xlevel1text1) - 1,		//stereo madness 2
	sizeof(TEXT_subtle) - 1,			//subtle oddities
	0,									//the angel
	0,									//the seven seas
	0,									//thoughts
	sizeof(TEXT_xlevel2text8) - 1,		//time machine full
	sizeof(TEXT_ultimate) - 1,			//ultimate destruction
	sizeof(TEXT_youvebeen) - 1,			//youve been trolled
	sizeof(TEXT_future) - 1,			//whats a future funk
	0,									//windfall
	0,									//xo
	sizeof(TEXT_years) - 1,				//years (gdw cut)
	0,									//emeht unem
	sizeof(TEXT_ssendam_oerets) - 1,	//ssendam oerets
	0,									//hsaD
	0,									//repmuJ
	
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
	
	TEXT_against2,						//8-bit against the odds redux
	TEXT_accelerate,					//accelerate
	TEXT_2textspeed,					//at the speed of light pt 1
	TEXT_2textspeed2,					//at the speed of light pt 2
	TEXT_2textspeed3,					//at the speed of light pt 3
	TEXT_2textspeedfull,				//at the speed of light full
	TEXT_trackfull,						//back on track full
	TEXT_GDW,							//beast mode (gdw cut)
	TEXT_beepbeep,						//beepbeep
	TEXT_candyland,						//candyland
	TEXT_xlevel1textD,					//can't electroman
	TEXT_remix,							//can't let go remixed
	TEXT_chaozairflow,					//chaoz airflow
	TEXT_2textchaoz,					//chaoz fantasy
	TEXT_speedracer,					//chaoz impact
	TEXT_2textfullversion,				//clubstep full
	TEXT_2clutterfunk2,					//clutterfunk 2
	TEXT_2textfullversion,				//dash full
	TEXT_2deathmoon,					//death moon
	TEXT_driving2,						//driving by night
	TEXT_2textfullversion,				//dry out full
	TEXT_eighto,						//eighto
	TEXT_xlevel2textE,					//endgame
	TEXT_fingerbang,					//fingerbang
	TEXT_flow,							//flow
	TEXT_freedom2,						//freedom drive
	TEXT_glint,							//glint
	TEXT_retray,						//golden haze
	TEXT_groundto3,						//ground to krusty krab
	TEXT_groundto2,						//ground to space
	TEXT_2textwoods,					//lost in the woods
	TEXT_idols,							//idols
	TEXT_2textinfernoplex,				//infernoplex
	TEXT_2textfullversion,				//infernoplex full version
	TEXT_isolation,						//isolation
	TEXT_jackrussel,					//jack russel
	TEXT_2textfullversion,				//jumper full ver
	TEXT_2textjustright,				//just right
	TEXT_2textfullversion,				//just right full ver
	TEXT_kesobomb,						//kesobomb
	TEXT_kratos,						//kratos
	TEXT_2textlost,						//lost
	TEXT_ludicrous2,					//ludicrous speed
	TEXT_GDW,							//machina (gdw cut)
	TEXT_magictouch,					//magic touch
	TEXT_mayhem2,						//mayhem short ver
	TEXT_mayhem,						//mayhem
	TEXT_metamorphasis,					//metamorphasis
	TEXT_2textmidnight,					//midnight
	TEXT_ninox2,						//ninox
	TEXT_2textcrackdown,				//okiba crackdown
	TEXT_GDW,							//payload (gdw cut)
	TEXT_powertrip,						//power trip
	TEXT_2textproblematic,				//problematic
	TEXT_pyrophoric,					//pyrophoric
	TEXT_rainbowt2,						//rainbow tylenol
	TEXT_GDW,							//round 1 (gdw cut)
	TEXT_sonicblaster,					//sonic blaster
	TEXT_GDW,							//space pirates (gdw cut)
	TEXT_2textstalemate,				//stalemate
	TEXT_2textfullversion,				//stalemate full version
	TEXT_2textstereo,					//stereo madness 2
	TEXT_subtle2,						//subtle oddities
	TEXT_2texteon,						//the angel
	TEXT_thesevenseas,					//the seven seas
	TEXT_thoughts,						//thoughts
	TEXT_2textfullversion,				//time machine full
	TEXT_ultimate2,						//ultimate destruction
	TEXT_youvebeen2,					//you've been trolled
	TEXT_future2,						//whats a future funk
	TEXT_windfall,						//windfall
	TEXT_xo,							//xo
	TEXT_GDW,							//years (gdw cut)
	TEXT_unem2,							//emeht unem
	TEXT_ssendam_oerets2,				//ssendam oerets
	TEXT_hsad2,							//hsaD
	TEXT_repmuj2,						//repmuJ
	
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
	
	sizeof(TEXT_against2) - 1,						//8-bit against the odds redux
	sizeof(TEXT_accelerate) - 1,					//accelerate
	sizeof(TEXT_2textspeed) - 1,					//at the speed of light pt 1
	sizeof(TEXT_2textspeed2) - 1,					//at the speed of light pt 2
	sizeof(TEXT_2textspeed3) - 1,					//at the speed of light pt 3
	sizeof(TEXT_2textspeedfull) - 1,				//at the speed of light full
	sizeof(TEXT_trackfull) - 1,						//back on track full
	sizeof(TEXT_GDW) - 1,							//beast mode (gdw cut)
	sizeof(TEXT_beepbeep) - 1,						//beep beep
	sizeof(TEXT_candyland) - 1,						//candyland
	sizeof(TEXT_xlevel1textD) - 1,					//can't electroman
	sizeof(TEXT_remix) - 1,							//can't let go remixed
	sizeof(TEXT_chaozairflow) - 1,					//chaoz airflow
	sizeof(TEXT_2textchaoz) - 1,					//chaoz fantasy
	sizeof(TEXT_speedracer) - 1,					//chaoz impact
	sizeof(TEXT_2textfullversion) - 1,				//clubstep full
	sizeof(TEXT_2clutterfunk2) - 1,					//clutterfunk 2
	sizeof(TEXT_2textfullversion) - 1,				//dash full
	sizeof(TEXT_2deathmoon) - 1,					//death moon
	sizeof(TEXT_driving2) - 1,						//driving by midnight
	sizeof(TEXT_2textfullversion) - 1,				//dry out full version
	sizeof(TEXT_eighto) - 1,						//eighto
	sizeof(TEXT_xlevel2textE) - 1,					//endgame
	sizeof(TEXT_fingerbang) - 1,					//fingerbang
	sizeof(TEXT_flow) - 1,							//flow
	sizeof(TEXT_freedom2) - 1,						//freedom dive
	sizeof(TEXT_glint) - 1,							//glint
	sizeof(TEXT_retray) - 1,						//golden haze
	sizeof(TEXT_groundto3) - 1,						//ground to krusty krab
	sizeof(TEXT_groundto2) - 1,						//ground to space
	sizeof(TEXT_2textwoods) - 1,					//lost in the woods
	sizeof(TEXT_idols) - 1,							//idols
	sizeof(TEXT_2textinfernoplex) - 1,				//infernoplex
	sizeof(TEXT_2textfullversion) - 1,				//infernoplex full version
	sizeof(TEXT_isolation) - 1,						//isolation
	sizeof(TEXT_jackrussel) - 1,					//jack russel
	sizeof(TEXT_2textfullversion) - 1,				//jumper full version
	sizeof(TEXT_2textjustright) - 1,				//just right
	sizeof(TEXT_2textfullversion) - 1,				//just right full ver
	sizeof(TEXT_kesobomb) - 1,						//kesobomb
	sizeof(TEXT_kratos) - 1,						//kratos
	sizeof(TEXT_2textlost) - 1,						//lost
	sizeof(TEXT_ludicrous2) - 1,					//ludicrous speed
	sizeof(TEXT_GDW) - 1,							//machina (gdw cut)
	sizeof(TEXT_magictouch) - 1,					//magic touch
	sizeof(TEXT_mayhem2) - 1,						//mayhem short ver
	sizeof(TEXT_mayhem) - 1,						//mayhem
	sizeof(TEXT_metamorphasis) - 1,					//metamorphasis
	sizeof(TEXT_2textmidnight) - 1,					//midnight
	sizeof(TEXT_ninox2) - 1,						//ninox
	sizeof(TEXT_2textcrackdown) - 1,				//okiba crackdown
	sizeof(TEXT_GDW) - 1,							//payload (gdw cut)
	sizeof(TEXT_powertrip) - 1,						//power trip
	sizeof(TEXT_2textproblematic) - 1,				//problematic
	sizeof(TEXT_pyrophoric) - 1,					//pyrophoric
	sizeof(TEXT_rainbowt2) - 1,						//rainbow tylenol
	sizeof(TEXT_GDW) - 1,							//round 1 (gdw cut)
	sizeof(TEXT_sonicblaster) - 1,					//sonic blaster
	sizeof(TEXT_GDW) - 1,							//space pirates
	sizeof(TEXT_2textstalemate) - 1,				//stalemate
	sizeof(TEXT_2textfullversion) - 1,				//stalemate full version
	sizeof(TEXT_2textstereo) - 1,					//stereo madness 2
	sizeof(TEXT_subtle2) - 1,						//subtle oddities
	sizeof(TEXT_2texteon) - 1,						//the angel
	sizeof(TEXT_thesevenseas) - 1,					//the seven seas
	sizeof(TEXT_thoughts) - 1,						//thoughts
	sizeof(TEXT_2textfullversion) - 1,				//time machine full
	sizeof(TEXT_ultimate2) - 1,						//ultimate destruction
	sizeof(TEXT_youvebeen2) - 1,					//you've been trolled
	sizeof(TEXT_future2) - 1,						//whats a future funk
	sizeof(TEXT_windfall) - 1,						//windfall
	sizeof(TEXT_xo) - 1,							//xo
	sizeof(TEXT_GDW) - 1,							//years (gdw cut)
	sizeof(TEXT_unem2) - 1,							//unem emeht
	sizeof(TEXT_ssendam_oerets2) - 1,				//ssendam oerets
	sizeof(TEXT_hsad2) - 1,							//hsaD
	sizeof(TEXT_repmuj2) - 1,						//repmuJ
	
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
const unsigned char TEXT_gdcolon[]="GD$COLON";
const unsigned char TEXT_nighthawk22[]="NIGHTHAWK22";
const unsigned char TEXT_aaron[]="EDEN$$$$AARON";
const unsigned char TEXT_musselwhite[]="MUSSELWHITE";
const unsigned char TEXT_shappy[]="SHAPPY";
const unsigned char TEXT_jomekka[]="JOMEKKA";


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
const unsigned char TEXT_creo[]="CREO";
const unsigned char TEXT_schtiffles[]="SCHTIFFLES";
const unsigned char TEXT_boomkitty[]="BOOM$KITTY";






const unsigned char* const origartists2[] = {
	TEXT_robtop, 			//menu theme
	TEXT_gdcolon, 			//menu theme 2.2
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
	TEXT_mdk,				//fingerdash
	TEXT_mdk,				//dash
	TEXT_robtop, 			//the challenge
	TEXT_ocular, 			//practice
	TEXT_kevin_macleod, 	//scheming weasel
	
	TEXT_eliteferrex, 		//8-bit against the odds redux
	TEXT_acidnotation,		//accelerate
	TEXT_dimrain47, 		//at the speed of light 1
	TEXT_dimrain47, 		//at the speed of light 2
	TEXT_dimrain47, 		//at the speed of light 3
	TEXT_dimrain47, 		//at the speed of light full
	TEXT_djvi,				//back on track full
	TEXT_dexarson,			//beast mode GDW cut
	TEXT_schtiffles,		//beep beep
	TEXT_tobu,				//candyland
	TEXT_djvi,				//can't electroman
	TEXT_djvi,				//can't let go remixed
	TEXT_paragonx9,			//chaoz airflow
	TEXT_paragonx9,			//chaoz fantasy
	TEXT_paragonx9,			//chaoz impact
	TEXT_djnate,			//clubstep full
	TEXT_waterflame,		//clutterfunk 2
	TEXT_mdk,				//dash full
	TEXT_soundholick,		//death moon
	TEXT_reinn,				//driving by night
	TEXT_djvi, 				//dry out full version
	TEXT_jomekka, 			//eighto
	TEXT_waterflame, 		//endgame
	TEXT_mdk, 				//fingerbang
	TEXT_creo, 				//flow
	TEXT_xi, 				//freedom dive
	TEXT_dominuus, 			//glint
	TEXT_detious, 			//golden haze
	TEXT_seaglowingpro,		//ground to krusty krab
	TEXT_seaglowingpro,		//ground to space
	TEXT_waterflame, 		//haunted woods
	TEXT_virtual_riot,		//idols
	TEXT_dimrain47, 		//infernoplex
	TEXT_dimrain47, 		//infernoplex full
	TEXT_nighthawk22,		//isolation
	TEXT_bossfight,			//jack russel
	TEXT_waterflame,		//jumper full version
	TEXT_tessaviolet,		//just right
	TEXT_tessaviolet,		//just right full
	TEXT_rymdkraft,			//kesobomb
	TEXT_shappy,			//kratos
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
	TEXT_boomkitty,			//power trip
	TEXT_nk,				//problematic
	TEXT_nerdboy,			//pyrophoric
	TEXT_kitsune,			//rainbow tylenol
	TEXT_dexarson,			//round 1 (gdw cut)
	TEXT_f777,				//sonic blaster
	TEXT_waterflame,		//space pirates (gdw cut)
	TEXT_kayoszx,			//stalemate
	TEXT_kayoszx,			//stalemate full
	TEXT_foreverbound,		//stereo madness2
	TEXT_lemondemon,		//subtle oddities
	TEXT_cacola,			//the angel
	TEXT_f777,				//the seven seas
	TEXT_craftyjumper,		//thoughts
	TEXT_waterflame,		//time machine full
	TEXT_tmm43,				//ultimate destruction
	TEXT_theclydecash,		//you've been trolled
	TEXT_lemkuuja,			//what's a future funk
	TEXT_thefatrat,			//windfall
	TEXT_aaron,				//xo
	TEXT_dexarson,			//years GDW cut
	TEXT_robtop,			//emeht uneM
	TEXT_foreverbound,		//ssendam oerets
	TEXT_mdk,				//hsaD
	TEXT_waterflame,		//repmuJ
	
};


const unsigned char origartists2_size[] = {
	sizeof(TEXT_robtop) - 1,		//menu
	sizeof(TEXT_gdcolon) - 1,		//menu b sides
	sizeof(TEXT_foreverbound) - 1,	//stereo madness
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
	sizeof(TEXT_acidnotation) - 1, 		//accelerate
	sizeof(TEXT_dimrain47) - 1, 		//at the speed of light 1
	sizeof(TEXT_dimrain47) - 1, 		//at the speed of light 2
	sizeof(TEXT_dimrain47) - 1, 		//at the speed of light 3
	sizeof(TEXT_dimrain47) - 1, 		//at the speed of light full
	sizeof(TEXT_djvi) - 1,				//back on track full
	sizeof(TEXT_dexarson) - 1,			//beast mode GDW cut
	sizeof(TEXT_schtiffles) - 1,		//beep beep
	sizeof(TEXT_tobu) - 1,				//candyland
	sizeof(TEXT_djvi) - 1,				//can't electroman
	sizeof(TEXT_djvi) - 1,				//can't let go remixed
	sizeof(TEXT_paragonx9) - 1,			//chaoz airflow
	sizeof(TEXT_paragonx9) - 1,			//chaoz fantasy
	sizeof(TEXT_paragonx9) - 1,			//chaoz impact
	sizeof(TEXT_djnate) - 1,			//clubstep full
	sizeof(TEXT_waterflame) - 1,		//clutterfunk 2
	sizeof(TEXT_mdk) - 1,				//dash full
	sizeof(TEXT_soundholick) - 1,		//death moon
	sizeof(TEXT_reinn) - 1,				//driving by night
	sizeof(TEXT_djvi) - 1, 				//dry out full version
	sizeof(TEXT_jomekka) - 1, 			//eighto
	sizeof(TEXT_waterflame) - 1, 		//endgame
	sizeof(TEXT_mdk) - 1, 				//fingerbang
	sizeof(TEXT_creo) - 1, 				//flow
	sizeof(TEXT_xi) - 1, 				//freedom dive
	sizeof(TEXT_dominuus) - 1, 			//glint
	sizeof(TEXT_detious) - 1, 			//golden haze
	sizeof(TEXT_seaglowingpro) - 1,		//ground to krusty krab
	sizeof(TEXT_seaglowingpro) - 1,		//ground to space
	sizeof(TEXT_waterflame) - 1, 		//haunted woods
	sizeof(TEXT_virtual_riot) - 1,		//idols
	sizeof(TEXT_dimrain47) - 1, 		//infernoplex
	sizeof(TEXT_dimrain47) - 1, 		//infernoplex full
	sizeof(TEXT_nighthawk22) - 1,		//isolation
	sizeof(TEXT_bossfight) - 1,			//jack russel
	sizeof(TEXT_waterflame) - 1,		//jumper full version
	sizeof(TEXT_tessaviolet) - 1,		//just right
	sizeof(TEXT_tessaviolet) - 1,		//just right full
	sizeof(TEXT_rymdkraft) - 1,			//kesobomb
	sizeof(TEXT_shappy) - 1,			//kratos
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
	sizeof(TEXT_boomkitty) - 1,			//power trip
	sizeof(TEXT_nk) - 1,				//problematic
	sizeof(TEXT_nerdboy) - 1,			//pyrophoric
	sizeof(TEXT_kitsune) - 1,			//rainbow tylenol
	sizeof(TEXT_dexarson) - 1,			//round 1 (gdw cut)
	sizeof(TEXT_f777) - 1,				//sonic blaster
	sizeof(TEXT_waterflame) - 1,		//space pirates (gdw cut)
	sizeof(TEXT_kayoszx) - 1,			//stalemate
	sizeof(TEXT_kayoszx) - 1,			//stalemate full
	sizeof(TEXT_foreverbound) - 1,		//stereo madness2
	sizeof(TEXT_lemondemon) - 1,		//subtle oddities
	sizeof(TEXT_cacola) - 1,			//the angel
	sizeof(TEXT_f777) - 1,				//the seven seas
	sizeof(TEXT_craftyjumper) - 1,		//thoughts
	sizeof(TEXT_waterflame) - 1,		//time machine full
	sizeof(TEXT_tmm43) - 1,				//ultimate destruction
	sizeof(TEXT_theclydecash) - 1,		//you've been trolled
	sizeof(TEXT_lemkuuja) - 1,			//what's a future funk
	sizeof(TEXT_thefatrat) - 1,			//windfall
	sizeof(TEXT_aaron) - 1,				//xo
	sizeof(TEXT_dexarson) - 1,			//years GDW cut
	sizeof(TEXT_robtop) - 1,			//emeht unem
	sizeof(TEXT_foreverbound) - 1,		//ssendam oerets
	sizeof(TEXT_mdk) - 1,				//hsaD
	sizeof(TEXT_waterflame) - 1,		//repmuJ
};

const unsigned char* const origartists1[] = {
	0, 										//menu theme
	0, 										//menu theme 2.2
	0, 										//stereo madness
	0, 										//back on track
	0, 										//polargeist
	0, 										//dry out
	0,										//base after base
	0, 										//can't let go
	0, 										//jumper
	0, 										//time machine
	0, 										//cycles
	0, 										//xstep
	0, 										//clutterfunk
	0,										//theory of everything
	0, 										//electroman adventures
	0, 										//clubstep
	0, 										//electrodynamix
	0, 										//hexagon force
	0, 										//blast processing
	0, 										//theory of everything 2
	0, 										//geometrical dominator
	0, 										//deadlocked
	0, 										//fingerdash
	0, 										//dash
	0, 										//the challenge
	0, 										//practice
	0, 										//scheming weasel
	
	0, 										//8-bit against the odds redux
	0, 										//accelerate
	0, 										//at the speed of light 1
	0, 										//at the speed of light 2
	0, 										//at the speed of light 3
	0, 										//at the speed of light full
	0, 										//back on track full
	0, 										//beast mode GDW cut
	0, 										//beep beep
	0, 										//candyland
	0, 										//can't electroman
	0, 										//can't let go remixed
	0, 										//chaoz airflow
	0, 										//chaoz fantasy
	0, 										//chaoz impact
	0,										//clubstep full
	0, 										//clutterfunk 2
	0,										//dash full
	0, 										//death moon
	0, 										//driving by night
	0, 										//dry out full version
	0, 										//eighto
	0, 										//endgame
	0, 										//fingerbang
	0, 										//flow
	0, 										//freedom dive
	0, 										//glint
	0, 										//golden haze
	0, 										//ground to krusty krab
	0, 										//ground to space
	0, 										//haunted woods
	0, 										//idols
	0, 										//infernoplex
	0, 										//infernoplex full
	0, 										//isolation
	0, 										//jack russel
	0, 										//jumper full version
	TEXT_dan_harrison,						//just right
	TEXT_dan_harrison,						//just right full
	0, 										//kesobomb
	0, 										//kratos
	0, 										//lost
	0, 										//ludacris speed
	0, 										//machina GDW cut
	0, 										//magic touch
	0, 										//mayhem short ver
	0, 										//mayhem
	0, 										//metamorphasis
	0, 										//midnight
	0, 										//ninox
	0, 										//okiba crackdown
	0, 										//payload GDW cut
	0, 										//power trip
	0, 										//problematic
	0, 										//pyrophoric
	0, 										//rainbow tylenol
	0, 										//round 1 (gdw cut)
	0, 										//sonic blaster
	0, 										//space pirates (gdw cut)
	0, 										//stalemate
	0, 										//stalemate full
	0, 										//stereo madness2
	0, 										//subtle oddities
	0, 										//the angel
	0, 										//the seven seas
	0, 										//thoughts
	0,										//time machine full
	0, 										//ultimate destruction
	0, 										//you've been trolled
	0, 										//what's a future funk
	0, 										//windfall
	TEXT_musselwhite,						//xo
	0, 										//years GDW cut
	0,										//emeht unem	
	0,										//ssendam oerets
	0, 										//hsaD
	0, 										//repmuJ
};

const unsigned char origartists1_size[] = {
	0, 										//menu theme
	0, 										//menu theme 2.2
	0, 										//stereo madness
	0, 										//back on track
	0, 										//polargeist
	0, 										//dry out
	0,										//base after base
	0, 										//can't let go
	0, 										//jumper
	0, 										//time machine
	0, 										//cycles
	0, 										//xstep
	0, 										//clutterfunk
	0,										//theory of everything
	0, 										//electroman adventures
	0, 										//clubstep
	0, 										//electrodynamix
	0, 										//hexagon force
	0, 										//blast processing
	0, 										//theory of everything 2
	0, 										//geometrical dominator
	0, 										//deadlocked
	0, 										//fingerdash
	0, 										//dash
	0, 										//the challenge
	0, 										//practice
	0, 										//scheming weasel
	
	0, 										//8-bit against the odds redux
	0, 										//accelerate
	0, 										//at the speed of light 1
	0, 										//at the speed of light 2
	0, 										//at the speed of light 3
	0, 										//at the speed of light full
	0, 										//back on track full
	0, 										//beast mode GDW cut
	0, 										//beep beep
	0, 										//candyland
	0, 										//can't electroman
	0, 										//can't let go remixed
	0, 										//chaoz airflow
	0, 										//chaoz fantasy
	0, 										//chaoz impact
	0,										//clubstep full
	0, 										//clutterfunk 2
	0,										//dash full
	0, 										//death moon
	0, 										//driving by night
	0, 										//dry out full version
	0, 										//eighto
	0, 										//endgame
	0, 										//fingerbang
	0, 										//flow
	0, 										//freedom dive
	0, 										//glint
	0, 										//golden haze
	0, 										//ground to krusty krab
	0, 										//ground to space
	0, 										//haunted woods
	0, 										//idols
	0, 										//infernoplex
	0, 										//infernoplex full
	0, 										//isolation
	0, 										//jack russel
	0, 										//jumper full version
	sizeof(TEXT_dan_harrison) - 1,			//just right
	sizeof(TEXT_dan_harrison) - 1,			//just right full
	0, 										//kesobomb
	0, 										//kratos
	0, 										//lost
	0, 										//ludacris speed
	0, 										//machina GDW cut
	0, 										//magic touch
	0, 										//mayhem short ver
	0, 										//mayhem
	0, 										//metamorphasis
	0, 										//midnight
	0, 										//ninox
	0, 										//okiba crackdown
	0, 										//payload GDW cut
	0, 										//power trip
	0, 										//problematic
	0, 										//pyrophoric
	0, 										//rainbow tylenol
	0, 										//round 1 (gdw cut)
	0, 										//sonic blaster
	0, 										//space pirates (gdw cut)
	0, 										//stalemate
	0, 										//stalemate full
	0, 										//stereo madness2
	0, 										//subtle oddities
	0, 										//the angel
	0, 										//the seven seas
	0, 										//thoughts
	0,										//time machine full
	0, 										//ultimate destruction
	0, 										//you've been trolled
	0, 										//what's a future funk
	0, 										//windfall
	sizeof(TEXT_musselwhite) - 1,			//xo
	0, 										//years GDW cut
	0,										//emeht unem	
	0,										//ssendam oerets
	0, 										//hsaD
	0, 										//repmuJ
};

const unsigned char* const coveringartists1[] = {
	TEXT_zenith, 				//menu theme
	TEXT_usersniper, 			//menu theme 2.2
	TEXT_zenith,				//stereo madness
	TEXT_aquamarine,			//back on track
	TEXT_zenith,				//polargeist
	TEXT_usersniper,			//dry out
	TEXT_vikrinox,				//base after base
	TEXT_usersniper,			//can't let go
	TEXT_zenith,				//jumper
	TEXT_zenith,				//time machine
	TEXT_aquamarine,			//cycles
	TEXT_vikrinox,				//xstep
	TEXT_aquamarine,			//clutterfunk
	TEXT_vikrinox,				//theory of everything
	TEXT_cloud54,				//electroman adventures
	TEXT_cloud54,				//clubstep
	TEXT_aquamarine,			//electrodynamix
	TEXT_vikrinox,				//hexagon force
	TEXT_elangel,				//blast processing
	TEXT_vikrinox,				//theory of everything 2
	TEXT_cloud54,				//geometrical dominator
	TEXT_usersniper,			//deadlocked
	TEXT_elangel,				//fingerdash
	TEXT_craftyjumper,			//dash
	TEXT_elangel, 				//the challenge
	TEXT_usersniper, 			//practice
	TEXT_usersniper, 			//scheming weasel
	
	TEXT_elangel, 				//8-bit against the odds redux
	TEXT_elangel, 				//accelerate
	TEXT_elangel, 				//at the speed of light 1
	TEXT_elangel, 				//at the speed of light 2
	TEXT_elangel, 				//at the speed of light 3
	TEXT_elangel, 				//at the speed of light full
	TEXT_seaglowingpro,			//back on track full
	TEXT_elangel,				//beast mode GDW cut
	TEXT_clickerty,				//beep beep
	TEXT_nerdboy,				//candyland
	TEXT_craftyjumper,			//can't electroman
	TEXT_craftyjumper,			//can't let go remixed
	TEXT_seaglowingpro,			//chaoz airflow
	TEXT_usersniper,			//chaoz fantasy
	TEXT_elangel,				//chaoz impact
	TEXT_seaglowingpro,			//clubstep full
	TEXT_cloud54,				//clutterfunk 2
	TEXT_craftyjumper,			//dash full
	TEXT_elangel,				//death moon
	TEXT_nerdboy,				//driving by night
	TEXT_seaglowingpro,			//dry out full version
	TEXT_sussysy, 				//eighto
	TEXT_vikrinox, 				//endgame
	TEXT_craftyjumper, 			//fingerbang
	TEXT_seaglowingpro, 		//flow
	TEXT_seaglowingpro, 		//freedom dive
	TEXT_seaglowingpro, 		//glint
	TEXT_craftyjumper, 			//golden haze
	TEXT_seaglowingpro,			//ground to krusty krab
	TEXT_seaglowingpro,			//ground to space
	TEXT_sussysy, 				//haunted woods
	TEXT_seaglowingpro,			//idols
	TEXT_cloud54, 				//infernoplex
	TEXT_cloud54, 				//infernoplex full
	TEXT_craftyjumper,			//isolation
	TEXT_nerdboy,				//jack russel
	TEXT_seaglowingpro,			//jumper full version
	TEXT_seaglowingpro,			//just right
	TEXT_seaglowingpro,			//just right full
	TEXT_nerdboy,				//kesobomb
	TEXT_seaglowingpro, 		//kratos
	TEXT_seaglowingpro, 		//lost
	TEXT_elangel,				//ludacris speed
	TEXT_elangel,				//machina GDW cut
	TEXT_seaglowingpro,			//magic touch
	TEXT_craftyjumper,			//mayhem short ver
	TEXT_craftyjumper,			//mayhem
	TEXT_elangel,				//metamorphasis
	TEXT_seaglowingpro,			//midnight
	TEXT_seaglowingpro,			//ninox
	TEXT_sussysy,				//okiba crackdown
	TEXT_elangel,				//payload GDW cut
	TEXT_craftyjumper,			//power trip
	TEXT_elangel,				//problematic
	TEXT_nerdboy,				//pyrophoric
	TEXT_clickerty,				//rainbow tylenol
	TEXT_seaglowingpro,			//round 1 (gdw cut)
	TEXT_elangel,				//sonic blaster
	TEXT_elangel,				//space pirates (gdw cut)
	TEXT_elangel,				//stalemate
	TEXT_elangel,				//stalemate full
	TEXT_elangel,				//stereo madness2
	TEXT_dwedit,				//subtle oddities
	TEXT_elangel,				//the angel
	TEXT_craftyjumper,			//the seven seas
	TEXT_craftyjumper,			//thoughts
	TEXT_seaglowingpro,			//time machine full
	TEXT_usersniper,			//ultimate destruction
	TEXT_seaglowingpro,			//you've been trolled
	TEXT_seaglowingpro,			//what's a future funk
	TEXT_seaglowingpro,			//windfall
	TEXT_seaglowingpro,			//xo
	TEXT_elangel,				//years GDW cut
	TEXT_craftyjumper,			//emeht unem
	TEXT_craftyjumper,			//ssendam oerets
	TEXT_craftyjumper,			//hsaD
	TEXT_seaglowingpro,			//repmuJ
};


const unsigned char coveringartists1_size[] = {
	sizeof(TEXT_zenith) - 1, 				//menu theme
	sizeof(TEXT_usersniper) - 1, 			//menu theme 2.2
	sizeof(TEXT_zenith) - 1,				//stereo madness
	sizeof(TEXT_aquamarine) - 1,			//back on track
	sizeof(TEXT_zenith) - 1,				//polargeist
	sizeof(TEXT_usersniper) - 1,			//dry out
	sizeof(TEXT_vikrinox) - 1,				//base after base
	sizeof(TEXT_usersniper) - 1,			//can't let go
	sizeof(TEXT_zenith) - 1,				//jumper
	sizeof(TEXT_zenith) - 1,				//time machine
	sizeof(TEXT_aquamarine) - 1,			//cycles
	sizeof(TEXT_vikrinox) - 1,				//xstep
	sizeof(TEXT_aquamarine) - 1,			//clutterfunk
	sizeof(TEXT_vikrinox) - 1,				//theory of everything
	sizeof(TEXT_cloud54) - 1,				//electroman adventures
	sizeof(TEXT_cloud54) - 1,				//clubstep
	sizeof(TEXT_aquamarine) - 1,			//electrodynamix
	sizeof(TEXT_vikrinox) - 1,				//hexagon force
	sizeof(TEXT_elangel) - 1,				//blast processing
	sizeof(TEXT_vikrinox) - 1,				//theory of everything 2
	sizeof(TEXT_cloud54) - 1,				//geometrical dominator
	sizeof(TEXT_usersniper) - 1,			//deadlocked
	sizeof(TEXT_elangel) - 1,				//fingerdash
	sizeof(TEXT_craftyjumper) - 1,			//dash
	sizeof(TEXT_elangel) - 1, 				//the challenge
	sizeof(TEXT_usersniper) - 1, 			//practice
	sizeof(TEXT_usersniper) - 1, 			//scheming weasel
	
	sizeof(TEXT_elangel) - 1, 				//8-bit against the odds redux
	sizeof(TEXT_elangel) - 1, 				//accelerate
	sizeof(TEXT_elangel) - 1, 				//at the speed of light 1
	sizeof(TEXT_elangel) - 1, 				//at the speed of light 2
	sizeof(TEXT_elangel) - 1, 				//at the speed of light 3
	sizeof(TEXT_elangel) - 1, 				//at the speed of light full
	sizeof(TEXT_seaglowingpro) - 1,			//back on track full
	sizeof(TEXT_elangel) - 1,				//beast mode GDW cut
	sizeof(TEXT_clickerty) - 1,				//beep beep
	sizeof(TEXT_nerdboy) - 1,				//candyland
	sizeof(TEXT_craftyjumper) - 1,			//can't electroman
	sizeof(TEXT_craftyjumper) - 1,			//can't let go remixed
	sizeof(TEXT_seaglowingpro) - 1,			//chaoz airflow
	sizeof(TEXT_usersniper) - 1,			//chaoz fantasy
	sizeof(TEXT_elangel) - 1,				//chaoz impact
	sizeof(TEXT_seaglowingpro) - 1,			//clubstep full
	sizeof(TEXT_cloud54) - 1,				//clutterfunk 2
	sizeof(TEXT_craftyjumper) - 1,			//dash full
	sizeof(TEXT_elangel) - 1,				//death moon
	sizeof(TEXT_nerdboy) - 1,				//driving by night
	sizeof(TEXT_seaglowingpro) - 1, 		//dry out full
	sizeof(TEXT_sussysy) - 1, 				//eighto
	sizeof(TEXT_vikrinox) - 1, 				//endgame
	sizeof(TEXT_craftyjumper) - 1, 			//fingerbang
	sizeof(TEXT_seaglowingpro) - 1, 		//flow
	sizeof(TEXT_seaglowingpro) - 1, 		//freedom dive
	sizeof(TEXT_seaglowingpro) - 1, 		//glint
	sizeof(TEXT_craftyjumper) - 1, 			//golden haze
	sizeof(TEXT_seaglowingpro) - 1,			//ground to krusty krab
	sizeof(TEXT_seaglowingpro) - 1,			//ground to space
	sizeof(TEXT_sussysy) - 1, 				//haunted woods
	sizeof(TEXT_seaglowingpro) - 1,			//idols
	sizeof(TEXT_cloud54) - 1, 				//infernoplex
	sizeof(TEXT_cloud54) - 1, 				//infernoplex full
	sizeof(TEXT_craftyjumper) - 1,			//isolation
	sizeof(TEXT_nerdboy) - 1,				//jack russel
	sizeof(TEXT_seaglowingpro) - 1,			//jumper full version
	sizeof(TEXT_seaglowingpro) - 1,			//just right
	sizeof(TEXT_seaglowingpro) - 1,			//just right full
	sizeof(TEXT_nerdboy) - 1,				//kesobomb
	sizeof(TEXT_seaglowingpro) - 1, 		//kratos
	sizeof(TEXT_seaglowingpro) - 1, 		//lost
	sizeof(TEXT_elangel) - 1,				//ludacris speed
	sizeof(TEXT_elangel) - 1,				//machina GDW cut
	sizeof(TEXT_seaglowingpro) - 1,			//magic touch
	sizeof(TEXT_craftyjumper) - 1,			//mayhem short ver
	sizeof(TEXT_craftyjumper) - 1,			//mayhem
	sizeof(TEXT_elangel) - 1,				//metamorphasis
	sizeof(TEXT_seaglowingpro) - 1,			//midnight
	sizeof(TEXT_seaglowingpro) - 1,			//ninox
	sizeof(TEXT_sussysy) - 1,				//okiba crackdown
	sizeof(TEXT_elangel) - 1,				//payload GDW cut
	sizeof(TEXT_craftyjumper) - 1,			//power trip
	sizeof(TEXT_elangel) - 1,				//problematic
	sizeof(TEXT_nerdboy) - 1,				//pyrophoric
	sizeof(TEXT_clickerty) - 1,				//rainbow tylenol
	sizeof(TEXT_seaglowingpro) - 1,			//round 1 (gdw cut)
	sizeof(TEXT_elangel) - 1,				//sonic blaster
	sizeof(TEXT_elangel) - 1,				//space pirates (gdw cut)
	sizeof(TEXT_elangel) - 1,				//stalemate
	sizeof(TEXT_elangel) - 1,				//stalemate full
	sizeof(TEXT_elangel) - 1,				//stereo madness2
	sizeof(TEXT_dwedit) - 1,				//subtle oddities
	sizeof(TEXT_elangel) - 1,				//the angel
	sizeof(TEXT_craftyjumper) - 1,			//the seven seas
	sizeof(TEXT_craftyjumper) - 1,			//thoughts
	sizeof(TEXT_seaglowingpro) - 1,			//time machine full
	sizeof(TEXT_usersniper) - 1,			//ultimate destruction
	sizeof(TEXT_seaglowingpro) - 1,			//you've been trolled
	sizeof(TEXT_seaglowingpro) - 1,			//what's a future funk
	sizeof(TEXT_seaglowingpro) - 1,			//windfall
	sizeof(TEXT_seaglowingpro) - 1,			//xo
	sizeof(TEXT_elangel) - 1,				//years GDW cut
	sizeof(TEXT_craftyjumper) - 1,			//emeht unem
	sizeof(TEXT_craftyjumper) - 1,			//ssendam oerets
	sizeof(TEXT_craftyjumper) - 1,			//hsaD
	sizeof(TEXT_seaglowingpro) - 1,			//repmuJ
};


const unsigned char* const coveringartists2[] = {
	0, 										//menu theme
	0, 										//menu theme 2.2
	TEXT_usersniper,						//stereo madness
	0,										//back on track
	TEXT_usersniper,						//polargeist
	0,										//dry out
	TEXT_usersniper,						//base after base
	TEXT_alexmush,							//can't let go
	TEXT_zukinnyk,							//jumper
	TEXT_vikrinox,							//time machine
	TEXT_alexmush,							//cycles
	TEXT_alexmush,							//xstep
	TEXT_vikrinox,							//clutterfunk
	TEXT_usersniper,						//theory of everything
	TEXT_usersniper,						//electroman adventures
	0,										//clubstep
	0,										//electrodynamix
	TEXT_alexmush,							//hexagon force
	0,										//blast processing
	0,										//theory of everything 2
	TEXT_vikrinox,							//geometrical dominator
	TEXT_vikrinox,							//deadlocked
	0,										//fingerdash
	0,										//dash
	0, 										//the challenge
	0, 										//practice
	0, 										//scheming weasel
	
	0, 										//8-bit against the odds redux
	0, 										//accelerate
	0, 										//at the speed of light 1
	0, 										//at the speed of light 2
	0, 										//at the speed of light 3
	0, 										//at the speed of light full
	TEXT_aquamarine,						//back on track full
	0,										//beast mode GDW cut
	0,										//beep beep
	0,										//candyland
	0,										//can't electroman
	0,										//can't let go remixed
	0,										//chaoz airflow
	TEXT_seaglowingpro,						//chaoz fantasy
	0,										//chaoz impact
	TEXT_cloud54,							//clubstep full
	0,										//clutterfunk 2
	0,										//dash full
	0,										//death moon
	0,										//driving by night
	TEXT_usersniper, 						//dry out full version
	0, 										//eighto
	0, 										//endgame
	TEXT_elangel, 							//fingerbang
	0, 										//flow
	0, 										//freedom dive
	0, 										//glint
	TEXT_elangel, 							//golden haze
	0, 										//ground to krusty krab
	0,										//ground to space
	0, 										//haunted woods
	0,										//idols
	0, 										//infernoplex
	TEXT_seaglowingpro, 					//infernoplex full
	TEXT_seaglowingpro, 					//isolation
	0, 										//jack russel
	TEXT_zenith,							//jumper full version
	TEXT_elangel,							//just right
	TEXT_elangel,							//just right full
	0, 										//kesobomb
	0, 										//kratos
	0, 										//lost
	0, 										//ludacris speed
	0, 										//machina GDW cut
	0, 										//magic touch
	0, 										//mayhem short ver
	0, 										//mayhem
	0, 										//metamorphasis
	0, 										//midnight
	0, 										//ninox
	0, 										//okiba crackdown
	0, 										//payload GDW cut
	0, 										//power trip
	0, 										//problematic
	0, 										//pyrophoric
	0, 										//rainbow tylenol
	0, 										//round 1 (gdw cut)
	0, 										//sonic blaster
	0, 										//space pirates
	0, 										//stalemate
	TEXT_seaglowingpro,						//stalemate full
	0, 										//stereo madness2
	0, 										//subtle oddities
	0, 										//the angel
	0, 										//the seven seas
	0, 										//thoughts
	TEXT_zenith,							//time machine full
	0, 										//ultimate destruction
	0, 										//you've been trolled
	0, 										//what's a future funk
	0, 										//windfall
	0, 										//xo
	0, 										//years GDW cut
	0,										//emeht unem	
	0,										//ssendam oerets
	0, 										//hsaD
	0, 										//repmuJ
};


const unsigned char coveringartists2_size[] = {
	0, 										//menu theme
	0, 										//menu theme 2.2
	sizeof(TEXT_usersniper) - 1,			//stereo madness
	0, 										//back on track
	sizeof(TEXT_usersniper) - 1,			//polargeist
	0, 										//dry out
	sizeof(TEXT_usersniper) - 1,			//base after base
	sizeof(TEXT_alexmush) - 1,				//can't let go
	sizeof(TEXT_zukinnyk) - 1,				//jumper
	sizeof(TEXT_vikrinox) - 1,				//time machine
	sizeof(TEXT_alexmush) - 1,				//cycles
	sizeof(TEXT_alexmush) - 1,				//xstep
	sizeof(TEXT_vikrinox) - 1,				//clutterfunk
	sizeof(TEXT_usersniper) - 1,			//theory of everything
	sizeof(TEXT_usersniper) - 1,			//electroman adventures
	0, 										//clubstep
	0, 										//electrodynamix
	sizeof(TEXT_alexmush) - 1,				//hexagon force
	0, 										//blast processing
	0, 										//theory of everything 2
	sizeof(TEXT_vikrinox) - 1, 				//geometrical dominator
	sizeof(TEXT_vikrinox) - 1, 				//deadlocked
	0, 										//fingerdash
	0, 										//dash
	0, 										//the challenge
	0, 										//practice
	0, 										//scheming weasel
	
	0, 										//8-bit against the odds redux
	0, 										//accelerate
	0, 										//at the speed of light 1
	0, 										//at the speed of light 2
	0, 										//at the speed of light 3
	0, 										//at the speed of light full
	sizeof(TEXT_aquamarine) - 1,			//back on track full
	0, 										//beast mode GDW cut
	0, 										//beep beep
	0, 										//candyland
	0, 										//can't electroman
	0, 										//can't let go remixed
	0, 										//chaoz airflow
	sizeof(TEXT_seaglowingpro) - 1, 		//chaoz fantasy
	0, 										//chaoz impact
	sizeof(TEXT_cloud54) - 1,				//clubstep full
	0, 										//clutterfunk 2
	0,										//dash full
	0, 										//death moon
	0, 										//driving by night
	sizeof(TEXT_usersniper) - 1, 			//dry out full version
	0, 										//eighto
	0, 										//endgame
	sizeof(TEXT_elangel) - 1,				//fingerbang
	0, 										//flow
	0, 										//freedom dive
	0, 										//glint
	sizeof(TEXT_elangel) - 1, 				//golden haze
	0, 										//ground to krusty krab
	0, 										//ground to space
	0, 										//haunted woods
	0, 										//idols
	0, 										//infernoplex
	sizeof(TEXT_seaglowingpro) - 1, 		//infernoplex full
	sizeof(TEXT_seaglowingpro) - 1,			//isolation
	0,										//jack russel
	sizeof(TEXT_zenith) - 1,				//jumper full version
	sizeof(TEXT_elangel) - 1,				//just right
	sizeof(TEXT_elangel) - 1,				//just right full
	0, 										//kesobomb
	0, 										//kratos
	0, 										//lost
	0, 										//ludacris speed
	0, 										//machina GDW cut
	0, 										//magic touch
	0, 										//mayhem short ver
	0, 										//mayhem
	0, 										//metamorphasis
	0, 										//midnight
	0, 										//ninox
	0, 										//okiba crackdown
	0, 										//payload GDW cut
	0, 										//power trip
	0, 										//problematic
	0, 										//pyrophoric
	0, 										//rainbow tylenol
	0, 										//round 1 (gdw cut)
	0, 										//sonic blaster
	0, 										//space pirates
	0, 										//stalemate
	sizeof(TEXT_seaglowingpro) - 1,			//stalemate full
	0, 										//stereo madness2
	0, 										//subtle oddities
	0, 										//the angel
	0, 										//the seven seas
	0, 										//thoughts
	sizeof(TEXT_zenith) - 1, 				//time machine full
	0, 										//ultimate destruction
	0, 										//you've been trolled
	0, 										//what's a future funk
	0, 										//windfall
	0, 										//xo
	0, 										//years GDW cut
	0,										//emeht unem	
	0,										//ssendam oerets
	0, 										//hsaD
	0, 										//repmuJ
};

const unsigned char* const coveringartists3[] = {
	0, 										//menu theme
	0, 										//menu theme 2.2
	0, 										//stereo madness
	0, 										//back on track
	TEXT_vikrinox,							//polargeist
	0, 										//dry out
	TEXT_zenith,							//base after base
	0, 										//can't let go
	TEXT_usersniper,						//jumper
	TEXT_alexmush, 							//time machine
	0, 										//cycles
	0, 										//xstep
	TEXT_zenith,							//clutterfunk
	TEXT_zenith,							//theory of everything
	TEXT_alexmush,							//electroman adventures
	0, 										//clubstep
	0, 										//electrodynamix
	0, 										//hexagon force
	0, 										//blast processing
	0, 										//theory of everything 2
	0, 										//geometrical dominator
	0, 										//deadlocked
	0, 										//fingerdash
	0, 										//dash
	0, 										//the challenge
	0, 										//practice
	0, 										//scheming weasel
	
	0, 										//8-bit against the odds redux
	0, 										//accelerate
	0, 										//at the speed of light 1
	0, 										//at the speed of light 2
	0, 										//at the speed of light 3
	0, 										//at the speed of light full
	0, 										//back on track full
	0, 										//beast mode GDW cut
	0, 										//beep beep
	0, 										//candyland
	0, 										//can't electroman
	0, 										//can't let go remixed
	0, 										//chaoz airflow
	0, 										//chaoz fantasy
	0, 										//chaoz impact
	0,										//clubstep full
	0, 										//clutterfunk 2
	0,										//dash full
	0, 										//death moon
	0, 										//driving by night
	0, 										//dry out full version
	0, 										//eighto
	0, 										//endgame
	0, 										//fingerbang
	0, 										//flow
	0, 										//freedom dive
	0, 										//glint
	0, 										//golden haze
	0, 										//ground to krusty krab
	0, 										//ground to space
	0, 										//haunted woods
	0, 										//idols
	0, 										//infernoplex
	0, 										//infernoplex full
	0, 										//isolation
	0, 										//jack russel
	TEXT_zukinnyk, 							//jumper full version
	0, 										//just right
	0, 										//just right full
	0, 										//kesobomb
	0, 										//kratos
	0, 										//lost
	0, 										//ludacris speed
	0, 										//machina GDW cut
	0, 										//magic touch
	0, 										//mayhem short ver
	0, 										//mayhem
	0, 										//metamorphasis
	0, 										//midnight
	0, 										//ninox
	0, 										//okiba crackdown
	0, 										//payload GDW cut
	0, 										//power trip
	0, 										//problematic
	0, 										//pyrophoric
	0, 										//rainbow tylenol
	0, 										//round 1 (gdw cut)
	0, 										//sonic blaster
	0, 										//space pirates
	0, 										//stalemate
	0, 										//stalemate full
	0, 										//stereo madness2
	0, 										//subtle oddities
	0, 										//the angel
	0, 										//the seven seas
	0, 										//thoughts
	TEXT_vikrinox, 							//time machine full
	0, 										//ultimate destruction
	0, 										//you've been trolled
	0, 										//what's a future funk
	0, 										//windfall
	0, 										//xo
	0, 										//years GDW cut
	0,										//emeht unem	
	0,										//ssendam oerets
	0, 										//hsaD
	0, 										//repmuJ
};


const unsigned char coveringartists3_size[] = {
	0, 										//menu theme
	0, 										//menu theme 2.2
	0, 										//stereo madness
	0, 										//back on track
	sizeof(TEXT_vikrinox) - 1,				//polargeist
	0,										//dry out
	sizeof(TEXT_zenith) - 1,				//base after base
	0,										//can't let go
	sizeof(TEXT_usersniper) - 1,			//jumper
	sizeof(TEXT_alexmush) - 1,				//time machine
	0, 										//cycles
	0, 										//xstep
	sizeof(TEXT_zenith) - 1,				//clutterfunk
	sizeof(TEXT_zenith) - 1,				//theory of everything
	sizeof(TEXT_alexmush) - 1,				//electroman adventures
	0, 										//clubstep
	0, 										//electrodynamix
	0, 										//hexagon force
	0, 										//blast processing
	0, 										//theory of everything 2
	0, 										//geometrical dominator
	0, 										//deadlocked
	0, 										//fingerdash
	0, 										//dash
	0, 										//the challenge
	0, 										//practice
	0, 										//scheming weasel
	
	0, 										//8-bit against the odds redux
	0, 										//accelerate
	0, 										//at the speed of light 1
	0, 										//at the speed of light 2
	0, 										//at the speed of light 3
	0, 										//at the speed of light full
	0, 										//back on track full
	0, 										//beast mode GDW cut
	0, 										//beep beep
	0, 										//candyland
	0, 										//can't electroman
	0, 										//can't let go remixed
	0, 										//chaoz airflow
	0, 										//chaoz fantasy
	0, 										//chaoz impact
	0,										//clubstep full
	0, 										//clutterfunk 2
	0,										//dash full
	0, 										//death moon
	0, 										//driving by night
	0, 										//dry out full version
	0, 										//eighto
	0, 										//endgame
	0, 										//fingerbang
	0, 										//flow
	0, 										//freedom dive
	0, 										//glint
	0, 										//golden haze
	0, 										//ground to krusty krab
	0, 										//ground to space
	0, 										//haunted woods
	0, 										//idols
	0, 										//infernoplex
	0, 										//infernoplex full
	0, 										//isolation
	0, 										//jack russel
	sizeof(TEXT_zukinnyk) - 1,				//jumper full version
	0, 										//just right
	0, 										//just right full
	0, 										//kesobomb
	0, 										//kratos
	0, 										//lost
	0, 										//ludacris speed
	0, 										//machina GDW cut
	0, 										//magic touch
	0, 										//mayhem short ver
	0, 										//mayhem
	0, 										//metamorphasis
	0, 										//midnight
	0, 										//ninox
	0, 										//okiba crackdown
	0, 										//payload GDW cut
	0, 										//power trip
	0, 										//problematic
	0, 										//pyrophoric
	0, 										//rainbow tylenol
	0, 										//round 1 (gdw cut)
	0, 										//sonic blaster
	0, 										//space pirates
	0, 										//stalemate
	0, 										//stalemate full
	0, 										//stereo madness2
	0, 										//subtle oddities
	0, 										//the angel
	0, 										//the seven seas
	0, 										//thoughts
	sizeof(TEXT_vikrinox) - 1,				//time machine full
	0, 										//ultimate destruction
	0, 										//you've been trolled
	0, 										//what's a future funk
	0, 										//windfall
	0, 										//xo
	0, 										//years GDW cut
	0,										//emeht unem	
	0,										//ssendam oerets
	0, 										//hsaD
	0, 										//repmuJ
};

const unsigned char* const coveringartists4[] = {
	0, 										//menu theme
	0, 										//menu theme 2.2
	0, 										//stereo madness
	0, 										//back on track
	0, 										//polargeist
	0, 										//dry out
	TEXT_alexmush,							//base after base
	0, 										//can't let go
	0, 										//jumper
	0, 										//time machine
	0, 										//cycles
	0, 										//xstep
	0, 										//clutterfunk
	TEXT_leejh20,							//theory of everything
	TEXT_craftyjumper, 						//electroman adventures
	0, 										//clubstep
	0, 										//electrodynamix
	0, 										//hexagon force
	0, 										//blast processing
	0, 										//theory of everything 2
	0, 										//geometrical dominator
	0, 										//deadlocked
	0, 										//fingerdash
	0, 										//dash
	0, 										//the challenge
	0, 										//practice
	0, 										//scheming weasel
	
	0, 										//8-bit against the odds redux
	0, 										//accelerate
	0, 										//at the speed of light 1
	0, 										//at the speed of light 2
	0, 										//at the speed of light 3
	0, 										//at the speed of light full
	0, 										//back on track full
	0, 										//beast mode GDW cut
	0, 										//beep beep
	0, 										//candyland
	0, 										//can't electroman
	0, 										//can't let go remixed
	0, 										//chaoz airflow
	0, 										//chaoz fantasy
	0, 										//chaoz impact
	0,										//clubstep full
	0, 										//clutterfunk 2
	0,										//dash full
	0, 										//death moon
	0, 										//driving by night
	0, 										//dry out full version
	0, 										//eighto
	0, 										//endgame
	0, 										//fingerbang
	0, 										//flow
	0, 										//freedom dive
	0, 										//glint
	0, 										//golden haze
	0, 										//ground to krusty krab
	0, 										//ground to space
	0, 										//haunted woods
	0, 										//idols
	0, 										//infernoplex
	0, 										//infernoplex full
	0, 										//isolation
	0, 										//jack russel
	TEXT_usersniper, 						//jumper full version
	0,										//just right
	0,										//just right full
	0, 										//kesobomb
	0, 										//kratos
	0, 										//lost
	0, 										//ludacris speed
	0, 										//machina GDW cut
	0, 										//magic touch
	0, 										//mayhem short ver
	0, 										//mayhem
	0, 										//metamorphasis
	0, 										//midnight
	0, 										//ninox
	0, 										//okiba crackdown
	0, 										//payload GDW cut
	0, 										//power trip
	0, 										//problematic
	0, 										//pyrophoric
	0, 										//rainbow tylenol
	0, 										//round 1 (gdw cut)
	0, 										//sonic blaster
	0, 										//space pirates
	0, 										//stalemate
	0, 										//stalemate full
	0, 										//stereo madness2
	0, 										//subtle oddities
	0, 										//the angel
	0, 										//the seven seas
	0, 										//thoughts
	TEXT_alexmush,							//time machine full
	0, 										//ultimate destruction
	0, 										//you've been trolled
	0, 										//what's a future funk
	0, 										//windfall
	0, 										//xo
	0, 										//years GDW cut
	0,										//emeht unem	
	0,										//ssendam oerets
	0, 										//hsaD
	0, 										//repmuJ
};


const unsigned char coveringartists4_size[] = {
	0, 										//menu theme
	0, 										//menu theme 2.2
	0, 										//stereo madness
	0, 										//back on track
	0, 										//polargeist
	0, 										//dry out
	sizeof(TEXT_alexmush) - 1,				//base after base
	0, 										//can't let go
	0, 										//jumper
	0, 										//time machine
	0, 										//cycles
	0, 										//xstep
	0, 										//clutterfunk
	sizeof(TEXT_leejh20) - 1,				//theory of everything
	sizeof(TEXT_craftyjumper) - 1, 			//electroman adventures
	0, 										//clubstep
	0, 										//electrodynamix
	0, 										//hexagon force
	0, 										//blast processing
	0, 										//theory of everything 2
	0, 										//geometrical dominator
	0, 										//deadlocked
	0, 										//fingerdash
	0, 										//dash
	0, 										//the challenge
	0, 										//practice
	0, 										//scheming weasel
	
	0, 										//8-bit against the odds redux
	0, 										//accelerate
	0, 										//at the speed of light 1
	0, 										//at the speed of light 2
	0, 										//at the speed of light 3
	0, 										//at the speed of light full
	0, 										//back on track full
	0, 										//beast mode GDW cut
	0, 										//beep beep
	0, 										//candyland
	0, 										//can't electroman
	0, 										//can't let go remixed
	0, 										//chaoz airflow
	0, 										//chaoz fantasy
	0, 										//chaoz impact
	0,										//clubstep full
	0, 										//clutterfunk 2
	0,										//dash full
	0, 										//death moon
	0, 										//driving by night
	0, 										//dry out full version
	0, 										//eighto
	0, 										//endgame
	0, 										//fingerbang
	0, 										//flow
	0, 										//freedom dive
	0, 										//glint
	0, 										//golden haze
	0, 										//ground to krusty krab
	0, 										//ground to space
	0, 										//haunted woods
	0, 										//idols
	0, 										//infernoplex
	0, 										//infernoplex full
	0, 										//isolation
	0, 										//jack russel
	sizeof(TEXT_usersniper) - 1,			//jumper full version
	0,										//just right
	0,										//just right full
	0, 										//kesobomb
	0, 										//kratos
	0, 										//lost
	0, 										//ludacris speed
	0, 										//machina GDW cut
	0, 										//magic touch
	0, 										//mayhem short ver
	0, 										//mayhem
	0, 										//metamorphasis
	0, 										//midnight
	0, 										//ninox
	0, 										//okiba crackdown
	0, 										//payload GDW cut
	0, 										//power trip
	0, 										//problematic
	0, 										//pyrophoric
	0, 										//rainbow tylenol
	0, 										//round 1 (gdw cut)
	0, 										//sonic blaster
	0, 										//space pirates
	0, 										//stalemate
	0, 										//stalemate full
	0, 										//stereo madness2
	0, 										//subtle oddities
	0, 										//the angel
	0, 										//the seven seas
	0, 										//thoughts
	sizeof(TEXT_alexmush) - 1,				//time machine full
	0, 										//ultimate destruction
	0, 										//you've been trolled
	0, 										//what's a future funk
	0, 										//windfall
	0, 										//xo
	0, 										//years GDW cut
	0,										//emeht unem	
	0,										//ssendam oerets
	0, 										//hsaD
	0, 										//repmuJ
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
	song_hell,
	song_atthespeedoflight,
	song_atthespeedoflight2,
	song_atthespeedoflight3,
	song_atthespeedoflightfull,
	song_back_on_track_full,
	song_beast_mode_gdw_cut,
	song_beep_beep,
	song_candyland,
	song_cant_electroman,
	song_cant_let_go_remix,
	song_chaoz_airflow,
	song_chaozfantasy,
	song_chaoz_impact,
	song_clubstep_full,
	song_clutterfunk_2,
	song_dash_full,
	song_death_moon,
	song_driving_by_night,
	song_dry_out_full,
	song_eighto,
	song_endgame,
	song_fingerbang,
	song_flow,
	song_freedom_dive,
	song_glint,
	song_retray,
	song_ground_to_krusty_krab,
	song_ground_to_space,
	song_haunted_woods,
	song_idols,
	song_infernoplex,
	song_infernoplex_full,
	song_isolation,
	song_jack_russel,
	song_jumper_full,
	song_just_right,
	song_just_right_full,
	song_kesobomb,
	song_kratos,
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
	song_power_trip,
	song_problematic,
	song_pyrophoric,
	song_rainbow_tylenol,
	song_round_1_gdw_cut,
	song_sonic_blaster,
	song_space_pirates_gdw_cut,
	song_stalemate,
	song_stalemate_full,
	song_stereo_madness_2,
	song_subtle_oddities,
	song_eon,
	song_the_seven_seas,
	song_thoughts,
	song_time_machine_full,
	song_ultimatedestruction,
	song_youve_been_trolled,
	song_whats_a_future_funk,
	song_windfall,
	song_xo,
	song_years_gdw_cut,
	song_emeht_unem,
	song_ssendam_oerets,
	song_hsad,
	song_repmuj,
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
		if (tmp5) {
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
			tmp5 = 0;
		}
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
		if (!tmp4 || tmp4 == 0xFF) {
//					ppu_off();
//					crossPRGBankJump0(unrle_bgm2);
					update_text2();
//					ppu_on_all();
					tmp4 = 2;
		}
		else if (tmp4 == 1) {
					update_text3();
					tmp4 = 3;
		}			
		else if (tmp4 == 2) {
			for (tmp1 = 2; tmp1 < 4; tmp1++) {			//limited to 5??
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));		
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
			else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			tmp4 = 1;
			}
		}
		else if (tmp4 == 3) {
			for (tmp1 = 4; tmp1 < 6; tmp1++) {			//limited to 5??
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			if (music_queue[tmp1] != 0xFF) {
				text_stuff();			
			}
			else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			tmp4 = 4;
			}
		}
		else if (tmp4 == 4) {
			for (tmp1 = 6; tmp1 < 8; tmp1++) {			//limited to 5??
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			if (music_queue[tmp1] != 0xFF) {
				text_stuff();			
			}
			else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			tmp4 = 5;
			}
		}
		else if (tmp4 == 5) {
			for (tmp1 = 8; tmp1 < 10; tmp1++) {			//limited to 5??
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			if (music_queue[tmp1] != 0xFF) {
				text_stuff();			
			}
			else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
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
	
	__A__ = idx16_load_hi_NOC(origartists1, song);
	if (__A__) draw_padded_text(origartists1[song & 0x7F], origartists1_size[song], 14, NTADR_A(9, 14));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 14));
	__A__ = idx16_load_hi_NOC(origartists2, song);
	if (__A__) draw_padded_text(origartists2[song & 0x7F], origartists2_size[song], 14, NTADR_A(9, 13));
	else one_vram_buffer_horz_repeat('$', 15, NTADR_A(9, 13));

	tmp5 = 1;
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
	for (tmp1 = 0; tmp1 < 2; tmp1++) {			//limited to 5??
		if (music_queue[tmp1] != 0xFF) {
			one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
			text_stuff();
		}
		else one_vram_buffer_horz_repeat('$', 27, NTADR_A(3, (13 + (tmp1))));	
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
				
			//refresh_queue_screen();
			tmp4 = 0xFF;
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


void text_stuff() {
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

CODE_BANK_POP()

