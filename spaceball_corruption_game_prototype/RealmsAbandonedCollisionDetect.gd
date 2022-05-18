#Copyright 2020-2021 Cristian Achim
#All rights reserved

extends Node2D


#const collision_detect_debug_color: Color = Color(
#	0.964844, 0.094223, 0.298275, 1.0)

##TODO code for actual detection
#var collision_detect_N_N_point_nw: Vector2
#var collision_detect_N_N_point_sw: Vector2
#var collision_detect_N_N_point_se: Vector2
#var collision_detect_N_N_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_N_NW_point_nw: Vector2
#var collision_detect_N_NW_point_sw: Vector2
#var collision_detect_N_NW_point_se: Vector2
#var collision_detect_N_NW_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_N_W_point_nw: Vector2
#var collision_detect_N_W_point_sw: Vector2
#var collision_detect_N_W_point_se: Vector2
#var collision_detect_N_W_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_N_SW_point_nw: Vector2
#var collision_detect_N_SW_point_sw: Vector2
#var collision_detect_N_SW_point_se: Vector2
#var collision_detect_N_SW_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_N_S_point_nw: Vector2
#var collision_detect_N_S_point_sw: Vector2
#var collision_detect_N_S_point_se: Vector2
#var collision_detect_N_S_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_N_SE_point_nw: Vector2
#var collision_detect_N_SE_point_sw: Vector2
#var collision_detect_N_SE_point_se: Vector2
#var collision_detect_N_SE_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_N_E_point_nw: Vector2
#var collision_detect_N_E_point_sw: Vector2
#var collision_detect_N_E_point_se: Vector2
#var collision_detect_N_E_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_N_NE_point_nw: Vector2
#var collision_detect_N_NE_point_sw: Vector2
#var collision_detect_N_NE_point_se: Vector2
#var collision_detect_N_NE_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_W_N_point_nw: Vector2
#var collision_detect_W_N_point_sw: Vector2
#var collision_detect_W_N_point_se: Vector2
#var collision_detect_W_N_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_W_NW_point_nw: Vector2
#var collision_detect_W_NW_point_sw: Vector2
#var collision_detect_W_NW_point_se: Vector2
#var collision_detect_W_NW_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_W_W_point_nw: Vector2
#var collision_detect_W_W_point_sw: Vector2
#var collision_detect_W_W_point_se: Vector2
#var collision_detect_W_W_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_W_SW_point_nw: Vector2
#var collision_detect_W_SW_point_sw: Vector2
#var collision_detect_W_SW_point_se: Vector2
#var collision_detect_W_SW_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_W_S_point_nw: Vector2
#var collision_detect_W_S_point_sw: Vector2
#var collision_detect_W_S_point_se: Vector2
#var collision_detect_W_S_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_W_SE_point_nw: Vector2
#var collision_detect_W_SE_point_sw: Vector2
#var collision_detect_W_SE_point_se: Vector2
#var collision_detect_W_SE_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_W_E_point_nw: Vector2
#var collision_detect_W_E_point_sw: Vector2
#var collision_detect_W_E_point_se: Vector2
#var collision_detect_W_E_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_W_NE_point_nw: Vector2
#var collision_detect_W_NE_point_sw: Vector2
#var collision_detect_W_NE_point_se: Vector2
#var collision_detect_W_NE_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_S_N_point_nw: Vector2
#var collision_detect_S_N_point_sw: Vector2
#var collision_detect_S_N_point_se: Vector2
#var collision_detect_S_N_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_S_NW_point_nw: Vector2
#var collision_detect_S_NW_point_sw: Vector2
#var collision_detect_S_NW_point_se: Vector2
#var collision_detect_S_NW_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_S_W_point_nw: Vector2
#var collision_detect_S_W_point_sw: Vector2
#var collision_detect_S_W_point_se: Vector2
#var collision_detect_S_W_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_S_SW_point_nw: Vector2
#var collision_detect_S_SW_point_sw: Vector2
#var collision_detect_S_SW_point_se: Vector2
#var collision_detect_S_SW_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_S_S_point_nw: Vector2
#var collision_detect_S_S_point_sw: Vector2
#var collision_detect_S_S_point_se: Vector2
#var collision_detect_S_S_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_S_SE_point_nw: Vector2
#var collision_detect_S_SE_point_sw: Vector2
#var collision_detect_S_SE_point_se: Vector2
#var collision_detect_S_SE_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_S_E_point_nw: Vector2
#var collision_detect_S_E_point_sw: Vector2
#var collision_detect_S_E_point_se: Vector2
#var collision_detect_S_E_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_S_NE_point_nw: Vector2
#var collision_detect_S_NE_point_sw: Vector2
#var collision_detect_S_NE_point_se: Vector2
#var collision_detect_S_NE_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_E_N_point_nw: Vector2
#var collision_detect_E_N_point_sw: Vector2
#var collision_detect_E_N_point_se: Vector2
#var collision_detect_E_N_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_E_NW_point_nw: Vector2
#var collision_detect_E_NW_point_sw: Vector2
#var collision_detect_E_NW_point_se: Vector2
#var collision_detect_E_NW_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_E_W_point_nw: Vector2
#var collision_detect_E_W_point_sw: Vector2
#var collision_detect_E_W_point_se: Vector2
#var collision_detect_E_W_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_E_SW_point_nw: Vector2
#var collision_detect_E_SW_point_sw: Vector2
#var collision_detect_E_SW_point_se: Vector2
#var collision_detect_E_SW_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_E_S_point_nw: Vector2
#var collision_detect_E_S_point_sw: Vector2
#var collision_detect_E_S_point_se: Vector2
#var collision_detect_E_S_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_E_SE_point_nw: Vector2
#var collision_detect_E_SE_point_sw: Vector2
#var collision_detect_E_SE_point_se: Vector2
#var collision_detect_E_SE_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_E_E_point_nw: Vector2
#var collision_detect_E_E_point_sw: Vector2
#var collision_detect_E_E_point_se: Vector2
#var collision_detect_E_E_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_E_NE_point_nw: Vector2
#var collision_detect_E_NE_point_sw: Vector2
#var collision_detect_E_NE_point_se: Vector2
#var collision_detect_E_NE_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_SB_N_point_nw: Vector2
#var collision_detect_SB_N_point_sw: Vector2
#var collision_detect_SB_N_point_se: Vector2
#var collision_detect_SB_N_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_SB_W_point_nw: Vector2
#var collision_detect_SB_W_point_sw: Vector2
#var collision_detect_SB_W_point_se: Vector2
#var collision_detect_SB_W_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_SB_S_point_nw: Vector2
#var collision_detect_SB_S_point_sw: Vector2
#var collision_detect_SB_S_point_se: Vector2
#var collision_detect_SB_S_point_ne: Vector2
#
##TODO code for actual detection
#var collision_detect_SB_E_point_nw: Vector2
#var collision_detect_SB_E_point_sw: Vector2
#var collision_detect_SB_E_point_se: Vector2
#var collision_detect_SB_E_point_ne: Vector2

