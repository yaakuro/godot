/*************************************************************************/
/*  rasterizer_storage_vulkan.cpp                                        */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2018 Cengiz Terzibas (Yaakuro)                     */
/* Copyright (c) 2014-2017 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "rasterizer_storage_vulkan.h"
#include "rasterizer_vulkan.h"

Image::Format VkFormatToFormat(VkFormat vkFormat) {
	switch(vkFormat) {
		case VK_FORMAT_R8_UNORM: return Image::FORMAT_R8;
		case VK_FORMAT_R8G8_UNORM: return Image::FORMAT_RG8;
		case VK_FORMAT_R8G8B8_UNORM: return Image::FORMAT_RGB8;
		case VK_FORMAT_R8G8B8A8_UNORM: return Image::FORMAT_RGBA8;
		case VK_FORMAT_R32_SFLOAT: return Image::FORMAT_RF;
		case VK_FORMAT_R32G32_SFLOAT: return Image::FORMAT_RGF;
		case VK_FORMAT_R32G32B32_SFLOAT: return Image::FORMAT_RGBF;
		case VK_FORMAT_R32G32B32A32_SFLOAT: return Image::FORMAT_RGBAF;
		case VK_FORMAT_R16_SFLOAT: return Image::FORMAT_RH; //half float
		case VK_FORMAT_R16G16_SFLOAT: return Image::FORMAT_RGH;
		// case Image::FORMAT_RGBH: return VK_FORMAT_R16G16B16_SFLOAT;
		// case Image::FORMAT_RGBAH: return VK_FORMAT_R16G16B16A16_SFLOAT;
		// case Image::FORMAT_DXT1: return VK_FORMAT_BC1_RGBA_UNORM_BLOCK; //s3tc bc1
		// case Image::FORMAT_DXT3: return VK_FORMAT_BC2_UNORM_BLOCK; //bc2
		// case Image::FORMAT_DXT5: return VK_FORMAT_BC3_UNORM_BLOCK; //bc3
		// case Image::FORMAT_PVRTC2: return VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG; //pvrtc
		// case Image::FORMAT_PVRTC4: return VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG;
		// case Image::FORMAT_ETC: return VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK; //etc1
		// case Image::FORMAT_ETC2_R11: return VK_FORMAT_EAC_R11_UNORM_BLOCK; //etc2
		// case Image::FORMAT_ETC2_R11S: return VK_FORMAT_EAC_R11_SNORM_BLOCK; //signed, NOT srgb.
		// case Image::FORMAT_ETC2_RG11: return VK_FORMAT_EAC_R11G11_UNORM_BLOCK;
		// case Image::FORMAT_ETC2_RG11S: return VK_FORMAT_EAC_R11G11_SNORM_BLOCK;
		// case Image::FORMAT_ETC2_RGB8: return VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK;
		// case Image::FORMAT_ETC2_RGBA8: return VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK;
		// case Image::FORMAT_ETC2_RGB8A1: return VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK;

		// case Image::FORMAT_L8:
		// case Image::FORMAT_LA8:
		// case Image::FORMAT_RGBA4444:
		// case Image::FORMAT_RGBA5551:
		// case Image::FORMAT_RGBE9995:
		// case Image::FORMAT_RGTC_R:
		// case Image::FORMAT_RGTC_RG:
		// case Image::FORMAT_BPTC_RGBA: //btpc bc7
		// case Image::FORMAT_BPTC_RGBF: //float bc6h
		// case Image::FORMAT_BPTC_RGBFU: //unsigned float bc6hu
		// case Image::FORMAT_PVRTC2A:
		// case Image::FORMAT_PVRTC4A:
		default: break;
	}
	return Image::FORMAT_RGBA8;
}

VkFormat FormatToVkFormat(Image::Format format) {
	switch(format) {
		case Image::FORMAT_R8: return VK_FORMAT_R8_UNORM;
		case Image::FORMAT_RG8: return VK_FORMAT_R8G8_UNORM;
		case Image::FORMAT_RGB8: return VK_FORMAT_R8G8B8A8_UNORM; // TODO We will use normal rgba.
		case Image::FORMAT_RGBA8: return VK_FORMAT_R8G8B8A8_UNORM;
		case Image::FORMAT_RF: return VK_FORMAT_R32_SFLOAT;
		case Image::FORMAT_RGF: return VK_FORMAT_R32G32_SFLOAT;
		case Image::FORMAT_RGBF: return VK_FORMAT_R32G32B32_SFLOAT;
		case Image::FORMAT_RGBAF: return VK_FORMAT_R32G32B32A32_SFLOAT;
		case Image::FORMAT_RH: return VK_FORMAT_R16_SFLOAT; //half float
		case Image::FORMAT_RGH: return VK_FORMAT_R16G16_SFLOAT;
		case Image::FORMAT_RGBH: return VK_FORMAT_R16G16B16_SFLOAT;
		case Image::FORMAT_RGBAH: return VK_FORMAT_R16G16B16A16_SFLOAT;
		case Image::FORMAT_DXT1: return VK_FORMAT_BC1_RGBA_UNORM_BLOCK; //s3tc bc1
		case Image::FORMAT_DXT3: return VK_FORMAT_BC2_UNORM_BLOCK; //bc2
		case Image::FORMAT_DXT5: return VK_FORMAT_BC3_UNORM_BLOCK; //bc3
		case Image::FORMAT_PVRTC2: return VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG; //pvrtc
		case Image::FORMAT_PVRTC4: return VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG;
		case Image::FORMAT_ETC: return VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK; //etc1
		case Image::FORMAT_ETC2_R11: return VK_FORMAT_EAC_R11_UNORM_BLOCK; //etc2
		case Image::FORMAT_ETC2_R11S: return VK_FORMAT_EAC_R11_SNORM_BLOCK; //signed, NOT srgb.
		case Image::FORMAT_ETC2_RG11: return VK_FORMAT_EAC_R11G11_UNORM_BLOCK;
		case Image::FORMAT_ETC2_RG11S: return VK_FORMAT_EAC_R11G11_SNORM_BLOCK;
		case Image::FORMAT_ETC2_RGB8: return VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK;
		case Image::FORMAT_ETC2_RGBA8: return VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK;
		case Image::FORMAT_ETC2_RGB8A1: return VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK;

		case Image::FORMAT_L8: return VK_FORMAT_R8_UNORM;
		case Image::FORMAT_LA8: return VK_FORMAT_R8G8_UNORM;
		case Image::FORMAT_RGBA4444:
		case Image::FORMAT_RGBA5551:
		case Image::FORMAT_RGBE9995:
		case Image::FORMAT_RGTC_R:
		case Image::FORMAT_RGTC_RG:
		case Image::FORMAT_BPTC_RGBA: //btpc bc7
		case Image::FORMAT_BPTC_RGBF: //float bc6h
		case Image::FORMAT_BPTC_RGBFU: //unsigned float bc6hu
		case Image::FORMAT_PVRTC2A:
		case Image::FORMAT_PVRTC4A:
		default: break;
	}
	return VK_FORMAT_UNDEFINED;
}

/* TEXTURE API */

