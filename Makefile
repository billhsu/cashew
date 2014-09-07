CC        := g++
LDFLAGS   := -lGL -lGLU -lglut -lrt -llua
CFLAGS    := -g

MODULES   := src/core/camera src/core/math src/core/scene src/core/scene/states src/core/UI src/core/texture src/impl src/core/scripting
SRC_DIR   := $(addprefix ,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst %.cpp,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR)) -Ilib/freeglut-2.8.1/include -Llib/freeglut-2.8.1/src/.libs -Ilib/lua-5.2.3/src -Llib/lua-5.2.3/src

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

build/src/core/camera/Camera.o: src/core/camera/Camera.h
build/src/core/camera/Camera.o: src/core/math/Vectors.h src/core/scene/Ray.h
build/src/core/camera/Camera.o: src/core/scene/Plane.h
build/src/core/camera/Camera.o: src/core/scene/LineSegment.h
build/src/core/camera/Camera.o: src/core/math/Quaternion.h
build/src/core/camera/Camera.o: src/core/math/Matrices.h
build/src/core/camera/Camera.o: src/core/math/Vectors.h src/impl/Utility.h
build/src/core/camera/Camera.o: /usr/include/stdio.h /usr/include/features.h
build/src/core/camera/Camera.o: /usr/include/bits/predefs.h
build/src/core/camera/Camera.o: /usr/include/sys/cdefs.h
build/src/core/camera/Camera.o: /usr/include/bits/wordsize.h
build/src/core/camera/Camera.o: /usr/include/gnu/stubs.h
build/src/core/camera/Camera.o: /usr/include/gnu/stubs-64.h
build/src/core/camera/Camera.o: /usr/include/bits/types.h
build/src/core/camera/Camera.o: /usr/include/bits/typesizes.h
build/src/core/camera/Camera.o: /usr/include/libio.h /usr/include/_G_config.h
build/src/core/camera/Camera.o: /usr/include/wchar.h
build/src/core/camera/Camera.o: /usr/include/bits/stdio_lim.h
build/src/core/camera/Camera.o: /usr/include/bits/sys_errlist.h
build/src/core/camera/Camera.o: /usr/include/stdlib.h
build/src/core/camera/Camera.o: /usr/include/bits/waitflags.h
build/src/core/camera/Camera.o: /usr/include/bits/waitstatus.h
build/src/core/camera/Camera.o: /usr/include/endian.h
build/src/core/camera/Camera.o: /usr/include/bits/endian.h
build/src/core/camera/Camera.o: /usr/include/bits/byteswap.h
build/src/core/camera/Camera.o: /usr/include/sys/types.h /usr/include/time.h
build/src/core/camera/Camera.o: /usr/include/sys/select.h
build/src/core/camera/Camera.o: /usr/include/bits/select.h
build/src/core/camera/Camera.o: /usr/include/bits/sigset.h
build/src/core/camera/Camera.o: /usr/include/bits/time.h
build/src/core/camera/Camera.o: /usr/include/sys/sysmacros.h
build/src/core/camera/Camera.o: /usr/include/bits/pthreadtypes.h
build/src/core/camera/Camera.o: /usr/include/alloca.h
build/src/core/camera/Camera.o: /usr/include/GL/freeglut.h
build/src/core/camera/Camera.o: /usr/include/GL/freeglut_std.h
build/src/core/camera/Camera.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
build/src/core/camera/Camera.o: /usr/include/inttypes.h /usr/include/stdint.h
build/src/core/camera/Camera.o: /usr/include/bits/wchar.h
build/src/core/camera/Camera.o: /usr/include/GL/glu.h
build/src/core/camera/Camera.o: /usr/include/GL/freeglut_ext.h
build/src/core/camera/Camera.o: src/core/scene/Controller.h
build/src/core/camera/Camera.o: src/core/scene/Plane.h
build/src/core/camera/Camera.o: src/core/scene/LineSegment.h
build/src/core/camera/Camera.o: src/core/scene/Scene.h src/core/scene/Ray.h
build/src/core/camera/Camera.o: src/core/UI/UI.h src/core/UI/UINode.h
build/src/core/camera/Camera.o: /usr/include/string.h /usr/include/xlocale.h
build/src/core/camera/Camera.o: src/core/UI/UIButton.h
build/src/core/camera/Camera.o: src/core/UI/UIRadioButton.h
build/src/core/camera/Camera.o: src/core/UI/UILabel.h
build/src/core/math/Matrices.o: src/core/math/Matrices.h
build/src/core/math/Matrices.o: src/core/math/Vectors.h
build/src/core/math/Quaternion.o: src/core/math/Quaternion.h
build/src/core/math/Quaternion.o: src/core/math/Matrices.h
build/src/core/math/Quaternion.o: src/core/math/Vectors.h src/impl/Utility.h
build/src/core/math/Quaternion.o: /usr/include/stdio.h
build/src/core/math/Quaternion.o: /usr/include/features.h
build/src/core/math/Quaternion.o: /usr/include/bits/predefs.h
build/src/core/math/Quaternion.o: /usr/include/sys/cdefs.h
build/src/core/math/Quaternion.o: /usr/include/bits/wordsize.h
build/src/core/math/Quaternion.o: /usr/include/gnu/stubs.h
build/src/core/math/Quaternion.o: /usr/include/gnu/stubs-64.h
build/src/core/math/Quaternion.o: /usr/include/bits/types.h
build/src/core/math/Quaternion.o: /usr/include/bits/typesizes.h
build/src/core/math/Quaternion.o: /usr/include/libio.h
build/src/core/math/Quaternion.o: /usr/include/_G_config.h
build/src/core/math/Quaternion.o: /usr/include/wchar.h
build/src/core/math/Quaternion.o: /usr/include/bits/stdio_lim.h
build/src/core/math/Quaternion.o: /usr/include/bits/sys_errlist.h
build/src/core/math/Quaternion.o: /usr/include/stdlib.h
build/src/core/math/Quaternion.o: /usr/include/bits/waitflags.h
build/src/core/math/Quaternion.o: /usr/include/bits/waitstatus.h
build/src/core/math/Quaternion.o: /usr/include/endian.h
build/src/core/math/Quaternion.o: /usr/include/bits/endian.h
build/src/core/math/Quaternion.o: /usr/include/bits/byteswap.h
build/src/core/math/Quaternion.o: /usr/include/sys/types.h
build/src/core/math/Quaternion.o: /usr/include/time.h
build/src/core/math/Quaternion.o: /usr/include/sys/select.h
build/src/core/math/Quaternion.o: /usr/include/bits/select.h
build/src/core/math/Quaternion.o: /usr/include/bits/sigset.h
build/src/core/math/Quaternion.o: /usr/include/bits/time.h
build/src/core/math/Quaternion.o: /usr/include/sys/sysmacros.h
build/src/core/math/Quaternion.o: /usr/include/bits/pthreadtypes.h
build/src/core/math/Quaternion.o: /usr/include/alloca.h
build/src/core/scene/Controller.o: src/core/scene/Controller.h
build/src/core/scene/Controller.o: src/core/math/Vectors.h
build/src/core/scene/Controller.o: src/core/scene/Plane.h
build/src/core/scene/Controller.o: src/core/scene/LineSegment.h
build/src/core/scene/Controller.o: /usr/include/GL/freeglut.h
build/src/core/scene/Controller.o: /usr/include/GL/freeglut_std.h
build/src/core/scene/Controller.o: /usr/include/GL/gl.h
build/src/core/scene/Controller.o: /usr/include/GL/glext.h
build/src/core/scene/Controller.o: /usr/include/inttypes.h
build/src/core/scene/Controller.o: /usr/include/features.h
build/src/core/scene/Controller.o: /usr/include/bits/predefs.h
build/src/core/scene/Controller.o: /usr/include/sys/cdefs.h
build/src/core/scene/Controller.o: /usr/include/bits/wordsize.h
build/src/core/scene/Controller.o: /usr/include/gnu/stubs.h
build/src/core/scene/Controller.o: /usr/include/gnu/stubs-64.h
build/src/core/scene/Controller.o: /usr/include/stdint.h
build/src/core/scene/Controller.o: /usr/include/bits/wchar.h
build/src/core/scene/Controller.o: /usr/include/GL/glu.h
build/src/core/scene/Controller.o: /usr/include/stdlib.h
build/src/core/scene/Controller.o: /usr/include/bits/waitflags.h
build/src/core/scene/Controller.o: /usr/include/bits/waitstatus.h
build/src/core/scene/Controller.o: /usr/include/endian.h
build/src/core/scene/Controller.o: /usr/include/bits/endian.h
build/src/core/scene/Controller.o: /usr/include/bits/byteswap.h
build/src/core/scene/Controller.o: /usr/include/sys/types.h
build/src/core/scene/Controller.o: /usr/include/bits/types.h
build/src/core/scene/Controller.o: /usr/include/bits/typesizes.h
build/src/core/scene/Controller.o: /usr/include/time.h
build/src/core/scene/Controller.o: /usr/include/sys/select.h
build/src/core/scene/Controller.o: /usr/include/bits/select.h
build/src/core/scene/Controller.o: /usr/include/bits/sigset.h
build/src/core/scene/Controller.o: /usr/include/bits/time.h
build/src/core/scene/Controller.o: /usr/include/sys/sysmacros.h
build/src/core/scene/Controller.o: /usr/include/bits/pthreadtypes.h
build/src/core/scene/Controller.o: /usr/include/alloca.h
build/src/core/scene/Controller.o: /usr/include/GL/freeglut_ext.h
build/src/core/scene/Controller.o: src/core/scene/states/State.h
build/src/core/scene/Controller.o: src/core/camera/Camera.h
build/src/core/scene/Controller.o: src/core/scene/Ray.h
build/src/core/scene/Controller.o: src/core/scene/Plane.h
build/src/core/scene/Controller.o: src/core/scene/LineSegment.h
build/src/core/scene/Controller.o: src/core/math/Quaternion.h
build/src/core/scene/Controller.o: src/core/math/Matrices.h
build/src/core/scene/Controller.o: src/core/math/Vectors.h src/impl/Utility.h
build/src/core/scene/Controller.o: /usr/include/stdio.h /usr/include/libio.h
build/src/core/scene/Controller.o: /usr/include/_G_config.h
build/src/core/scene/Controller.o: /usr/include/wchar.h
build/src/core/scene/Controller.o: /usr/include/bits/stdio_lim.h
build/src/core/scene/Controller.o: /usr/include/bits/sys_errlist.h
build/src/core/scene/Controller.o: src/core/scene/Scene.h
build/src/core/scene/Controller.o: src/core/scene/Ray.h src/core/UI/UI.h
build/src/core/scene/Controller.o: src/core/UI/UINode.h /usr/include/string.h
build/src/core/scene/Controller.o: /usr/include/xlocale.h
build/src/core/scene/Controller.o: src/core/UI/UIButton.h
build/src/core/scene/Controller.o: src/core/UI/UIRadioButton.h
build/src/core/scene/Controller.o: src/core/UI/UILabel.h
build/src/core/scene/Controller.o: src/core/texture/g2Images.h
build/src/core/scene/Controller.o: src/core/texture/stb_image.h
build/src/core/scene/LineSegment.o: src/core/scene/LineSegment.h
build/src/core/scene/LineSegment.o: src/core/math/Vectors.h
build/src/core/scene/LineSegment.o: /usr/include/GL/freeglut.h
build/src/core/scene/LineSegment.o: /usr/include/GL/freeglut_std.h
build/src/core/scene/LineSegment.o: /usr/include/GL/gl.h
build/src/core/scene/LineSegment.o: /usr/include/GL/glext.h
build/src/core/scene/LineSegment.o: /usr/include/inttypes.h
build/src/core/scene/LineSegment.o: /usr/include/features.h
build/src/core/scene/LineSegment.o: /usr/include/bits/predefs.h
build/src/core/scene/LineSegment.o: /usr/include/sys/cdefs.h
build/src/core/scene/LineSegment.o: /usr/include/bits/wordsize.h
build/src/core/scene/LineSegment.o: /usr/include/gnu/stubs.h
build/src/core/scene/LineSegment.o: /usr/include/gnu/stubs-64.h
build/src/core/scene/LineSegment.o: /usr/include/stdint.h
build/src/core/scene/LineSegment.o: /usr/include/bits/wchar.h
build/src/core/scene/LineSegment.o: /usr/include/GL/glu.h
build/src/core/scene/LineSegment.o: /usr/include/stdlib.h
build/src/core/scene/LineSegment.o: /usr/include/bits/waitflags.h
build/src/core/scene/LineSegment.o: /usr/include/bits/waitstatus.h
build/src/core/scene/LineSegment.o: /usr/include/endian.h
build/src/core/scene/LineSegment.o: /usr/include/bits/endian.h
build/src/core/scene/LineSegment.o: /usr/include/bits/byteswap.h
build/src/core/scene/LineSegment.o: /usr/include/sys/types.h
build/src/core/scene/LineSegment.o: /usr/include/bits/types.h
build/src/core/scene/LineSegment.o: /usr/include/bits/typesizes.h
build/src/core/scene/LineSegment.o: /usr/include/time.h
build/src/core/scene/LineSegment.o: /usr/include/sys/select.h
build/src/core/scene/LineSegment.o: /usr/include/bits/select.h
build/src/core/scene/LineSegment.o: /usr/include/bits/sigset.h
build/src/core/scene/LineSegment.o: /usr/include/bits/time.h
build/src/core/scene/LineSegment.o: /usr/include/sys/sysmacros.h
build/src/core/scene/LineSegment.o: /usr/include/bits/pthreadtypes.h
build/src/core/scene/LineSegment.o: /usr/include/alloca.h
build/src/core/scene/LineSegment.o: /usr/include/GL/freeglut_ext.h
build/src/core/scene/Plane.o: /usr/include/GL/freeglut.h
build/src/core/scene/Plane.o: /usr/include/GL/freeglut_std.h
build/src/core/scene/Plane.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
build/src/core/scene/Plane.o: /usr/include/inttypes.h /usr/include/features.h
build/src/core/scene/Plane.o: /usr/include/bits/predefs.h
build/src/core/scene/Plane.o: /usr/include/sys/cdefs.h
build/src/core/scene/Plane.o: /usr/include/bits/wordsize.h
build/src/core/scene/Plane.o: /usr/include/gnu/stubs.h
build/src/core/scene/Plane.o: /usr/include/gnu/stubs-64.h
build/src/core/scene/Plane.o: /usr/include/stdint.h /usr/include/bits/wchar.h
build/src/core/scene/Plane.o: /usr/include/GL/glu.h /usr/include/stdlib.h
build/src/core/scene/Plane.o: /usr/include/bits/waitflags.h
build/src/core/scene/Plane.o: /usr/include/bits/waitstatus.h
build/src/core/scene/Plane.o: /usr/include/endian.h
build/src/core/scene/Plane.o: /usr/include/bits/endian.h
build/src/core/scene/Plane.o: /usr/include/bits/byteswap.h
build/src/core/scene/Plane.o: /usr/include/sys/types.h
build/src/core/scene/Plane.o: /usr/include/bits/types.h
build/src/core/scene/Plane.o: /usr/include/bits/typesizes.h
build/src/core/scene/Plane.o: /usr/include/time.h /usr/include/sys/select.h
build/src/core/scene/Plane.o: /usr/include/bits/select.h
build/src/core/scene/Plane.o: /usr/include/bits/sigset.h
build/src/core/scene/Plane.o: /usr/include/bits/time.h
build/src/core/scene/Plane.o: /usr/include/sys/sysmacros.h
build/src/core/scene/Plane.o: /usr/include/bits/pthreadtypes.h
build/src/core/scene/Plane.o: /usr/include/alloca.h
build/src/core/scene/Plane.o: /usr/include/GL/freeglut_ext.h
build/src/core/scene/Plane.o: src/core/scene/Plane.h
build/src/core/scene/Scene.o: src/core/scene/Scene.h src/core/scene/Ray.h
build/src/core/scene/Scene.o: src/core/scene/Plane.h src/core/math/Vectors.h
build/src/core/scene/Scene.o: src/core/scene/LineSegment.h
build/src/core/scene/Scene.o: /usr/include/GL/freeglut.h
build/src/core/scene/Scene.o: /usr/include/GL/freeglut_std.h
build/src/core/scene/Scene.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
build/src/core/scene/Scene.o: /usr/include/inttypes.h /usr/include/features.h
build/src/core/scene/Scene.o: /usr/include/bits/predefs.h
build/src/core/scene/Scene.o: /usr/include/sys/cdefs.h
build/src/core/scene/Scene.o: /usr/include/bits/wordsize.h
build/src/core/scene/Scene.o: /usr/include/gnu/stubs.h
build/src/core/scene/Scene.o: /usr/include/gnu/stubs-64.h
build/src/core/scene/Scene.o: /usr/include/stdint.h /usr/include/bits/wchar.h
build/src/core/scene/Scene.o: /usr/include/GL/glu.h /usr/include/stdlib.h
build/src/core/scene/Scene.o: /usr/include/bits/waitflags.h
build/src/core/scene/Scene.o: /usr/include/bits/waitstatus.h
build/src/core/scene/Scene.o: /usr/include/endian.h
build/src/core/scene/Scene.o: /usr/include/bits/endian.h
build/src/core/scene/Scene.o: /usr/include/bits/byteswap.h
build/src/core/scene/Scene.o: /usr/include/sys/types.h
build/src/core/scene/Scene.o: /usr/include/bits/types.h
build/src/core/scene/Scene.o: /usr/include/bits/typesizes.h
build/src/core/scene/Scene.o: /usr/include/time.h /usr/include/sys/select.h
build/src/core/scene/Scene.o: /usr/include/bits/select.h
build/src/core/scene/Scene.o: /usr/include/bits/sigset.h
build/src/core/scene/Scene.o: /usr/include/bits/time.h
build/src/core/scene/Scene.o: /usr/include/sys/sysmacros.h
build/src/core/scene/Scene.o: /usr/include/bits/pthreadtypes.h
build/src/core/scene/Scene.o: /usr/include/alloca.h
build/src/core/scene/Scene.o: /usr/include/GL/freeglut_ext.h
build/src/core/scene/states/State.o: src/core/scene/states/State.h
build/src/core/scene/states/State.o: /usr/include/GL/freeglut.h
build/src/core/scene/states/State.o: /usr/include/GL/freeglut_std.h
build/src/core/scene/states/State.o: /usr/include/GL/gl.h
build/src/core/scene/states/State.o: /usr/include/GL/glext.h
build/src/core/scene/states/State.o: /usr/include/inttypes.h
build/src/core/scene/states/State.o: /usr/include/features.h
build/src/core/scene/states/State.o: /usr/include/bits/predefs.h
build/src/core/scene/states/State.o: /usr/include/sys/cdefs.h
build/src/core/scene/states/State.o: /usr/include/bits/wordsize.h
build/src/core/scene/states/State.o: /usr/include/gnu/stubs.h
build/src/core/scene/states/State.o: /usr/include/gnu/stubs-64.h
build/src/core/scene/states/State.o: /usr/include/stdint.h
build/src/core/scene/states/State.o: /usr/include/bits/wchar.h
build/src/core/scene/states/State.o: /usr/include/GL/glu.h
build/src/core/scene/states/State.o: /usr/include/stdlib.h
build/src/core/scene/states/State.o: /usr/include/bits/waitflags.h
build/src/core/scene/states/State.o: /usr/include/bits/waitstatus.h
build/src/core/scene/states/State.o: /usr/include/endian.h
build/src/core/scene/states/State.o: /usr/include/bits/endian.h
build/src/core/scene/states/State.o: /usr/include/bits/byteswap.h
build/src/core/scene/states/State.o: /usr/include/sys/types.h
build/src/core/scene/states/State.o: /usr/include/bits/types.h
build/src/core/scene/states/State.o: /usr/include/bits/typesizes.h
build/src/core/scene/states/State.o: /usr/include/time.h
build/src/core/scene/states/State.o: /usr/include/sys/select.h
build/src/core/scene/states/State.o: /usr/include/bits/select.h
build/src/core/scene/states/State.o: /usr/include/bits/sigset.h
build/src/core/scene/states/State.o: /usr/include/bits/time.h
build/src/core/scene/states/State.o: /usr/include/sys/sysmacros.h
build/src/core/scene/states/State.o: /usr/include/bits/pthreadtypes.h
build/src/core/scene/states/State.o: /usr/include/alloca.h
build/src/core/scene/states/State.o: /usr/include/GL/freeglut_ext.h
build/src/core/scene/states/State.o: src/core/math/Vectors.h
build/src/core/scene/states/State.o: src/core/scene/LineSegment.h
build/src/core/scene/states/State.o: src/core/scene/Controller.h
build/src/core/scene/states/State.o: src/core/scene/Plane.h
build/src/core/scene/states/State.o: src/core/scene/Scene.h
build/src/core/scene/states/State.o: src/core/scene/Ray.h
build/src/core/UI/UIButton.o: src/core/UI/UIButton.h src/core/UI/UINode.h
build/src/core/UI/UIButton.o: /usr/include/GL/freeglut.h
build/src/core/UI/UIButton.o: /usr/include/GL/freeglut_std.h
build/src/core/UI/UIButton.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
build/src/core/UI/UIButton.o: /usr/include/inttypes.h /usr/include/features.h
build/src/core/UI/UIButton.o: /usr/include/bits/predefs.h
build/src/core/UI/UIButton.o: /usr/include/sys/cdefs.h
build/src/core/UI/UIButton.o: /usr/include/bits/wordsize.h
build/src/core/UI/UIButton.o: /usr/include/gnu/stubs.h
build/src/core/UI/UIButton.o: /usr/include/gnu/stubs-64.h
build/src/core/UI/UIButton.o: /usr/include/stdint.h /usr/include/bits/wchar.h
build/src/core/UI/UIButton.o: /usr/include/GL/glu.h /usr/include/stdlib.h
build/src/core/UI/UIButton.o: /usr/include/bits/waitflags.h
build/src/core/UI/UIButton.o: /usr/include/bits/waitstatus.h
build/src/core/UI/UIButton.o: /usr/include/endian.h
build/src/core/UI/UIButton.o: /usr/include/bits/endian.h
build/src/core/UI/UIButton.o: /usr/include/bits/byteswap.h
build/src/core/UI/UIButton.o: /usr/include/sys/types.h
build/src/core/UI/UIButton.o: /usr/include/bits/types.h
build/src/core/UI/UIButton.o: /usr/include/bits/typesizes.h
build/src/core/UI/UIButton.o: /usr/include/time.h /usr/include/sys/select.h
build/src/core/UI/UIButton.o: /usr/include/bits/select.h
build/src/core/UI/UIButton.o: /usr/include/bits/sigset.h
build/src/core/UI/UIButton.o: /usr/include/bits/time.h
build/src/core/UI/UIButton.o: /usr/include/sys/sysmacros.h
build/src/core/UI/UIButton.o: /usr/include/bits/pthreadtypes.h
build/src/core/UI/UIButton.o: /usr/include/alloca.h
build/src/core/UI/UIButton.o: /usr/include/GL/freeglut_ext.h
build/src/core/UI/UIButton.o: /usr/include/string.h /usr/include/xlocale.h
build/src/core/UI/UIButton.o: /usr/include/math.h
build/src/core/UI/UIButton.o: /usr/include/bits/huge_val.h
build/src/core/UI/UIButton.o: /usr/include/bits/huge_valf.h
build/src/core/UI/UIButton.o: /usr/include/bits/huge_vall.h
build/src/core/UI/UIButton.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
build/src/core/UI/UIButton.o: /usr/include/bits/mathdef.h
build/src/core/UI/UIButton.o: /usr/include/bits/mathcalls.h
build/src/core/UI/UIButton.o: src/core/math/Vectors.h
build/src/core/UI/UI.o: /usr/include/GL/freeglut.h
build/src/core/UI/UI.o: /usr/include/GL/freeglut_std.h /usr/include/GL/gl.h
build/src/core/UI/UI.o: /usr/include/GL/glext.h /usr/include/inttypes.h
build/src/core/UI/UI.o: /usr/include/features.h /usr/include/bits/predefs.h
build/src/core/UI/UI.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
build/src/core/UI/UI.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
build/src/core/UI/UI.o: /usr/include/stdint.h /usr/include/bits/wchar.h
build/src/core/UI/UI.o: /usr/include/GL/glu.h /usr/include/stdlib.h
build/src/core/UI/UI.o: /usr/include/bits/waitflags.h
build/src/core/UI/UI.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
build/src/core/UI/UI.o: /usr/include/bits/endian.h
build/src/core/UI/UI.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
build/src/core/UI/UI.o: /usr/include/bits/types.h
build/src/core/UI/UI.o: /usr/include/bits/typesizes.h /usr/include/time.h
build/src/core/UI/UI.o: /usr/include/sys/select.h /usr/include/bits/select.h
build/src/core/UI/UI.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
build/src/core/UI/UI.o: /usr/include/sys/sysmacros.h
build/src/core/UI/UI.o: /usr/include/bits/pthreadtypes.h
build/src/core/UI/UI.o: /usr/include/alloca.h /usr/include/GL/freeglut_ext.h
build/src/core/UI/UI.o: src/core/UI/UI.h src/core/UI/UINode.h
build/src/core/UI/UI.o: /usr/include/string.h /usr/include/xlocale.h
build/src/core/UI/UI.o: src/core/UI/UIButton.h src/core/UI/UIRadioButton.h
build/src/core/UI/UI.o: src/core/UI/UILabel.h
build/src/core/UI/UILabel.o: src/core/UI/UILabel.h src/core/UI/UINode.h
build/src/core/UI/UILabel.o: /usr/include/GL/freeglut.h
build/src/core/UI/UILabel.o: /usr/include/GL/freeglut_std.h
build/src/core/UI/UILabel.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
build/src/core/UI/UILabel.o: /usr/include/inttypes.h /usr/include/features.h
build/src/core/UI/UILabel.o: /usr/include/bits/predefs.h
build/src/core/UI/UILabel.o: /usr/include/sys/cdefs.h
build/src/core/UI/UILabel.o: /usr/include/bits/wordsize.h
build/src/core/UI/UILabel.o: /usr/include/gnu/stubs.h
build/src/core/UI/UILabel.o: /usr/include/gnu/stubs-64.h
build/src/core/UI/UILabel.o: /usr/include/stdint.h /usr/include/bits/wchar.h
build/src/core/UI/UILabel.o: /usr/include/GL/glu.h /usr/include/stdlib.h
build/src/core/UI/UILabel.o: /usr/include/bits/waitflags.h
build/src/core/UI/UILabel.o: /usr/include/bits/waitstatus.h
build/src/core/UI/UILabel.o: /usr/include/endian.h /usr/include/bits/endian.h
build/src/core/UI/UILabel.o: /usr/include/bits/byteswap.h
build/src/core/UI/UILabel.o: /usr/include/sys/types.h
build/src/core/UI/UILabel.o: /usr/include/bits/types.h
build/src/core/UI/UILabel.o: /usr/include/bits/typesizes.h
build/src/core/UI/UILabel.o: /usr/include/time.h /usr/include/sys/select.h
build/src/core/UI/UILabel.o: /usr/include/bits/select.h
build/src/core/UI/UILabel.o: /usr/include/bits/sigset.h
build/src/core/UI/UILabel.o: /usr/include/bits/time.h
build/src/core/UI/UILabel.o: /usr/include/sys/sysmacros.h
build/src/core/UI/UILabel.o: /usr/include/bits/pthreadtypes.h
build/src/core/UI/UILabel.o: /usr/include/alloca.h
build/src/core/UI/UILabel.o: /usr/include/GL/freeglut_ext.h
build/src/core/UI/UILabel.o: /usr/include/string.h /usr/include/xlocale.h
build/src/core/UI/UINode.o: src/core/UI/UINode.h /usr/include/GL/freeglut.h
build/src/core/UI/UINode.o: /usr/include/GL/freeglut_std.h
build/src/core/UI/UINode.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
build/src/core/UI/UINode.o: /usr/include/inttypes.h /usr/include/features.h
build/src/core/UI/UINode.o: /usr/include/bits/predefs.h
build/src/core/UI/UINode.o: /usr/include/sys/cdefs.h
build/src/core/UI/UINode.o: /usr/include/bits/wordsize.h
build/src/core/UI/UINode.o: /usr/include/gnu/stubs.h
build/src/core/UI/UINode.o: /usr/include/gnu/stubs-64.h /usr/include/stdint.h
build/src/core/UI/UINode.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
build/src/core/UI/UINode.o: /usr/include/stdlib.h
build/src/core/UI/UINode.o: /usr/include/bits/waitflags.h
build/src/core/UI/UINode.o: /usr/include/bits/waitstatus.h
build/src/core/UI/UINode.o: /usr/include/endian.h /usr/include/bits/endian.h
build/src/core/UI/UINode.o: /usr/include/bits/byteswap.h
build/src/core/UI/UINode.o: /usr/include/sys/types.h
build/src/core/UI/UINode.o: /usr/include/bits/types.h
build/src/core/UI/UINode.o: /usr/include/bits/typesizes.h /usr/include/time.h
build/src/core/UI/UINode.o: /usr/include/sys/select.h
build/src/core/UI/UINode.o: /usr/include/bits/select.h
build/src/core/UI/UINode.o: /usr/include/bits/sigset.h
build/src/core/UI/UINode.o: /usr/include/bits/time.h
build/src/core/UI/UINode.o: /usr/include/sys/sysmacros.h
build/src/core/UI/UINode.o: /usr/include/bits/pthreadtypes.h
build/src/core/UI/UINode.o: /usr/include/alloca.h
build/src/core/UI/UINode.o: /usr/include/GL/freeglut_ext.h
build/src/core/UI/UINode.o: /usr/include/string.h /usr/include/xlocale.h
build/src/core/UI/UIRadioButton.o: src/core/UI/UIRadioButton.h
build/src/core/UI/UIRadioButton.o: src/core/UI/UINode.h
build/src/core/UI/UIRadioButton.o: /usr/include/GL/freeglut.h
build/src/core/UI/UIRadioButton.o: /usr/include/GL/freeglut_std.h
build/src/core/UI/UIRadioButton.o: /usr/include/GL/gl.h
build/src/core/UI/UIRadioButton.o: /usr/include/GL/glext.h
build/src/core/UI/UIRadioButton.o: /usr/include/inttypes.h
build/src/core/UI/UIRadioButton.o: /usr/include/features.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/predefs.h
build/src/core/UI/UIRadioButton.o: /usr/include/sys/cdefs.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/wordsize.h
build/src/core/UI/UIRadioButton.o: /usr/include/gnu/stubs.h
build/src/core/UI/UIRadioButton.o: /usr/include/gnu/stubs-64.h
build/src/core/UI/UIRadioButton.o: /usr/include/stdint.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/wchar.h
build/src/core/UI/UIRadioButton.o: /usr/include/GL/glu.h
build/src/core/UI/UIRadioButton.o: /usr/include/stdlib.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/waitflags.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/waitstatus.h
build/src/core/UI/UIRadioButton.o: /usr/include/endian.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/endian.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/byteswap.h
build/src/core/UI/UIRadioButton.o: /usr/include/sys/types.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/types.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/typesizes.h
build/src/core/UI/UIRadioButton.o: /usr/include/time.h
build/src/core/UI/UIRadioButton.o: /usr/include/sys/select.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/select.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/sigset.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/time.h
build/src/core/UI/UIRadioButton.o: /usr/include/sys/sysmacros.h
build/src/core/UI/UIRadioButton.o: /usr/include/bits/pthreadtypes.h
build/src/core/UI/UIRadioButton.o: /usr/include/alloca.h
build/src/core/UI/UIRadioButton.o: /usr/include/GL/freeglut_ext.h
build/src/core/UI/UIRadioButton.o: /usr/include/string.h
build/src/core/UI/UIRadioButton.o: /usr/include/xlocale.h
build/src/core/texture/g2Images.o: src/core/texture/g2Images.h
build/src/core/texture/g2Images.o: src/core/texture/stb_image.h
build/src/core/texture/g2Images.o: /usr/include/stdio.h
build/src/core/texture/g2Images.o: /usr/include/features.h
build/src/core/texture/g2Images.o: /usr/include/bits/predefs.h
build/src/core/texture/g2Images.o: /usr/include/sys/cdefs.h
build/src/core/texture/g2Images.o: /usr/include/bits/wordsize.h
build/src/core/texture/g2Images.o: /usr/include/gnu/stubs.h
build/src/core/texture/g2Images.o: /usr/include/gnu/stubs-64.h
build/src/core/texture/g2Images.o: /usr/include/bits/types.h
build/src/core/texture/g2Images.o: /usr/include/bits/typesizes.h
build/src/core/texture/g2Images.o: /usr/include/libio.h
build/src/core/texture/g2Images.o: /usr/include/_G_config.h
build/src/core/texture/g2Images.o: /usr/include/wchar.h
build/src/core/texture/g2Images.o: /usr/include/bits/stdio_lim.h
build/src/core/texture/g2Images.o: /usr/include/bits/sys_errlist.h
build/src/core/texture/g2Images.o: /usr/include/GL/freeglut.h
build/src/core/texture/g2Images.o: /usr/include/GL/freeglut_std.h
build/src/core/texture/g2Images.o: /usr/include/GL/gl.h
build/src/core/texture/g2Images.o: /usr/include/GL/glext.h
build/src/core/texture/g2Images.o: /usr/include/inttypes.h
build/src/core/texture/g2Images.o: /usr/include/stdint.h
build/src/core/texture/g2Images.o: /usr/include/bits/wchar.h
build/src/core/texture/g2Images.o: /usr/include/GL/glu.h
build/src/core/texture/g2Images.o: /usr/include/stdlib.h
build/src/core/texture/g2Images.o: /usr/include/bits/waitflags.h
build/src/core/texture/g2Images.o: /usr/include/bits/waitstatus.h
build/src/core/texture/g2Images.o: /usr/include/endian.h
build/src/core/texture/g2Images.o: /usr/include/bits/endian.h
build/src/core/texture/g2Images.o: /usr/include/bits/byteswap.h
build/src/core/texture/g2Images.o: /usr/include/sys/types.h
build/src/core/texture/g2Images.o: /usr/include/time.h
build/src/core/texture/g2Images.o: /usr/include/sys/select.h
build/src/core/texture/g2Images.o: /usr/include/bits/select.h
build/src/core/texture/g2Images.o: /usr/include/bits/sigset.h
build/src/core/texture/g2Images.o: /usr/include/bits/time.h
build/src/core/texture/g2Images.o: /usr/include/sys/sysmacros.h
build/src/core/texture/g2Images.o: /usr/include/bits/pthreadtypes.h
build/src/core/texture/g2Images.o: /usr/include/alloca.h
build/src/core/texture/g2Images.o: /usr/include/GL/freeglut_ext.h
build/src/core/texture/g2Images.o: /usr/include/string.h
build/src/core/texture/g2Images.o: /usr/include/xlocale.h
build/src/core/texture/stb_image.o: src/core/texture/stb_image.h
build/src/core/texture/stb_image.o: /usr/include/stdio.h
build/src/core/texture/stb_image.o: /usr/include/features.h
build/src/core/texture/stb_image.o: /usr/include/bits/predefs.h
build/src/core/texture/stb_image.o: /usr/include/sys/cdefs.h
build/src/core/texture/stb_image.o: /usr/include/bits/wordsize.h
build/src/core/texture/stb_image.o: /usr/include/gnu/stubs.h
build/src/core/texture/stb_image.o: /usr/include/gnu/stubs-64.h
build/src/core/texture/stb_image.o: /usr/include/bits/types.h
build/src/core/texture/stb_image.o: /usr/include/bits/typesizes.h
build/src/core/texture/stb_image.o: /usr/include/libio.h
build/src/core/texture/stb_image.o: /usr/include/_G_config.h
build/src/core/texture/stb_image.o: /usr/include/wchar.h
build/src/core/texture/stb_image.o: /usr/include/bits/stdio_lim.h
build/src/core/texture/stb_image.o: /usr/include/bits/sys_errlist.h
build/src/core/texture/stb_image.o: /usr/include/math.h
build/src/core/texture/stb_image.o: /usr/include/bits/huge_val.h
build/src/core/texture/stb_image.o: /usr/include/bits/huge_valf.h
build/src/core/texture/stb_image.o: /usr/include/bits/huge_vall.h
build/src/core/texture/stb_image.o: /usr/include/bits/inf.h
build/src/core/texture/stb_image.o: /usr/include/bits/nan.h
build/src/core/texture/stb_image.o: /usr/include/bits/mathdef.h
build/src/core/texture/stb_image.o: /usr/include/bits/mathcalls.h
build/src/core/texture/stb_image.o: /usr/include/string.h
build/src/core/texture/stb_image.o: /usr/include/xlocale.h
build/src/core/texture/stb_image.o: /usr/include/stdlib.h
build/src/core/texture/stb_image.o: /usr/include/bits/waitflags.h
build/src/core/texture/stb_image.o: /usr/include/bits/waitstatus.h
build/src/core/texture/stb_image.o: /usr/include/endian.h
build/src/core/texture/stb_image.o: /usr/include/bits/endian.h
build/src/core/texture/stb_image.o: /usr/include/bits/byteswap.h
build/src/core/texture/stb_image.o: /usr/include/sys/types.h
build/src/core/texture/stb_image.o: /usr/include/time.h
build/src/core/texture/stb_image.o: /usr/include/sys/select.h
build/src/core/texture/stb_image.o: /usr/include/bits/select.h
build/src/core/texture/stb_image.o: /usr/include/bits/sigset.h
build/src/core/texture/stb_image.o: /usr/include/bits/time.h
build/src/core/texture/stb_image.o: /usr/include/sys/sysmacros.h
build/src/core/texture/stb_image.o: /usr/include/bits/pthreadtypes.h
build/src/core/texture/stb_image.o: /usr/include/alloca.h
build/src/core/texture/stb_image.o: /usr/include/memory.h
build/src/core/texture/stb_image.o: /usr/include/assert.h
build/src/impl/main.o: /usr/include/stdio.h /usr/include/features.h
build/src/impl/main.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
build/src/impl/main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
build/src/impl/main.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
build/src/impl/main.o: /usr/include/bits/typesizes.h /usr/include/libio.h
build/src/impl/main.o: /usr/include/_G_config.h /usr/include/wchar.h
build/src/impl/main.o: /usr/include/bits/stdio_lim.h
build/src/impl/main.o: /usr/include/bits/sys_errlist.h /usr/include/GL/glut.h
build/src/impl/main.o: /usr/include/GL/freeglut_std.h /usr/include/GL/gl.h
build/src/impl/main.o: /usr/include/GL/glext.h /usr/include/inttypes.h
build/src/impl/main.o: /usr/include/stdint.h /usr/include/bits/wchar.h
build/src/impl/main.o: /usr/include/GL/glu.h /usr/include/stdlib.h
build/src/impl/main.o: /usr/include/bits/waitflags.h
build/src/impl/main.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
build/src/impl/main.o: /usr/include/bits/endian.h
build/src/impl/main.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
build/src/impl/main.o: /usr/include/time.h /usr/include/sys/select.h
build/src/impl/main.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
build/src/impl/main.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
build/src/impl/main.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
build/src/impl/main.o: src/core/scene/Ray.h src/core/math/Vectors.h
build/src/impl/main.o: src/core/scene/Plane.h src/core/scene/Scene.h
build/src/impl/main.o: src/core/scene/Ray.h src/core/scene/Plane.h
build/src/impl/main.o: src/core/scene/LineSegment.h src/impl/Utility.h
build/src/impl/main.o: src/core/scene/Controller.h /usr/include/GL/freeglut.h
build/src/impl/main.o: /usr/include/GL/freeglut_ext.h src/core/UI/UI.h
build/src/impl/main.o: src/core/UI/UINode.h /usr/include/string.h
build/src/impl/main.o: /usr/include/xlocale.h src/core/UI/UIButton.h
build/src/impl/main.o: src/core/UI/UIRadioButton.h src/core/UI/UILabel.h
build/src/impl/main.o: src/core/UI/UINode.h src/core/UI/UIButton.h
build/src/impl/main.o: /usr/include/math.h /usr/include/bits/huge_val.h
build/src/impl/main.o: /usr/include/bits/huge_valf.h
build/src/impl/main.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
build/src/impl/main.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
build/src/impl/main.o: /usr/include/bits/mathcalls.h
build/src/impl/Utility.o: src/impl/Utility.h /usr/include/stdio.h
build/src/impl/Utility.o: /usr/include/features.h /usr/include/bits/predefs.h
build/src/impl/Utility.o: /usr/include/sys/cdefs.h
build/src/impl/Utility.o: /usr/include/bits/wordsize.h
build/src/impl/Utility.o: /usr/include/gnu/stubs.h
build/src/impl/Utility.o: /usr/include/gnu/stubs-64.h
build/src/impl/Utility.o: /usr/include/bits/types.h
build/src/impl/Utility.o: /usr/include/bits/typesizes.h /usr/include/libio.h
build/src/impl/Utility.o: /usr/include/_G_config.h /usr/include/wchar.h
build/src/impl/Utility.o: /usr/include/bits/stdio_lim.h
build/src/impl/Utility.o: /usr/include/bits/sys_errlist.h
build/src/impl/Utility.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
build/src/impl/Utility.o: /usr/include/bits/waitstatus.h
build/src/impl/Utility.o: /usr/include/endian.h /usr/include/bits/endian.h
build/src/impl/Utility.o: /usr/include/bits/byteswap.h
build/src/impl/Utility.o: /usr/include/sys/types.h /usr/include/time.h
build/src/impl/Utility.o: /usr/include/sys/select.h
build/src/impl/Utility.o: /usr/include/bits/select.h
build/src/impl/Utility.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
build/src/impl/Utility.o: /usr/include/sys/sysmacros.h
build/src/impl/Utility.o: /usr/include/bits/pthreadtypes.h
build/src/impl/Utility.o: /usr/include/alloca.h
