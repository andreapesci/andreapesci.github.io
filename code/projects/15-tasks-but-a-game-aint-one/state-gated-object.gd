class_name TaskObject
extends Node2D

signal interaction_completed(object: TaskObject)

@export var active_task_state: State
@export var state_machine: StateMachine
@export var drag_threshold := 10.0

var _drag_origin := Vector2.ZERO
var _press_position := Vector2.ZERO
var _is_dragging := false
var _is_over_drop_zone := false


func _on_input_event(
	_viewport: Node,
	event: InputEvent,
	_shape_index: int,
) -> void:
	if event is not InputEventMouseButton:
		return
	if event.button_index != MOUSE_BUTTON_LEFT:
		return

	if event.pressed:
		_drag_origin = global_position
		_press_position = get_global_mouse_position()
		_is_dragging = true
		return

	var distance := _press_position.distance_to(get_global_mouse_position())
	if distance < drag_threshold:
		_handle_click()
	else:
		_finish_drag()


func _input(event: InputEvent) -> void:
	if _is_dragging and event is InputEventMouseMotion:
		global_position = get_global_mouse_position()


func _finish_drag() -> void:
	_is_dragging = false
	global_position = _drag_origin

	if _is_over_drop_zone and _is_active_task():
		interaction_completed.emit(self)


func _is_active_task() -> bool:
	return state_machine.current_state == active_task_state


func set_drop_zone_active(is_active: bool) -> void:
	_is_over_drop_zone = is_active


func _handle_click() -> void:
	_is_dragging = false
	global_position = _drag_origin
