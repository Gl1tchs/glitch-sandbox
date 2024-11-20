#pragma once

#include <renderer/types.h>

#include "scene_data.h"

class Example {
public:
	virtual void on_init() = 0;
	virtual void on_render(
			CommandBuffer p_cmd, const SceneData& p_scene_data) = 0;
	virtual void on_destroy() = 0;
};