RID RasterizerStorageVulkan::texture_create() {
	Texture *texture = memnew(Texture);
	ERR_FAIL_COND_V(!texture, RID());

	texture->vulkan_texture = NULL;
	texture->proxy = NULL;
	texture->active = false;

	return texture_owner.make_rid(texture);
}
void RasterizerStorageVulkan::texture_allocate(	RID p_texture,
																								int p_width,
																								int p_height,
																								int p_depth_3d,
																								Image::Format p_format,
																								VS::TextureType p_type,
																								uint32_t p_flags) {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND(!texture);

	if (p_flags & VS::TEXTURE_FLAG_USED_FOR_STREAMING) {
		p_flags &= ~VS::TEXTURE_FLAG_MIPMAPS; // no mipies for video
	}

	// TODO This part needs to be changed later for sure. We just assume now it is always color attachment.
	VkFormat format = FormatToVkFormat(p_format);
	switch(p_type) {
		case VS::TextureType::TEXTURE_TYPE_2D: {
			texture->vulkan_texture = new vkf::Texture2D(RasterizerVulkan::get_device(), format, p_width, p_height);
		} break;
		case VS::TextureType::TEXTURE_TYPE_2D_ARRAY: {
			texture->vulkan_texture = new vkf::TextureArray2D(RasterizerVulkan::get_device(), format, p_width, p_height, p_depth_3d);
		} break;
		case VS::TextureType::TEXTURE_TYPE_3D: {
			texture->vulkan_texture = new vkf::Texture3D(RasterizerVulkan::get_device(), format, p_width, p_height, p_depth_3d);
		} break;
		case VS::TextureType::TEXTURE_TYPE_CUBEMAP: {
			texture->vulkan_texture = new vkf::TextureCube(RasterizerVulkan::get_device(), format, p_width, p_height);
		} break;
		default: {
			ERR_FAIL_COND(!texture->vulkan_texture);
			break;
		}
	}

	VkResult result = texture->vulkan_texture->init();
	if(VK_SUCCESS != result) {
		delete texture->vulkan_texture;
		texture->vulkan_texture = NULL; 
	} else {
		texture->active = true;
		texture->flags = p_flags;
	}
	
	texture->texture_sampler = new vkf::TextureSampler(RasterizerVulkan::get_device());
	texture->texture_sampler->init();
}

void RasterizerStorageVulkan::texture_set_data(RID p_texture, const Ref<Image> &p_image, int p_level) {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND(!texture);

	ERR_FAIL_COND(!texture->active);
	ERR_FAIL_COND(p_image.is_null());

	PoolVector<uint8_t>::Read read = p_image->get_data().read();
	int size, ofs;
	int mipmaplevel = 0;
	p_image->get_mipmap_offset_and_size(mipmaplevel, ofs, size);
	texture->vulkan_texture->upload((uint8_t*)&read[0], vkf::BufferSize(size), ofs);

	// TODO This needs more work.
}

void RasterizerStorageVulkan::texture_set_data_partial(RID p_texture,
															const Ref<Image> &p_image,
															int src_x, int src_y,
															int src_w, int src_h,
															int dst_x, int dst_y,
															int p_dst_mip,
															int p_level) {}

Ref<Image> RasterizerStorageVulkan::texture_get_data(RID p_texture, int p_level) const {}

void RasterizerStorageVulkan::texture_set_flags(RID p_texture, uint32_t p_flags) {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND(!texture);

	// TODO This needs more work.
}

uint32_t RasterizerStorageVulkan::texture_get_flags(RID p_texture) const {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND_V(!texture, 0);
	return texture->flags;	
}

Image::Format RasterizerStorageVulkan::texture_get_format(RID p_texture) const {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND_V(!texture, Image::FORMAT_L8);
	return VkFormatToFormat(texture->vulkan_texture->getFormat());
}

VS::TextureType RasterizerStorageVulkan::texture_get_type(RID p_texture) const {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND_V(!texture, VS::TEXTURE_TYPE_2D);
	return texture->type;
}

uint32_t RasterizerStorageVulkan::texture_get_texid(RID p_texture) const {
	// TODO Its like me, I used something similar in my project and now difficult to get rid of.
	return 0;
}

uint32_t RasterizerStorageVulkan::texture_get_width(RID p_texture) const {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND_V(!texture, 0);
	return texture->vulkan_texture->getWidth();	
}

uint32_t RasterizerStorageVulkan::texture_get_height(RID p_texture) const {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND_V(!texture, 0);
	return texture->vulkan_texture->getHeight();	
}

uint32_t RasterizerStorageVulkan::texture_get_depth(RID p_texture) const {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND_V(!texture, 0);
	return texture->depth;
}

void RasterizerStorageVulkan::texture_set_size_override(RID p_texture, int p_width, int p_height, int p_depth_3d) {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND(!texture);
	ERR_FAIL_COND(p_width <= 0 || p_width > 16384);
	ERR_FAIL_COND(p_height <= 0 || p_height > 16384);

	texture->width = p_width;
	texture->height = p_height;	
}

void RasterizerStorageVulkan::texture_set_path(RID p_texture, const String &p_path) {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND(!texture);

	texture->path = p_path;	
}
String RasterizerStorageVulkan::texture_get_path(RID p_texture) const {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND_V(!texture, String());
	
	return texture->path;	
}

