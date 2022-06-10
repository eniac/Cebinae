dptf := ../../../dptf

BF_DRV_SRC := ${SDE}/pkgsrc/bf-drivers

TOFINO_CPP_FLAGS := -Wno-missing-field-initializers -Werror -Wshadow -g -O2 -std=c++11
TOFINO_CPP_LIBS := -ldriver -lbfsys -lbf_switchd_lib -lpifeproto -lpiall -lm -ldl -lpthread -pthread -Wl,--disable-new-dtags -L${SDE_INSTALL}/lib -Wl,-rpath -Wl,${SDE_INSTALL}/lib

.PHONY: test

# Compile lucid code to P4 library
compile: egress.dpt
	$(dptf) egress.dpt

# compile P4 program and control plane
build: main.p4 egress.dpt.p4 main.py main.cpp
	./libs/p4tapp.sh build main.p4
	${SDE_INSTALL}/bin/generate_tofino_pd --context_json ./main/pipe/context.json -o pd	
	./pd_helpers_gen.py
	g++ -I${BF_DRV_SRC}/include -I${SDE_INSTALL}/include ${TOFINO_CPP_FLAGS} -o main/bf_switchd main.cpp ${TOFINO_CPP_LIBS}

# compile control plane only
buildcontrol: main.cpp
	${SDE_INSTALL}/bin/generate_tofino_pd --context_json ./main/pipe/context.json -o pd	
	./pd_helpers_gen.py
	g++ -I${BF_DRV_SRC}/include -I${SDE_INSTALL}/include ${TOFINO_CPP_FLAGS} -o main/bf_switchd main.cpp ${TOFINO_CPP_LIBS}



# Run test case in tofino asic simulator.
test:
	./libs/p4tapp.sh test main.p4 test.json # $(RUN_ARGS)

sim: 
	./libs/p4tapp.sh sim main.p4

test_on_running_sim:
	./libs/p4tapp.sh test_on_running_sim test.json


hw_baseline: 
	- sudo killall bf_switchd
	./libs/p4tapp.sh hw main.p4 baseline

hw_cebinae:
	- sudo killall bf_switchd
	./libs/p4tapp.sh hw main.p4 cebinae



# TODO -- run switchd and controller on physical tofino. 
# run