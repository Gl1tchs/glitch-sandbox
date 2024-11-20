#include "game.h"

#include <core/event/input.h>
#include <renderer/renderer.h>

#include "scene_data.h"

#include "examples/hello_triangle/hello_triangle.h"

Game::Game(const ApplicationCreateInfo& p_info) : Application(p_info) {}

void Game::_on_start() {
	backend = Renderer::get_backend();

	camera_controller.set_camera(&camera, &camera_transform);

	examples.push_back(create_ref<ExampleHelloTriangle>());
	active_example = examples.front();

	if (active_example) {
		active_example->on_init();
	}
}

void Game::_on_update(float p_dt) {
	for (int i = 1; i <= 9; i++) {
		if (Input::is_key_pressed(static_cast<KeyCode>(KEY_CODE_1 + (i - 1))) &&
				examples.size() > i) {
			{
				backend->device_wait();
				active_example->on_destroy();
			}
			active_example = examples[i - 1];
			active_example->on_init();
			break;
		}
	}

	camera.aspect_ratio = get_window()->get_aspect_ratio();

	static bool mouse_disabled = false;
	if (Input::is_mouse_pressed(MOUSE_BUTTON_RIGHT)) {
		if (!mouse_disabled) {
			get_window()->set_cursor_mode(WINDOW_CURSOR_MODE_DISABLED);
			mouse_disabled = true;
		}

		camera_controller.update(p_dt);
	} else {
		camera_controller.last_mouse_pos.x = Input::get_mouse_position().x;
		camera_controller.last_mouse_pos.y = Input::get_mouse_position().y;
	}

	if (Input::is_mouse_released(MOUSE_BUTTON_RIGHT)) {
		if (mouse_disabled) {
			get_window()->set_cursor_mode(WINDOW_CURSOR_MODE_NORMAL);
			mouse_disabled = false;
		}
	}

	_on_render();
}

void Game::_on_destroy() {
	backend->device_wait();
	active_example->on_destroy();
}

void Game::_on_render() {
	Ref<Renderer> renderer = get_renderer();

	CommandBuffer cmd = renderer->begin_render();

	backend->command_begin_rendering(
			cmd, renderer->get_draw_extent(), renderer->get_draw_image());

	if (active_example) {
		SceneData scene_data = {
			.view = camera.get_view_matrix(camera_transform),
			.projection = camera.get_projection_matrix(),
			.camera_position = camera_transform.get_position(),
		};

		active_example->on_render(cmd, scene_data);
	}

	backend->command_end_rendering(cmd);

	renderer->end_render();
}