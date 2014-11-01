CC        := g++
OS := $(shell uname)
ifeq ($(OS),Darwin)
	LDFLAGS   := -framework OpenGL -framework GLUT -llua
else
	LDFLAGS   := -lGL -lGLU -lglut -lrt -llua
endif

CFLAGS    := -g

MODULES   := src/core/camera src/core/math src/core/scene src/core/scene/states src/core/UI src/core/texture src/impl src/core/scripting
SRC_DIR   := $(addprefix ,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst %.cpp,build/%.o,$(SRC))
ifeq ($(OS),Darwin)
	INCLUDES  := $(addprefix -I,$(SRC_DIR)) -Ilib/lua-5.2.3/src -Llib/lua-5.2.3/src
else
	INCLUDES  := $(addprefix -I,$(SRC_DIR)) -Ilib/freeglut-2.8.1/include -Llib/freeglut-2.8.1/src/.libs -Ilib/lua-5.2.3/src -Llib/lua-5.2.3/src
endif

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean depend

all: checkdirs cashew

cashew: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LDFLAGS) -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

depend:
	@makedepend -pbuild/ --  $(CFLAGS) -- $(SRC)
	
$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
# DO NOT DELETE

