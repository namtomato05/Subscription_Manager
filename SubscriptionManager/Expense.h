#pragma once
#include <afxwin.h>

class Expense {
public:
    CString m_serviceName;
    int     m_paymentDay;
    int     m_monthlyFee;
    int     m_partySize;

    Expense() : m_paymentDay(1), m_monthlyFee(0), m_partySize(1) {}

    Expense(CString name, int day, int fee, int party)
        : m_serviceName(name), m_paymentDay(day),
        m_monthlyFee(fee), m_partySize(party) {
    }

    int getMyShare() const {
        return (m_partySize > 0) ? m_monthlyFee / m_partySize : m_monthlyFee;
    }

    bool isDueSoon(int today) const {
        int diff = m_paymentDay - today;
        return (diff >= 0 && diff <= 3);
    }
};