void RasterizerStorageVulkan::texture_set_shrink_all_x2_on_set_data(bool p_enable) {
	config.shrink_textures_x2 = p_enable;
}

void RasterizerStorageVulkan::texture_debug_usage(List<VS::TextureInfo> *r_info) {
	List<RID> textures;
	texture_owner.get_owned_list(&textures);

	for (List<RID>::Element *E = textures.front(); E; E = E->next()) {

		Texture *t = texture_owner.get(E->get());
		if (!t)
			continue;
		VS::TextureInfo tinfo;
		tinfo.path = t->path;
		tinfo.format = t->format;
		tinfo.bytes = t->vulkan_texture->getSize();
		r_info->push_back(tinfo);
	}	
}

RID RasterizerStorageVulkan::texture_create_radiance_cubemap(RID p_source, int p_resolution) const {
	Texture *texture = texture_owner.get(p_source);
	// TODO This needs more work.
}

void RasterizerStorageVulkan::texture_set_detect_3d_callback(RID p_texture, VisualServer::TextureDetectCallback p_callback, void *p_userdata) {

	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND(!texture);

	texture->detect_3d = p_callback;
	texture->detect_3d_ud = p_userdata;	
}
void RasterizerStorageVulkan::texture_set_detect_srgb_callback(RID p_texture, VisualServer::TextureDetectCallback p_callback, void *p_userdata) {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND(!texture);

	texture->detect_srgb = p_callback;
	texture->detect_srgb_ud = p_userdata;
}
void RasterizerStorageVulkan::texture_set_detect_normal_callback(RID p_texture, VisualServer::TextureDetectCallback p_callback, void *p_userdata) {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND(!texture);

	texture->detect_normal = p_callback;
	texture->detect_normal_ud = p_userdata;	
}

void RasterizerStorageVulkan::textures_keep_original(bool p_enable) {
	config.keep_original_textures = p_enable;
}

void RasterizerStorageVulkan::texture_set_proxy(RID p_texture, RID p_proxy) {
	Texture *texture = texture_owner.get(p_texture);
	ERR_FAIL_COND(!texture);

	if (texture->proxy) {
		texture->proxy->proxy_owners.erase(texture);
		texture->proxy = NULL;
	}

	if (p_proxy.is_valid()) {
		Texture *proxy = texture_owner.get(p_proxy);
		ERR_FAIL_COND(!proxy);
		ERR_FAIL_COND(proxy == texture);
		proxy->proxy_owners.insert(texture);
		texture->proxy = proxy;
	}
}

void RasterizerStorageVulkan::texture_set_force_redraw_if_visible(RID p_texture, bool p_enable) {
	
}

/* SKY API */

RID RasterizerStorageVulkan::sky_create() {
	Sky *sky = memnew(Sky);
	sky->radiance = 0;
	return sky_owner.make_rid(sky);	
}

void RasterizerStorageVulkan::sky_set_texture(RID p_sky, RID p_panorama, int p_radiance_size) {
	Sky *sky = sky_owner.getornull(p_sky);
	ERR_FAIL_COND(!sky);

	if (sky->panorama.is_valid()) {
		sky->panorama = RID();
		//glDeleteTextures(1, &sky->radiance);
		sky->radiance = 0;
	}

	sky->panorama = p_panorama;
	if (!sky->panorama.is_valid())
		return; //cleared

	Texture *texture = texture_owner.getornull(sky->panorama);
	if (!texture) {
		sky->panorama = RID();
		ERR_FAIL_COND(!texture);
	}

	// TODO Needs more work here.
}

/* SHADER API */

void RasterizerStorageVulkan::_shader_make_dirty(Shader *p_shader) {
	
		// if (p_shader->dirty_list.in_list())
		// 	return;
	
		// _shader_dirty_list.add(&p_shader->dirty_list);
	}

RID RasterizerStorageVulkan::shader_create() {

	Shader *shader = memnew(Shader);
	shader->mode = VS::SHADER_SPATIAL;
	shader->shader = scene->state.scene_shader;
	RID rid = shader_owner.make_rid(shader);
	_shader_make_dirty(shader);
	shader->self = rid;	
}

void RasterizerStorageVulkan::shader_set_code(RID p_shader, const String &p_code) {}
String RasterizerStorageVulkan::shader_get_code(RID p_shader) const {}
void RasterizerStorageVulkan::shader_get_param_list(RID p_shader, List<PropertyInfo> *p_param_list) const {}

void RasterizerStorageVulkan::shader_set_default_texture_param(RID p_shader, const StringName &p_name, RID p_texture) {}
RID RasterizerStorageVulkan::shader_get_default_texture_param(RID p_shader, const StringName &p_name) const {}

/* COMMON MATERIAL API */

RID RasterizerStorageVulkan::material_create() {}

void RasterizerStorageVulkan::material_set_render_priority(RID p_material, int priority) {}
void RasterizerStorageVulkan::material_set_shader(RID p_shader_material, RID p_shader) {}
RID RasterizerStorageVulkan::material_get_shader(RID p_shader_material) const {}

void RasterizerStorageVulkan::material_set_param(RID p_material, const StringName &p_param, const Variant &p_value) {}
Variant RasterizerStorageVulkan::material_get_param(RID p_material, const StringName &p_param) const {}

void RasterizerStorageVulkan::material_set_line_width(RID p_material, float p_width) {}

void RasterizerStorageVulkan::material_set_next_pass(RID p_material, RID p_next_material) {}

bool RasterizerStorageVulkan::material_is_animated(RID p_material) {}
bool RasterizerStorageVulkan::material_casts_shadows(RID p_material) {}

void RasterizerStorageVulkan::material_add_instance_owner(RID p_material, RasterizerScene::InstanceBase *p_instance) {}
void RasterizerStorageVulkan::material_remove_instance_owner(RID p_material, RasterizerScene::InstanceBase *p_instance) {}

/* MESH API */

RID RasterizerStorageVulkan::mesh_create() {}

