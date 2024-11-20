#include "game.h"

#include <glitch/core/event/input.h>
#include <imgui/imgui.h>
#include <glitch/renderer/renderer.h>

#include "scene_data.h"

#include "examples/hello_triangle/hello_triangle.h"
#include "examples/spinning_cube/spinning_cube.h"
#include "examples/textures/textures.h"

Game::Game(const ApplicationCreateInfo& p_info) : Application(p_info) {}

void Game::_on_start() {
	backend = Renderer::get_backend();

	camera_controller.set_camera(&camera, &camera_transform);

	examples.push_back(create_ref<ExampleHelloTriangle>());
	examples.push_back(create_ref<ExampleSpinningCube>());
	examples.push_back(create_ref<ExampleTextures>());

	active_example = examples.front();

	if (active_example) {
		active_example->on_init();
	}
}

void Game::_on_update(float p_dt) {
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

	_on_render(p_dt);
}

void Game::_on_destroy() {
	backend->device_wait();
	active_example->on_destroy();
}

void Game::_on_render(float p_dt) {
	if (!active_example) {
		return;
	}

	Ref<Renderer> renderer = get_renderer();

	renderer->imgui_begin();
	{
		ImGui::Begin("Examples");
		for (const auto& example : examples) {
			if (ImGui::Selectable(example->get_name(),
						active_example &&
								active_example->get_name() ==
										example->get_name())) {
				// wait for gpu to finish operations
				backend->device_wait();

				// end current example and run new one
				active_example->on_destroy();
				active_example = example;
				active_example->on_init();
			}
		}
		ImGui::End();

		ImGui::Begin("Stats");
		ImGui::Text("Perf:\n\tms: %.4f\n\tfps: %.1f", p_dt, 1.0f / p_dt);
		ImGui::End();

		active_example->on_imgui();
	}
	renderer->imgui_end();

	CommandBuffer cmd = renderer->begin_render();
	{
		backend->command_begin_rendering(
				cmd, renderer->get_draw_extent(), renderer->get_draw_image());

		SceneData scene_data = {
			.view = camera.get_view_matrix(camera_transform),
			.projection = camera.get_projection_matrix(),
			.camera_position = camera_transform.get_position(),
			.delta_time = p_dt,
		};

		active_example->on_render(cmd, scene_data);
		backend->command_end_rendering(cmd);
	}
	renderer->end_render();
}
