SRCSF = $(TEST) \
		texture/texture.c \
		texture/pixel.c \
		texture/texture_util.c \
		texture/texture_blit.c \
		texture/deferred.c \
		texture/circle.c \
		vector/vector2_math_extra.c \
		vector/vector2_math_div.c \
		vector/vector2_math.c \
		vector/vector2_angle.c \
		vector/vector2_dist.c \
		vector/vector2_lerp.c \
		vector/vector2.c \
		vector/vector2i_math_extra.c \
		vector/vector2i_math.c \
		vector/vector2i.c \
		vector/vector3_math_extra.c \
		vector/vector3_math.c \
		vector/vector3_math_div.c \
		vector/vector3.c \
		vector/vector4_math.c \
		vector/vtoa.c \
		vector/vector2_conv.c \
		vector/vector3_conv.c \
		vector/rect.c \
		render/render_util.c \
		render/loop.c \
		render/floor_render.c \
		render/column_render.c \
		render/wall_render.c \
		render/line.c \
		render/rect_render.c \
		render/intersect_test.c \
		render/raycast.c \
		render/skybox.c \
		controls/controls.c \
		controls/player_controls.c \
		util/time.c \
		util/math.c \
		util/random.c \
		util/memory_utils.c \
		util/debug_functions.c \
		util/csv.c \
		util/string_utils.c \
		util/error_handler.c \
		map_parser/map_setup.c \
		map_parser/map_dimensions.c \
		map_parser/map_tile_processing.c \
		map_parser/map_tools.c \
		map_parser/map_checker_tile.c \
		map_parser/map_checker_element.c \
		map_parser/map_default_map.c \
		map_parser/map_utils.c \
		modifiers/modifier_setup.c \
		modifiers/modifier_after.c \
		modifiers/modifier_utils.c \
		modifiers/mod_func_cardinal_texture.c \
		modifiers/mod_func_fivelights.c \
		modifiers/mod_func_orbit_task.c \
		modifiers/mod_func_floor_ceiling_color.c \
		modifiers/mod_func_door_setup.c \
		modifiers/mod_func_minimap.c \
		modifiers/mod_func_alert.c \
		modifiers/mod_func_enemy.c \
		modifiers/mod_func_wincon.c \
		modifiers/mod_func_window.c \
		modifiers/mod_func_window_line.c \
		modifiers/mod_func_target_handles.c \
		modifiers/mod_func_trigger_area.c \
		mini_map/mmap_draw.c \
		mini_map/mmap_draw_anim.c \
		mini_map/mmap_image_decider.c \
		mini_map/mmap_input.c \
		mini_map/mmap_setup.c \
		mini_map/mmap_tile_assign.c \
		events/event_alert.c \
		events/event_door.c \
		events/event_five_lights.c \
		events/event_handler.c \
		events/event_orbit_task.c \
		events/event_trigger_handlers.c \
		events/event_trigger_handle_gates.c \
		events/event_trigger_handle_tasks.c \
		entities/player_setup.c \
		entities/sprite.c \
		entities/entity.c \
		entities/door.c \
		entities/enemy/enemy_go_to_target.c \
		entities/enemy/enemy_img_setup.c \
		entities/enemy/enemy_path_and_patrol.c \
		entities/enemy/enemy_routines.c \
		entities/models/orbit_task_model.c \
		a_star/a_star_path_collect.c \
		a_star/a_star_neighboring.c \
		a_star/a_star_memory.c \
		input/input.c \
		input/input_hooks.c \
		input/input_setup.c \
		input/keys.c \
		input/mouse.c \
		sound/sound_setup.c \
		sound/sound_use.c \
		task/task.c \
		task/task_fl_wrapper/task_fl_wrapper.c \
		task/five_lights/fl_setup.c \
		task/five_lights/fl_state_manage.c \
		task/five_lights/fl_state_modes.c \
		task/five_lights/fl_state_rules.c \
		task/five_lights/fl_state_rules_down.c \
		task/five_lights/fl_state_rules_up.c \
		task/orbit/sys/cart_to_kep.c \
		task/orbit/sys/ktoc_position.c \
		task/orbit/sys/ktoc_velocity.c \
		task/orbit/sys/kep_angle.c \
		task/orbit/sys/kep_angle_util.c \
		task/orbit/sys/kep_properties.c \
		task/orbit/sys/transform.c \
		task/orbit/sys/render.c \
		task/orbit/sys/render_extra.c \
		task/orbit/sys/body.c \
		task/orbit/sys/generate.c \
		task/orbit/sys/equality.c \
		task/orbit/orbit.c \
		task/orbit/mui/orbit_mui.c \
		task/mui.c \
		task/mui_process.c \
		task/mui_process_extra.c \
		task/mui_render.c \
		title/title_animation.c \
		title/title_end_screen.c \
		title/title_load_map_screen.c \
		title/title_options.c \
		title/title_setup.c \
		title/title_states.c \
		cerror.c \
		image_loader.c \
		setup_textures.c \
		destroy.c \

#		task/orbit/task2.c
# TODO: Add other headers?
INCSF = cubed.h

ifndef $(TEST)
TEST=main.c
endif

ifndef $(OS)
OS := $(shell uname)
endif

$(info Compiling for OS:$(OS))

NAME = cub3D

DIRSRC = src
DIROBJ = obj/$(CONF)
DIRINC = inc
DIRLIB = lib

LIBFT = libft/libft.a
LIBGNL = gnl/libgnl.a

ifeq ($(OS),Linux)
LIBMLX = mlx-linux/libmlx.a
else
LIBMLX = mlx/libmlx.a
endif

