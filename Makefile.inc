mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
	Waker_LT.o \
	BalancingWalker_LT.o \
	LineMonitor_LT.o \
	BalancerCpp_LT.o \
	Starter_LT.o \
	TailController_LT.o \
	LineTracer_LT.o \
	LineTracerWithStarter_LT.o \
	Switcher.o \
	InitValues.o \
	GrayDetector.o \
	UsecaseDetector.o \
	DistanceMonitor.o \
	Stopper_G.o \
	Waker_S.o \
	GarageStopper_G.o \
	LineMonitor_G.o \
	Starter_G.o \
	TailController_G.o \
	TailWalker_G.o \
	LineTracerWithStarter_S.o \
	LineTracer_S.o \
	StairWalker_S.o \
	BalancerCpp_S.o \
	BalancingWalker_S.o \
	LineMonitor_S.o \
	LineMonitorForTail_S.o \
	ObstacleDitector_S.o \
	StairTurner_S.o \
	Starter_S.o \
	TailController_S.o \
	TailWalker_S.o \
	LookUpGate_LG.o \
	BalancerCpp_LG.o \
	BalancingWalker_LG.o \
	LineMonitor_LG.o \
	Starter_LG.o \
	TailController_LG.o \

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIR += \
	 $(mkfile_path)app \
	 $(mkfile_path)unit \
 	 $(mkfile_path)Garage/app \
  	 $(mkfile_path)Garage/unit \
	 $(mkfile_path)Stair/app \
	 $(mkfile_path)Stair/unit \
	 $(mkfile_path)LookUpGate/app \
	 $(mkfile_path)LookUpGate/unit \
	 $(mkfile_path)LineTrace/app \
 	 $(mkfile_path)LineTrace/unit \

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit \
	-I$(mkfile_path)Garage/app \
	-I$(mkfile_path)Garage/unit \
	-I$(mkfile_path)Stair/app \
	-I$(mkfile_path)Stair/unit \
	-I$(mkfile_path)LookUpGate/app \
	-I$(mkfile_path)LookUpGate/unit \
	-I$(mkfile_path)LineTrace/app \
	-I$(mkfile_path)LineTrace/unit \

COPTS += -fno-use-cxa-atexit
