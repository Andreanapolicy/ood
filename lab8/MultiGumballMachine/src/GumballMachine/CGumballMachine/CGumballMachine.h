#pragma once
#include "../../State/CMaxQuarterCountState/CMaxQuarterCountState.h"
#include "../../State/CHasQuarterState/CHasQuarterState.h"
#include "../../State/CNoQuarterState/CNoQuarterState.h"
#include "../../State/CSoldOutState/CSoldOutState.h"
#include "../../State/CSoldState/CSoldState.h"
#include "../IGumballMachine/IGumballMachine.h"

class CGumballMachine : private IGumballMachine
{
public:
    explicit CGumballMachine(unsigned int gumballsCount)
            : m_count(gumballsCount), m_soldState(*this), m_soldOutState(*this), m_noQuarterState(*this),
              m_hasQuarterState(*this), m_maxQuarterCountState(*this), m_state(&m_soldOutState)
    {
        if (m_count > 0)
        {
            m_state = &m_noQuarterState;
        }
    }

    void EjectQuarter()
    {
        m_state->EjectQuarter();
    }

    void InsertQuarter()
    {
        m_state->InsertQuarter();
    }

    void TurnCrank()
    {
        m_state->TurnCrank();
        m_state->Dispense();
    }

    std::string ToString() const
    {
        return "Best C++ gumball Machine\nGumballs count: " + std::to_string(m_count) + "\nQuarters count: " +
               std::to_string(m_quarterCount) + "\nMachine state: " + m_state->ToString();
    }

private:
    unsigned int GetBallsCount() const override
    {
        return m_count;
    }

    unsigned int GetQuartersCount() const override
    {
        return m_quarterCount;
    }

    void SetSoldOutState() override
    {
        m_state = &m_soldOutState;
    }

    void SetNoQuarterState() override
    {
        m_state = &m_noQuarterState;
    }

    void SetSoldState() override
    {
        m_state = &m_soldState;
    }

    void SetHasQuarterState() override
    {
        m_state = &m_hasQuarterState;
    }

    void SetMaxQuarterCountState() override
    {
        m_state = &m_maxQuarterCountState;
    }

    void ReleaseBall() override
    {
        if (m_count == 0)
        {
            return;
        }

        std::cout << "A gumball comes rolling out the slot\n" << std::endl;
        m_count--;
    }

    void ReleaseQuarter(unsigned int count = 1) override
    {
        if (m_quarterCount == 0)
        {
            return;
        }

        count = std::min(count, GetQuartersCount());

        m_quarterCount = m_quarterCount - count;
    }

    void AddQuarter() override
    {
        m_quarterCount++;
    }

    unsigned int m_count = 0;
    unsigned int m_quarterCount = 0;
    CSoldState m_soldState;
    CSoldOutState m_soldOutState;
    CNoQuarterState m_noQuarterState;
    CHasQuarterState m_hasQuarterState;
    CMaxQuarterCountState m_maxQuarterCountState;
    IState *m_state;
};