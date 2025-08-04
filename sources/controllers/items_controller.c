/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:14:37 by cberneri          #+#    #+#             */
/*   Updated: 2025/07/31 15:19:55 by cberneri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

//IS NOT USED, IGNORE THIS FILE
//items controllers has to draw the items and calculate them in amount for the UI

//- Figures out where each item/sprite should appear on screen
//- Respects distance (scaling), occlusion (walls), and transparency
//- Draws them efficiently using vertical strips and zbuffer

/*

//this has to go somewhere to count the items and their positions
if (map[y][x] == 'I') {
	g->item.sprites[g->item.count].x = x + 0.5;
	g->item.sprites[g->item.count].y = y + 0.5;
	g->item.count++;
}
*/

/*
void	render_item(t_struct *g)
{


	//delete later // item hardcogind
	g->item.count = 1;
	g->item.sprites[g->item.count].x = 22 + 0.5;
	g->item.sprites[g->item.count].y = 8 + 0.5;

	///// en of item hardcoding (DELETE LATER)

	for (int i = 0; i < g->item.count; i++)
	{
		// Sprite position relative to player
		double dx = g->item.sprites[i].x - g->player.pos.x;
		double dy = g->item.sprites[i].y - g->player.pos.y;

		// Inverse camera matrix
		double inv_det = 1.0 / (g->player.plane.x * g->player.dir.y - g->player.dir.x * g->player.plane.y);
		double transform_x = inv_det * (g->player.dir.y * dx - g->player.dir.x * dy);
		double transform_y = inv_det * (-g->player.plane.y * dx + g->player.plane.x * dy);

		if (transform_y <= 0)
			continue; // behind the player

		// Project sprite to screen
		int screen_x = (int)((WINDOW_WIDTH / 2) * (1 + transform_x / transform_y));
		int sprite_height = abs((int)(WINDOW_HEIGHT / transform_y));
		int sprite_width = sprite_height;

		int draw_start_y = -sprite_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_start_y < 0) draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + WINDOW_HEIGHT / 2;
		if (draw_end_y >= WINDOW_HEIGHT) draw_end_y = WINDOW_HEIGHT - 1;

		int draw_start_x = -sprite_width / 2 + screen_x;
		if (draw_start_x < 0) draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + screen_x;
		if (draw_end_x >= WINDOW_WIDTH) draw_end_x = WINDOW_WIDTH - 1;

		for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			if (transform_y > 0 && stripe >= 0 && stripe < WINDOW_WIDTH && transform_y < g->zbuffer[stripe])
			{
				int tex_x = (int)((stripe - draw_start_x) * g->item.texture_item->width / sprite_width);

				for (int y = draw_start_y; y < draw_end_y; y++)
				{
					int d = y * 256 - WINDOW_HEIGHT * 128 + sprite_height * 128;
					int tex_y = (d * g->item.texture_item->height) / sprite_height / 256;

					uint32_t *pixels = (uint32_t *)g->item.texture_item->pixels;
					uint32_t color = pixels[tex_y * g->item.texture_item->width + tex_x];

					// Skip transparent
					if ((color & 0xFF000000) != 0x00000000)
						mlx_put_pixel(g->main_img, stripe, y, color);
				}
			}
		}
	}
}


void	items_controller(t_struct *game_struct)
{
	(void)game_struct;
	//render_item(game_struct);
}

*/