#	#TODO code for actual detection
#	collision_detect_N_N_point_nw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 1.0)
#	collision_detect_N_N_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 2.0)
#	collision_detect_N_N_point_se= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 2.0)
#	collision_detect_N_N_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 1.0)
#
#	#TODO code for actual detection
#	collision_detect_N_NW_point_nw= Vector2(
#		game_resolution_multiplicity * 5.0,
#		game_resolution_multiplicity * 4.0)
#	collision_detect_N_NW_point_sw= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 4.0)
#	collision_detect_N_NW_point_se= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 2.0)
#	collision_detect_N_NW_point_ne= Vector2(
#		game_resolution_multiplicity * 8.0, 
#		game_resolution_multiplicity * 1.0)
#
#	#TODO code for actual detection
#	collision_detect_N_W_point_nw= Vector2(
#		game_resolution_multiplicity * 5.0,
#		game_resolution_multiplicity * 4.0)
#	collision_detect_N_W_point_sw= Vector2(
#		game_resolution_multiplicity * 5.0,
#		game_resolution_multiplicity * 6.0)
#	collision_detect_N_W_point_se= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 6.0)
#	collision_detect_N_W_point_ne= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 4.0)
#
#	#TODO code for actual detection
#	collision_detect_N_SW_point_nw= Vector2(
#		game_resolution_multiplicity * 5.0,
#		game_resolution_multiplicity * 6.0
#	)
#	collision_detect_N_SW_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 9.0
#	)
#	collision_detect_N_SW_point_se= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_N_SW_point_ne= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 6.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_N_S_point_nw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_N_S_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 9.0
#	)
#	collision_detect_N_S_point_se= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 9.0
#	)
#	collision_detect_N_S_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 8.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_N_SE_point_nw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 6.0
#	)
#	collision_detect_N_SE_point_sw= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_N_SE_point_se= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 9.0
#	)
#	collision_detect_N_SE_point_ne= Vector2(
#		game_resolution_multiplicity * 13.0,
#		game_resolution_multiplicity * 6.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_N_E_point_nw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 4.0
#	)
#	collision_detect_N_E_point_sw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 6.0
#	)
#	collision_detect_N_E_point_se= Vector2(
#		game_resolution_multiplicity * 13.0,
#		game_resolution_multiplicity * 6.0
#	)
#	collision_detect_N_E_point_ne= Vector2(
#		game_resolution_multiplicity * 13.0,
#		game_resolution_multiplicity * 4.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_N_NE_point_nw= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 2.0
#	)
#	collision_detect_N_NE_point_sw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 4.0
#	)
#	collision_detect_N_NE_point_se= Vector2(
#		game_resolution_multiplicity * 13.0,
#		game_resolution_multiplicity * 4.0
#	)
#	collision_detect_N_NE_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 1.0
#	)
#
#		#TODO code for actual detection
#	collision_detect_W_N_point_nw= Vector2(
#		game_resolution_multiplicity * 4.0,
#		game_resolution_multiplicity * 5.0)
#	collision_detect_W_N_point_sw= Vector2(
#		game_resolution_multiplicity * 4.0,
#		game_resolution_multiplicity * 6.0)
#	collision_detect_W_N_point_se= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 6.0)
#	collision_detect_W_N_point_ne= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 5.0)
#
#	#TODO code for actual detection
#	collision_detect_W_NW_point_nw= Vector2(
#		game_resolution_multiplicity * 1.0,
#		game_resolution_multiplicity * 8.0)
#	collision_detect_W_NW_point_sw= Vector2(
#		game_resolution_multiplicity * 2.0,
#		game_resolution_multiplicity * 8.0)
#	collision_detect_W_NW_point_se= Vector2(
#		game_resolution_multiplicity * 4.0,
#		game_resolution_multiplicity * 6.0)
#	collision_detect_W_NW_point_ne= Vector2(
#		game_resolution_multiplicity * 4.0, 
#		game_resolution_multiplicity * 5.0)
#
#	#TODO code for actual detection
#	collision_detect_W_W_point_nw= Vector2(
#		game_resolution_multiplicity * 1.0,
#		game_resolution_multiplicity * 8.0)
#	collision_detect_W_W_point_sw= Vector2(
#		game_resolution_multiplicity * 1.0,
#		game_resolution_multiplicity * 10.0)
#	collision_detect_W_W_point_se= Vector2(
#		game_resolution_multiplicity * 2.0,
#		game_resolution_multiplicity * 10.0)
#	collision_detect_W_W_point_ne= Vector2(
#		game_resolution_multiplicity * 2.0,
#		game_resolution_multiplicity * 8.0)
#
#	#TODO code for actual detection
#	collision_detect_W_SW_point_nw= Vector2(
#		game_resolution_multiplicity * 1.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_W_SW_point_sw= Vector2(
#		game_resolution_multiplicity * 4.0,
#		game_resolution_multiplicity * 13.0
#	)
#	collision_detect_W_SW_point_se= Vector2(
#		game_resolution_multiplicity * 4.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_W_SW_point_ne= Vector2(
#		game_resolution_multiplicity * 2.0,
#		game_resolution_multiplicity * 10.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_W_S_point_nw= Vector2(
#		game_resolution_multiplicity * 4.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_W_S_point_sw= Vector2(
#		game_resolution_multiplicity * 4.0,
#		game_resolution_multiplicity * 13.0
#	)
#	collision_detect_W_S_point_se= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 13.0
#	)
#	collision_detect_W_S_point_ne= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 12.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_W_SE_point_nw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_W_SE_point_sw= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_W_SE_point_se= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 13.0
#	)
#	collision_detect_W_SE_point_ne= Vector2(
#		game_resolution_multiplicity * 9.0,
#		game_resolution_multiplicity * 10.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_W_E_point_nw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_W_E_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_W_E_point_se= Vector2(
#		game_resolution_multiplicity * 9.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_W_E_point_ne= Vector2(
#		game_resolution_multiplicity * 9.0,
#		game_resolution_multiplicity * 8.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_W_NE_point_nw= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 6.0
#	)
#	collision_detect_W_NE_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_W_NE_point_se= Vector2(
#		game_resolution_multiplicity * 9.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_W_NE_point_ne= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 5.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_S_N_point_nw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 9.0)
#	collision_detect_S_N_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 10.0)
#	collision_detect_S_N_point_se= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 10.0)
#	collision_detect_S_N_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 9.0)
#
#	#TODO code for actual detection
#	collision_detect_S_NW_point_nw= Vector2(
#		game_resolution_multiplicity * 5.0,
#		game_resolution_multiplicity * 12.0)
#	collision_detect_S_NW_point_sw= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 12.0)
#	collision_detect_S_NW_point_se= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 10.0)
#	collision_detect_S_NW_point_ne= Vector2(
#		game_resolution_multiplicity * 8.0, 
#		game_resolution_multiplicity * 9.0)
#
#	#TODO code for actual detection
#	collision_detect_S_W_point_nw= Vector2(
#		game_resolution_multiplicity * 5.0,
#		game_resolution_multiplicity * 12.0)
#	collision_detect_S_W_point_sw= Vector2(
#		game_resolution_multiplicity * 5.0,
#		game_resolution_multiplicity * 14.0)
#	collision_detect_S_W_point_se= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 14.0)
#	collision_detect_S_W_point_ne= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 12.0)
#
#	#TODO code for actual detection
#	collision_detect_S_SW_point_nw= Vector2(
#		game_resolution_multiplicity * 5.0,
#		game_resolution_multiplicity * 14.0
#	)
#	collision_detect_S_SW_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 17.0
#	)
#	collision_detect_S_SW_point_se= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 16.0
#	)
#	collision_detect_S_SW_point_ne= Vector2(
#		game_resolution_multiplicity * 6.0,
#		game_resolution_multiplicity * 14.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_S_S_point_nw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 16.0
#	)
#	collision_detect_S_S_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 17.0
#	)
#	collision_detect_S_S_point_se= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 17.0
#	)
#	collision_detect_S_S_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 16.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_S_SE_point_nw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 14.0
#	)
#	collision_detect_S_SE_point_sw= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 16.0
#	)
#	collision_detect_S_SE_point_se= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 17.0
#	)
#	collision_detect_S_SE_point_ne= Vector2(
#		game_resolution_multiplicity * 13.0,
#		game_resolution_multiplicity * 14.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_S_E_point_nw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_S_E_point_sw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 14.0
#	)
#	collision_detect_S_E_point_se= Vector2(
#		game_resolution_multiplicity * 13.0,
#		game_resolution_multiplicity * 14.0
#	)
#	collision_detect_S_E_point_ne= Vector2(
#		game_resolution_multiplicity * 13.0,
#		game_resolution_multiplicity * 12.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_S_NE_point_nw= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_S_NE_point_sw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_S_NE_point_se= Vector2(
#		game_resolution_multiplicity * 13.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_S_NE_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 9.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_E_N_point_nw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 5.0)
#	collision_detect_E_N_point_sw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 6.0)
#	collision_detect_E_N_point_se= Vector2(
#		game_resolution_multiplicity * 14.0,
#		game_resolution_multiplicity * 6.0)
#	collision_detect_E_N_point_ne= Vector2(
#		game_resolution_multiplicity * 14.0,
#		game_resolution_multiplicity * 5.0)
#
#	#TODO code for actual detection
#	collision_detect_E_NW_point_nw= Vector2(
#		game_resolution_multiplicity * 9.0,
#		game_resolution_multiplicity * 8.0)
#	collision_detect_E_NW_point_sw= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 8.0)
#	collision_detect_E_NW_point_se= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 6.0)
#	collision_detect_E_NW_point_ne= Vector2(
#		game_resolution_multiplicity * 12.0, 
#		game_resolution_multiplicity * 5.0)
#
#	#TODO code for actual detection
#	collision_detect_E_W_point_nw= Vector2(
#		game_resolution_multiplicity * 9.0,
#		game_resolution_multiplicity * 8.0)
#	collision_detect_E_W_point_sw= Vector2(
#		game_resolution_multiplicity * 9.0,
#		game_resolution_multiplicity * 10.0)
#	collision_detect_E_W_point_se= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 10.0)
#	collision_detect_E_W_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 8.0)
#
#	#TODO code for actual detection
#	collision_detect_E_SW_point_nw= Vector2(
#		game_resolution_multiplicity * 9.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_E_SW_point_sw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 13.0
#	)
#	collision_detect_E_SW_point_se= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_E_SW_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 10.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_E_S_point_nw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_E_S_point_sw= Vector2(
#		game_resolution_multiplicity * 12.0,
#		game_resolution_multiplicity * 13.0
#	)
#	collision_detect_E_S_point_se= Vector2(
#		game_resolution_multiplicity * 14.0,
#		game_resolution_multiplicity * 13.0
#	)
#	collision_detect_E_S_point_ne= Vector2(
#		game_resolution_multiplicity * 14.0,
#		game_resolution_multiplicity * 12.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_E_SE_point_nw= Vector2(
#		game_resolution_multiplicity * 16.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_E_SE_point_sw= Vector2(
#		game_resolution_multiplicity * 14.0,
#		game_resolution_multiplicity * 12.0
#	)
#	collision_detect_E_SE_point_se= Vector2(
#		game_resolution_multiplicity * 14.0,
#		game_resolution_multiplicity * 13.0
#	)
#	collision_detect_E_SE_point_ne= Vector2(
#		game_resolution_multiplicity * 17.0,
#		game_resolution_multiplicity * 10.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_E_E_point_nw= Vector2(
#		game_resolution_multiplicity * 16.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_E_E_point_sw= Vector2(
#		game_resolution_multiplicity * 16.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_E_E_point_se= Vector2(
#		game_resolution_multiplicity * 17.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_E_E_point_ne= Vector2(
#		game_resolution_multiplicity * 17.0,
#		game_resolution_multiplicity * 8.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_E_NE_point_nw= Vector2(
#		game_resolution_multiplicity * 14.0,
#		game_resolution_multiplicity * 6.0
#	)
#	collision_detect_E_NE_point_sw= Vector2(
#		game_resolution_multiplicity * 16.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_E_NE_point_se= Vector2(
#		game_resolution_multiplicity * 17.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_E_NE_point_ne= Vector2(
#		game_resolution_multiplicity * 14.0,
#		game_resolution_multiplicity * 5.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_SB_N_point_nw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 7.0
#	)
#	collision_detect_SB_N_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_SB_N_point_se= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_SB_N_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 7.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_SB_W_point_nw= Vector2(
#		game_resolution_multiplicity * 7.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_SB_W_point_sw= Vector2(
#		game_resolution_multiplicity * 7.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_SB_W_point_se= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_SB_W_point_ne= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 8.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_SB_S_point_nw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_SB_S_point_sw= Vector2(
#		game_resolution_multiplicity * 8.0,
#		game_resolution_multiplicity * 11.0
#	)
#	collision_detect_SB_S_point_se= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 11.0
#	)
#	collision_detect_SB_S_point_ne= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 10.0
#	)
#
#	#TODO code for actual detection
#	collision_detect_SB_E_point_nw= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 8.0
#	)
#	collision_detect_SB_E_point_sw= Vector2(
#		game_resolution_multiplicity * 10.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_SB_E_point_se= Vector2(
#		game_resolution_multiplicity * 11.0,
#		game_resolution_multiplicity * 10.0
#	)
#	collision_detect_SB_E_point_ne= Vector2(
#		game_resolution_multiplicity * 11.0,
#		game_resolution_multiplicity * 8.0
#	)

# Called when the node enters the scene tree for the first time.
#func _ready():
#	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
