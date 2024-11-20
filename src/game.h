#pragma once

#include <core/application.h>
#include <renderer/camera.h>
#include <renderer/render_backend.h>

#include "camera_controller.h"
#include "example.h"

class Game : public Application {
public:
	Game(const ApplicationCreateInfo& info);
	virtual ~Game() = default;

protected:
	void _on_start() override;

	void _on_update(float p_dt) override;

	void _on_destroy() override;

private:
	void _on_render();

private:
	Ref<RenderBackend> backend;

	CameraController camera_controller;
	PerspectiveCamera camera;
	Transform camera_transform;

	std::vector<Ref<Example>> examples;
	Ref<Example> active_example;
};
