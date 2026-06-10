#pragma once
#include "SubManager.h"

class CSubscriptionManagerDlg : public CDialogEx
{
public:
    CSubscriptionManagerDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SUBSCRIPTIONMANAGER_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

public:
    // 변수들
    CString m_strName;
    CString m_strDay;
    CString m_strFee;
    CString m_strParty;
    CString m_strShare;
    CString m_strTotal;
    CString m_strMyShare;
    CString m_strDueSoon;
    CListCtrl m_listSub;

    // SubManager 객체
    SubManager m_manager;

    // 버튼 이벤트
    afx_msg void OnBnClickedBtnRegister();  // 등록 탭 전환
    afx_msg void OnBnClickedBtnList();      // 목록 탭 전환
    afx_msg void OnBnClickedBtnStats();     // 통계 탭 전환
    afx_msg void OnBnClickedBtnAdd();       // 등록 실행
    afx_msg void OnBnClickedBtnClear();     // 초기화
    afx_msg void OnBnClickedBtnDelete();    // 삭제

    // 화면 전환 함수
    void ShowRegisterPage();
    void ShowListPage();
    void ShowStatsPage();
    void HideAll();

    // 목록 새로고침
    void RefreshList();
};