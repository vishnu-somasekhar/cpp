#include "test.h"

AAA::AAA()
{
    m_iVal = 100;
}

Student::Student()
{
    m_iValue = 10;
}

int Student::Get()
{
    return m_iValue;
}

void Student::Set(int i)
{
    m_iValue = i;
}

VFWRETVAL VSampleWithTabCtrlCmd::VStartProgressBarRes::OnExecute(const VInputResParam& inputResParam)
{
    VProcRunner processRunnerObj;
    VProcRunnerInput procRunnerInput;

    IVProcessLogger* pLogger         = new VProgressBarProcessLogger();
    procRunnerInput.m_pProcessLogger = pLogger;

    IVProcessProgressTracker* pProgressTracker = new VProgressBarProgressTracker();
    procRunnerInput.m_pProcessProgressTracker  = pProgressTracker;

    procRunnerInput.m_sProgressBarTitle         = "Timer running please wait!";
    procRunnerInput.m_sProgressBarButtonCaption = "Abort";

    processRunnerObj.Start(procRunnerInput);

    return VFW_SUCCESS;
}
