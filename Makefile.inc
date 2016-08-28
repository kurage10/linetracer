mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
	BalancingWalker.o \
	LineMonitor.o \
	LineMonitor.o \
	BalancerCpp.o \
	Starter.o \
	TailController.o \
	LineTracer.o \
	LineTracerWithStarter.o \
	Switcher.o \
	UsecaseDetector.o \
	DistanceMonitor.o \
	Stopper.o \
	ObstacleDitector.o \
	StairTurner.o \
	TailWalker.o \
	StairWalker.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIR += \
	 $(mkfile_path)app \
	 $(mkfile_path)unit \
 	 $(mkfile_path)Garage/app \
	 $(mkfile_path)Stair/app \
	 $(mkfile_path)Stair/unit \
	 $(mkfile_path)LineTrace/app \
 	 $(mkfile_path)LineTrace/unit \

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit \
	-I$(mkfile_path)Garage/app \
	-I$(mkfile_path)Stair/app \
	-I$(mkfile_path)Stair/unit \
	-I$(mkfile_path)LineTrace/app \
	-I$(mkfile_path)LineTrace/unit \

COPTS += -fno-use-cxa-atexit
