extends Node2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

const game_resolution_multiplicity: float = 30.0
const realm_border_color: Color = Color(
    0.12, 0.95, 0.0, 1.0)
var time: int = 0
var seconds: int = 0

var northern_realm_point_nnw: Vector2
var northern_realm_point_wnw: Vector2
var northern_realm_point_wsw: Vector2
var northern_realm_point_ssw: Vector2
var northern_realm_point_sse: Vector2
var northern_realm_point_ese: Vector2
var northern_realm_point_ene: Vector2
var northern_realm_point_nne: Vector2

var western_realm_point_nnw: Vector2
var western_realm_point_wnw: Vector2
var western_realm_point_wsw: Vector2
var western_realm_point_ssw: Vector2
var western_realm_point_sse: Vector2
var western_realm_point_ese: Vector2
var western_realm_point_ene: Vector2
var western_realm_point_nne: Vector2

var southern_realm_point_nnw: Vector2
var southern_realm_point_wnw: Vector2
var southern_realm_point_wsw: Vector2
var southern_realm_point_ssw: Vector2
var southern_realm_point_sse: Vector2
var southern_realm_point_ese: Vector2
var southern_realm_point_ene: Vector2
var southern_realm_point_nne: Vector2

var eastern_realm_point_nnw: Vector2
var eastern_realm_point_wnw: Vector2
var eastern_realm_point_wsw: Vector2
var eastern_realm_point_ssw: Vector2
var eastern_realm_point_sse: Vector2
var eastern_realm_point_ese: Vector2
var eastern_realm_point_ene: Vector2
var eastern_realm_point_nne: Vector2

func _ready():
    
#TODO use spaceball_corruption_grid_computation_aider
#to determine the points for each line to draw
    northern_realm_point_nnw = Vector2(
        game_resolution_multiplicity * 8.0,
        game_resolution_multiplicity * 2.0
       )
    northern_realm_point_wnw = Vector2(
        game_resolution_multiplicity * 6.0,
        game_resolution_multiplicity * 4.0
       )
    northern_realm_point_wsw = Vector2(
        game_resolution_multiplicity * 6.0,
        game_resolution_multiplicity * 6.0
       )
    northern_realm_point_ssw = Vector2(
        game_resolution_multiplicity * 8.0,
        game_resolution_multiplicity * 8.0
       )
    northern_realm_point_sse = Vector2(
        game_resolution_multiplicity * 10.0,
        game_resolution_multiplicity * 8.0
       )
    northern_realm_point_ese = Vector2(
        game_resolution_multiplicity * 12.0,
        game_resolution_multiplicity * 6.0
       )
    northern_realm_point_ene = Vector2(
        game_resolution_multiplicity * 12.0,
        game_resolution_multiplicity * 4.0
       )
    northern_realm_point_nne = Vector2(
        game_resolution_multiplicity * 10.0,
        game_resolution_multiplicity * 2.0
       )
    #<----> <---->
    western_realm_point_nnw = Vector2(
        game_resolution_multiplicity * 4.0,
        game_resolution_multiplicity * 6.0
       )
    western_realm_point_wnw = Vector2(
        game_resolution_multiplicity * 2.0,
        game_resolution_multiplicity * 8.0
       )
    western_realm_point_wsw = Vector2(
        game_resolution_multiplicity * 2.0,
        game_resolution_multiplicity * 10.0
       )
    western_realm_point_ssw = Vector2(
        game_resolution_multiplicity * 4.0,
        game_resolution_multiplicity * 12.0
       )
    western_realm_point_sse = Vector2(
        game_resolution_multiplicity * 6.0,
        game_resolution_multiplicity * 12.0
       )
    western_realm_point_ese = Vector2(
        game_resolution_multiplicity * 8.0,
        game_resolution_multiplicity * 10.0
       )
    western_realm_point_ene = Vector2(
        game_resolution_multiplicity * 8.0,
        game_resolution_multiplicity * 8.0
       )
    western_realm_point_nne = Vector2(
        game_resolution_multiplicity * 6.0,
        game_resolution_multiplicity * 6.0
       )
    #<----> <---->
    southern_realm_point_nnw = Vector2(
        game_resolution_multiplicity * 8.0,
        game_resolution_multiplicity * 10.0
       )
    southern_realm_point_wnw = Vector2(
        game_resolution_multiplicity * 6.0,
        game_resolution_multiplicity * 12.0
       )
    southern_realm_point_wsw = Vector2(
        game_resolution_multiplicity * 6.0,
        game_resolution_multiplicity * 14.0
       )
    southern_realm_point_ssw = Vector2(
        game_resolution_multiplicity * 8.0,
        game_resolution_multiplicity * 16.0
       )
    southern_realm_point_sse = Vector2(
        game_resolution_multiplicity * 10.0,
        game_resolution_multiplicity * 16.0
       )
    southern_realm_point_ese = Vector2(
        game_resolution_multiplicity * 12.0,
        game_resolution_multiplicity * 14.0
       )
    southern_realm_point_ene = Vector2(
        game_resolution_multiplicity * 12.0,
        game_resolution_multiplicity * 12.0
       )
    southern_realm_point_nne = Vector2(
        game_resolution_multiplicity * 10.0,
        game_resolution_multiplicity * 10.0
       )
    #<----> <---->
    eastern_realm_point_nnw = Vector2(
        game_resolution_multiplicity * 12.0,
        game_resolution_multiplicity * 6.0
       )
    eastern_realm_point_wnw = Vector2(
        game_resolution_multiplicity * 10.0,
        game_resolution_multiplicity * 8.0
       )
    eastern_realm_point_wsw = Vector2(
        game_resolution_multiplicity * 10.0,
        game_resolution_multiplicity * 10.0
       )
    eastern_realm_point_ssw = Vector2(
        game_resolution_multiplicity * 12.0,
        game_resolution_multiplicity * 12.0
       )
    eastern_realm_point_sse = Vector2(
        game_resolution_multiplicity * 14.0,
        game_resolution_multiplicity * 12.0
       )
    eastern_realm_point_ese = Vector2(
        game_resolution_multiplicity * 16.0,
        game_resolution_multiplicity * 10.0
       )
    eastern_realm_point_ene = Vector2(
        game_resolution_multiplicity * 16.0,
        game_resolution_multiplicity * 8.0
       )
    eastern_realm_point_nne = Vector2(
        game_resolution_multiplicity * 14.0,
        game_resolution_multiplicity * 6.0
       )
    
