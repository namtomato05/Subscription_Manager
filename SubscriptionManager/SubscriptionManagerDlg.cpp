#include "pch.h"
#include "SubscriptionManager.h"
#include "SubscriptionManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CSubscriptionManagerDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_register, &CSubscriptionManagerDlg::OnBnClickedBtnRegister)
    ON_BN_CLICKED(IDC_BTN_list, &CSubscriptionManagerDlg::OnBnClickedBtnList)
    ON_BN_CLICKED(IDC_BTN_stats, &CSubscriptionManagerDlg::OnBnClickedBtnStats)
    ON_BN_CLICKED(IDC_BTN_add, &CSubscriptionManagerDlg::OnBnClickedBtnAdd)
    ON_BN_CLICKED(IDC_BTN_clear, &CSubscriptionManagerDlg::OnBnClickedBtnClear)
    ON_BN_CLICKED(IDC_BTN_delete, &CSubscriptionManagerDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()

CSubscriptionManagerDlg::CSubscriptionManagerDlg(CWnd* pParent)
    : CDialogEx(IDD_SUBSCRIPTIONMANAGER_DIALOG, pParent)
    , m_strName(_T(""))
    , m_strDay(_T(""))
    , m_strFee(_T(""))
    , m_strParty(_T(""))
    , m_strShare(_T(""))
    , m_strTotal(_T(""))
    , m_strMyShare(_T(""))
    , m_strDueSoon(_T(""))
{
}

void CSubscriptionManagerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_name, m_strName);
    DDX_Text(pDX, IDC_EDIT_day, m_strDay);
    DDX_Text(pDX, IDC_EDIT_fee, m_strFee);
    DDX_Text(pDX, IDC_EDIT_party, m_strParty);
    DDX_Text(pDX, IDC_EDIT_share, m_strShare);
    DDX_Text(pDX, IDC_EDIT_total, m_strTotal);
    DDX_Text(pDX, IDC_EDIT_myshare, m_strMyShare);
    DDX_Text(pDX, IDC_EDIT_duesoon, m_strDueSoon);
    DDX_Control(pDX, IDC_LIST_sub, m_listSub);
}

BOOL CSubscriptionManagerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_listSub.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    m_listSub.InsertColumn(0, _T("서비스명"), LVCFMT_CENTER, 120);
    m_listSub.InsertColumn(1, _T("결제일"), LVCFMT_CENTER, 80);
    m_listSub.InsertColumn(2, _T("월 금액"), LVCFMT_CENTER, 100);
    m_listSub.InsertColumn(3, _T("인원수"), LVCFMT_CENTER, 80);
    m_listSub.InsertColumn(4, _T("내 부담금"), LVCFMT_CENTER, 100);

    ShowRegisterPage();

    return TRUE;
}

// ===================== 화면 전환 =====================

void CSubscriptionManagerDlg::HideAll()
{
    // 등록 영역
    GetDlgItem(IDC_EDIT_name)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_day)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_fee)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_party)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_share)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BTN_add)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BTN_clear)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_name)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_day)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_fee)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_party)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_share)->ShowWindow(SW_HIDE);

    // 목록 영역
    GetDlgItem(IDC_LIST_sub)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BTN_delete)->ShowWindow(SW_HIDE);

    // 통계 영역
    GetDlgItem(IDC_EDIT_total)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_myshare)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_duesoon)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_total)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_myshare)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_duesoon)->ShowWindow(SW_HIDE);
}

void CSubscriptionManagerDlg::ShowRegisterPage()
{
    HideAll();
    GetDlgItem(IDC_EDIT_name)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_EDIT_day)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_EDIT_fee)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_EDIT_party)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_EDIT_share)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BTN_add)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BTN_clear)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_name)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_day)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_fee)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_party)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_share)->ShowWindow(SW_SHOW);
}

void CSubscriptionManagerDlg::ShowListPage()
{
    HideAll();
    RefreshList();
    GetDlgItem(IDC_LIST_sub)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_BTN_delete)->ShowWindow(SW_SHOW);
}

