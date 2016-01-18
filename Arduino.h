#include <fcntl.h> 
#include <stdio.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <string>
#include <thread>         // std::thread
#include <mutex>          // std::mutex

#include <sstream>
#include <vector>

using namespace std;

struct ArduinoData {
  string direction;
  int pulseSensorStableValue;
  int pulseSensorRealValue;
  int skinResistenceStableValue;
  int skinResistenceRealValue;
  int hungry;
} ;

class Arduino
{

  string str="", last_str = "";

  public:
    void getData();
    ArduinoData getGameData();
};
