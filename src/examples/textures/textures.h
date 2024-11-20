#pragma once

#include "example.h"

#include <core/transform.h>
#include <renderer/render_backend.h>
#include <renderer/types.h>

class ExampleTextures : public Example {
public:
	void on_init() override;
	void on_render(CommandBuffer p_cmd, const SceneData& p_scene_data) override;
	void on_destroy() override;

	void on_imgui() override;

private:
	Ref<RenderBackend> backend;

	Pipeline pipeline;
	Shader shader;

	Buffer vertex_buffer;
	Buffer index_buffer;

	UniformSet uniform_set;

	Image texture;
	Sampler sampler;
};