void RasterizerStorageVulkan::mesh_add_surface(RID p_mesh, uint32_t p_format, VS::PrimitiveType p_primitive, const PoolVector<uint8_t> &p_array, int p_vertex_count, const PoolVector<uint8_t> &p_index_array, int p_index_count, const AABB &p_aabb, const Vector<PoolVector<uint8_t> > &p_blend_shapes, const Vector<AABB> &p_bone_aabbs) {}

void RasterizerStorageVulkan::mesh_set_blend_shape_count(RID p_mesh, int p_amount) {}
int RasterizerStorageVulkan::mesh_get_blend_shape_count(RID p_mesh) const {}

void RasterizerStorageVulkan::mesh_set_blend_shape_mode(RID p_mesh, VS::BlendShapeMode p_mode) {}
VS::BlendShapeMode RasterizerStorageVulkan::mesh_get_blend_shape_mode(RID p_mesh) const {}
void RasterizerStorageVulkan::mesh_surface_update_region(RID p_mesh, int p_surface, int p_offset, const PoolVector<uint8_t> &p_data) {}
void RasterizerStorageVulkan::mesh_surface_set_material(RID p_mesh, int p_surface, RID p_material) {}
RID RasterizerStorageVulkan::mesh_surface_get_material(RID p_mesh, int p_surface) const {}

int RasterizerStorageVulkan::mesh_surface_get_array_len(RID p_mesh, int p_surface) const {}
int RasterizerStorageVulkan::mesh_surface_get_array_index_len(RID p_mesh, int p_surface) const {}

PoolVector<uint8_t> RasterizerStorageVulkan::mesh_surface_get_array(RID p_mesh, int p_surface) const {}
PoolVector<uint8_t> RasterizerStorageVulkan::mesh_surface_get_index_array(RID p_mesh, int p_surface) const {}

uint32_t RasterizerStorageVulkan::mesh_surface_get_format(RID p_mesh, int p_surface) const {}
VS::PrimitiveType RasterizerStorageVulkan::mesh_surface_get_primitive_type(RID p_mesh, int p_surface) const {}

AABB RasterizerStorageVulkan::mesh_surface_get_aabb(RID p_mesh, int p_surface) const {}
Vector<PoolVector<uint8_t> > RasterizerStorageVulkan::mesh_surface_get_blend_shapes(RID p_mesh, int p_surface) const {}
Vector<AABB> RasterizerStorageVulkan::mesh_surface_get_skeleton_aabb(RID p_mesh, int p_surface) const {}

void RasterizerStorageVulkan::mesh_remove_surface(RID p_mesh, int p_index) {}
int RasterizerStorageVulkan::mesh_get_surface_count(RID p_mesh) const {}

void RasterizerStorageVulkan::mesh_set_custom_aabb(RID p_mesh, const AABB &p_aabb) {}
AABB RasterizerStorageVulkan::mesh_get_custom_aabb(RID p_mesh) const {}

AABB RasterizerStorageVulkan::mesh_get_aabb(RID p_mesh, RID p_skeleton) const {}
void RasterizerStorageVulkan::mesh_clear(RID p_mesh) {}

/* MULTIMESH API */

RID RasterizerStorageVulkan::multimesh_create() {}

void RasterizerStorageVulkan::multimesh_allocate(RID p_multimesh, int p_instances, VS::MultimeshTransformFormat p_transform_format, VS::MultimeshColorFormat p_color_format, VS::MultimeshCustomDataFormat p_data) {}
int RasterizerStorageVulkan::multimesh_get_instance_count(RID p_multimesh) const {}

void RasterizerStorageVulkan::multimesh_set_mesh(RID p_multimesh, RID p_mesh) {}
void RasterizerStorageVulkan::multimesh_instance_set_transform(RID p_multimesh, int p_index, const Transform &p_transform) {}
void RasterizerStorageVulkan::multimesh_instance_set_transform_2d(RID p_multimesh, int p_index, const Transform2D &p_transform) {}
void RasterizerStorageVulkan::multimesh_instance_set_color(RID p_multimesh, int p_index, const Color &p_color) {}
void RasterizerStorageVulkan::multimesh_instance_set_custom_data(RID p_multimesh, int p_index, const Color &p_color) {}
RID RasterizerStorageVulkan::multimesh_get_mesh(RID p_multimesh) const {}

Transform RasterizerStorageVulkan::multimesh_instance_get_transform(RID p_multimesh, int p_index) const {}
Transform2D RasterizerStorageVulkan::multimesh_instance_get_transform_2d(RID p_multimesh, int p_index) const {}
Color RasterizerStorageVulkan::multimesh_instance_get_color(RID p_multimesh, int p_index) const {}
Color RasterizerStorageVulkan::multimesh_instance_get_custom_data(RID p_multimesh, int p_index) const {}
void RasterizerStorageVulkan::multimesh_set_as_bulk_array(RID p_multimesh, const PoolVector<float> &p_array) {}
void RasterizerStorageVulkan::multimesh_set_visible_instances(RID p_multimesh, int p_visible) {}
int RasterizerStorageVulkan::multimesh_get_visible_instances(RID p_multimesh) const {}

AABB RasterizerStorageVulkan::multimesh_get_aabb(RID p_multimesh) const {}

/* IMMEDIATE API */

RID RasterizerStorageVulkan::immediate_create() {}
void RasterizerStorageVulkan::immediate_begin(RID p_immediate, VS::PrimitiveType p_rimitive, RID p_texture) {}
void RasterizerStorageVulkan::immediate_vertex(RID p_immediate, const Vector3 &p_vertex) {}
void RasterizerStorageVulkan::immediate_normal(RID p_immediate, const Vector3 &p_normal) {}
void RasterizerStorageVulkan::immediate_tangent(RID p_immediate, const Plane &p_tangent) {}
void RasterizerStorageVulkan::immediate_color(RID p_immediate, const Color &p_color) {}
void RasterizerStorageVulkan::immediate_uv(RID p_immediate, const Vector2 &tex_uv) {}
void RasterizerStorageVulkan::immediate_uv2(RID p_immediate, const Vector2 &tex_uv) {}
void RasterizerStorageVulkan::immediate_end(RID p_immediate) {}
void RasterizerStorageVulkan::immediate_clear(RID p_immediate) {}
void RasterizerStorageVulkan::immediate_set_material(RID p_immediate, RID p_material) {}
RID RasterizerStorageVulkan::immediate_get_material(RID p_immediate) const {}
AABB RasterizerStorageVulkan::immediate_get_aabb(RID p_immediate) const {}

