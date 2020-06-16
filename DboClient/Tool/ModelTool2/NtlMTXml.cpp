#include "StdAfx.h"
#include "NtlMTXml.h"
#include "comutil.h"
#include "NtlDebug.h"
#include "NtlStringHandler.h"

CNtlMTXml::CNtlMTXml(void)
{
}

CNtlMTXml::~CNtlMTXml(void)
{
    
}

BOOL CNtlMTXml::CreateXML(char* szRootNodeName)
{
    Create();

    IXMLDOMProcessingInstruction* pPI = NULL;

    m_pXMLDocument->createProcessingInstruction(L"xml", L"version=\"1.0\" encoding = \"UTF-8\"", &pPI);
    m_pXMLDocument->appendChild(pPI, NULL);

    m_pXMLDocument->createElement(L"FOLDER", &m_pRootElem);
    m_pXMLDocument->appendChild(m_pRootElem, NULL);
    
    IXMLDOMAttribute* pAttr;
    m_pXMLDocument->createAttribute(L"NAME", &pAttr);
    m_pRootElem->setAttributeNode(pAttr, NULL);

    m_pRootElem->setAttribute(L"NAME", (_variant_t)szRootNodeName);

    return TRUE;
}

bool CNtlMTXml::Save(char* szFileName)
{
    if(!m_pXMLDocument || !szFileName)
        return false;

    // 스타일 시트를 적용하여 세이브 한다.
    IXMLDOMDocument* pXSL = NULL;
    CoCreateInstance(__uuidof(DOMDocument30), NULL, CLSCTX_INPROC_SERVER, __uuidof(IXMLDOMDocument), (void**)&pXSL);
    if(!pXSL)
        return false;

    VARIANT_BOOL vBool;
    pXSL->put_async(VARIANT_FALSE);
    pXSL->load((_variant_t)L"indent.xsl", &vBool);

    VARIANT vObject;
    VariantInit(&vObject);
    vObject.vt = VT_DISPATCH;
    vObject.pdispVal = m_pXMLDocument;
    
    m_pXMLDocument->transformNodeToObject(pXSL, vObject);

    HRESULT hr = m_pXMLDocument->save((_variant_t)szFileName);
   
    if(pXSL)
    {
        pXSL->Release();
        pXSL = NULL;
    }
    if(hr == S_OK)
    {
        return true;
    }
    else
    {
        return false;
    }        
}

bool CNtlMTXml::LoadTreeXML(char* szFileName, SItemNode* itemNode)
{
    if(!Create())
        return FALSE;

    if(!Load(szFileName))
        return FALSE;

	// 첫번째 폴더 노드를 찾는다.
	IXMLDOMNodeList* pNodeList = SelectNodeList(L"FOLDER");
	if(pNodeList)
	{
		IXMLDOMNode* pNode = NULL;
		pNodeList->get_item(0, &pNode);
		LoadScipt(pNode, itemNode, TRUE);

		pNode->Release();
		pNodeList->Release();
	}

    return TRUE;
}

void CNtlMTXml::LoadScipt(IXMLDOMNode* pNode, SItemNode* pParentItem, bool bRoot /* = FALSE */)
{
	if(!pNode || !pParentItem)
		return;

	SItemNode* pItemNode = NULL;
	if(bRoot)
	{
		pItemNode = pParentItem;
	}
	else
	{
		pItemNode = new SItemNode();
	}

	// 노드 자신의 정보를 설정한다.
	WCHAR szNodeName[32] = {0,};
	GetTextWithAttributeName(pNode, L"NAME", szNodeName, 32);
	
	pItemNode->strNodeName = szNodeName;
	pItemNode->eNodeType = NODE_FOLDER;

	
	// 자신의 자식으로 스크립트가 있으면 추가한다.
	IXMLDOMNodeList* pNodeList = NULL;	
	pNode->get_childNodes(&pNodeList);
	if(pNodeList)
	{
		long listLen = 0;
		pNodeList->get_length(&listLen);
		for(long i = 0; i < listLen; ++i)
		{
			IXMLDOMNode* pNodeChild = NULL;
			pNodeList->get_item(i, &pNodeChild);
			if(!pNodeChild)
				continue;

			// 폴더면 재귀 함수에 돌고, 스크립트면 자식으로 추가한다.
			BSTR strNodeName;
			pNodeChild->get_nodeName(&strNodeName);
			if(wcscmp(L"FOLDER", strNodeName) == 0)
			{
				LoadScipt(pNodeChild, pItemNode);
			}
			else
			{
				SItemNode* pItemChild = new SItemNode();

				// 데이터 내용
				BSTR strText;
				pNodeChild->get_text(&strText);

				pItemChild->strNodeName = strText;
				pItemChild->eNodeType = NODE_SCIRPT;
				pItemNode->vecChildList.push_back(pItemChild);
			}

			pNodeChild->Release();
		}

		pNodeList->Release();
	}

	if(!bRoot)
	{
		pParentItem->vecChildList.push_back(pItemNode);
	}	
}

/**
 * 새로운 폴더 노드를 추가한다
 * \param szParentFolder 붙일 부모 폴더의 이름, NULL인 경우에는 루트에 붙인다.
 * \param szFolderName 추가할 폴더노드의 이름 
 */
void CNtlMTXml::AddFolderNode(char* szParentFolder, char* szFolderName)
{
    if(!szFolderName)
        return;

    IXMLDOMElement* pElem = NULL;
    m_pXMLDocument->createElement(L"FOLDER", &pElem);
    if(!pElem)
        return;

    IXMLDOMAttribute* pAttr;
    m_pXMLDocument->createAttribute(L"NAME", &pAttr);
    pElem->setAttributeNode(pAttr, NULL);
    pElem->setAttribute(L"NAME", (_variant_t)szFolderName);

    if(szParentFolder == NULL)
    {
        // Attach to the root node.        
        m_pRootElem->appendChild(pElem, NULL);        
    }
    else
    {
        // Locate the parent node and attach it below it.
        WCHAR szNodeName[128];
        swprintf(szNodeName, 128, L"//FOLDER[@NAME=\"%S\"]", szParentFolder);
        IXMLDOMNode* pNode = NULL;
        m_pXMLDocument->selectSingleNode(szNodeName, &pNode);
        if(pNode)
        {
            pNode->appendChild(pElem, NULL);
        }
    }
    if(pElem)
    {
        pElem->Release();
        pElem = NULL;
    }
}

void CNtlMTXml::AddScriptNode(char* szParentFolder, char* szScriptName)
{
    if(!szParentFolder || !szScriptName)
        return;

    WCHAR szParentName[128] = {0,};
     swprintf(szParentName, 128, L"//FOLDER[@NAME=\"%S\"]", szParentFolder);
    IXMLDOMNode* pNode = NULL;
    m_pXMLDocument->selectSingleNode(szParentName, &pNode);
    if(pNode)
    {
        IXMLDOMElement* pElem = NULL;
        m_pXMLDocument->createElement(L"SCRIPT", &pElem);        


		const WCHAR* swScriptName = s2ws(szScriptName).c_str();

        IXMLDOMText* pText = NULL;
        m_pXMLDocument->createTextNode((WCHAR*)swScriptName, &pText);

        pElem->appendChild(pText, NULL);
        pNode->appendChild(pElem, NULL);

        if(pText)
        {
            pText->Release();
            pText = NULL;
        }

        if(pElem)
        {
            pElem->Release();
            pElem = NULL;
        }
    }
}



