#include <RabirdToolkitConfigNonOS.h>
#include <RabirdToolkit.h>
#include <RCoRoutine.h>
#include <RApplication.h>
#include <RUniquePointer.h>
#include <RSlot.h>
#include <RTimer.h>

class Application;

RCR_DECLARE(CrKknd, Application);

class Application : public RApplication
{
public:
  Application();

private:
  R_DECLARE_PRIVATE(Application)
};

R_IMPLEMENT_PRIVATE(Application);

struct ApplicationImpl : public Application
{
public:
};

struct ApplicationPrivate
{
public:
};

RCR_BEGIN(CrKknd, Application)
RCR_IMPL(CrKknd, Application)

while(1)
{
  Serial.print(millis());
  Serial.println(F(" : Hello, world! From NonOS mode!"));

  for(int i = 0; i < 2000; ++i)
  {
    delayMicroseconds(1000);
  }

  RCR_YIELD();
}

RCR_END()

Application::Application()
{
  RCR_SPAWN_DETACHED(CrKknd);
}

int
rMain(int argc, rfchar *argv[])
{
  // Add your initialization code here
  Serial.begin(9600);

  while(!Serial)
  {
  }

  // Application starts from here!
  new Application();

  return 0; // After rMain(), program will enter event loop.
}
