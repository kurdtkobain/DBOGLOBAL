// Venus.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "Venus.h"
#include "VenusFrame.h"

#include "VenusDoc.h"
#include "VenusView.h"

#include "VenusAPI.h"

#include "StatusBarDialog.h"
#include "LightDialog.h"
#include "OptionDialog.h"

#include "EventLayer.h"

#include "NtlEventQueue.h"
#include "NtlPLEntityFreeList.h"
#include "NtlEffectSystemFreeList.h"

#include ".\venuspropertycontainer.h"
#include ".\venusvisualmanager.h"

#include "VenusPlayerEventManager.h"

#include "VenusFramework.H"

#include ".\venusconfig.h"

#include "MeshLayer.h"
#include "TextureLayer.h"

#include "Splash.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVenusApp

BEGIN_MESSAGE_MAP(CVenusApp, CWinApp)	
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CVenusApp 생성

CVenusApp::CVenusApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
	m_bInitialize = FALSE;
}


// 유일한 CVenusApp 개체입니다.

CVenusApp theApp;

// CVenusApp 초기화

BOOL CVenusApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControls()가 필요합니다. 
	// InitCommonControls()를 사용하지 않으면 창을 만들 수 없습니다.
	InitCommonControls();

	CWinApp::InitInstance();

	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.
	// 응용 프로그램의 문서 템플릿을 등록합니다. 문서 템플릿은
	// 문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CVenusDoc),
		RUNTIME_CLASS(CVenusFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CVenusView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// splash window
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

	// 명령줄에 지정된 명령을 디스패치합니다. 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// 접미사가 있을 경우에만 DragAcceptFiles를 호출합니다.
	// SDI 응용 프로그램에서는 ProcessShellCommand 후에 이러한 호출이 발생해야 합니다.

	RwChar strMainPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, strMainPath);
	CVenusConfig::GetInstance().m_strMainPath = strMainPath;
	CVenusConfig::GetInstance().Load();

	CStatusBarDialog::GetInstance().BuildData();
	CLightDialog::GetInstance().BuildData();
	COptionDialog::GetInstance().BuildGridWidth();
	COptionDialog::GetInstance().BuildGridCount();

	CEventLayer* pEventLayer = (CEventLayer*) gGetEditLayer(EDIT_LAYER_EVENT);
	pEventLayer->BuildData();

	CVenusFramework::GetInstance().Create(gMainView()->GetSafeHwnd(), FALSE);

	//CreateVenus();

	m_bInitialize = TRUE;

	CSplashWnd::DestroySplashWnd();

	if (CVenusConfig::GetInstance().m_bShowUpdateNews)
	{
		CVenusConfig::GetInstance().ShowUpdateNews();
	}    

	return TRUE;
}

void CVenusApp::DeleteVenus()
{
	CVenusPlayerEventManager::GetInstance().Delete();

	CVenusVisualManager::GetInstance().Destroy();

	CNtlEffectSystemFreeList::Destroy();

	CVenusPropertyContainer::GetInstance().Destroy();

	// Close the event system
	RWS::CEventHandler::UnRegisterStreamChunkHandlers();
	RWS::CEventHandler::Close ();

	CNtlEventQueue::GetInstance()->Destroy();
}

BOOL CVenusApp::OnIdle(LONG lCount)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(m_pMainWnd->IsIconic())
		return FALSE;

	if(m_bInitialize)
	{
		CVenusFramework::GetInstance().OnIdle();
	}

	__super::OnIdle(lCount);
	return TRUE;
//	return CWinApp::OnIdle(lCount);
}

