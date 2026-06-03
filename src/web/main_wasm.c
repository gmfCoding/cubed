typedef struct s_web_game
{
	float	px;
	float	py;
	float	angle;
	float	speed;
	int		width;
	int		height;
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
}t_web_game;

static t_web_game	g;

static float	clampf(float v, float min, float max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

void	init_game(int width, int height)
{
	g.width = width;
	g.height = height;
	g.px = (float)width * 0.5f;
	g.py = (float)height * 0.5f;
	g.angle = 0.0f;
	g.speed = 180.0f;
	g.key_w = 0;
	g.key_a = 0;
	g.key_s = 0;
	g.key_d = 0;
	g.key_left = 0;
	g.key_right = 0;
}

void	set_viewport(int width, int height)
{
	g.width = width;
	g.height = height;
	g.px = clampf(g.px, 0.0f, (float)width);
	g.py = clampf(g.py, 0.0f, (float)height);
}

void	key_down(int code)
{
	if (code == 87)
		g.key_w = 1;
	if (code == 65)
		g.key_a = 1;
	if (code == 83)
		g.key_s = 1;
	if (code == 68)
		g.key_d = 1;
	if (code == 37)
		g.key_left = 1;
	if (code == 39)
		g.key_right = 1;
}

void	key_up(int code)
{
	if (code == 87)
		g.key_w = 0;
	if (code == 65)
		g.key_a = 0;
	if (code == 83)
		g.key_s = 0;
	if (code == 68)
		g.key_d = 0;
	if (code == 37)
		g.key_left = 0;
	if (code == 39)
		g.key_right = 0;
}

void	update_game(float dt)
{
	float	dx;
	float	dy;

	dx = 0.0f;
	dy = 0.0f;
	if (g.key_w)
		dy -= g.speed * dt;
	if (g.key_s)
		dy += g.speed * dt;
	if (g.key_a)
		dx -= g.speed * dt;
	if (g.key_d)
		dx += g.speed * dt;
	if (g.key_left)
		g.angle -= 2.4f * dt;
	if (g.key_right)
		g.angle += 2.4f * dt;
	g.px = clampf(g.px + dx, 0.0f, (float)g.width);
	g.py = clampf(g.py + dy, 0.0f, (float)g.height);
}

float	get_player_x(void)
{
	return (g.px);
}

float	get_player_y(void)
{
	return (g.py);
}

float	get_player_angle(void)
{
	return (g.angle);
}

float	get_player_speed(void)
{
	return (g.speed);
}
