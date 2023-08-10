//
// Created by xmmmmmovo on 30/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_OBJECT_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_OBJECT_HPP

namespace voxel {

template<typename T>
class OGLObject {
protected:
    T _description{};

public:
    T const &getDescription() const noexcept { return _description; }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_OBJECT_HPP
