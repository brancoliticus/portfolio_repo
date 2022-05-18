#Copyright 2020-2022 Cristian Achim
#All rights reserved

extends Node2D

const game_resolution_multiplicity: float = 35.0
const realm_border_color: Color = Color(
	0.12, 0.95, 0.0, 1.0
)

var draw_north_to_west_border: bool
var draw_west_to_south_border: bool
var draw_south_to_east_border: bool
var draw_east_to_north_border: bool
var draw_north_to_spaceball_border: bool
var draw_west_to_spaceball_border: bool
var draw_south_to_spaceball_border: bool
var draw_east_to_spaceball_border: bool

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

var spaceball_island_realm_point_nw: Vector2
var spaceball_island_realm_point_sw: Vector2
var spaceball_island_realm_point_se: Vector2
var spaceball_island_realm_point_ne: Vector2

var spaceball_island_collision_object: CollisionPolygon2D
var northern_realm_collision_object: CollisionObject2D
var western_realm_collision_object: CollisionObject2D
var southern_realm_collision_object: CollisionObject2D
var eastern_realm_collision_object: CollisionObject2D

var spaceball_island_poolvector2array: PoolVector2Array
var northern_realm_poolvector2array: PoolVector2Array
var western_realm_poolvector2array: PoolVector2Array
var southern_realm_poolvector2array: PoolVector2Array
var eastern_realm_poolvector2array: PoolVector2Array

# Called when the node enters the scene tree for the first time.
func _ready():
	init_border_point_coordinates()
	init_draw_bools()
	init_collision_areas()

func init_border_point_coordinates():
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
	# <----> <---->
	spaceball_island_realm_point_nw = Vector2(
		game_resolution_multiplicity * 8.0,
		game_resolution_multiplicity * 8.0
	)
	spaceball_island_realm_point_sw = Vector2(
		game_resolution_multiplicity * 8.0,
		game_resolution_multiplicity * 10.0
	)
	spaceball_island_realm_point_se = Vector2(
		game_resolution_multiplicity * 10.0,
		game_resolution_multiplicity * 10.0
	   )
	spaceball_island_realm_point_ne = Vector2(
		game_resolution_multiplicity * 10.0,
		game_resolution_multiplicity * 8.0
	   )

func init_draw_bools():
	draw_north_to_west_border = true
	draw_west_to_south_border = true
	draw_south_to_east_border = true
	draw_east_to_north_border = true
	draw_north_to_spaceball_border = true
	draw_west_to_spaceball_border = true
	draw_south_to_spaceball_border = true
	draw_east_to_spaceball_border = true

func init_collision_areas() -> void:
	init_spaceball_island_collision_area()
	init_northern_realm_collision_area()
	init_western_realm_collision_area()
	init_southern_realm_collision_area()
	init_eastern_realm_collision_area()

#TODO
func init_spaceball_island_collision_area() -> void:
	spaceball_island_collision_object=(
			CollisionPolygon2D.new()
	)
	spaceball_island_poolvector2array.append(
		spaceball_island_realm_point_nw
	)
	spaceball_island_poolvector2array.append(
		spaceball_island_realm_point_sw
	)
	spaceball_island_poolvector2array.append(
		spaceball_island_realm_point_se
	)
	spaceball_island_poolvector2array.append(
		spaceball_island_realm_point_ne
	)
	spaceball_island_collision_object.set_polygon(
		spaceball_island_poolvector2array
	)
	spaceball_island_collision_object.set_build_mode(
		CollisionPolygon2D.BUILD_SEGMENTS
	)
	spaceball_island_collision_object.one_way_collision_margin = (
		10.0
	) 
	add_child(spaceball_island_collision_object)

func init_northern_realm_collision_area() -> void:
	# northern_realm_collision_object: CollisionObject2D
	#var northern_realm_poolvector2array: PoolVector2Array
	pass

func init_western_realm_collision_area():
	#var western_realm_collision_object: CollisionObject2D
	#var western_realm_poolvector2array: PoolVector2Array
	pass

func init_southern_realm_collision_area():
	#var southern_realm_collision_object: CollisionObject2D
	#var southern_realm_poolvector2array: PoolVector2Array
	pass

