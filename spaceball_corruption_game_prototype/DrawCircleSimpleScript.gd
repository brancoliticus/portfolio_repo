#Copyright 2020-2022 Cristian Achim
#All rights reserved

extends KinematicBody2D


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

var circle_position: Vector2
var circle_radius: float
var circle_color: Color

var direction: Vector2
var speed: int

# Called when the node enters the scene tree for the first time.
func _ready():
	self.circle_position = Vector2(300.0, 300.0)
	self.circle_radius = 8.0
	self. circle_color = Color(
		0.578125,
		0.11041, 
		0.033875
	)
	
	self.direction = Vector2(
		rand_range(-1, 1),
		rand_range(-1, 1)
	)
	self.speed = 200

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	update()

func _physics_process(delta):
	var collision := move_and_collide(direction * delta * speed)
	if collision:
		print(collision)
		self.direction = direction.bounce(
			-collision.normal
		)
#		direction = collision.normal

func _draw():
	draw_circle(
		self.circle_position,
		self.circle_radius,
		self.circle_color
	)