void CSubscriptionManagerDlg::ShowStatsPage()
{
    HideAll();

    int total = m_manager.getTotalMonthly();
    m_strTotal.Format(_T("%d 원"), total);

    int myTotal = 0;
    for (const auto& sub : m_manager.m_subList)
        myTotal += sub.getMyShare();
    m_strMyShare.Format(_T("%d 원"), myTotal);

    CTime today = CTime::GetCurrentTime();
    int todayDay = today.GetDay();
    auto dueSoon = m_manager.getDueSoon(todayDay);

    if (dueSoon.empty()) {
        m_strDueSoon = _T("없음");
    }
    else {
        m_strDueSoon = _T("");
        for (const auto& sub : dueSoon)
            m_strDueSoon += sub.m_serviceName + _T(" ");
    }

    UpdateData(FALSE);

    GetDlgItem(IDC_EDIT_total)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_EDIT_myshare)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_EDIT_duesoon)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_total)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_myshare)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_duesoon)->ShowWindow(SW_SHOW);
}

// ===================== 목록 새로고침 =====================

void CSubscriptionManagerDlg::RefreshList()
{
    m_listSub.DeleteAllItems();
    for (int i = 0; i < (int)m_manager.m_subList.size(); i++) {
        const Expense& sub = m_manager.m_subList[i];
        CString fee, day, party, share;
        fee.Format(_T("%d"), sub.m_monthlyFee);
        day.Format(_T("%d"), sub.m_paymentDay);
        party.Format(_T("%d"), sub.m_partySize);
        share.Format(_T("%d"), sub.getMyShare());

        m_listSub.InsertItem(i, sub.m_serviceName);
        m_listSub.SetItemText(i, 1, day);
        m_listSub.SetItemText(i, 2, fee);
        m_listSub.SetItemText(i, 3, party);
        m_listSub.SetItemText(i, 4, share);
    }
}

// ===================== 버튼 이벤트 =====================

void CSubscriptionManagerDlg::OnBnClickedBtnRegister()
{
    ShowRegisterPage();
}

void CSubscriptionManagerDlg::OnBnClickedBtnList()
{
    ShowListPage();
}

void CSubscriptionManagerDlg::OnBnClickedBtnStats()
{
    ShowStatsPage();
}

void CSubscriptionManagerDlg::OnBnClickedBtnAdd()
{
    UpdateData(TRUE);

    if (m_strName.IsEmpty() || m_strDay.IsEmpty() ||
        m_strFee.IsEmpty() || m_strParty.IsEmpty()) {
        AfxMessageBox(_T("모든 항목을 입력해주세요."));
        return;
    }

    int day = _ttoi(m_strDay);
    int fee = _ttoi(m_strFee);
    int party = _ttoi(m_strParty);

    if (day < 1 || day > 31) {
        AfxMessageBox(_T("결제일은 1~31 사이로 입력해주세요."));
        return;
    }
    if (party < 1) party = 1;

    Expense sub(m_strName, day, fee, party);
    m_manager.addSubscription(sub);

    m_strShare.Format(_T("%d 원"), sub.getMyShare());
    UpdateData(FALSE);

    AfxMessageBox(_T("등록 완료!"));
}

void CSubscriptionManagerDlg::OnBnClickedBtnClear()
{
    m_strName = _T("");
    m_strDay = _T("");
    m_strFee = _T("");
    m_strParty = _T("");
    m_strShare = _T("");
    UpdateData(FALSE);
}

void CSubscriptionManagerDlg::OnBnClickedBtnDelete()
{
    int sel = m_listSub.GetNextItem(-1, LVNI_SELECTED);
    if (sel == -1) {
        AfxMessageBox(_T("삭제할 항목을 선택해주세요."));
        return;
    }
    CString name = m_listSub.GetItemText(sel, 0);
    m_manager.removeSubscription(name);
    RefreshList();
}