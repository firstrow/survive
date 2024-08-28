%module game

%{
    #include "funcs.h"
    #include "entity/entity.h"
    #include "core/types.h"
    #include "core/direction.h"
    #include "input/keyboard.h"
    #include "gfx/texture.h"
    #include "gfx/animation.h"
    #include "map/map.h"
%}

%typemap(in) i32 {
	$1 = (i32) lua_tonumber(L,$input);
}

%typemap(in) i8 {
	$1 = (i8) lua_tonumber(L,$input);
}

%typemap(in) time_millis {
	$1 = (time_millis) lua_tonumber(L,$input);
}

%include "src/core/types.h"
%include "src/core/direction.h"
%include "src/entity/entity.h"
%include "src/input/keyboard.h"
%include "src/gfx/texture.h"
%include "src/gfx/animation.h"
%include "src/map/map.h"

%include "funcs.h"
