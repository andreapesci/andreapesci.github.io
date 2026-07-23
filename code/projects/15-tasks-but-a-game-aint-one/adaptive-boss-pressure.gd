class_name BossPressureController
extends Node

@export var state_machine: StateMachine
@export var computer_setup_state: State
@export_range(0.0, 1.0) var appearance_step := 0.1
@export_range(0.0, 1.0) var inspection_step := 0.1
@export var progress_check_interval := 20.0
@export var computer_setup_grace_multiplier := 3.0

var appearance_intensity := 0.5
var inspection_probability := 0.2
var _last_state: State


func evaluate_progress() -> void:
	var current_state := state_machine.current_state

	if current_state == _last_state:
		appearance_intensity = minf(appearance_intensity + appearance_step, 1.0)
		inspection_probability = minf(
			inspection_probability + inspection_step,
			1.0,
		)

	_last_state = current_state


func next_progress_check_delay() -> float:
	if state_machine.current_state == computer_setup_state:
		return progress_check_interval * computer_setup_grace_multiplier

	return progress_check_interval


func next_appearance_delay(
	slow_range: WaitTimeRange,
	fast_range: WaitTimeRange,
) -> float:
	var quietness := 1.0 - appearance_intensity
	var minimum := lerpf(fast_range.min_time, slow_range.min_time, quietness)
	var maximum := lerpf(fast_range.max_time, slow_range.max_time, quietness)
	return randf_range(minimum, maximum)


func should_inspect(
	remaining_walk_time: float,
	inspection_duration: float,
) -> bool:
	var has_time_to_inspect := remaining_walk_time > inspection_duration + 0.5
	return has_time_to_inspect and randf() < inspection_probability
