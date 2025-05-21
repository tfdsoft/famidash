#pragma rodata-name (push, "XCD_BANK_02")

#include "menus/h/DialogBox.h"
#include "defines/charmap/dialogbox_charmap.h"

void draw_dialog_box(const char * data);
#define include_nested_dialog_string(data) (__AX__ = (uintptr_t)data, __asm__("jsr pushax "))

// Horz size: 22

/*
    Character table:
    
    BrC*| BlC*| What is
    ' ' |  $  | Space
    0-9 | --- | Numbers
    a-z | A-Z | ASCII
     /  |  \\ | Forward slash
     %  |  &  | Percentage sign
     :  |  ;  | Colon
    --- | ( ) | Black BG rounding characters
    --- |  *  | Star

    *BrC = Brown BG Character, BlC = Black BG character

    Escape characters:
    \a  - Include a substring (its address has to have been pushed to the C stack)
    \b  - Replaces the entire line with Black BG characters, rewinds to the beginning
    \n  - Jumps to the beginning of the next line
    \t  - Skip the next few characters, the byte right after this indicates the amount
    \v  - Skip the next few lines and jump to the beginning, the byte right after this indicates the amount
    \0 (automatically done by cc65) - End of string

    How to include arguments:
    \a  - use include_nested_dialog_string(the ptr to the data). Since this is a stack, you need to include the stirngs in a reverse order
    \t and \v - include the argument byte right after the control code itself. You can either do this in hex ("\0x10" or "\x10") or in octal ("\020" or "\20")
*/ 

const char dialogBox_saveFileSafetyHeader[] = "$$SAVE$$FILE$$SAFETY$$\v\2";
const char dialogBox_pleasePressB[] = "\a please hold  (RESET)\v\2  while powering off\v\2\t\3real nes/famicom \v\2  hardware  to avoid\v\2 save file corruption\v\2\b  [\t\20]  \n  $PRESS$ANY$BUTTON$\n  $$$TO$$CONTINUE$$$\n\b  {\t\20}  ";
const char dialogBox_itIsNowSafe[] = "\a\n  it is now safe to\v\2 turn off your system\v\6\b  [\t\20]  \n  $$$$PRESS$B$TO$$$$\n  $$$$GO$BACK$TO$$$$\n  $THE$TITLE$SCREEN$\n\b  {\t\20}  ";

const char dialogBox_wrongSaveFileVersion[] = " for a\a version";
const char dialogBox_nolder[] = "n older";
const char dialogBox_newer[] = " newer ";
const char dialogBox_saveFileMissingCorrupt[] = "  missing or corrupt";
const char dialogBox_saveIssues[] = "$$INVALID$$SAVE$FILE$$\v\5  your save  file is\v\2\a\v\6 (A;$CREATE$NEW$SAVE)\v\2 (B;$LOAD$ANYWAY$$$$)";

#include "defines/charmap/no_remap_charmap.h"
#pragma rodata-name (pop)