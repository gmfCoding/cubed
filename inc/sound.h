#ifndef SOUND_H
# define SOUND_H


#define SFX_DOOR 0
#define SFX_GAME_01 1
#define SFX_HEARTBEAT 2
#define SFX_INTRO 3
#define SFX_ALERT 4
#define SFX_SELECT 5
#define SFX_SELECTION 6
#define SFX_SWITCH 7
#define SFX_ESTEP01 8
#define SFX_ESTEP02 9
#define SFX_ESTEP03 10
#define SFX_PSTEP01 11
#define SFX_PSTEP02 12
#define SFX_PSTEP03 13
#define SFX_PSTEP04 14
#define SFX_TASK 15
#define SFX_TASK_COMPLETE 16
#define SFX_CLANK 17
#define SFX_ORBIT 18
#define SFX_AMOUNT 19

typedef enum	e_sound_state
{
    STOP, // Sound is stopped
    PLAY, // Sound is playing
    LOOP, // Sound is playing and looping
}		t_sound_state;

typedef struct s_game t_game;
//typedef struct s_sound t_sound;
//typedef struct s_sound_manager t_sound_manager;
typedef enum e_sound_state t_sound_state;

void	sound_init(t_game *game);
void	sound_manager_deallocate(void *s_mgr);
void	play_sound(void *s_sfx, unsigned int index, t_sound_state sfc_ctrl);
void	stop_all_sound(void *s_sfx);
void	set_sound_volume(void *s_sfx, unsigned int index, double volume);

#endif