LIBSF = $(LIBFT) $(LIBGNL) $(LIBMLX)

# All relative to Makefile's folder
SRCS = $(patsubst %.c,$(DIRSRC)/%.c, $(SRCSF))
OBJS = $(SRCS:$(DIRSRC)/%.c=$(DIROBJ)/%.o)
LIBS = $(patsubst %.a,$(DIRLIB)/%.a, $(LIBSF)) 
INCS = $(patsubst %.h,$(DIRINC)/%.h, $(INCSF))
DEPS = $(OBJS:.o=.d)

LIB-I = $(patsubst %,-I%,$(dir $(LIBS))) -I$(DIRLIB)
LIB-l = $(subst lib,-l,$(basename $(notdir $(LIBSF))))
LIB-L = $(patsubst %,-L$(DIRLIB)/%, $(dir $(LIBSF)))

CC = cc

WFLAGS = #-Wall -Werror -Wextra
CPPFLAGS =-I$(DIRINC) $(LIB-I) -MMD -MP
CFLAGS = $(OPFLAG) $(DFLAGS) $(XCFLAGS) $(WFLAGS)
LDFLAGS = $(OPFLAG) $(DFLAGS) $(XLDFLAGS) $(LIB-L) $(LIB-l) -lz -lm -lpthread -ldl
OPFLAG = -O3 -flto -march=native -mtune=native -msse4.2 

OPTS = $(OPT)
SAN = address 

CONF = release
CONF_TARGET = .target

ifneq (,$(findstring debug,$(CONF)))
OPTS = fsan,debug
endif

ifneq (,$(findstring none,$(OPTS)))
OPFLAG = -O0
endif
ifneq (,$(findstring debug,$(OPTS)))
	OPFLAG = -O0
	DFLAGS += -g3
endif
ifneq (,$(findstring fdeb,$(OPTS)))
	OPFLAG = -O1 -march=native
	DFLAGS += -g3
endif
ifneq (,$(findstring fsan,$(OPTS)))
# -fno-sanitize-ignorelist -fsanitize-ignorelist=ignorelist.txt
# Compile with selected sanitizer:
# And when using other sanitizers such as memory or undefined, it may be useful to not prematurely stop,
# Use UBSAN_OPTIONS=halt_on_error=0 (need -fs..-recover=..) or equivelent
# Also might be nice to redirect stderr to a file
# USE 
	DFLAGS += -fsanitize=$(SAN) -fsanitize-recover=$(SAN) 
endif
ifneq (,$(findstring gmon,$(OPTS)))
	PGFLAGS += -pg
endif

ifeq ($(EXTRA),1)
CPPFLAGS += -D EXTRA
endif

ifneq ($(OS),Linux) 
LDFLAGS += -framework OpenGL -framework AppKit 
else 
LDFLAGS += -lX11 -lXext
endif

# RULES
all: $(NAME)

# EVALUATE:
# 	grep -v -q $(CONF) $(CONF_TARGET) && echo $(CONF) > $(CONF_TARGET)


# marker for the last built architecture
BUILT_MARKER := $(CONF).built

$(BUILT_MARKER):
	@-rm -f *.built
	@touch $(BUILT_MARKER)

# OBJ TO PROJECT
$(NAME): $(LIBS) $(OBJS) $(BUILT_MARKER)
	-@printf "${BLUE}"
	$(CC) $(PGFLAGS) $(OBJS) $(LDFLAGS) -o $@
	-@printf "${NC}"

# SOURCE TO OBJ
$(OBJS): $(DIROBJ)%.o : $(DIRSRC)%.c $(INCS) | $(DIROBJ)
	-@mkdir -p $(dir $@)
	-@printf "${GREEN}"
	-$(CC) $(PGFLAGS) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<
	-@printf "${NC}"

# TODO: Merge with fclean before submitting
lclean: clean
	-make -C $(dir $(DIRLIB)/$(LIBFT)) fclean
	-make -C $(dir $(DIRLIB)/$(LIBMLX)) fclean
	-make -C $(dir $(DIRLIB)/$(LIBGNL)) fclean

# CLEANING
fclean: clean
	-@printf "${BRED}Cleaning executable!\n${RED}"
	-rm -f $(NAME)
	-@printf "${NC}"

clean:
	-@printf "${BYELLOW}Cleaning objects!\n${RED}"
	-rm -rf $(DIROBJ)
	-@printf "${NC}"

re: fclean all

# Dependencies
-include $(DEPS)

$(DIRLIB)/$(LIBFT):
	make -s -C $(dir $@) all bonus DFLAGS="$(DFLAGS)"

$(DIRLIB)/$(LIBGNL):
	make -s -C $(dir $@) all DFLAGS="$(DFLAGS)"

$(DIRLIB)/$(LIBMLX):
	make -s -C $(dir $@) DFLAGS="$(DFLAGS)"

$(DIRLIB)/$(LIBMLX_SO): $(LIBMLX)
	cp $(DIRMLX)/libmlx.so ./libmlx.so

# Folders
$(DIROBJ):
	-@printf "${CYAN}"
	-mkdir -p $(DIROBJ)
	-@printf "${NC}"

.PHONY: all re fclean clean libclean

# COLORS
export BGREEN = \033[1;32m
export GREEN = \033[0;32m
export BRED = \033[1;31m
export RED = \033[0;31m
export BYELLOW = \033[1;33m
export YELLOW = \033[0;33m
export BBLUE = \033[1;34m
export BLUE = \033[0;34m
export BCYAN = \033[1;36m
export CYAN = \033[0;36m
export NC = \033[0m