/* SKELETON API */

RID RasterizerStorageVulkan::skeleton_create() {}
void RasterizerStorageVulkan::skeleton_allocate(RID p_skeleton, int p_bones, bool p_2d_skeleton) {}
int RasterizerStorageVulkan::skeleton_get_bone_count(RID p_skeleton) const {}
void RasterizerStorageVulkan::skeleton_bone_set_transform(RID p_skeleton, int p_bone, const Transform &p_transform) {}
void RasterizerStorageVulkan::skeleton_bone_set_transform_2d(RID p_skeleton, int p_bone, const Transform2D &p_transform) {}
Transform RasterizerStorageVulkan::skeleton_bone_get_transform(RID p_skeleton, int p_bone) const {}
Transform2D RasterizerStorageVulkan::skeleton_bone_get_transform_2d(RID p_skeleton, int p_bone) const {}
void RasterizerStorageVulkan::skeleton_set_base_transform_2d(RID p_skeleton, const Transform2D &p_base_transform) {}

/* Light API */

RID RasterizerStorageVulkan::light_create(VS::LightType p_type) {}
void RasterizerStorageVulkan::light_set_reverse_cull_face_mode(RID, bool){}
void RasterizerStorageVulkan::light_set_color(RID p_light, const Color &p_color) {}
void RasterizerStorageVulkan::light_set_param(RID p_light, VS::LightParam p_param, float p_value) {}
void RasterizerStorageVulkan::light_set_shadow(RID p_light, bool p_enabled) {}
void RasterizerStorageVulkan::light_set_shadow_color(RID p_light, const Color &p_color) {}
void RasterizerStorageVulkan::light_set_projector(RID p_light, RID p_texture) {}
void RasterizerStorageVulkan::light_set_negative(RID p_light, bool p_enable) {}
void RasterizerStorageVulkan::light_set_cull_mask(RID p_light, uint32_t p_mask) {}
void RasterizerStorageVulkan::light_omni_set_shadow_mode(RID p_light, VS::LightOmniShadowMode p_mode) {}
void RasterizerStorageVulkan::light_omni_set_shadow_detail(RID p_light, VS::LightOmniShadowDetail p_detail) {}
void RasterizerStorageVulkan::light_directional_set_shadow_mode(RID p_light, VS::LightDirectionalShadowMode p_mode) {}
void RasterizerStorageVulkan::light_directional_set_blend_splits(RID p_light, bool p_enable) {}
bool RasterizerStorageVulkan::light_directional_get_blend_splits(RID p_light) const {}
void RasterizerStorageVulkan::light_directional_set_shadow_depth_range_mode(RID p_light, VS::LightDirectionalShadowDepthRangeMode p_range_mode) {}
VS::LightDirectionalShadowDepthRangeMode RasterizerStorageVulkan::light_directional_get_shadow_depth_range_mode(RID p_light) const {}
VS::LightDirectionalShadowMode RasterizerStorageVulkan::light_directional_get_shadow_mode(RID p_light) {}
VS::LightOmniShadowMode RasterizerStorageVulkan::light_omni_get_shadow_mode(RID p_light) {}
bool RasterizerStorageVulkan::light_has_shadow(RID p_light) const {}
VS::LightType RasterizerStorageVulkan::light_get_type(RID p_light) const {}
AABB RasterizerStorageVulkan::light_get_aabb(RID p_light) const {}
float RasterizerStorageVulkan::light_get_param(RID p_light, VS::LightParam p_param) {}
Color RasterizerStorageVulkan::light_get_color(RID p_light) {}
uint64_t RasterizerStorageVulkan::light_get_version(RID p_light) const {}

/* PROBE API */

RID RasterizerStorageVulkan::reflection_probe_create() {}

void RasterizerStorageVulkan::reflection_probe_set_update_mode(RID p_probe, VS::ReflectionProbeUpdateMode p_mode) {}
void RasterizerStorageVulkan::reflection_probe_set_intensity(RID p_probe, float p_intensity) {}
void RasterizerStorageVulkan::reflection_probe_set_interior_ambient(RID p_probe, const Color &p_ambient) {}
void RasterizerStorageVulkan::reflection_probe_set_interior_ambient_energy(RID p_probe, float p_energy) {}
void RasterizerStorageVulkan::reflection_probe_set_interior_ambient_probe_contribution(RID p_probe, float p_contrib) {}
void RasterizerStorageVulkan::reflection_probe_set_max_distance(RID p_probe, float p_distance) {}
void RasterizerStorageVulkan::reflection_probe_set_extents(RID p_probe, const Vector3 &p_extents) {}
void RasterizerStorageVulkan::reflection_probe_set_origin_offset(RID p_probe, const Vector3 &p_offset) {}
void RasterizerStorageVulkan::reflection_probe_set_as_interior(RID p_probe, bool p_enable) {}
void RasterizerStorageVulkan::reflection_probe_set_enable_box_projection(RID p_probe, bool p_enable) {}
void RasterizerStorageVulkan::reflection_probe_set_enable_shadows(RID p_probe, bool p_enable) {}
void RasterizerStorageVulkan::reflection_probe_set_cull_mask(RID p_probe, uint32_t p_layers) {}

AABB RasterizerStorageVulkan::reflection_probe_get_aabb(RID p_probe) const {}
VS::ReflectionProbeUpdateMode RasterizerStorageVulkan::reflection_probe_get_update_mode(RID p_probe) const {}
uint32_t RasterizerStorageVulkan::reflection_probe_get_cull_mask(RID p_probe) const {}
Vector3 RasterizerStorageVulkan::reflection_probe_get_extents(RID p_probe) const {}
Vector3 RasterizerStorageVulkan::reflection_probe_get_origin_offset(RID p_probe) const {}
float RasterizerStorageVulkan::reflection_probe_get_origin_max_distance(RID p_probe) const {}
bool RasterizerStorageVulkan::reflection_probe_renders_shadows(RID p_probe) const {}

