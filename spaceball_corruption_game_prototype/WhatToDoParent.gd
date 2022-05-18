#Copyright 2020-2022 Cristian Achim
#All rights reserved

extends OptionButton


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var selected_index: int

#mouse position functionality
var mouse_pos: Vector2
var print_mouse_pos_always_enabled: bool
var print_mouse_pos: bool

#what to do parent indexes
const ACTIVATE_AND_DEACTIVATE_BORDERS_INDEX = 1
const TEST_ITEM_INDEX = 2
const MOUSE_MOVED_COORDINATES_INDEX = 3

#what to do child indexes for activate and deactivate borders
const NORTH_TO_WEST_BORDER_INDEX = 1
const WEST_TO_SOUTH_BORDER_INDEX = 2
const SOUTH_TO_EAST_BORDER_INDEX = 3
const EAST_TO_NORTH_BORDER_INDEX = 4
const NORTH_TO_SPACEBALL_BORDER_INDEX = 5
const WEST_TO_SPACEBALL_BORDER_INDEX = 6
const SOUTH_TO_SPACEBALL_BORDER_INDEX = 7
const EAST_TO_SPACEBALL_BORDER_INDEX = 8

#what to do child indexes for nothing options for testing
const NOTHING_1_INEDX = 1
const NOTHING_2_INDEX = 2

#what to do child indexes for printing mouse coordinates options
const MOUSE_COORDS_ON_PRESS_DO_IT_BUTTON = 1
const MOUSE_COORDS_ALWAYS_ENABLED = 2

# Called when the node enters the scene tree for the first time.
func _ready():
	add_item(
		"Activate and deactivate borders",
		ACTIVATE_AND_DEACTIVATE_BORDERS_INDEX
	)
	add_item(
		"Test item",
		TEST_ITEM_INDEX
	)
	add_item(
		"Mouse moved coordinates",
		MOUSE_MOVED_COORDINATES_INDEX
	)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if print_mouse_pos_always_enabled:
		print_mouse_pos_now()
	else:
		print_mouse_pos_always_enabled = false
		if print_mouse_pos:
			print_mouse_pos_now()
			print_mouse_pos = false

func print_mouse_pos_now():
	mouse_pos = get_viewport().get_mouse_position()
	debug_label_print(
		mouse_pos.x as String + " " + mouse_pos.y as String
	)

func _on_WhatToDoParent_item_selected(index):
	var the_item_id : int
	the_item_id = get_item_id(index)
	if the_item_id == ACTIVATE_AND_DEACTIVATE_BORDERS_INDEX:
		get_parent().get_node(
			"WhatToDoChild"
		).clear()
		
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"north to west border",
			NORTH_TO_WEST_BORDER_INDEX
		)
		
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"west to south border",
			WEST_TO_SOUTH_BORDER_INDEX
		)
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"south to east border",
			SOUTH_TO_EAST_BORDER_INDEX
		)
		
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"east to north border",
			EAST_TO_NORTH_BORDER_INDEX
		)
		
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"north to spaceball border",
			NORTH_TO_SPACEBALL_BORDER_INDEX
		)
		
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"west to spaceball border",
			WEST_TO_SPACEBALL_BORDER_INDEX
		)
		
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"south to spaceball border",
			SOUTH_TO_SPACEBALL_BORDER_INDEX
		)
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"east to spaceball border",
			EAST_TO_SPACEBALL_BORDER_INDEX
		)

	elif the_item_id == TEST_ITEM_INDEX:
		get_parent().get_node(
			"WhatToDoChild"
		).clear()
		
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"nothing 1",
			NOTHING_1_INEDX
		)
		
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"nothing 2",
			NOTHING_2_INDEX
		)

	elif the_item_id == MOUSE_MOVED_COORDINATES_INDEX:
		get_parent().get_node(
			"WhatToDoChild"
		).clear()
		
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"mouse coords now",
			MOUSE_MOVED_COORDINATES_INDEX
		)
		get_parent().get_node(
			"WhatToDoChild"
		).add_item(
			"mouse coordinates always",
			MOUSE_COORDS_ALWAYS_ENABLED
		)


func _on_DoItButton_button_up():
	match get_selected_id():
		ACTIVATE_AND_DEACTIVATE_BORDERS_INDEX:
			match get_parent().get_node(
					"WhatToDoChild").get_selected_id():
				NORTH_TO_WEST_BORDER_INDEX:
					debug_label_print("north to west border")
					flip_north_to_west_border()
				WEST_TO_SOUTH_BORDER_INDEX:
					debug_label_print("west to south border")
					flip_west_to_south_border()
				SOUTH_TO_EAST_BORDER_INDEX:
					debug_label_print("south to east border")
					flip_south_to_east_border()
				EAST_TO_NORTH_BORDER_INDEX:
					debug_label_print("east to north border")
					flip_east_to_north_border()
				NORTH_TO_SPACEBALL_BORDER_INDEX:
					debug_label_print("north to spaceball border")
					flip_north_to_spaceball_border()
				WEST_TO_SPACEBALL_BORDER_INDEX:
					debug_label_print("west to spaceball border")
					flip_west_to_spaceball_border()
				SOUTH_TO_SPACEBALL_BORDER_INDEX:
					debug_label_print("south to spaceball border")
					flip_south_to_spaceball_border()
				EAST_TO_SPACEBALL_BORDER_INDEX:
					debug_label_print("east to spaceball border")
					flip_east_to_spaceball_border()
		TEST_ITEM_INDEX:
			match get_parent().get_node(
					"WhatToDoChild").get_selected_id():
				NOTHING_1_INEDX:
					debug_label_print("nothing 1")
				NOTHING_2_INDEX:
					debug_label_print("nothing 2")
		MOUSE_MOVED_COORDINATES_INDEX:
			match get_parent().get_node(
					"WhatToDoChild").get_selected_id():
				MOUSE_COORDS_ALWAYS_ENABLED:
					print_mouse_pos_always_enabled =(
						not print_mouse_pos_always_enabled
					)
				MOUSE_MOVED_COORDINATES_INDEX:
					print_mouse_pos = not print_mouse_pos

func debug_label_print(text: String):
	get_parent().get_node("DebugLabel").set_text(text)        
	
func flip_north_to_west_border():
	get_parent().get_parent().get_node(
		"Realms/RealmsBorders"
	).flip_north_to_west_border()

func flip_west_to_south_border():
	get_parent().get_parent().get_node(
		"Realms/RealmsBorders"
	).flip_west_to_south_border()

func flip_south_to_east_border():
	get_parent().get_parent().get_node(
		"Realms/RealmsBorders"
	).flip_south_to_east_border()

func flip_east_to_north_border():
	get_parent().get_parent().get_node(
		"Realms/RealmsBorders"
	).flip_east_to_north_border()

func flip_north_to_spaceball_border():
	get_parent().get_parent().get_node(
		"Realms/RealmsBorders"
	).flip_north_to_spaceball_border()

func flip_west_to_spaceball_border():
	get_parent().get_parent().get_node(
		"Realms/RealmsBorders"
	).flip_west_to_spaceball_border()

func flip_south_to_spaceball_border():
	get_parent().get_parent().get_node(
		"Realms/RealmsBorders"
	).flip_south_to_spaceball_border()

func flip_east_to_spaceball_border():
	get_parent().get_parent().get_node(
		"Realms/RealmsBorders"
	).flip_east_to_spaceball_border()
