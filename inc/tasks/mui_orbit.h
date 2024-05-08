/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mui_orbit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <clovell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:35:52 by clovell           #+#    #+#             */
/*   Updated: 2024/05/08 15:32:55 by kmordaun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MUI_ORBIT_H
# define MUI_ORBIT_H
# include "mui.h"

# define ORB_MUI_BTN_MS0 0
# define ORB_MUI_BTN_MS1 1
# define ORB_MUI_BTN_MS2 2
# define ORB_MUI_BTN_MS3 3
# define ORB_MUI_BTN_MS4 4
# define ORB_MUI_BTN_APPLY 5

# define ORB_MUI_IND0 0
# define ORB_MUI_IND1 1
# define ORB_MUI_IND2 2
# define ORB_MUI_IND3 3
# define ORB_MUI_IND4 4

# define ORB_MUI_LEN_BTN 6

# define ORB_MUI_DIAL_M0 0
# define ORB_MUI_DIAL_M1 1
# define ORB_MUI_DIAL_M2 2
# define ORB_MUI_DIAL_M3 3
# define ORB_MUI_DIAL_M4 4

# define ORB_MUI_DIAL_X 5
# define ORB_MUI_DIAL_Y 6
# define ORB_MUI_DIAL_Z 7
# define ORB_MUI_DIAL_B 8
# define ORB_MUI_LEN_DIAL 9

# define ORB_MUI_SLD_THROTTLE 0

# define T_ORBIT_MAX_MAN 5
# define T_ORBIT_MAX_ALL 7

# define ORB_MSA_MAX_Y 374
# define ORB_MSA_Y 349

# define ORB_MS0_MAX_X 149
# define ORB_MS1_MAX_X 202
# define ORB_MS2_MAX_X 255
# define ORB_MS3_MAX_X 309
# define ORB_MS4_MAX_X 362

# define ORB_MS0_X 124
# define ORB_MS1_X 177
# define ORB_MS2_X 231
# define ORB_MS3_X 284
# define ORB_MS4_X 337

# define ORB_APL_MAX_Y 331
# define ORB_APL_MAX_X 50
# define ORB_APL_Y 306
# define ORB_APL_X 23

# define ORB_DMA_MAX_Y 350
# define ORB_DMA_Y 325

# define ORB_DMS0_MAX_X 152
# define ORB_DMS0_X 122

# define ORB_DMS1_MAX_X 204
# define ORB_DMS1_X 176

# define ORB_DMS2_MAX_X 257
# define ORB_DMS2_X 229

# define ORB_DMS3_MAX_X 311
# define ORB_DMS3_X 283

# define ORB_DMS4_MAX_X 364
# define ORB_DMS4_X 336

# define ORB_BA_Y 301

# define ORB_BX_X 285
# define ORB_BX_MAX_X 303
# define ORB_BX_MAX_Y 318

# define ORB_BY_X 305
# define ORB_BY_MAX_X 323
# define ORB_BY_MAX_Y 319

# define ORB_BZ_X 325
# define ORB_BZ_MAX_X 343
# define ORB_BZ_MAX_Y 318

# define ORB_BB_X 344
# define ORB_BB_MAX_X 362
# define ORB_BB_MAX_Y 318

# define ORB_THRTL_MAX_X 100
# define ORB_THRTL_MAX_Y 376
# define ORB_THRTL_X 61
# define ORB_THRTL_Y 298

void	mui_orbit_setup(t_app *app, t_mui_ctx **mui);
void	orbit_mui_control_action(t_mui_ctx *ctx);
#endif
