COPTS += -DMAKE_EV3
COPTS += -DMAKE_EV3
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += \

APPL_CXXOBJS += \
				system.o\
				LineTrace.o\
				Action.o\
				Controller.o\
				PIDControl.o\
				ColorSensor.o\
				ColorSpace.o\
				HSV.o\
				CarData.o\
				LeftMotor.o\
				Motor.o\
				RightMotor.o\
				Steering.o\
				AccelerationCurve.o\
				AccelerationDesigner.o\
				TrapezoidControl.o\
				Curve.o\
				Straight.o\
				Turn.o\
				PaternGarage.o\
				PaternSlalom.o\
				PaternJudge.o\
				SceneControl.o\
				Task.o\
				FileIO.o\
				SceneInfo.o\
				UltraSonicSensor.o\
				UltraSonic.o\
				AngleDecision.o\
				CoordinateDecision.o\
				HSVDecision.o\
				Judgement.o\
				RGBDecision.o\
				UltraSonicDecision.o\
				UseJudgement.o\
				Correction.o\
				ArmMotor.o\
#
SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries


#include $(mkfile_path)/workspace/library/RyujiEv3/Makefile

endif 

# COPTS += -DMAKE_BT_DISABLE

APPL_DIRS +=\
	$(mkfile_path)workspace/src/Action\
	$(mkfile_path)workspace/src/ColorSpace\
	$(mkfile_path)workspace/src/Steering\
	$(mkfile_path)workspace/src/system\
	$(mkfile_path)workspace/src/CarData\
	$(mkfile_path)workspace/src/Scene\
	$(mkfile_path)workspace/src/Avoidance\
	$(mkfile_path)workspace/src/Task\
	$(mkfile_path)workspace/src/Judge\
	$(mkfile_path)workspace/src/FileOp\
	$(mkfile_path)workspace/src/SceneInfo\
	$(mkfile_path)workspace/src/Sonic\
	$(mkfile_path)workspace/src/Correction\

INCLUDES +=\
	-I$(mkfile_path)workspace/include/Action\
	-I$(mkfile_path)workspace/include/ColorSpace\
	-I$(mkfile_path)workspace/include/Steering\
	-I$(mkfile_path)workspace/include/system\
	-I$(mkfile_path)workspace/include/CarData\
	-I$(mkfile_path)workspace/include/Scene\
	-I$(mkfile_path)workspace/include/Avoidance\
	-I$(mkfile_path)workspace/include/Task\
	-I$(mkfile_path)workspace/include/Judge\
	-I$(mkfile_path)workspace/include/FileOp\
	-I$(mkfile_path)workspace/include/SceneInfo\
	-I$(mkfile_path)workspace/include/Sonic\
	-I$(mkfile_path)workspace/include/Correction\

COPTS += -I$(ETROBO_HRP3_WORKSPACE)/etroboc_common
COPTS += -DMAKE_EV3
COPTS += -std=gnu++11
COPTS += -fno-threadsafe-statics
