#include <iostream>
#include "logger.h"

int main()
{
    Logger log;
    log.Info("This is log.Info() function");
    log.Error("This is log.Error() function");
    log.Warn("This is log.Warn() function");
    log.Debug("This is log.Debug() function");
}

