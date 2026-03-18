# Project overview
The goal of this project is to create a “realistic” 3D graphical
representation of the inside of a maze from a
first-person perspective using the Ray-Casting principles
replicating the style of Wolfenstein 3D game (1992).

### How to Run

To compile, `cd` into the cloned directory and:

```shell
make
```

If library needs to adjust permissions use chmod +x.

To run the program:

```shell
./cub3d <assets/maps/map0.cub>
```

### Available Maps
| Map Name         |   
|------------------|
| map0.cub         |
| map1.cub         |
| map8.cub         |
| validmap.cub     |
| validmap6.cub    |
| validmap7.cub    |
--------------------


The program takes a map file as an argument. Maps are available in the `maps` directory. There is a valid map which the program should run smoothly with, and invalid maps which the program should reject.
For example:

./cub3d <assets/maps/map0.cub> should run.

./cub3d <assets/maps/map3.cub> should print an error and abort.


### Controls
| Key             | Action          |   
|-----------------|-----------------|
|        W        | move forward    |
|        S        | move back       |
|        A        | move left       |
|        D        | move right      |
|   left arrow    | rotate left     |
|   right arrow   | rotate right    |
|       esc       | Quit game       |
-------------------------------------------------



 
### Resources

Minilibx/MLX:
- https://gontjarow.github.io/MiniLibX/;
- https://harm-smits.github.io/42docs/libs/minilibx;
- https://github.com/keuhdall/images_example - MLX images;
- https://pulgamecanica.herokuapp.com/posts/mlx42-intro;

Raycasting:
- https://lodev.org/cgtutor/raycasting.html;
- https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/;
- http://gamecodeschool.com/essentials/calculating-heading-in-2d-games-using-trigonometric-functions-part-1/;

Cub3d:
- https://hackmd.io/@nszl/H1LXByIE2 - tutorial;
- https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf - tutorial;
- https://www.youtube.com/watch?v=xW8skO7MFYw&list=PLIjaEJdsNvfaHNUckKiStNndJOGSZM2RI - youtube playlist;
- https://www.youtube.com/watch?v=gYRrGTC7GtA&list=PLCWsH9Tj9oWyDM4W43VMj5yo2PdyYMGst - youtube playlist;
