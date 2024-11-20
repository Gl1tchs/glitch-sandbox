#pragma once

#include "example.h"

#include <renderer/render_backend.h>

class ExampleHelloTriangle : public Example {
public:
	void on_init() override;
	void on_render(CommandBuffer p_cmd, const SceneData& p_scene_data) override;
	void on_destroy() override;

private:
	Ref<RenderBackend> backend;

	Pipeline pipeline;
	Shader shader;

	Buffer vertex_buffer;
};
