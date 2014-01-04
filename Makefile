CC        := g++
LDFLAGS   := -lGL -lGLU -lglut -lrt
CFLAGS    := 

MODULES   := src/core/camera src/core/math src/core/scene src/impl 
SRC_DIR   := $(addprefix ,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC       := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ       := $(patsubst %.cpp,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all checkdirs clean depend

all: checkdirs nextsketch

nextsketch: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@
	

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
build/src/core/camera/Camera.o: /usr/include/GL/freeglut.h
build/src/core/camera/Camera.o: /usr/include/GL/freeglut_std.h
build/src/core/camera/Camera.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
build/src/core/camera/Camera.o: /usr/include/inttypes.h
build/src/core/camera/Camera.o: /usr/include/features.h
build/src/core/camera/Camera.o: /usr/include/bits/predefs.h
build/src/core/camera/Camera.o: /usr/include/sys/cdefs.h
build/src/core/camera/Camera.o: /usr/include/bits/wordsize.h
build/src/core/camera/Camera.o: /usr/include/gnu/stubs.h
build/src/core/camera/Camera.o: /usr/include/gnu/stubs-64.h
build/src/core/camera/Camera.o: /usr/include/stdint.h
build/src/core/camera/Camera.o: /usr/include/bits/wchar.h
build/src/core/camera/Camera.o: /usr/include/GL/glu.h /usr/include/stdlib.h
build/src/core/camera/Camera.o: /usr/include/bits/waitflags.h
build/src/core/camera/Camera.o: /usr/include/bits/waitstatus.h
build/src/core/camera/Camera.o: /usr/include/endian.h
build/src/core/camera/Camera.o: /usr/include/bits/endian.h
build/src/core/camera/Camera.o: /usr/include/bits/byteswap.h
build/src/core/camera/Camera.o: /usr/include/sys/types.h
build/src/core/camera/Camera.o: /usr/include/bits/types.h
build/src/core/camera/Camera.o: /usr/include/bits/typesizes.h
build/src/core/camera/Camera.o: /usr/include/time.h /usr/include/sys/select.h
build/src/core/camera/Camera.o: /usr/include/bits/select.h
build/src/core/camera/Camera.o: /usr/include/bits/sigset.h
build/src/core/camera/Camera.o: /usr/include/bits/time.h
build/src/core/camera/Camera.o: /usr/include/sys/sysmacros.h
build/src/core/camera/Camera.o: /usr/include/bits/pthreadtypes.h
build/src/core/camera/Camera.o: /usr/include/alloca.h
build/src/core/camera/Camera.o: /usr/include/GL/freeglut_ext.h
build/src/core/math/Matrices.o: src/core/math/Matrices.h
build/src/core/math/Matrices.o: src/core/math/Vectors.h
build/src/core/math/Quaternion.o: src/core/math/Quaternion.h
build/src/core/math/Quaternion.o: src/core/math/Matrices.h
build/src/core/math/Quaternion.o: src/core/math/Vectors.h
build/src/core/scene/Controller.o: src/core/scene/Controller.h
build/src/core/scene/Controller.o: src/core/math/Vectors.h
build/src/core/scene/Controller.o: src/core/scene/Plane.h
build/src/core/scene/Controller.o: src/core/scene/LineSegment.h
build/src/core/scene/Controller.o: /usr/include/GL/glut.h
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
build/src/core/scene/Controller.o: src/core/scene/State.h
build/src/core/scene/Controller.o: src/core/camera/Camera.h
build/src/core/scene/Controller.o: src/core/scene/Scene.h
build/src/core/scene/Controller.o: src/core/scene/Ray.h
build/src/core/scene/LineSegment.o: src/core/scene/LineSegment.h
build/src/core/scene/LineSegment.o: src/core/math/Vectors.h
build/src/core/scene/LineSegment.o: /usr/include/GL/glut.h
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
build/src/core/scene/Plane.o: /usr/include/GL/glut.h
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
build/src/core/scene/Plane.o: /usr/include/alloca.h src/core/scene/Plane.h
build/src/core/scene/Plane.o: src/core/math/Vectors.h
build/src/core/scene/Scene.o: src/core/scene/Scene.h src/core/scene/Ray.h
build/src/core/scene/Scene.o: src/core/math/Vectors.h src/core/scene/Plane.h
build/src/core/scene/Scene.o: /usr/include/GL/glut.h
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
build/src/core/scene/State.o: src/core/scene/State.h /usr/include/GL/glut.h
build/src/core/scene/State.o: /usr/include/GL/freeglut_std.h
build/src/core/scene/State.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
build/src/core/scene/State.o: /usr/include/inttypes.h /usr/include/features.h
build/src/core/scene/State.o: /usr/include/bits/predefs.h
build/src/core/scene/State.o: /usr/include/sys/cdefs.h
build/src/core/scene/State.o: /usr/include/bits/wordsize.h
build/src/core/scene/State.o: /usr/include/gnu/stubs.h
build/src/core/scene/State.o: /usr/include/gnu/stubs-64.h
build/src/core/scene/State.o: /usr/include/stdint.h /usr/include/bits/wchar.h
build/src/core/scene/State.o: /usr/include/GL/glu.h /usr/include/stdlib.h
build/src/core/scene/State.o: /usr/include/bits/waitflags.h
build/src/core/scene/State.o: /usr/include/bits/waitstatus.h
build/src/core/scene/State.o: /usr/include/endian.h
build/src/core/scene/State.o: /usr/include/bits/endian.h
build/src/core/scene/State.o: /usr/include/bits/byteswap.h
build/src/core/scene/State.o: /usr/include/sys/types.h
build/src/core/scene/State.o: /usr/include/bits/types.h
build/src/core/scene/State.o: /usr/include/bits/typesizes.h
build/src/core/scene/State.o: /usr/include/time.h /usr/include/sys/select.h
build/src/core/scene/State.o: /usr/include/bits/select.h
build/src/core/scene/State.o: /usr/include/bits/sigset.h
build/src/core/scene/State.o: /usr/include/bits/time.h
build/src/core/scene/State.o: /usr/include/sys/sysmacros.h
build/src/core/scene/State.o: /usr/include/bits/pthreadtypes.h
build/src/core/scene/State.o: /usr/include/alloca.h src/core/math/Vectors.h
build/src/core/scene/State.o: src/core/scene/Controller.h
build/src/core/scene/State.o: src/core/scene/Plane.h
build/src/core/scene/State.o: src/core/scene/LineSegment.h
build/src/core/scene/State.o: src/core/camera/Camera.h src/core/scene/Scene.h
build/src/core/scene/State.o: src/core/scene/Ray.h src/core/math/Quaternion.h
build/src/core/scene/State.o: src/core/math/Matrices.h
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
build/src/impl/main.o: src/impl/Utility.h src/core/scene/Controller.h
build/src/impl/main.o: src/core/scene/LineSegment.h /usr/include/math.h
build/src/impl/main.o: /usr/include/bits/huge_val.h
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