func init_eastern_realm_collision_area():
	#var eastern_realm_collision_object: CollisionObject2D
	#var eastern_realm_poolvector2array: PoolVector2Array
	pass

func _process(delta):
	update()
	
#    time += delta
#
#    if seconds < time:
#        seconds += 1
#        update()
#		
#    get_parent().get_parent().get_node(
#        "CommandAndDebugUI").get_node(
#            "DebugLabel").text=str(seconds)
	
func _draw():
	draw_permanent_borders()
	draw_north_to_west_border_f()
	draw_west_to_south_border_f()
	draw_south_to_east_border_f()
	draw_east_to_north_border_f()
	draw_north_to_spaceball_border_f()
	draw_west_to_spaceball_border_f()
	draw_south_to_spaceball_border_f()
	draw_east_to_spaceball_border_f()
#    if seconds % 2 == 0:
#        draw_1()

func flip_north_to_west_border():
	draw_north_to_west_border = not draw_north_to_west_border

func draw_north_to_west_border_f():
	if draw_north_to_west_border:
		draw_line(
			northern_realm_point_wsw,
			northern_realm_point_ssw,
			realm_border_color
			)
		draw_line(
			western_realm_point_ene,
			western_realm_point_nne,
			realm_border_color
			)

func flip_west_to_south_border():
	draw_west_to_south_border = not draw_west_to_south_border

func draw_west_to_south_border_f():
	if draw_west_to_south_border:
		draw_line(
			western_realm_point_sse,
			western_realm_point_ese,
			realm_border_color
			)
		draw_line(
			southern_realm_point_nnw,
			southern_realm_point_wnw,
			realm_border_color
		)

func flip_south_to_east_border():
	draw_south_to_east_border = not draw_south_to_east_border

func draw_south_to_east_border_f():
	if draw_south_to_east_border:
		draw_line(
			southern_realm_point_ene,
			southern_realm_point_nne,
			realm_border_color
			)
		draw_line(
			eastern_realm_point_wsw,
			eastern_realm_point_ssw,
			realm_border_color
			)

func flip_east_to_north_border():
	draw_east_to_north_border = not draw_east_to_north_border

func draw_east_to_north_border_f():
	if draw_east_to_north_border:
		draw_line(
			eastern_realm_point_nnw,
			eastern_realm_point_wnw,
			realm_border_color
		)
		draw_line(
			northern_realm_point_sse,
			northern_realm_point_ese,
			realm_border_color
			)

func flip_north_to_spaceball_border():
	draw_north_to_spaceball_border = not draw_north_to_spaceball_border
	
func draw_north_to_spaceball_border_f():
	if draw_north_to_spaceball_border:
		draw_line(
			northern_realm_point_ssw,
			northern_realm_point_sse,
			realm_border_color
			)
		draw_line(
			spaceball_island_realm_point_ne,
			spaceball_island_realm_point_nw,
			realm_border_color
		)

func flip_west_to_spaceball_border():
	draw_west_to_spaceball_border = not draw_west_to_spaceball_border

func draw_west_to_spaceball_border_f():
	if draw_west_to_spaceball_border:
		draw_line(
			western_realm_point_ese,
			western_realm_point_ene,
			realm_border_color
			)
		draw_line(
			spaceball_island_realm_point_nw,
			spaceball_island_realm_point_sw,
			realm_border_color
		)

func flip_south_to_spaceball_border():
	draw_south_to_spaceball_border = not draw_south_to_spaceball_border

func draw_south_to_spaceball_border_f():
	if draw_south_to_spaceball_border:
		draw_line(
			southern_realm_point_nne,
			southern_realm_point_nnw,
			realm_border_color
		)
		draw_line(
			spaceball_island_realm_point_sw,
			spaceball_island_realm_point_se,
			realm_border_color
			)

func flip_east_to_spaceball_border():
	draw_east_to_spaceball_border = not draw_east_to_spaceball_border

func draw_east_to_spaceball_border_f():
	if draw_east_to_spaceball_border:
		draw_line(
			eastern_realm_point_wnw,
			eastern_realm_point_wsw,
			realm_border_color
			)
		draw_line(
			spaceball_island_realm_point_se,
			spaceball_island_realm_point_ne,
			realm_border_color
			)

func draw_permanent_borders():
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
		western_realm_point_nne,
		western_realm_point_nnw,
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
	
