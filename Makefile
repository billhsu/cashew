CC        := g++
LDFLAGS   := -lGL -lGLU -lglut -lrt
CFLAGS    := 

MODULES   := src/core/camera src/core/math src/core/scene src/impl 
SRC_DIR   := $(addprefix ,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst %.cpp,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR)) -Ilib/freeglut-2.8.1/include -Llib/freeglut-2.8.1/src/.libs

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean depend

all: checkdirs nextsketch

nextsketch: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJ) -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

depend:
	@makedepend -pbuild/ --  $(CFLAGS) -- $(SRC)
	
$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

# DO NOT DELETE

