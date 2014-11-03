CC        := g++

LDFLAGS   := -llua
CFLAGS    := -g

MODULES   := src/cashew/camera src/cashew/math src/cashew/scene src/cashew/scene/states src/cashew/UI src/cashew/texture src/impl src/cashew/scripting
SRC_DIR   := $(addprefix ,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst %.cpp,build/%.o,$(SRC))

INCLUDES  := -Iinclude/ -Ilib/lua-5.2.3/src
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
# DO NOT DELETE

