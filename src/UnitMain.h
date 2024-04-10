//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *MOpen;
	TMenuItem *MReload;
	TMenuItem *MSaveReport;
	TImage *ImagePRG;
	TOpenDialog *OpenDialogNES;
	TImage *ImageCHR;
	TMenuItem *MWatch;
	TTimer *TimerWatch;
	TSaveDialog *SaveDialogReport;
	TMenuItem *MEmptyValue;
	TMenuItem *MEmptyAuto;
	TMenuItem *MEmpty00;
	TMenuItem *MEmptyFF;
	TScrollBox *ScrollBoxView;
	TImage *ImageView;
	void __fastcall MOpenClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall MReloadClick(TObject *Sender);
	void __fastcall MSaveReportClick(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall TimerWatchTimer(TObject *Sender);
	void __fastcall MWatchClick(TObject *Sender);
	void __fastcall MEmptyAutoClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void __fastcall DrawPRG(int x,int y,unsigned char *data,int fill);
	void __fastcall DrawCHR(int x,int y,unsigned char *data);
	bool __fastcall LoadNES(AnsiString name);
	void __fastcall ShowNES(void);
	void __fastcall DropFilesHandler(TWMDropFiles &Message);
	bool __fastcall ImageToPNG(AnsiString name,TImage* image);

BEGIN_MESSAGE_MAP
   MESSAGE_HANDLER(WM_DROPFILES,TWMDropFiles,DropFilesHandler)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
