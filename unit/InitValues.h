#ifndef EV3_UNIT_INIT_VALUES_H_
#define EV3_UNIT_INIT_VALUES_H_

namespace unit{

  class InitValues{
  public:
    enum Name{
      GYRO_OFFSET
    };
    
    InitValues();
    
    void put(Name name, int value);
    int get(Name name);

  private:
    int GyroOffset;
    
  };
}
#endif
