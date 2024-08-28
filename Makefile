run:
	# $(MAKE) -C ./build && gdb -e run ./build/survive
	$(MAKE) -C ./build && ./build/survive

swig:
	swig -lua -o ./src/lua_engine/game_wrap.c ./src/lua_engine/game.i 
	gcc -I/usr/include/lua  -I./src/ -I. -c ./src/lua_engine/game_wrap.c -o libs/swig.o