void RasterizerStorageVulkan::instance_add_skeleton(RID p_skeleton, RasterizerScene::InstanceBase *p_instance) {}
void RasterizerStorageVulkan::instance_remove_skeleton(RID p_skeleton, RasterizerScene::InstanceBase *p_instance) {}

void RasterizerStorageVulkan::instance_add_dependency(RID p_base, RasterizerScene::InstanceBase *p_instance) {}
void RasterizerStorageVulkan::instance_remove_dependency(RID p_base, RasterizerScene::InstanceBase *p_instance) {}

/* GI PROBE API */

RID RasterizerStorageVulkan::gi_probe_create() {}

void RasterizerStorageVulkan::gi_probe_set_bounds(RID p_probe, const AABB &p_bounds) {}
AABB RasterizerStorageVulkan::gi_probe_get_bounds(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_cell_size(RID p_probe, float p_range) {}
float RasterizerStorageVulkan::gi_probe_get_cell_size(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_to_cell_xform(RID p_probe, const Transform &p_xform) {}
Transform RasterizerStorageVulkan::gi_probe_get_to_cell_xform(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_dynamic_data(RID p_probe, const PoolVector<int> &p_data) {}
PoolVector<int> RasterizerStorageVulkan::gi_probe_get_dynamic_data(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_dynamic_range(RID p_probe, int p_range) {}
int RasterizerStorageVulkan::gi_probe_get_dynamic_range(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_energy(RID p_probe, float p_range) {}
float RasterizerStorageVulkan::gi_probe_get_energy(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_bias(RID p_probe, float p_range) {}
float RasterizerStorageVulkan::gi_probe_get_bias(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_normal_bias(RID p_probe, float p_range) {}
float RasterizerStorageVulkan::gi_probe_get_normal_bias(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_propagation(RID p_probe, float p_range) {}
float RasterizerStorageVulkan::gi_probe_get_propagation(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_interior(RID p_probe, bool p_enable) {}
bool RasterizerStorageVulkan::gi_probe_is_interior(RID p_probe) const {}

void RasterizerStorageVulkan::gi_probe_set_compress(RID p_probe, bool p_enable) {}
bool RasterizerStorageVulkan::gi_probe_is_compressed(RID p_probe) const {}

uint32_t RasterizerStorageVulkan::gi_probe_get_version(RID p_probe) {}

RasterizerStorage::GIProbeCompression RasterizerStorageVulkan::gi_probe_get_dynamic_data_get_preferred_compression() const {}
RID RasterizerStorageVulkan::gi_probe_dynamic_data_create(int p_width, int p_height, int p_depth, GIProbeCompression p_compression) {}
void RasterizerStorageVulkan::gi_probe_dynamic_data_update(RID p_gi_probe_data, int p_depth_slice, int p_slice_count, int p_mipmap, const void *p_data) {}

/* LIGHTMAP CAPTURE */
RID RasterizerStorageVulkan::lightmap_capture_create() {}
void RasterizerStorageVulkan::lightmap_capture_set_bounds(RID p_capture, const AABB &p_bounds) {}
AABB RasterizerStorageVulkan::lightmap_capture_get_bounds(RID p_capture) const {}
void RasterizerStorageVulkan::lightmap_capture_set_octree(RID p_capture, const PoolVector<uint8_t> &p_octree) {}
PoolVector<uint8_t> RasterizerStorageVulkan::lightmap_capture_get_octree(RID p_capture) const {}
void RasterizerStorageVulkan::lightmap_capture_set_octree_cell_transform(RID p_capture, const Transform &p_xform) {}
Transform RasterizerStorageVulkan::lightmap_capture_get_octree_cell_transform(RID p_capture) const {}
void RasterizerStorageVulkan::lightmap_capture_set_octree_cell_subdiv(RID p_capture, int p_subdiv) {}
int RasterizerStorageVulkan::lightmap_capture_get_octree_cell_subdiv(RID p_capture) const {}
void RasterizerStorageVulkan::lightmap_capture_set_energy(RID p_capture, float p_energy) {}
float RasterizerStorageVulkan::lightmap_capture_get_energy(RID p_capture) const {}
const PoolVector<RasterizerStorage::LightmapCaptureOctree> *RasterizerStorageVulkan::lightmap_capture_get_octree_ptr(RID p_capture) const {}

/* PARTICLES */

RID RasterizerStorageVulkan::particles_create() {}

void RasterizerStorageVulkan::particles_set_emitting(RID p_particles, bool p_emitting) {}
bool RasterizerStorageVulkan::particles_get_emitting(RID p_particles) {}
void RasterizerStorageVulkan::particles_set_amount(RID p_particles, int p_amount) {}
void RasterizerStorageVulkan::particles_set_lifetime(RID p_particles, float p_lifetime) {}
void RasterizerStorageVulkan::particles_set_one_shot(RID p_particles, bool p_one_shot) {}
void RasterizerStorageVulkan::particles_set_pre_process_time(RID p_particles, float p_time) {}
void RasterizerStorageVulkan::particles_set_explosiveness_ratio(RID p_particles, float p_ratio) {}
void RasterizerStorageVulkan::particles_set_randomness_ratio(RID p_particles, float p_ratio) {}
void RasterizerStorageVulkan::particles_set_custom_aabb(RID p_particles, const AABB &p_aabb) {}
void RasterizerStorageVulkan::particles_set_speed_scale(RID p_particles, float p_scale) {}
void RasterizerStorageVulkan::particles_set_use_local_coordinates(RID p_particles, bool p_enable) {}
void RasterizerStorageVulkan::particles_set_process_material(RID p_particles, RID p_material) {}
void RasterizerStorageVulkan::particles_set_fixed_fps(RID p_particles, int p_fps) {}
void RasterizerStorageVulkan::particles_set_fractional_delta(RID p_particles, bool p_enable) {}
void RasterizerStorageVulkan::particles_restart(RID p_particles) {}

void RasterizerStorageVulkan::particles_set_draw_order(RID p_particles, VS::ParticlesDrawOrder p_order) {}

void RasterizerStorageVulkan::particles_set_draw_passes(RID p_particles, int p_count) {}
void RasterizerStorageVulkan::particles_set_draw_pass_mesh(RID p_particles, int p_pass, RID p_mesh) {}

void RasterizerStorageVulkan::particles_request_process(RID p_particles) {}
AABB RasterizerStorageVulkan::particles_get_current_aabb(RID p_particles) {}
AABB RasterizerStorageVulkan::particles_get_aabb(RID p_particles) const {}

void RasterizerStorageVulkan::particles_set_emission_transform(RID p_particles, const Transform &p_transform) {}

int RasterizerStorageVulkan::particles_get_draw_passes(RID p_particles) const {}
RID RasterizerStorageVulkan::particles_get_draw_pass_mesh(RID p_particles, int p_pass) const {}

/* RENDER TARGET */

RID RasterizerStorageVulkan::render_target_create() {}
void RasterizerStorageVulkan::render_target_set_size(RID p_render_target, int p_width, int p_height) {}
RID RasterizerStorageVulkan::render_target_get_texture(RID p_render_target) const {}
void RasterizerStorageVulkan::render_target_set_flag(RID p_render_target, RenderTargetFlags p_flag, bool p_value) {}
bool RasterizerStorageVulkan::render_target_was_used(RID p_render_target) {}
void RasterizerStorageVulkan::render_target_clear_used(RID p_render_target) {}
void RasterizerStorageVulkan::render_target_set_msaa(RID p_render_target, VS::ViewportMSAA p_msaa) {}

/* CANVAS SHADOW */

RID RasterizerStorageVulkan::canvas_light_shadow_buffer_create(int p_width) {}

/* LIGHT SHADOW MAPPING */

RID RasterizerStorageVulkan::canvas_light_occluder_create() {}
void RasterizerStorageVulkan::canvas_light_occluder_set_polylines(RID p_occluder, const PoolVector<Vector2> &p_lines) {}

VS::InstanceType RasterizerStorageVulkan::get_base_type(RID p_rid) const {}

bool RasterizerStorageVulkan::free(RID p_rid) {
	// if (render_target_owner.owns(p_rid)) {

	// 	RenderTarget *rt = render_target_owner.getornull(p_rid);
	// 	_render_target_clear(rt);
	// 	Texture *t = texture_owner.get(rt->texture);
	// 	texture_owner.free(rt->texture);
	// 	memdelete(t);
	// 	render_target_owner.free(p_rid);
	// 	memdelete(rt);

	// } else 
	if (texture_owner.owns(p_rid)) {
		// delete the texture
	// 	Texture *texture = texture_owner.get(p_rid);
	// 	ERR_FAIL_COND_V(texture->render_target, true); //can't free the render target texture, dude
	// 	info.texture_mem -= texture->vulkan_texture->getSize();
	// 	texture_owner.free(p_rid);
	// 	memdelete(texture);
	// } else if (sky_owner.owns(p_rid)) {
	// 	// delete the sky
	// 	Sky *sky = sky_owner.get(p_rid);
	// 	sky_set_texture(p_rid, RID(), 256);
	// 	sky_owner.free(p_rid);
	// 	memdelete(sky);

	} else if (shader_owner.owns(p_rid)) {

		// delete the texture
		//Shader *shader = shader_owner.get(p_rid);

		// if (shader->shader)
		// 	shader->shader->free_custom_shader(shader->custom_code_id);

		// if (shader->dirty_list.in_list())
		// 	_shader_dirty_list.remove(&shader->dirty_list);

		// while (shader->materials.first()) {

		// 	Material *mat = shader->materials.first()->self();

		// 	mat->shader = NULL;
		// 	_material_make_dirty(mat);

		// 	shader->materials.remove(shader->materials.first());
		//}

		//material_shader.free_custom_shader(shader->custom_code_id);
		//shader_owner.free(p_rid);
		// memdelete(shader);

	} else if (material_owner.owns(p_rid)) {

		// delete the texture
		Material *material = material_owner.get(p_rid);

		if (material->shader) {
			material->shader->materials.remove(&material->list);
		}

		//remove from owners
		for (Map<Geometry *, int>::Element *E = material->geometry_owners.front(); E; E = E->next()) {

			Geometry *g = E->key();
			g->material = RID();
		}
		for (Map<RasterizerScene::InstanceBase *, int>::Element *E = material->instance_owners.front(); E; E = E->next()) {
			RasterizerScene::InstanceBase *ins = E->key();
			if (ins->material_override == p_rid) {
				ins->material_override = RID();
			}

			for (int i = 0; i < ins->materials.size(); i++) {
				if (ins->materials[i] == p_rid) {
					//ins->materials[i] = RID();
				}
			}
		}

		material_owner.free(p_rid);
		memdelete(material);

	} else if (skeleton_owner.owns(p_rid)) {

		// delete the texture
		Skeleton *skeleton = skeleton_owner.get(p_rid);
		if (skeleton->update_list.in_list()) {
			skeleton_update_list.remove(&skeleton->update_list);
		}

		for (Set<RasterizerScene::InstanceBase *>::Element *E = skeleton->instances.front(); E; E = E->next()) {
			E->get()->skeleton = RID();
		}

		skeleton_allocate(p_rid, 0, false);
		skeleton_owner.free(p_rid);
		memdelete(skeleton);

	} else if (mesh_owner.owns(p_rid)) {

		// delete the texture
		Mesh *mesh = mesh_owner.get(p_rid);
		mesh->instance_remove_deps();
		mesh_clear(p_rid);

		while (mesh->multimeshes.first()) {
			MultiMesh *multimesh = mesh->multimeshes.first()->self();
			multimesh->mesh = RID();
			multimesh->dirty_aabb = true;
			mesh->multimeshes.remove(mesh->multimeshes.first());

			if (!multimesh->update_list.in_list()) {
				multimesh_update_list.add(&multimesh->update_list);
			}
		}

		mesh_owner.free(p_rid);
		memdelete(mesh);

	} else if (multimesh_owner.owns(p_rid)) {

		// delete the texture
		MultiMesh *multimesh = multimesh_owner.get(p_rid);
		multimesh->instance_remove_deps();

		if (multimesh->mesh.is_valid()) {
			Mesh *mesh = mesh_owner.getornull(multimesh->mesh);
			if (mesh) {
				mesh->multimeshes.remove(&multimesh->mesh_list);
			}
		}

		multimesh_allocate(p_rid, 0, VS::MULTIMESH_TRANSFORM_2D, VS::MULTIMESH_COLOR_NONE); //frees multimesh
		update_dirty_multimeshes();

		multimesh_owner.free(p_rid);
		memdelete(multimesh);
	} else if (immediate_owner.owns(p_rid)) {

		Immediate *immediate = immediate_owner.get(p_rid);
		immediate->instance_remove_deps();

		immediate_owner.free(p_rid);
		memdelete(immediate);
	} else if (light_owner.owns(p_rid)) {

		// delete the texture
		Light *light = light_owner.get(p_rid);
		light->instance_remove_deps();

		light_owner.free(p_rid);
		memdelete(light);

	} else if (reflection_probe_owner.owns(p_rid)) {

		// delete the texture
		ReflectionProbe *reflection_probe = reflection_probe_owner.get(p_rid);
		reflection_probe->instance_remove_deps();

		reflection_probe_owner.free(p_rid);
		memdelete(reflection_probe);

	} else if (gi_probe_owner.owns(p_rid)) {

		// delete the texture
		GIProbe *gi_probe = gi_probe_owner.get(p_rid);

		gi_probe_owner.free(p_rid);
		memdelete(gi_probe);
	} else if (gi_probe_data_owner.owns(p_rid)) {

		// delete the texture
		GIProbeData *gi_probe_data = gi_probe_data_owner.get(p_rid);

		gi_probe_owner.free(p_rid);
		memdelete(gi_probe_data);

	} else if (canvas_occluder_owner.owns(p_rid)) {

		CanvasOccluder *co = canvas_occluder_owner.get(p_rid);
		canvas_occluder_owner.free(p_rid);
		memdelete(co);

	} else if (canvas_light_shadow_owner.owns(p_rid)) {

		CanvasLightShadow *cls = canvas_light_shadow_owner.get(p_rid);
		canvas_light_shadow_owner.free(p_rid);
		memdelete(cls);
	} else {
		return false;
	}

	return true;
}

bool RasterizerStorageVulkan::has_os_feature(const String &p_feature) const {
	if (p_feature == "s3tc")
		return config.s3tc_supported;

	if (p_feature == "etc")
		return config.etc_supported;

	if (p_feature == "etc2")
		return config.etc2_supported;

	if (p_feature == "pvrtc")
		return config.pvrtc_supported;

	return false;	
}

void RasterizerStorageVulkan::update_dirty_resources() {
	update_dirty_multimeshes();
	update_dirty_skeletons();
	update_dirty_shaders();
	update_dirty_materials();
	update_particles();	
}

void RasterizerStorageVulkan::set_debug_generate_wireframes(bool p_generate) {
	config.generate_wireframes = p_generate;
}

void RasterizerStorageVulkan::render_info_begin_capture() {
	info.snap = info.render;	
}

void RasterizerStorageVulkan::render_info_end_capture() {
	info.snap.object_count = info.render.object_count - info.snap.object_count;
	info.snap.draw_call_count = info.render.draw_call_count - info.snap.draw_call_count;
	info.snap.material_switch_count = info.render.material_switch_count - info.snap.material_switch_count;
	info.snap.surface_switch_count = info.render.surface_switch_count - info.snap.surface_switch_count;
	info.snap.shader_rebind_count = info.render.shader_rebind_count - info.snap.shader_rebind_count;
	info.snap.vertices_count = info.render.vertices_count - info.snap.vertices_count;	
}

int RasterizerStorageVulkan::get_captured_render_info(VS::RenderInfo p_info) {
	switch (p_info) {
		case VS::INFO_OBJECTS_IN_FRAME: {

			return info.snap.object_count;
		} break;
		case VS::INFO_VERTICES_IN_FRAME: {

			return info.snap.vertices_count;
		} break;
		case VS::INFO_MATERIAL_CHANGES_IN_FRAME: {
			return info.snap.material_switch_count;
		} break;
		case VS::INFO_SHADER_CHANGES_IN_FRAME: {
			return info.snap.shader_rebind_count;
		} break;
		case VS::INFO_SURFACE_CHANGES_IN_FRAME: {
			return info.snap.surface_switch_count;
		} break;
		case VS::INFO_DRAW_CALLS_IN_FRAME: {
			return info.snap.draw_call_count;
		} break;
		default: {
			return get_render_info(p_info);
		}
	}	
}

int RasterizerStorageVulkan::get_render_info(VS::RenderInfo p_info) {
	switch (p_info) {
		case VS::INFO_OBJECTS_IN_FRAME: {

			return info.render_final.object_count;
		} break;
		case VS::INFO_VERTICES_IN_FRAME: {

			return info.render_final.vertices_count;
		} break;
		case VS::INFO_MATERIAL_CHANGES_IN_FRAME: {
			return info.render_final.material_switch_count;
		} break;
		case VS::INFO_SHADER_CHANGES_IN_FRAME: {
			return info.render_final.shader_rebind_count;
		} break;
		case VS::INFO_SURFACE_CHANGES_IN_FRAME: {
			return info.render_final.surface_switch_count;
		} break;
		case VS::INFO_DRAW_CALLS_IN_FRAME: {
			return info.render_final.draw_call_count;
		} break;
		case VS::INFO_USAGE_VIDEO_MEM_TOTAL: {

			return 0; //no idea
		} break;
		case VS::INFO_VIDEO_MEM_USED: {

			return info.vertex_mem + info.texture_mem;
		} break;
		case VS::INFO_TEXTURE_MEM_USED: {

			return info.texture_mem;
		} break;
		case VS::INFO_VERTEX_MEM_USED: {

			return info.vertex_mem;
		} break;
	}	
}

RasterizerStorageVulkan::RasterizerStorageVulkan() {}

RasterizerStorageVulkan::~RasterizerStorageVulkan() {}

void RasterizerStorageVulkan::initialize() {}
void RasterizerStorageVulkan::finalize() {}

void RasterizerStorageVulkan::update_dirty_multimeshes() {

}
void RasterizerStorageVulkan::update_dirty_skeletons() {

}
void RasterizerStorageVulkan::update_dirty_shaders() {

}
void RasterizerStorageVulkan::update_dirty_materials() {

}
void RasterizerStorageVulkan::update_particles() {
	
}