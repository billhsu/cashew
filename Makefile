CC        := g++
OS := $(shell uname)
ifeq ($(OS),Darwin)
	LDFLAGS   := -llua
else
	LDFLAGS   := -lrt -llua
endif

CFLAGS    := -g

MODULES   := src/Core/Camera src/Core/Math src/Core/Basic src/Core/Graphics src/Core/Util src/Core/State src/Core/Scripting
SRC_DIR   := $(addprefix ,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst %.cpp,build/%.o,$(SRC))
ifeq ($(OS),Darwin)
	INCLUDES  := -Isrc/ -Ilib/lua-5.2.3/src -Wno-deprecated-declarations
else
	INCLUDES  := -Isrc/ -Ilib/lua-5.2.3/src
endif

OUT := libcashew.a
vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean depend

all: checkdirs $(OUT)

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

depend:
	@makedepend -pbuild/ --  $(CFLAGS) -- $(SRC)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