func _process(delta):
    time += delta
    seconds = time % 60
    update()
    
func _draw():
    if seconds % 2 == 0:
        draw_1()

func draw_1():
    draw_line(
        northern_realm_point_nnw,
        northern_realm_point_wnw,
        realm_border_color
       )
    draw_line(
        northern_realm_point_wnw,
        northern_realm_point_wsw,
        realm_border_color
        )
    draw_line(
        northern_realm_point_wsw,
        northern_realm_point_ssw,
        realm_border_color
        )
    draw_line(
        northern_realm_point_ssw,
        northern_realm_point_sse,
        realm_border_color
        )
    draw_line(
        northern_realm_point_sse,
        northern_realm_point_ese,
        realm_border_color
        )
    draw_line(
        northern_realm_point_ese,
        northern_realm_point_ene,
        realm_border_color
        )
    draw_line(
        northern_realm_point_ene,
        northern_realm_point_nne,
        realm_border_color
        )
    draw_line(
        northern_realm_point_nne,
        northern_realm_point_nnw,
        realm_border_color
       )
    draw_line(
        western_realm_point_nnw,
        western_realm_point_wnw,
        realm_border_color
       )
    draw_line(
        western_realm_point_wnw,
        western_realm_point_wsw,
        realm_border_color
        )
    draw_line(
        western_realm_point_wsw,
        western_realm_point_ssw,
        realm_border_color
        )
    draw_line(
        western_realm_point_ssw,
        western_realm_point_sse,
        realm_border_color
        )
    draw_line(
        western_realm_point_sse,
        western_realm_point_ese,
        realm_border_color
        )
    draw_line(
        western_realm_point_ese,
        western_realm_point_ene,
        realm_border_color
        )
    draw_line(
        western_realm_point_ene,
        western_realm_point_nne,
        realm_border_color
        )
    draw_line(
        western_realm_point_nne,
        western_realm_point_nnw,
        realm_border_color
       )
    draw_line(
        southern_realm_point_nnw,
        southern_realm_point_wnw,
        realm_border_color
       )
    draw_line(
        southern_realm_point_wnw,
        southern_realm_point_wsw,
        realm_border_color
        )
    draw_line(
        southern_realm_point_wsw,
        southern_realm_point_ssw,
        realm_border_color
        )
    draw_line(
        southern_realm_point_ssw,
        southern_realm_point_sse,
        realm_border_color
        )
    draw_line(
        southern_realm_point_sse,
        southern_realm_point_ese,
        realm_border_color
        )
    draw_line(
        southern_realm_point_ese,
        southern_realm_point_ene,
        realm_border_color
        )
    draw_line(
        southern_realm_point_ene,
        southern_realm_point_nne,
        realm_border_color
        )
    draw_line(
        southern_realm_point_nne,
        southern_realm_point_nnw,
        realm_border_color
       )
    draw_line(
        eastern_realm_point_nnw,
        eastern_realm_point_wnw,
        realm_border_color
       )
    draw_line(
        eastern_realm_point_wnw,
        eastern_realm_point_wsw,
        realm_border_color
        )
    draw_line(
        eastern_realm_point_wsw,
        eastern_realm_point_ssw,
        realm_border_color
        )
    draw_line(
        eastern_realm_point_ssw,
        eastern_realm_point_sse,
        realm_border_color
        )
    draw_line(
        eastern_realm_point_sse,
        eastern_realm_point_ese,
        realm_border_color
        )
    draw_line(
        eastern_realm_point_ese,
        eastern_realm_point_ene,
        realm_border_color
        )
    draw_line(
        eastern_realm_point_ene,
        eastern_realm_point_nne,
        realm_border_color
        )
    draw_line(
        eastern_realm_point_nne,
        eastern_realm_point_nnw,
        realm_border_color
       )
