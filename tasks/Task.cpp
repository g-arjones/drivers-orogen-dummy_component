/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <memory>
#include <unistd.h>
#include <fcntl.h>
#include <iodrivers_base/ConfigureGuard.hpp>

using namespace dummy_component;
using std::unique_ptr;
using std::runtime_error;
using std::cout;
using std::endl;
using iodrivers_base::ConfigureGuard;

Task::Task(std::string const& name)
    : TaskBase(name), m_driver(nullptr), m_iteration(0)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine), m_driver(nullptr), m_iteration(0)
{
}

Task::~Task()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    ConfigureGuard guard(this);
    
    delete m_driver;
    unique_ptr<DummyDriver> driver(new DummyDriver());
    driver->openURI(_io_port.value());

    m_driver = driver.release();
    setDriver(m_driver);

    if (! TaskBase::configureHook())
        return false;

    if (!m_iteration)
    {
        m_iteration++;
        throw runtime_error("Exception after base class is called");
    }

    guard.commit();
    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
    detachDriver();
    
    delete m_driver;
    m_driver = nullptr;
}
void Task::processIO()
{
}
