#pragma once
#include <afxwin.h>
#include <vector>
#include "Expense.h"
using namespace std;

class SubManager {
public:
    vector<Expense> m_subList;
    vector<CString> m_logList;

    void addSubscription(const Expense& sub) {
        m_subList.push_back(sub);
        CString log;
        log.Format(_T("[등록] %s / %d원 / %d일 / %d명"),
            sub.m_serviceName, sub.m_monthlyFee,
            sub.m_paymentDay, sub.m_partySize);
        m_logList.push_back(log);
    }

    bool removeSubscription(const CString& name) {
        for (auto it = m_subList.begin(); it != m_subList.end(); ++it) {
            if (it->m_serviceName == name) {
                CString log;
                log.Format(_T("[해지] %s"), name);
                m_logList.push_back(log);
                m_subList.erase(it);
                return true;
            }
        }
        return false;
    }

    int getTotalMonthly() const {
        int total = 0;
        for (const auto& sub : m_subList)
            total += sub.m_monthlyFee;
        return total;
    }

    vector<Expense> getDueSoon(int today) const {
        vector<Expense> result;
        for (const auto& sub : m_subList)
            if (sub.isDueSoon(today)) result.push_back(sub);
        return result;
    }
};